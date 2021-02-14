#include <DxLib.h>
#include "./../Header/Wing.h"
#include "./../Header/Input.h"

void Wing(int *y, bool *useFlag, bool input[], bool oldInput[])
{
	if (y == nullptr)
	{
		return;
	}

	if (input[InputAction] == TRUE && oldInput[InputAction] == FALSE)
	{
		*y -= 48;
		*useFlag = TRUE;
	}
}

void Gravity(int *y)
{
	*y += 2;
}