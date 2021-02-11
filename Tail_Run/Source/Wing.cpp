#include <DxLib.h>
#include "./../Header/Wing.h"

void Wing(int *y, bool *useFlag, bool input[], bool oldInput[])
{
	if (y != nullptr)
	{
		if (input[4] == TRUE && oldInput[4] == FALSE)
		{
			*y -= 48;
			*useFlag = TRUE;
		}
	}
}

void Gravity(int *y)
{
	*y += 2;
}