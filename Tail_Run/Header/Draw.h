#pragma once

//�w�i�̕`��
void BGDraw(const struct Graphic &graphic, const int &stageNo, const int &shakeX = 0, const int &shakeY = 0);

//�^�C�g����ʂ̕`��
void TitleDraw(const struct Graphic &graphic);

//�X�e�[�W�I���̕`��
void SelectDraw(const int &blockSize, const int &stageSelectX, const int &stageSelectY, const int star[], const int starAnimation, const struct Graphic graphic);

//���j���[�I���̕`��
void MenuDraw(const int &menuY, const struct Graphic &graphic);

void MusicDraw(const int musicSelectY, const int SeVolume, const int BgmVolume, const struct Graphic &graphic);
//�Q�[���I�[�o�[�̕`��
void GameOverDraw(const int &blockSize, const int &gameoverSelectY, const struct Graphic &graphic);

//�N���A��ʂ̕`��
void GameClearDraw(const char strNum[], const int clearAnimation, const struct Graphic &graphic);

//�X�e�[�W�̕`��
void StageDraw(const int &blockSize, const int &mapW, const int &mapH, const int mapChip[20 + 2][30 + 2],
	const struct Graphic &graphic, const int &animationCount, const int &shakeX = 0, const int &shakeY = 0);

//�v���C���[�̕`��
void PlayerDraw(const int x, const int y, const struct Graphic graphic, const bool turn, const int animationCount, const int clawFlag, const bool input[]);

//�Q���̕`��
void StarvationDrow(const int &x, const int &y, const struct Graphic &graphic, const bool &turn, const int &animationCount);

//�H�̕`��
void WingDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &turn, const bool &useFlag);

//�����܂̕`��
void ClawDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &playerTurn, const int &count);

//�󕠃Q�[�W
void HungryDraw(const int hungryTime, const struct Graphic &graphic);

//�S�[���o���邩�ǂ�����UI
void KeyDraw(const int goalFlag, const int GrHandle);

//�f�o�b�O�p�̐�
void DebugDraw(const int &blockSize, const int &winW, const int &winH, const int &mapW, const int &mapH, const int &playerX, const int &playerY, const int &playerW, const int &playerH);