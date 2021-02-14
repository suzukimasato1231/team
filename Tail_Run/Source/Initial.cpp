#include"./../Header/Initial.h"
#include "./../Header/Claws.h"

void Initial(const int &stageNo, int *playerX, int *playerY, int *clawFlag, int *chainCount,
	int *shakeX, int *shakeY, int *stageCoin, int *coinNum, int *keyFlag, int *goalFlag,
	int *perfectFlag, int *clearFlag, int *hungryTime, bool *hungryDeathFlag,
	bool *fallDeathFlag, bool *deathFlag)
{
	if (nullptr == playerX || nullptr == playerY || nullptr == clawFlag || nullptr == chainCount ||
		nullptr == shakeX || nullptr == shakeY || nullptr == stageCoin || nullptr == coinNum ||
		nullptr == keyFlag || nullptr == goalFlag || nullptr == perfectFlag || nullptr == clearFlag ||
		nullptr == hungryTime || nullptr == hungryDeathFlag ||
		nullptr == fallDeathFlag || nullptr == deathFlag)
	{
		return;
	}

	*clawFlag = Normal;
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
	case 0://�^�C�g��
		*playerX = 480;
		*playerY = 400;
		*stageCoin = 0;
		break;

	case 1://1�X�e�[�W
		*playerX = 480;
		*playerY = 450;
		*stageCoin = 2;
		*goalFlag = 1;
		break;
	case 2://2�X�e�[�W
		*playerX = 80;
		*playerY = 450;
		*stageCoin = 2;
		*goalFlag = 1;
		break;
	case 3://3�X�e�[�W
		*playerX = 80;
		*playerY = 80;
		*stageCoin = 4;
		*goalFlag = 1;
		break;
	case 4://4�X�e�[�W
		*playerX = 80;
		*playerY = 300;
		*stageCoin = 2;
		*goalFlag = 0;
		break;
	case 5://5�X�e�[�W
		*playerX = 928;
		*playerY = 208;
		*stageCoin = 18;
		*goalFlag = 0;
		break;
	case 6://6�X�e�[�W
		*playerX = 528;
		*playerY = 450;
		*stageCoin = 2;
		*goalFlag = 0;
		break;
	case 7://7�X�e�[�W
		*playerX = 480;
		*playerY = 80;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 8://8�X�e�[�W
		*playerX = 48;
		*playerY = 16;
		*stageCoin = 7;
		*goalFlag = 0;
		break;
	case 9://9�X�e�[�W
		*playerX = 480;
		*playerY = 240;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 10://10�X�e�[�W
		*playerX = 100;
		*playerY = 50;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 11://11�X�e�[�W
		*playerX = 100;
		*playerY = 50;
		*stageCoin = 4;
		*goalFlag = 0;
		break;
	case 12://12�X�e�[�W

		*playerX = 400;
		*playerY = 50;
		*stageCoin = 4;
		*goalFlag = 0;
		break;
	case 13://13�X�e�[�W
		*playerX = 480;
		*playerY = 50;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 14://14�X�e�[�W
		*playerX = 200;
		*playerY = 50;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 15://15�X�e�[�W
		*playerX = 50;
		*playerY = 50;
		*stageCoin = 5;
		*goalFlag = 0;
		break;
	case 16://16�X�e�[�W
		*playerX = 400;
		*playerY = 50;
		*stageCoin = 4;
		*goalFlag = 0;
		break;
	case 17://17�X�e�[�W
		*playerX = 650;
		*playerY = 50;
		*stageCoin = 3;
		*goalFlag = 0;
		break;
	case 18://18�X�e�[�W
		*playerX = 350;
		*playerY = 50;
		*stageCoin = 4;
		*goalFlag = 0;
		break;
	case 19://19�X�e�[�W
		*playerX = 350;
		*playerY = 50;
		*stageCoin = 4;
		*goalFlag = 0;
		break;
	case 20://�{�[�i�X�X�e�[�W
		*playerX = 100;
		*playerY = 450;
		*stageCoin = 0;
		break;
	}
}

void AnimationInit(int *animation, int *playerAnimation, int *wingAnimation,
	int *hungryAnimation, int *coinAnimation, int *clearAnimation)
{
	if (animation == nullptr || playerAnimation == nullptr || wingAnimation == nullptr ||
		hungryAnimation == nullptr || coinAnimation == nullptr || clearAnimation == nullptr)
	{
		return;
	}

	*animation = 0;
	*playerAnimation = 0;
	*wingAnimation = 0;
	*hungryAnimation = 0;
	*coinAnimation = 0;
	*clearAnimation = 0;
}