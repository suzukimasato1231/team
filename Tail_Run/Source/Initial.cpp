#include"./../Header/Initial.h"
void Initial(const int &stageNo, int *playerX, int *playerY,int *clawFlag, int *chainCount,
	int *shakeX, int *shakeY, int *stageCoin, int *coinNum, int *keyFlag, int *goalFlag,
	int *perfectFlag, int *clearFlag, int *hungryTime, bool *hungryDeathFlag,
	bool *fallDeathFlag, bool *deathFlag)
{
	if (nullptr != playerX && nullptr != playerY && nullptr != clawFlag && nullptr != chainCount &&
		nullptr != shakeX && nullptr != shakeY && nullptr != stageCoin && nullptr != coinNum &&
		nullptr != keyFlag && nullptr != goalFlag && nullptr != perfectFlag && nullptr != clearFlag &&
		nullptr != hungryTime && nullptr != hungryDeathFlag && 
		nullptr != fallDeathFlag && nullptr != deathFlag)
	{
		*deathFlag = false;
		*clawFlag = 0;
		*chainCount = 0;
		*shakeX = 0;
		*shakeY = 0;
		*coinNum = 0;
		*keyFlag = 1;
		*perfectFlag = 0;
		*clearFlag = 0;
		*hungryTime = 1630;
		*hungryDeathFlag = false;
		*fallDeathFlag = false;
		*deathFlag = false;

		switch (stageNo)
		{
		case 0://タイトル
			*playerX = 480;
			*playerY = 400;
			*stageCoin = 0;
			break;

		case 1://1ステージ
			*playerX = 480;
			*playerY = 450;
			*stageCoin = 2;
			*goalFlag = 1;
			break;
		case 2://2ステージ
			*playerX = 80;
			*playerY = 450;
			*stageCoin = 2;
			*goalFlag = 1;
			break;
		case 3://3ステージ
			*playerX = 80;
			*playerY = 80;
			*stageCoin = 4;
			*goalFlag = 1;
			break;
		case 4://4ステージ
			*playerX = 80;
			*playerY = 300;
			*stageCoin = 2;
			*goalFlag = 0;
			break;
		case 5://5ステージ
			*playerX = 928;
			*playerY = 208;
			*stageCoin = 18;
			*goalFlag = 0;
			break;
		case 6://6ステージ
			*playerX = 528;
			*playerY = 450;
			*stageCoin = 2;
			*goalFlag = 0;
			break;
		case 7://7ステージ
			*playerX = 480;
			*playerY = 80;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 8://8ステージ
			*playerX = 48;
			*playerY = 16;
			*stageCoin = 7;
			*goalFlag = 0;
			break;
		case 9://9ステージ
			*playerX = 480;
			*playerY = 240;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 10://10ステージ
			*playerX = 100;
			*playerY = 50;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 11://11ステージ
			*playerX = 100;
			*playerY = 50;
			*stageCoin = 4;
			*goalFlag = 0;
			break;
		case 12://12ステージ

			*playerX = 400;
			*playerY = 50;
			*stageCoin = 4;
			*goalFlag = 0;
			break;
		case 13://13ステージ
			*playerX = 480;
			*playerY = 50;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 14://14ステージ
			*playerX = 200;
			*playerY = 50;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 15://15ステージ
			*playerX = 50;
			*playerY = 50;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 16://16ステージ
			*playerX = 400;
			*playerY = 50;
			*stageCoin = 4;
			*goalFlag = 0;
			break;
		case 17://17ステージ
			*playerX = 650;
			*playerY = 50;
			*stageCoin = 3;
			*goalFlag = 0;
			break;
		case 18://18ステージ
			*playerX = 350;
			*playerY = 50;
			*stageCoin = 4;
			*goalFlag = 0;
			break;
		case 19://19ステージ
			*playerX = 350;
			*playerY = 50;
			*stageCoin = 4;
			*goalFlag = 0;
			break;
		case 20://ボーナスステージ
			*playerX = 100;
			*playerY = 450;
			*stageCoin = 0;
			break;
		}
	}
}