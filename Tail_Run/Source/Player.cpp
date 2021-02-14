#include <DxLib.h>
#include "./../Header/Player.h"
#include "../Header/Input.h"
#include "./../Header/Wing.h"
#include "./../Header/Stage.h"

void Player(int *x, int *y, bool *turn, bool input[], int map[20 + 2][30 + 2], int blockSize)
{
	if (x == nullptr || y == nullptr || turn == nullptr)
	{
		return;
	}

	int speed = 3;

	if (input[InputLeft] == TRUE)
	{
		*x -= speed;
		*turn = 1;
	}
	if (input[InputRight] == TRUE)
	{
		*x += speed;
		*turn = 0;
	}
	/*if (input[0] == TRUE)
	{
		*y -= 2;
	}
	if (input[1] == TRUE)
	{
		*y += 2;
	}*/

	if (*x <= 0)
	{
		*x = 0;
	}
	else if (*x >= blockSize * 30)
	{
		*x = blockSize * 30;
	}
	if (*y <= 0)
	{
		*y = 0;
	}
}

void PlayerCollision(int *x, int *y, int width, int heigth, int *memoryX, int *memoryY,
	int *leftMapnumX, int *rightMapnumX, int *upMapnumY, int *downMapnumY, bool input[], int map[20 + 2][30 + 2], int blockSize)
{
	if (nullptr == x || nullptr == y ||
		nullptr == memoryX || nullptr == memoryY ||
		nullptr == leftMapnumX || nullptr == rightMapnumX ||
		nullptr == upMapnumY || nullptr == downMapnumY)
	{
		return;
	}

	int centerMapNumX = (*x / blockSize) + 1;
	int centerMapNumY = (*y / blockSize) + 1;

	//�����̃I�u�W�F�N�g�̓����蔻��
	if (map[*downMapnumY][*leftMapnumX] == StageGround)
	{
		//�v���C���[�̍��������ɕǂ����邩�ǂ���
		if (map[*upMapnumY][*leftMapnumX] != StageGround && map[*downMapnumY][*rightMapnumX] != StageGround)
		{
			//*x += 1;
			*y -= 1;
		}
	}

	//����̃I�u�W�F�N�g�̓����蔻��
	if (map[*upMapnumY][*leftMapnumX] == StageGround)
	{
		//�v���C���[�̍�������ɕǂ����邩�ǂ���
		if (map[*downMapnumY][*leftMapnumX] != StageGround && map[*upMapnumY][*rightMapnumX] != StageGround)
		{
			//*x += 1;
			*y += 1;
		}
	}

	//�E���̃I�u�W�F�N�g�̓����蔻��
	if (map[*downMapnumY][*rightMapnumX] == StageGround)
	{
		//�v���C���[�̉E�������ɕǂ����邩�ǂ���
		if (map[*upMapnumY][*rightMapnumX] != StageGround && map[*downMapnumY][*leftMapnumX] != StageGround)
		{
			//*x -= 1;
			*y -= 1;
		}
	}

	//�E��̃I�u�W�F�N�g�̓����蔻��
	if (map[*upMapnumY][*rightMapnumX] == StageGround)
	{
		//�v���C���[�̉E������ɕǂ����邩�ǂ���
		if (map[*downMapnumY][*rightMapnumX] != StageGround && map[*upMapnumY][*leftMapnumX] != StageGround)
		{
			//*x -= 1;
			*y += 1;
		}
	}

	//������
	if (map[centerMapNumY][*leftMapnumX] == StageGround)
	{
		*x = max(*x, *memoryX);
		*x /= blockSize;
		*x *= blockSize;
		*x += width;
	}

	//�E����
	if (map[centerMapNumY][*rightMapnumX] == StageGround)
	{
		*x = max(*x, *memoryX);
		*x /= blockSize;
		*x *= blockSize;
		*x += blockSize - width;
	}

	//�ړ���
	if (map[*downMapnumY][centerMapNumX] == StageGround)
	{
		*y = max(*y, *memoryY);
		*y /= blockSize;
		*y *= blockSize;
		*y += blockSize - heigth;
	}

	//�ړ���
	if (map[*upMapnumY][centerMapNumX] == StageGround)
	{
		*y = max(*y, *memoryY);
		*y /= blockSize;
		*y *= blockSize;
		*y += heigth;
	}
}