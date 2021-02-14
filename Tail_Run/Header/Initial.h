#pragma once

void Initial(const int &stageNo, int *playerX, int *playerY, int *clawFlag, int *chainCount,
	int *shakeX, int *shakeY, int *stageCoin, int *coinNum, int *keyFlag, int *goalFlag,
	int *perfectFlag, int *clearFlag, int *hungryTime, bool *hungryDeathFlag,
	bool *fallDeathFlag, bool *deathFlag);

//アニメーションの初期化
void AnimationInit(int *animation, int *playerAnimation, int *wingAnimation,
	int *hungryAnimation, int *coinAnimation, int *clearAnimation);