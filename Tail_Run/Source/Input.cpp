#include <DxLib.h>
#include "./../Header/Input.h"

void Input(const char keys[], const XINPUT_STATE &pad, bool *input)
{
	if (keys[KEY_INPUT_UP] != 0 || pad.Buttons[0] != 0 || pad.ThumbLY >= 5500)
	{
		input[0] = TRUE;
	}
	else
	{
		input[0] = FALSE;
	}
	if (keys[KEY_INPUT_DOWN] != 0 || pad.Buttons[1] != 0 || pad.ThumbLY < -5500)
	{
		input[1] = TRUE;
	}
	else
	{
		input[1] = FALSE;
	}
	if (keys[KEY_INPUT_LEFT] != 0 || pad.Buttons[2] != 0 || pad.ThumbLX < -5500)
	{
		input[2] = TRUE;
	}
	else
	{
		input[2] = FALSE;
	}
	if (keys[KEY_INPUT_RIGHT] != 0 || pad.Buttons[3] != 0 || pad.ThumbLX >= 5500)
	{
		input[3] = TRUE;
	}
	else
	{
		input[3] = FALSE;
	}
	if (keys[KEY_INPUT_Z] != 0 || pad.Buttons[12] != 0)
	{
		input[4] = TRUE;
	}
	else
	{
		input[4] = FALSE;
	}
}