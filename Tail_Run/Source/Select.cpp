#include <DxLib.h>
#include "./../Header/Select.h"
#include "../Header/Input.h"
#include "./../Header/scene.h"
#include "./../Header/Load.h"

void Select(int *stageSelectX, int *stageSelectY, int *scene, int *stageNo, bool input[], bool oldInput[], int inputCount[], Sound sound)
{
	if (nullptr == stageSelectY || nullptr == stageSelectX || nullptr == scene || nullptr == stageNo)
	{
		return;
	}

	bool move = FALSE;

	//上
	if (inputCount[InputUp] % 10 == 1)
	{
		move = TRUE;
		*stageSelectY -= 1;
	}
	//下
	if (inputCount[InputDown] % 10 == 1)
	{
		move = TRUE;
		*stageSelectY += 1;
	}
	//左
	if (inputCount[InputLeft] % 10 == 1)
	{
		move = TRUE;
		*stageSelectX -= 1;
	}
	//右
	if (inputCount[InputRight] % 10 == 1)
	{
		move = TRUE;
		*stageSelectX += 1;
	}

	if (move == TRUE)
	{
		//セレクトのSE再生
		PlaySoundMem(sound.select, DX_PLAYTYPE_BACKBIT);
	}

	//決定
	if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
	{
		//決定のSE再生
		PlaySoundMem(sound.decision, DX_PLAYTYPE_BACKBIT);

		switch (*stageSelectY * 7 + *stageSelectX)
		{

		case 0://1ステージ目
			*stageNo = 1;
			*scene = Main;
			break;

		case 1://2ステージ目
			*stageNo = 2;
			*scene = Main;
			break;

		case 2://3ステージ目
			*stageNo = 3;
			*scene = Main;
			break;

		case 3://4ステージ目
			*stageNo = 4;
			*scene = Main;
			break;

		case 4://5ステージ目
			*stageNo = 5;
			*scene = Main;
			break;

		case 5://6ステージ目
			*stageNo = 6;
			*scene = Main;
			break;

		case 6://7ステージ目
			*stageNo = 7;
			*scene = Main;
			break;

		case 7://8ステージ目
			*stageNo = 8;
			*scene = Main;
			break;

		case 8://9ステージ目
			*stageNo = 9;
			*scene = Main;
			break;

		case 9://10ステージ目
			*stageNo = 10;
			*scene = Main;
			break;

		case 10://タイトル
			*stageNo = Title;
			*scene = Title;
			break;

		case 11://11ステージ目
			*stageNo = 11;
			*scene = Main;
			break;

		case 12://12ステージ目
			*stageNo = 12;
			*scene = Main;
			break;

		case 13://13ステージ目
			*stageNo = 13;
			*scene = Main;
			break;

		case 14://14ステージ目
			*stageNo = 14;
			*scene = Main;
			break;

		case 15://15ステージ目
			*stageNo = 15;
			*scene = Main;
			break;

		case 16://16ステージ目
			*stageNo = 16;
			*scene = Main;
			break;

		case 17://17ステージ目
			*stageNo = 17;
			*scene = Main;
			break;

		case 18://18ステージ目
			*stageNo = 18;
			*scene = Main;
			break;

		case 19://19ステージ目
			*stageNo = 19;
			*scene = Main;
			break;

		case 20://20ステージ目
			*stageNo = 20;
			*scene = Main;
			break;
		}

	}

	if (*stageSelectX > 6)
	{
		*stageSelectX = 0;
	}
	//マイナスにしない
	if (*stageSelectX < 0) {
		*stageSelectX = 6;
	}
	if (*stageSelectY > 2)
	{
		*stageSelectY = 0;
	}
	//マイナスにしない
	if (*stageSelectY < 0) {
		*stageSelectY = 2;
	}
}