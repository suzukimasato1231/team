#include <DxLib.h>
#include "./../Header/Change.h"

void Change(bool *flag, const int &stageNo)
{
	if (stageNo >= 20)
	{
		*flag = TRUE;
	}
	else
	{
		*flag = FALSE;
	}
}