#pragma once

enum InputData
{
	InputUp,
	InputDown,
	InputLeft,
	InputRight,
	InputAction,
	InputMenu
};

void Input(const char keys[], const tagXINPUT_STATE &pad, bool *input);