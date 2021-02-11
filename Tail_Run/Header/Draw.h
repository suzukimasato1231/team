#pragma once

//�w�i�̕`��
void BGDraw(const struct Graphic &graphic, const int &stageNo, const int &shakeX = 0, const int &shakeY = 0);

//�^�C�g����ʂ̕`��
void TitleDraw(const struct Graphic &graphic);

//�X�e�[�W�I���̕`��
void SelectDraw(const int &blockSize, const int &stageSelectX, const int &stageSelectY, const int star[], const struct Graphic &graphic);

//�Q�[���I�[�o�[�̕`��
void GameOverDraw(const int &blockSize, const int &gameoverSelectY, const struct Graphic &graphic);

//�N���A��ʂ̕`��
void GameClearDraw(const char strNum[], const int clearAnimation, const struct Graphic &graphic);

//�X�e�[�W�̕`��
void StageDraw(const int &blockSize, const int &mapW, const int &mapH, const int mapChip[20][30], const struct Graphic &graphic, const int &animationCount, const int &shakeX = 0, const int &shakeY = 0);

//�v���C���[�̕`��
void PlayerDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &turn, const int &animationCount, const bool input[]);

//�Q���̕`��
void StarvationDrow(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &turn, const int &animationCount);

//�H�̕`��
void WingDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &turn, const bool &useFlag);

//�����܂̕`��
void ClawDraw(const int &x, const int &y, const int &width, const int &height, const struct Graphic &graphic, const bool &playerTurn, const int &count);

//�󕠃Q�[�W
void HungryDraw(const int hungryTime, const struct Graphic &graphic);

//�f�o�b�O�p�̐�
void DebugDraw(const int &blockSize, const int &winW, const int &winH, const int &mapW, const int &mapH, const int &playerX, const int &playerY, const int &playerW, const int &playerH);