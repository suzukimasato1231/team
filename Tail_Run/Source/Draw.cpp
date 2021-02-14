#include <DxLib.h>
#include "./../Header/Draw.h"
#include "./../Header/Load.h"
#include "./../Header/Stage.h"
#include "./../Header/Input.h"
#include "./../Header/Claws.h"
#include <math.h>

void BGDraw(const Graphic &graphic, const int &stageNo, const int &shakeX, const int &shakeY)
{
	int i = 0;
	if (stageNo == 20)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	DrawGraph(shakeX, shakeY, graphic.background[i], TRUE);
}

void TitleDraw(const Graphic &graphic)
{
	BGDraw(graphic, 0);
	DrawGraph(48, 32, graphic.title, TRUE);
}

void SelectDraw(const int &blockSize, const int &stageSelectX, const int &stageSelectY, const int star[], const int starAnimation, const Graphic graphic)
{
	DrawGraph(0, 0, graphic.stage, TRUE);

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (x + y * 7 < 10)
			{
				switch (star[x + y * 7])
				{
				case 1:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[1], TRUE);
					break;
				case 2:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.rainbowStar[starAnimation], TRUE);
					break;
				default:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[0], TRUE);
					break;
				}
			}
			else if (x + y * 7 > 10)
			{
				switch (star[(x + y * 7) - 1])
				{
				case 1:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[1], TRUE);
					break;
				case 2:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.rainbowStar[starAnimation], TRUE);
					break;
				default:
					DrawGraph(x * 4 * blockSize + 38, y * 6 * blockSize + 56, graphic.star[0], TRUE);
					break;
				}
			}
		}
	}

	DrawGraph(stageSelectX * 4 * blockSize + 32, stageSelectY * 6 * blockSize + 48, graphic.stageselect, TRUE);
}

void GameOverDraw(const int &blockSize, const int &gameoverSelectY, const Graphic &graphic)
{
	DrawGraph(0, 0, graphic.gameover, TRUE);
	DrawGraph(0, gameoverSelectY * 5 * blockSize, graphic.gameoverselect, TRUE);
}

void GameClearDraw(const char strNum[], const int clearAnimation, const Graphic &graphic)
{
	DrawGraph(0, 0, graphic.clear[clearAnimation], TRUE);

	//数字を表示
	for (int i = 0; i < 10; i++) {
		int num = strNum[i] - 48;
		DrawGraph(96 * i + 290, 340, graphic.number[num], TRUE);
	}
}

void StageDraw(const int &blockSize, const int &mapW, const int &mapH, const int mapChip[20 + 2][30 + 2],
	const Graphic &graphic, const int &animationCount, const int &shakeX, const int &shakeY)
{
	for (int y = 0; y < mapH - 1; y++)
	{
		for (int x = 0; x < mapW - 2; x++)
		{
			switch (mapChip[y + 1][x + 1])
			{
			case StageNone:
				break;
			case StageGround:
				//地面の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.block[0], TRUE);
				break;
			case StageGoal:
				//ゴールの描画
				DrawGraph(blockSize * x + shakeX, blockSize * (y - 1) + shakeY, graphic.goal, TRUE);
				break;
			case StageCoin:
				//コインの描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.coin[animationCount], TRUE);
				break;
			case StageFood:
				//食べ物の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.food, TRUE);
				break;
			case StageKey:
				//鍵の描画
				DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.key, TRUE);
				break;
			case StagePile:
				//杭の描画
				if (mapChip[y][x + 1] == StagePile)
				{
					DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.pile[1], TRUE);
				}
				else
				{
					DrawGraph(blockSize * x + shakeX, blockSize * y + shakeY, graphic.pile[0], TRUE);
				}
				break;
			case StageSlime:
				break;
			case StageMagma:
				break;
			case StageIce:
				break;
			default:
				break;
			}
		}
	}
}

void PlayerDraw(const int x, const int y, const Graphic graphic, const bool turn, const int animationCount, const int clawFlag, const bool input[])
{
	if (input[InputLeft] == true || input[InputRight] == true)
	{
		if (clawFlag == Normal)
		{
			DrawRotaGraph(x, y, 1, 0, graphic.player.run[animationCount], true, turn);
		}
		else
		{
			DrawRotaGraph(x, y, 1, 0, graphic.player.idle[animationCount], true, turn);
		}
	}
	else
	{
		DrawRotaGraph(x, y, 1, 0, graphic.player.idle[animationCount], true, turn);
	}
}

void StarvationDrow(const int &x, const int &y, const Graphic &graphic, const bool &turn, const int &animationCount)
{
	DrawRotaGraph(x, y, 1, 0, graphic.player.hungry[animationCount], TRUE, turn);
}
//メニュー
void MenuDraw(const int &menuY, const struct Graphic &graphic)
{
	int space = 160;
	DrawGraph(0, 0, graphic.menu, TRUE);
	DrawGraph(0, menuY * space - 96, graphic.gameoverselect, TRUE);
	DrawGraph(280, 570, graphic.menuButton, TRUE);
}

void MusicDraw(const int musicSelectY, const int SeVolume, const int BgmVolume, const struct Graphic &graphic)
{
	int noteX = 360;
	int noteSpace = 96;
	int selectY = 150;
	DrawGraph(0, 0, graphic.music, TRUE);
	DrawGraph(0, musicSelectY * 190 + selectY, graphic.musicSelect, TRUE);
	DrawGraph(noteX + SeVolume * noteSpace, 190, graphic.note, TRUE);
	DrawGraph(noteX + BgmVolume * noteSpace, 385, graphic.note, TRUE);
	DrawGraph(280, 570, graphic.menuButton, TRUE);
}

void ClawDraw(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &playerTurn, const int &count)
{
	if (playerTurn == TRUE)
	{
		DrawGraph(x - width, y - height + 4, graphic.player.claw[0], TRUE);
		for (int i = 0; i < count; i++)
		{
			DrawGraph(x - width + width * 2 * i, y - height + 4, graphic.player.claw[1], TRUE);
		}
	}
	else
	{
		DrawTurnGraph(x - width, y - height + 4, graphic.player.claw[0], TRUE);
		for (int i = 0; i < count; i++)
		{
			DrawGraph(x - width - width * 2 * i, y - height + 4, graphic.player.claw[1], TRUE);
		}
	}
}

void WingDraw(const int &x, const int &y, const int &width, const int &height, const Graphic &graphic, const bool &turn, const bool &useFlag)
{
	if (turn == TRUE)
	{
		if (useFlag == TRUE)
		{
			DrawRotaGraph(x + width, y + height, 1.0, 0.0, graphic.player.wing, TRUE, FALSE, TRUE);
		}
		else
		{
			DrawRotaGraph(x + width, y - height, 1.0, 0.0, graphic.player.wing, TRUE, FALSE, FALSE);
		}
	}
	else
	{
		if (useFlag == TRUE)
		{
			DrawRotaGraph(x - width, y + height, 1.0, 0.0, graphic.player.wing, TRUE, TRUE, TRUE);
		}
		else
		{
			DrawRotaGraph(x - width, y - height, 1.0, 0.0, graphic.player.wing, TRUE, TRUE, FALSE);
		}
	}
}

void HungryDraw(const int hungryTime, const Graphic &graphic)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0xC0);
	DrawBox(35, 13, hungryTime / 4 + 35, 45, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0x00);
	DrawGraph(5, 0, graphic.hungry, TRUE);
	//
	DrawGraph(800, 10, graphic.menuButton, TRUE);
	DrawGraph(832, 10, graphic.menuLetters, TRUE);
}

void KeyDraw(const int goalFlag, const int GrHandle)
{
	if (goalFlag != 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0xC0);
		DrawCircle(460, 30, 12, GetColor(0x08, 0xF0, 0xF8), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0x00);
		DrawRotaGraph(460, 30, 0.75, atan(1.0) * 2, GrHandle, true);
	}
}

void DebugDraw(const int &blockSize, const int &winW, const int &winH, const int &mapW, const int &mapH, const int &playerX, const int &playerY, const int &playerW, const int &playerH)
{
	for (int x = 0; x < mapW; x++)
	{
		DrawLine(blockSize * x, 0, blockSize * x, winH, GetColor(0xFF, 0xFF, 0xFF));
	}
	for (int y = 0; y < mapH; y++)
	{
		DrawLine(0, blockSize * y, winW, blockSize * y, GetColor(0xFF, 0xFF, 0xFF));
	}
	DrawLineBox(playerX - 16, playerY - 16, playerX + 16, playerY + 16, GetColor(0xFF, 0xFF, 0xFF));
}