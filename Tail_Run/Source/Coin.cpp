#include <DxLib.h>
#include "./../Header/Coin.h"
#include "./../Header/Stage.h"

void Coin(int *coinNum, int map[20][30], int leftMapnumX, int rightMapnumX, int upMapnumY, int downMapnumY, int soundHandle)
{
	bool hit = FALSE;

	if (nullptr != coinNum)
	{
		//コインを取ったらそのコインを消す処理
		if (map[upMapnumY][leftMapnumX] == StageCoin)
		{
			hit = TRUE;
			map[upMapnumY][leftMapnumX] = StageNone;
		}

		else if (map[downMapnumY][leftMapnumX] == StageCoin)
		{
			hit = TRUE;
			map[downMapnumY][leftMapnumX] = StageNone;
		}

		else if (map[upMapnumY][rightMapnumX] == StageCoin)
		{
			hit = TRUE;
			map[upMapnumY][rightMapnumX] = StageNone;
		}

		else if (map[downMapnumY][rightMapnumX] == StageCoin)
		{
			hit = TRUE;
			map[downMapnumY][rightMapnumX] = StageNone;
		}

		if (hit == TRUE)
		{
			*coinNum += 1;

			//コインのSE再生
			PlaySoundMem(soundHandle, DX_PLAYTYPE_BACKBIT);
		}
	}
}