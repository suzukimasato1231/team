#pragma once

//背景の描画
void BGDraw(const struct Graphic &graphic, const int &stageNo, const int &shakeX = 0, const int &shakeY = 0);

//タイトル画面の描画
void TitleDraw(const struct Graphic &graphic);

//ステージ選択の描画
void SelectDraw(const int &blockSize, const int &stageSelectX, const int &stageSelectY, const int star[], const int starAnimation, const struct Graphic graphic);

//メニュー選択の描画
void MenuDraw(const int &menuY, const struct Graphic &graphic);

void MusicDraw(const int musicSelectY, const int SeVolume, const int BgmVolume, const struct Graphic &graphic);
//ゲームオーバーの描画
void GameOverDraw(const int &blockSize, const int &gameoverSelectY, const struct Graphic &graphic);

//クリア画面の描画
void GameClearDraw(const char strNum[], const int clearAnimation, const struct Graphic &graphic);

//ステージの描画
void StageDraw(const int &blockSize, const int &mapW, const int &mapH, const int mapChip[20 + 2][30 + 2],
	const struct Graphic &graphic, const int &animationCount, const int &shakeX = 0, const int &shakeY = 0);

//プレイヤーの描画
void PlayerDraw(const int x, const int y, const struct Graphic graphic, const bool turn, const int animationCount, const int clawFlag, const bool input[]);

//飢死の描画
void StarvationDrow(const int &x, const int &y, const struct Graphic &graphic, const bool &turn, const int &animationCount);

//羽の描画
void WingDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &turn, const bool &useFlag);

//かぎ爪の描画
void ClawDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &playerTurn, const int &count);

//空腹ゲージ
void HungryDraw(const int hungryTime, const struct Graphic &graphic);

//ゴール出来るかどうかのUI
void KeyDraw(const int goalFlag, const int GrHandle);

//デバッグ用の線
void DebugDraw(const int &blockSize, const int &winW, const int &winH, const int &mapW, const int &mapH, const int &playerX, const int &playerY, const int &playerW, const int &playerH);