#include <DxLib.h>
#include "./../Header/Key.h"

void Key(int *key, int *goal)
{
	if (key != nullptr && goal != nullptr)
	{
		if (*key != 0)
		{
			*goal = 1;
		}
	}
}