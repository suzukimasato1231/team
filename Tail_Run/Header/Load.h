#pragma once

typedef struct Player
{
	int idle[2] = { 0 };
	int run[4] = { 0 };
	int hungry[3] = { 0 };
	int claw[2] = { 0 };
	int wing = 0;
}Player;

typedef struct Graphic
{
	int background[2] = { 0 }, cloud[2] = { 0 }, block[2] = { 0 };
	int title = 0, star[2] = { 0 }, rainbowStar[8] = { 0 };
	int aButton = 0;
	
	int menuButton = 0;
	int goal = 0, key = 0;
	int food = 0;
	int coin[8] = { 0 };
	int pile[2] = { 0 };
	int slime = 0, magma = 0, ice = 0;
	int hungry = 0;
	int stage = 0, stageselect = 0;
	int gameover = 0, gameoverselect = 0;
	int clear[6] = { 0 }, number[11] = { 0 };
	
	int menu = 0;
	int menuLetters = 0;
	int music = 0;
	int note = 0;
	int musicSelect = 0;
	struct Player player;
}Graphic;

typedef struct Sound
{
	int bgm = 0;
	int shot = 0;
	int coin = 0;
	int food = 0;
	int key = 0;
	int goal = 0;
	int select = 0;
	int decision = 0;
}Sound;

void LoadGraphic(Graphic &graphic);

int LoadCSV(const int &i);

//âπó í≤êÆ
void SoundVolume(struct Sound sound);
void SoundVolumeChange(const int SeVolume,const int BgmVolume,Sound sound);

void LoadSound(Sound &sound);