#include <DxLib.h>
#include "./../Header/Player.h"
#include "../Header/Input.h"
#include "./../Header/Wing.h"
#include "./../Header/Stage.h"

void Player(int *x,int *y, bool *turn, bool input[],int map[20][30], int blockSize)
{
	if (x != nullptr && y != nullptr && turn != nullptr)
	{
		if (input[InputLeft] == TRUE)
		{
			*x -= 2;
			*turn = 1;
		}
		if (input[InputRight] == TRUE)
		{
			*x += 2;
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
}

void PlayerCollision(int *x, int *y, int width, int heigth, int *memoryX, int *memoryY, int *leftMapnumX, int *rightMapnumX, int *upMapnumY, int *downMapnumY, bool input[], int map[20][30], int blockSize)
{
	if (nullptr != x && nullptr != y &&
		nullptr != memoryX && nullptr != memoryY &&
		nullptr != leftMapnumX && nullptr != rightMapnumX &&
		nullptr != upMapnumY && nullptr != downMapnumY)
	{
		int hokan = 0;

		//左下のオブジェクトの当たり判定
		if (input[2] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Yの重なっているところを戻す
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
			//マップチップの何番目か
			//左下
			*leftMapnumX = (*x - width) / blockSize;
			*downMapnumY = (*y + heigth - 1) / blockSize;
			//それでも重なっている場合はYをもとの位置に戻しXを戻す
			if (map[*downMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*leftMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += width;
				//左下
				*leftMapnumX = (*x - width) / blockSize;
				*downMapnumY = (*y + heigth - 1) / blockSize;
				//それでも重なっている場合はYを戻し、Xを戻したままにする
				if (map[*downMapnumY][*leftMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += blockSize - heigth;
				}
			}
		}

		//左上のオブジェクトの当たり判定
		if (input[2] == TRUE && input[4] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround))
		{
			//Yの重なっているところを戻す
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
			//マップチップの何番目か
				//左上
			*leftMapnumX = (*x - width) / blockSize;
			*upMapnumY = (*y - heigth) / blockSize;
			//それでも重なっている場合はYをもとの位置に戻しXを戻す
			if (map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*leftMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += width;
				//マップチップの何番目か
				//左上
				*leftMapnumX = (*x - width) / blockSize;
				*upMapnumY = (*y - heigth) / blockSize;
				//それでも重なっている場合はYを戻し、Xを戻したままにする
				if (map[*upMapnumY][*leftMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += heigth;
				}
			}
		}

		//右下のオブジェクトの当たり判定
		if (input[3] == TRUE && (map[*downMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Yの重なっているところを戻す
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
			//マップチップの何番目か
			//右下
			*rightMapnumX = (*x + width - 1) / blockSize;
			*downMapnumY = (*y + heigth - 1) / blockSize;
			//それでも重なっている場合はYをもとの位置に戻しXを戻す
			if (map[*downMapnumY][*rightMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += blockSize - width;
				//マップチップの何番目か
				//右下
				*rightMapnumX = (*x + width - 1) / blockSize;
				*downMapnumY = (*y + heigth - 1) / blockSize;
				//それでも重なっている場合はYを戻し、Xを戻したままにする
				if (map[*downMapnumY][*rightMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += blockSize - heigth;
				}
			}
		}

		//右上のオブジェクトの当たり判定
		if (input[3] == TRUE && input[4] == TRUE && (map[*upMapnumY][*leftMapnumX] == StageGround ||
			map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			//Yの重なっているところを戻す
			hokan = *y;
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
			//マップチップの何番目か
			//右上
			*rightMapnumX = (*x + width - 1) / blockSize;
			*upMapnumY = (*y - heigth) / blockSize;
			//それでも重なっている場合はYをもとの位置に戻しXを戻す
			if (map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround)
			{
				*y = hokan;
				*x = max(*x, *memoryX);
				*x /= blockSize;
				*x *= blockSize;
				*x += blockSize - width;
				//マップチップの何番目か
				//右上
				*rightMapnumX = (*x + width - 1) / blockSize;
				*upMapnumY = (*y - heigth) / blockSize;
				//それでも重なっている場合はYを戻し、Xを戻したままにする
				if (map[*upMapnumY][*rightMapnumX] == StageGround)
				{
					*y = max(*y, *memoryY);
					*y /= blockSize;
					*y *= blockSize;
					*y += heigth;
				}
			}
		}

		//左方向
		if (*x != *memoryX && (map[*upMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*leftMapnumX] == StageGround))
		{
			*x = max(*x, *memoryX);
			*x /= blockSize;
			*x *= blockSize;
			*x += width;
		}

		//右方向壁当たり判定
		if (*x != *memoryX && (map[*upMapnumY][*rightMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			*x = max(*x, *memoryX);
			*x /= blockSize;
			*x *= blockSize;
			*x += blockSize - width;
		}

		//移動下
		if (*y != *memoryY && (map[*downMapnumY][*leftMapnumX] == StageGround || map[*downMapnumY][*rightMapnumX] == StageGround))
		{
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += blockSize - heigth;
		}

		//移動上
		if (*y != *memoryY && (map[*upMapnumY][*leftMapnumX] == StageGround || map[*upMapnumY][*rightMapnumX] == StageGround))
		{
			*y = max(*y, *memoryY);
			*y /= blockSize;
			*y *= blockSize;
			*y += heigth;
		}
	}
}