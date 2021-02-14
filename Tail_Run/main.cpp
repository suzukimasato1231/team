#include <DxLib.h>
#include "./Header/Load.h"
#include <ctype.h>
#include "./Header/Input.h"
#include "./Header/Stage.h"
#include "./Header/Scene.h"
#include "./Header/Player.h"
#include "./Header/Change.h"
#include "./Header/Wing.h"
#include "./Header/Claws.h"
#include "./Header/Food.h"
#include "./Header/Goal.h"
#include "./Header/Coin.h"
#include "./Header/Shake.h"
#include "./Header/Select.h"
#include "./Header/Scene.h"
#include "./Header/Initial.h"
#include "./Header/Draw.h"

#define blockSize 32
#define mapWidth 30 + 2
#define mapHeight 20 + 2

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Tail Run";

// ウィンドウ横幅
const int WIN_WIDTH = (mapWidth - 2) * blockSize;

// ウィンドウ縦幅
const int WIN_HEIGHT = (mapHeight - 2) * blockSize;

//アイコンの変更
int SetWindowIconID(101);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0xC0, 0xC0, 0xC0);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像の読み込み
	Graphic graph;
	LoadGraphic(graph);

	//サウンドの読み込み
	Sound sound;
	LoadSound(sound);

	//各ステージのマップチップ、最後はタイトル
	//[ステージ番号][mapHeight][mapWidth]
	int mapChip[21][mapHeight][mapWidth] = { 0 };

	int oldMapChip[mapHeight][mapWidth] = { 0 };

	//csvファイルを読み込んで、マップチップを作成
	for (int i = 0; i < 21; i++)
	{
		int fileHandle;
		char string[256];
		fileHandle = LoadCSV(i);

		for (int y = 0; y < mapHeight; y++)
		{
			FileRead_gets(string, 256, fileHandle);
			for (int x = 0, j = 0; string[j] != '\0'; j++)
			{
				if (ispunct(string[j]))
				{
					x++;
				}
				else
				{
					mapChip[i][y][x] = string[j] - '0';
				}
			}
		}
		FileRead_close(fileHandle);
	}

	//Xboxコントローラーの入力情報
	XINPUT_STATE pad;

	//キー入力とXboxコントローラーの入力の合成情報
	//0～3：上下左右, 4：アクションコマンド
	bool input[6] = { 0 };

	//1フレーム前のinputの情報
	bool oldInput[6] = { 0 };

	//
	//入力時間計測用(ちょい押しに対応させるため)
	int inputCount[6] = { 0 };
	//

	//ゲーム終了フラグ
	bool endFlag = false;

	//シーン用変数
	int scene = Title;

	//アニメーションループ用変数
	int animation = 0;
	int playerAnimation = 0, wingAnimation = 0, hungryAnimation = 0,
		coinAnimation = 0, clearAnimation = 0;

	//数字桁数上限
	const int length = 8;
	char strNum[length]{};
	int number;

	//ステージ番号
	int stageNo = Title;

	int playerX = WIN_WIDTH / 2, playerY = 400; //プレイヤーの座標
	const int playerWidth = 16, playerHeight = 14; //プレイヤーの大きさ(半分)

	//死亡フラグ
	bool deathFlag = FALSE;

	//死亡エフェクト用フラグ
	bool fallDeathFlag = FALSE, hungryDeathFlag = FALSE;

	//空腹
	int hungryTime = 200;

	int leftMapnumX = (playerX - playerWidth) / blockSize; //プレイヤーの左のマップチップの場所
	int rightMapnumX = (playerX + playerWidth) / blockSize; //プレイヤーの右のマップチップの場所
	int upMapnumY = (playerY - playerHeight) / blockSize; //プレイヤーの上のマップチップの場所
	int downMapnumY = (playerY + playerHeight) / blockSize; //プレイヤーの下のマップチップの場所

	int memoryX = playerX, memoryY = playerY; //動く前のプレイヤーの座標
	bool playerTurn = FALSE; //falseで右、trueで左を向かせる

	bool itemFlag = FALSE; //falseでかぎ爪、trueで羽が使える

	bool wingUseFlag = FALSE; //trueで羽ばたいている

	int clawX = -100, clawY = -100; //かぎ爪のヘッドの座標
	const int clawWidth = 8, clawHeight = 8; //かぎ爪の大きさ(半分)
	int chainCount = 0; //出てる鎖の数
	int clawFlag = Normal; //1で発射中、2でプレイヤーの移動、3ではね返し

	int coinNum = 0; //コイン
	int perfectFlag = 0, clearFlag = 0; //ゴールフラグ
	int keyFlag = 1;
	int goalFlag = 0; //ゴール出来るかどうか

	int stageCoin = 0; //ステージごとのコインの数を入れる

	int gameoverSelectY = 0;
	int stageSelectX = 0, stageSelectY = 0;

	int star[20] = { 0 };

	int shakeX = 0, shakeY = 0; //シェイク値
	double shakePower = 50; //シェイクの強さ
	int shakeTime = 30; //シェイク時間
	int shakeArea = 10; //シェイク範囲
	bool shakeResetFlag = FALSE; //シェイクのリセット(trueでリセット)

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//ゲームパッド入力処理
		GetJoypadXInputState(DX_INPUT_PAD1, &pad);

		//最新の入力情報だったものは1フレーム前の入力情報として保存
		for (int i = 0; i < 6; i++)
		{
			oldInput[i] = input[i];
		}

		//入力情報の結合
		Input(keys, pad, input);

		for (int i = 0; i < 4; i++)
		{
			if (input[i] == TRUE)
			{
				//入力時間計測
				inputCount[i]++;
			}
			else
			{
				//計測をリセットする
				inputCount[i] = 0;
			}
		}

		//アニメーション
		animation++;
		if (animation == 5)
		{
			animation = 0;

			coinAnimation++;
			coinAnimation %= 8;

			clearAnimation++;
			clearAnimation %= 6;

			if (hungryDeathFlag == TRUE)
			{
				if (coinAnimation % 4 == 0)
				{
					hungryAnimation++;
				}
			}

			if (input[InputAction] == TRUE)
			{
				if (coinAnimation % 2 == 0)
				{
					playerAnimation++;
				}
				playerAnimation %= 2;
			}
			else
			{
				if (input[InputLeft] == TRUE || input[InputRight] == TRUE)
				{
					playerAnimation++;
					playerAnimation %= 4;
				}
				else
				{
					if (coinAnimation % 2 == 0)
					{
						playerAnimation++;
					}
					playerAnimation %= 2;
				}
			}
		}

		//BGM再生
		if (CheckSoundMem(sound.bgm) == 0)
		{
			PlaySoundMem(sound.bgm, DX_PLAYTYPE_BACK);
		}

		// 更新処理
		switch (scene)
		{
		case Title:
			memoryX = playerX;
			memoryY = playerY;

			if (clawFlag == Normal)
			{
				Player(&playerX, &playerY, &playerTurn, input, mapChip[Title], blockSize);
				Gravity(&playerY);
				if (playerY >= WIN_HEIGHT)
				{
					playerX = WIN_WIDTH / 2;
					playerY = 400;
				}
			}

			//プレイヤーが移動した後のマップチップの場所
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//かぎ爪
			if (clawFlag == Normal)
			{
				if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
				{
					clawFlag = Launching;
					if (playerTurn == 0)
					{
						clawX = playerX;
						clawY = playerY;
					}
					else
					{
						clawX = playerX - playerWidth;
						clawY = playerY;
					}
				}

				//かぎ爪のSEの停止
				StopSoundMem(sound.shot);
			}
			else
			{
				Claws(&clawX, clawWidth, &chainCount, &playerX, playerWidth, playerTurn, clawFlag);
				switch (clawFlag)
				{
				case Launching:
					//発射中
					if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[Title]) == 1)
					{
						clawFlag = PlayerMove;
					}
					if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[Title]) == 2)
					{
						clawFlag = Cancel;
					}
					if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
					{
						clawFlag = Cancel;
					}
					break;
				case PlayerMove:
					//プレイヤーの移動中
					if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
					{
						clawFlag = Normal;
						clawX = -100;
						clawY = -100;
						chainCount = 0;
					}
					break;
				case Cancel:
					//かぎ爪のはね返し
					if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
					{
						clawFlag = Normal;
						clawX = -100;
						clawY = -100;
						chainCount = 0;
					}
					break;
				default:
					break;
				}

				//かぎ爪の効果音再生
				if (CheckSoundMem(sound.shot) == 0)
				{
					PlaySoundMem(sound.shot, DX_PLAYTYPE_BACKBIT);
				}
			}

			//プレイヤーの当たり判定・戻し処理
			PlayerCollision(&playerX, &playerY, playerWidth, playerHeight, &memoryX, &memoryY,
				&leftMapnumX, &rightMapnumX, &upMapnumY, &downMapnumY, input, mapChip[Title], blockSize);

			if (clawFlag == Normal)
			{
				if (playerX <= blockSize * 8)
				{
					endFlag = TRUE;
				}
				if (playerX >= blockSize * 22)
				{
					scene = StageSelection;

					//かぎ爪のSEの停止
					StopSoundMem(sound.shot);
				}
			}
			break;
		case StageSelection:
			Select(&stageSelectX, &stageSelectY, &scene, &stageNo, input, oldInput, inputCount, sound);
			//決定
			if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
			{
				//初期化フラグ
				Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
					&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
					&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
				AnimationInit(&animation, &playerAnimation, &wingAnimation,
					&hungryAnimation, &coinAnimation, &clearAnimation);

				if (scene != Title)
				{
					//ステージの保存
					for (int y = 0; y < mapHeight; y++)
					{
						for (int x = 0; x < mapWidth; x++)
						{
							oldMapChip[y][x] = mapChip[stageNo][y][x];
						}
					}
				}
			}
			break;
		case Main:
			memoryX = playerX;
			memoryY = playerY;

			Change(&itemFlag, stageNo);

			if (clawFlag == Normal)
			{
				if (input[InputAction] == FALSE)
				{
					Player(&playerX, &playerY, &playerTurn, input, mapChip[stageNo], blockSize);
				}
			}

			if (itemFlag == TRUE)
			{
				//羽
				if (wingUseFlag == TRUE)
				{
					Gravity(&playerY);
					if (wingAnimation <= 0)
					{
						wingUseFlag = FALSE;
					}
					wingAnimation--;
				}
				else
				{
					Gravity(&playerY);
					wingAnimation = 4;
					Wing(&playerY, &wingUseFlag, input, oldInput);
				}
			}
			else
			{
				//かぎ爪
				if (clawFlag == Normal)
				{
					Gravity(&playerY);
					if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
					{
						clawFlag = Launching;
						if (playerTurn == 0)
						{
							clawX = playerX;
							clawY = playerY;
						}
						else
						{
							clawX = playerX - playerWidth;
							clawY = playerY;
						}
					}

					//かぎ爪のSEの停止
					StopSoundMem(sound.shot);
				}
				else
				{
					Claws(&clawX, clawWidth, &chainCount, &playerX, playerWidth, playerTurn, clawFlag);
					switch (clawFlag)
					{
					case 1:
						//発射中
						if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[stageNo]) == 1)
						{
							clawFlag = PlayerMove;
						}
						if (PileHit(clawX, clawY, clawWidth, clawHeight, blockSize, mapChip[stageNo]) == 2)
						{
							clawFlag = Cancel;
						}
						if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
						{
							clawFlag = Cancel;
						}
						break;
					case 2:
						//プレイヤーの移動中
						if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
						{
							clawFlag = Normal;
							clawX = -100;
							clawY = -100;
							chainCount = 0;
						}
						break;
					case 3:
						//かぎ爪のはね返し
						if (ClawHit(clawX, clawWidth, playerX, playerWidth) == TRUE)
						{
							clawFlag = Normal;
							clawX = -100;
							clawY = -100;
							chainCount = 0;
						}
						break;
					default:
						break;
					}

					//かぎ爪の効果音再生
					if (CheckSoundMem(sound.shot) == 0)
					{
						PlaySoundMem(sound.shot, DX_PLAYTYPE_BACKBIT);
					}
				}
			}

			//プレイヤーが移動した後のマップチップの場所
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//プレイヤーの当たり判定・戻し処理
			PlayerCollision(&playerX, &playerY, playerWidth, playerHeight, &memoryX, &memoryY, &leftMapnumX, &rightMapnumX, &upMapnumY, &downMapnumY, input, mapChip[stageNo], blockSize);

			//プレイヤーが移動した後のマップチップの場所
			leftMapnumX = ((playerX - playerWidth) / blockSize) + 1;
			rightMapnumX = ((playerX + playerWidth - 1) / blockSize) + 1;
			upMapnumY = ((playerY - playerHeight) / blockSize) + 1;
			downMapnumY = ((playerY + playerHeight - 1) / blockSize) + 1;

			//コイン
			Coin(&coinNum, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, sound.coin);

			//空腹
			Food(&hungryTime, &hungryDeathFlag, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, stageNo, sound.food);

			//ゴール
			Goal(&coinNum, &clearFlag, &perfectFlag, &keyFlag, &goalFlag, stageCoin, mapChip[stageNo], leftMapnumX, rightMapnumX, upMapnumY, downMapnumY, sound);

			//空腹のエフェクト
			if (hungryAnimation >= 3)
			{
				hungryAnimation = 0;
				hungryDeathFlag = FALSE;
				scene = GameOver;

				//かぎ爪のSEの停止
				StopSoundMem(sound.shot);
			}

			//落下死のエフェクト
			if (playerY >= WIN_HEIGHT && fallDeathFlag == FALSE)
			{
				fallDeathFlag = TRUE;
				shakePower = 20;
				shakeTime = 10;
				shakeArea = 5;
			}

			if (fallDeathFlag == TRUE)
			{
				if (shakeTime >=
					Shake(&shakeX, &shakeY, &shakePower, &shakeTime, shakeArea, shakeResetFlag))
				{
					shakeResetFlag = TRUE;
				}
				else
				{
					shakeResetFlag = FALSE;
					if (shakeTime <= 0)
					{
						fallDeathFlag = FALSE;
						scene = GameOver;

						//かぎ爪のSEの停止
						StopSoundMem(sound.shot);
					}
				}
			}

			//DeathFlagの結合
			if (fallDeathFlag == TRUE || hungryDeathFlag == TRUE)
			{
				deathFlag = TRUE;
			}

			//ボーナスステージの処理
			if (stageNo == 20)
			{
				//コインの残り枚数が0ならマップリセット
				if (coinNum % 564 == 0)
				{
					for (int y = 0; y < mapHeight; y++)
					{
						for (int x = 0; x < mapWidth; x++)
						{
							mapChip[stageNo][y][x] = oldMapChip[y][x];
						}
					}
				}

				//クリアフラグ
				if (hungryTime <= 0)
				{
					perfectFlag = 1;
				}
			}

			//リトライ
			if (input[InputMenu] == 1 && oldInput[InputMenu] == 0)
			{
				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}
				Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
					&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
					&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
				AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);
			}
			
			//ゴール確認用
			if (clearFlag == 1 || perfectFlag == 1)
			{
				//strNumを'\0'で初期化
				for (int i = 0; i < length; i++)
				{
					strNum[i] = '\0';
				}

				//スコア計算
				number = coinNum * 1000;
				sprintf_s(strNum, sizeof(strNum), "%d", number);

				scene = GameClear;

				//かぎ爪のSEの停止
				StopSoundMem(sound.shot);
			}

			break;
		case GameOver:

			//上
			if (inputCount[InputUp] % 20 == 1)
			{
				gameoverSelectY -= 1;
			}
			//下
			if (inputCount[InputDown] % 20 == 1)
			{
				gameoverSelectY += 1;
			}

			//マイナスにしない
			if (gameoverSelectY < 0) {
				gameoverSelectY = 1;
			}
			if (gameoverSelectY > 1)
			{
				gameoverSelectY = 0;
			}
			//決定
			if (input[InputAction] == 1 && oldInput[InputAction] == 0)
			{
				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}

				//セレクトのSE再生
				PlaySoundMem(sound.decision, DX_PLAYTYPE_BACKBIT);

				if (gameoverSelectY == 1)
				{
					scene = Title;
					stageNo = 0;

					//初期化フラグ
					Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
						&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
						&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
					AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);
				}
				else
				{
					//初期化フラグ
					Initial(stageNo, &playerX, &playerY, &clawFlag, &chainCount, &shakeX, &shakeY,
						&stageCoin, &coinNum, &keyFlag, &goalFlag, &perfectFlag, &clearFlag,
						&hungryTime, &hungryDeathFlag, &fallDeathFlag, &deathFlag);
					AnimationInit(&animation, &playerAnimation, &wingAnimation, &hungryAnimation, &coinAnimation, &clearAnimation);

					scene = Main;
				}
			}
			break;

		case GameClear:
			if (input[InputAction] == 1 && oldInput[InputAction] == 0)
			{
				scene = StageSelection;

				if (perfectFlag == TRUE)
				{
					star[stageNo - 1] = TRUE;
				}

				for (int y = 0; y < mapHeight; y++)
				{
					for (int x = 0; x < mapWidth; x++)
					{
						mapChip[stageNo][y][x] = oldMapChip[y][x];
					}
				}
			}

			break;
		default:
			break;
		}

		if (endFlag == TRUE)
		{
			break;
		}

		// 描画処理
		switch (scene)
		{
		case Title:
			//背景の描画
			TitleDraw(graph);

			//地面の描画
			StageDraw(blockSize, mapWidth, mapHeight, mapChip[Title], graph, coinAnimation);

			//Aボタンの描画
			DrawGraph(blockSize * 14, blockSize * 16, graph.aButton, TRUE);

			//かぎ爪の描画
			if (clawFlag != Normal)
			{
				ClawDraw(clawX, clawY, clawWidth, clawHeight, graph, playerTurn, chainCount + 1);
			}

			//プレイヤーの描画
			PlayerDraw(playerX, playerY, graph, playerTurn, playerAnimation, input);

			break;
		case Main:
			//背景の描画
			BGDraw(graph, stageNo);

			//地面の描画
			StageDraw(blockSize, mapWidth, mapHeight, mapChip[stageNo], graph, coinAnimation);

			//落下死のエフェクト
			if (shakeX != 0 || shakeY != 0)
			{
				BGDraw(graph, stageNo, shakeX, shakeY);
				StageDraw(blockSize, mapWidth, mapHeight, mapChip[stageNo], graph, coinAnimation, shakeX, shakeY);
			}

			//空腹ゲージ
			HungryDraw(hungryTime, graph);

			KeyDraw(goalFlag, graph.key);

			if (itemFlag == TRUE)
			{
				//羽の描画
				WingDraw(playerX, playerY, playerWidth, playerHeight, graph, playerTurn, wingUseFlag);
			}
			else
			{
				//かぎ爪の描画
				if (clawFlag != Normal)
				{
					ClawDraw(clawX, clawY, clawWidth, clawHeight, graph, playerTurn, chainCount + 1);
				}
			}

			//プレイヤーの描画
			if (hungryDeathFlag == TRUE)
			{
				StarvationDrow(playerX, playerY, playerWidth, playerHeight, graph, playerTurn, hungryAnimation);
			}
			else
			{
				PlayerDraw(playerX, playerY, graph, playerTurn, playerAnimation, input);
			}

			break;
		case StageSelection:
			//セレクト画面
			SelectDraw(blockSize, stageSelectX, stageSelectY, star, graph);

			break;
		case GameOver:
			//ゲームオーバー画面
			GameOverDraw(blockSize, gameoverSelectY, graph);

			break;
		case GameClear:
			//ゲームクリア画面
			GameClearDraw(strNum, clearAnimation, graph);

			break;
		default:
			break;
		}

		//デバッグの描画
		//DebugDraw(blockSize, WIN_WIDTH, WIN_HEIGHT, mapWidth, mapHeight, playerX, playerY, playerWidth, playerHeight);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}