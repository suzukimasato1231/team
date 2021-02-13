#include <DxLib.h>
#include "./../Header/Claws.h"
#include "./../Header/Stage.h"

void Claws(int *clawX, const int &clawWidth, int *chainCount, int *playerX, const int &playerWidth, const bool &playerTurn, const int &flag)
{
	if (clawX == nullptr || chainCount == nullptr)
	{
		return;
	}

	switch (flag)
	{
	case Launching:
		if (playerTurn == TRUE)
		{
			*clawX -= 5;
			if (*clawX + clawWidth * 2 * (*chainCount) <= *playerX - playerWidth)
			{
				*chainCount += 1;
			}
		}
		else
		{
			*clawX += 5;
			if (*clawX - clawWidth * 2 * (*chainCount) >= *playerX + playerWidth)
			{
				*chainCount += 1;
			}
		}
		break;
	case PlayerMove:
		if (playerTurn == TRUE)
		{
			*playerX -= 10;
			if (*playerX - playerWidth <= *clawX + clawWidth * 2 * (*chainCount - 1))
			{
				*chainCount -= 1;
			}
		}
		else
		{
			*playerX += 10;
			if (*playerX + playerWidth >= *clawX - clawWidth * 2 * (*chainCount - 1))
			{
				*chainCount -= 1;
			}
		}
		break;
	case Cancel:
		if (playerTurn == TRUE)
		{
			*clawX += 5;
			if (*clawX + clawWidth * 2 * (*chainCount - 1) >= *playerX - playerWidth)
			{
				*chainCount -= 1;
			}
		}
		else
		{
			*clawX -= 5;
			if (*clawX - clawWidth * 2 * (*chainCount - 1) <= *playerX + playerWidth)
			{
				*chainCount -= 1;
			}
		}
		break;
	default:
		break;
	}
}

char PileHit(const int &x, const int &y, const int &width, const int &height, const int &blockSize, const int map[20][30])
{
	char hitFlag = 0;
	int blockLeft, blockRight;

	blockLeft = (x - width) / blockSize;
	blockRight = (x + width) / blockSize;

	for (int hitY = (y - height) + 1; hitY < (y + height) - 1; hitY++)
	{
		if (map[hitY / blockSize][blockLeft] == StagePile ||
			map[hitY / blockSize][blockRight] == StagePile)
		{
			hitFlag = 1;
			break;
		}
		if (map[hitY / blockSize][blockLeft] == StageGround ||
			map[hitY / blockSize][blockRight] == StageGround)
		{
			hitFlag = 2;
			break;
		}
	}
	if (x - width <= 0 || x + width >= blockSize * 30)
	{
		hitFlag = 2;
	}

	return hitFlag;
}

bool ClawHit(const int &clawX, const int &clawWidth, const int &playerX, const int &playerWidth)
{
	if (clawX - clawWidth <= playerX + playerWidth && clawX + clawWidth >= playerX - playerWidth)
	{
		return true;
	}

	return false;
}