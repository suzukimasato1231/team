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

	//左下のオブジェクトの当たり判定
	if (map[*downMapnumY][*leftMapnumX] == StageGround)
	{
		//プレイヤーの左側か下に壁があるかどうか
		if (map[*upMapnumY][*leftMapnumX] != StageGround && map[*downMapnumY][*rightMapnumX] != StageGround)
		{
			//*x += 1;
			*y -= 1;
		}
	}

	//左上のオブジェクトの当たり判定
	if (map[*upMapnumY][*leftMapnumX] == StageGround)
	{
		//プレイヤーの左側か上に壁があるかどうか
		if (map[*downMapnumY][*leftMapnumX] != StageGround && map[*upMapnumY][*rightMapnumX] != StageGround)
		{
			//*x += 1;
			*y += 1;
		}
	}

	//右下のオブジェクトの当たり判定
	if (map[*downMapnumY][*rightMapnumX] == StageGround)
	{
		//プレイヤーの右側か下に壁があるかどうか
		if (map[*upMapnumY][*rightMapnumX] != StageGround && map[*downMapnumY][*leftMapnumX] != StageGround)
		{
			//*x -= 1;
			*y -= 1;
		}
	}

	//右上のオブジェクトの当たり判定
	if (map[*upMapnumY][*rightMapnumX] == StageGround)
	{
		//プレイヤーの右側か上に壁があるかどうか
		if (map[*downMapnumY][*rightMapnumX] != StageGround && map[*upMapnumY][*leftMapnumX] != StageGround)
		{
			//*x -= 1;
			*y += 1;
		}
	}

	//左方向
	if (map[centerMapNumY][*leftMapnumX] == StageGround)
	{
		*x = max(*x, *memoryX);
		*x /= blockSize;
		*x *= blockSize;
		*x += width;
	}

	//右方向
	if (map[centerMapNumY][*rightMapnumX] == StageGround)
	{
		*x = max(*x, *memoryX);
		*x /= blockSize;
		*x *= blockSize;
		*x += blockSize - width;
	}

	//移動下
	if (map[*downMapnumY][centerMapNumX] == StageGround)
	{
		*y = max(*y, *memoryY);
		*y /= blockSize;
		*y *= blockSize;
		*y += blockSize - heigth;
	}

	//移動上
	if (map[*upMapnumY][centerMapNumX] == StageGround)
	{
		*y = max(*y, *memoryY);
		*y /= blockSize;
		*y *= blockSize;
		*y += heigth;
	}
}