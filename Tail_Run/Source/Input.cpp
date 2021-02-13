#include <DxLib.h>
#include "./../Header/Input.h"

void Input(const char keys[], const XINPUT_STATE &pad, bool *input)
{
	if (keys[KEY_INPUT_UP] != 0 || pad.Buttons[0] != 0 || pad.ThumbLY >= 25500)
	{
		input[InputUp] = TRUE;
	}
	else
	{
		input[InputUp] = FALSE;
	}
	if (keys[KEY_INPUT_DOWN] != 0 || pad.Buttons[1] != 0 || pad.ThumbLY < -25500)
	{
		input[InputDown] = TRUE;
	}
	else
	{
		input[InputDown] = FALSE;
	}
	if (keys[KEY_INPUT_LEFT] != 0 || pad.Buttons[2] != 0 || pad.ThumbLX < -25500)
	{
		input[InputLeft] = TRUE;
	}
	else
	{
		input[InputLeft] = FALSE;
	}
	if (keys[KEY_INPUT_RIGHT] != 0 || pad.Buttons[3] != 0 || pad.ThumbLX >= 25500)
	{
		input[InputRight] = TRUE;
	}
	else
	{
		input[InputRight] = FALSE;
	}
	if (keys[KEY_INPUT_Z] != 0 || pad.Buttons[12] != 0)
	{
		input[InputAction] = TRUE;
	}
	else
	{
		input[InputAction] = FALSE;
	}
	if (keys[KEY_INPUT_R] != 0 || pad.Buttons[4] != 0)
	{
		input[InputMenu] = TRUE;
	}
	else
	{
		input[InputMenu] = FALSE;
	}
}