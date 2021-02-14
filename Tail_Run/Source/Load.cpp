#include <DxLib.h>
#include "./../Header/Load.h"

void LoadGraphic(Graphic &graphic)
{
	graphic.background[0] = LoadGraph("./Resource/graphic/forest.png");
	graphic.background[1] = LoadGraph("./Resource/graphic/mountain.png");
	graphic.cloud[0] = LoadGraph("./Resource/graphic/cloud1.png");
	graphic.cloud[1] = LoadGraph("./Resource/graphic/cloud2.png");
	graphic.block[0] = LoadGraph("./Resource/graphic/forestBlock.png");
	graphic.block[1] = LoadGraph("./Resource/graphic/block_sample.png");
	graphic.title = LoadGraph("./Resource/graphic/title.png");
	LoadDivGraph("./Resource/graphic/star.png", 2, 2, 1, 32, 32, graphic.star);
	graphic.aButton = LoadGraph("./Resource/graphic/A_button.png");
	//
	graphic.menuButton = LoadGraph("./Resource/graphic/Menu_button.png");
	LoadDivGraph("./Resource/graphic/player/player_idle.png", 2, 2, 1, 32, 28, graphic.player.idle);
	LoadDivGraph("./Resource/graphic/player/player_run.png", 4, 4, 1, 32, 28, graphic.player.run);
	LoadDivGraph("./Resource/graphic/player/player_hungry.png", 3, 3, 1, 32, 28, graphic.player.hungry);
	LoadDivGraph("./Resource/graphic/player/hookShot.png", 2, 2, 1, 16, 16, graphic.player.claw);
	graphic.player.wing = LoadGraph("./Resource/graphic/player/wing.png");
	graphic.goal = LoadGraph("./Resource/graphic/door.png");
	graphic.key = LoadGraph("./Resource/graphic/Key.png");
	graphic.food = LoadGraph("./Resource/graphic/apple.png");
	LoadDivGraph("./Resource/graphic/coin.png", 8, 8, 1, 32, 32, graphic.coin);
	LoadDivGraph("./Resource/graphic/Pile.png", 2, 2, 1, 32, 32, graphic.pile);
	//graphic.slime = LoadGraph("./Resource/graphic/");
	//graphic.magma = LoadGraph("./Resource/graphic/");
	//graphic.ice = LoadGraph("./Resource/graphic/");
	graphic.stage = LoadGraph("./Resource/graphic/select.png");
	graphic.stageselect = LoadGraph("./Resource/graphic/stageSelect.png");

	graphic.gameover = LoadGraph("./Resource/graphic/gameover.png");
	graphic.gameoverselect = LoadGraph("./Resource/graphic/gameoverSelect.png");
	//
	graphic.menu = LoadGraph("./Resource/graphic/menu.png");
	graphic.menuLetters = LoadGraph("./Resource/graphic/Menu_Letters.png");

	graphic.music= LoadGraph("./Resource/graphic/music.png");
	graphic.note = LoadGraph("./Resource/graphic/note.png");
	graphic.musicSelect = LoadGraph("./Resource/graphic/soundSelect.png");
	
	graphic.hungry = LoadGraph("./Resource/graphic/hungry.png");

	LoadDivGraph("./Resource/graphic/clear.png", 6, 6, 1, 960, 640, graphic.clear);
	LoadDivGraph("./Resource/graphic/number.png", 10, 10, 1, 96, 96, graphic.number);
}

int LoadCSV(const int &i)
{
	int fileHandle;

	switch (i)
	{
	case 0:
		fileHandle = FileRead_open("./Resource/stage/title.csv");
		break;
	case 1:
		fileHandle = FileRead_open("./Resource/stage/stage1.csv");
		break;
	case 2:
		fileHandle = FileRead_open("./Resource/stage/stage2.csv");
		break;
	case 3:
		fileHandle = FileRead_open("./Resource/stage/stage3.csv");
		break;
	case 4:
		fileHandle = FileRead_open("./Resource/stage/stage4.csv");
		break;
	case 5:
		fileHandle = FileRead_open("./Resource/stage/stage5.csv");
		break;
	case 6:
		fileHandle = FileRead_open("./Resource/stage/stage6.csv");
		break;
	case 7:
		fileHandle = FileRead_open("./Resource/stage/stage7.csv");
		break;
	case 8:
		fileHandle = FileRead_open("./Resource/stage/stage8.csv");
		break;
	case 9:
		fileHandle = FileRead_open("./Resource/stage/stage9.csv");
		break;
	case 10:
		fileHandle = FileRead_open("./Resource/stage/stage10.csv");
		break;
	case 11:
		fileHandle = FileRead_open("./Resource/stage/stage11.csv");
		break;
	case 12:
		fileHandle = FileRead_open("./Resource/stage/stage12.csv");
		break;
	case 13:
		fileHandle = FileRead_open("./Resource/stage/stage13.csv");
		break;
	case 14:
		fileHandle = FileRead_open("./Resource/stage/stage14.csv");
		break;
	case 15:
		fileHandle = FileRead_open("./Resource/stage/stage15.csv");
		break;
	case 16:
		fileHandle = FileRead_open("./Resource/stage/stage16.csv");
		break;
	case 17:
		fileHandle = FileRead_open("./Resource/stage/stage17.csv");
		break;
	case 18:
		fileHandle = FileRead_open("./Resource/stage/stage18.csv");
		break;
	case 19:
		fileHandle = FileRead_open("./Resource/stage/stage19.csv");
		break;
	default:
		fileHandle = FileRead_open("./Resource/stage/stage20.csv");
		break;
	}

	return fileHandle;
}

void SoundVolume(Sound sound)
{
	ChangeVolumeSoundMem(120, sound.bgm);
	ChangeVolumeSoundMem(120, sound.shot);
	ChangeVolumeSoundMem(120, sound.coin);
	ChangeVolumeSoundMem(120, sound.food);
	ChangeVolumeSoundMem(120, sound.key);
	ChangeVolumeSoundMem(120, sound.goal);
	ChangeVolumeSoundMem(120, sound.select);
	ChangeVolumeSoundMem(120, sound.decision);
}

void SoundVolumeChange(const int SeVolume, const int BgmVolume, Sound sound)
{
	int volume = 40;
	ChangeVolumeSoundMem(BgmVolume * volume, sound.bgm);
	ChangeVolumeSoundMem(SeVolume * volume, sound.shot);
	ChangeVolumeSoundMem(SeVolume * volume, sound.coin);
	ChangeVolumeSoundMem(SeVolume * volume, sound.food);
	ChangeVolumeSoundMem(SeVolume * volume, sound.key);
	ChangeVolumeSoundMem(SeVolume * volume, sound.goal);
	ChangeVolumeSoundMem(SeVolume * volume, sound.select);
	ChangeVolumeSoundMem(SeVolume * volume, sound.decision);
}

void LoadSound(Sound &sound)
{
	sound.bgm = LoadSoundMem("./Resource/sound/bgm.mp3");
	sound.shot = LoadSoundMem("./Resource/sound/chain.mp3");
	sound.coin = LoadSoundMem("./Resource/sound/coin.mp3");
	sound.food = LoadSoundMem("./Resource/sound/food.mp3");
	sound.key = LoadSoundMem("./Resource/sound/key.mp3");
	sound.goal = LoadSoundMem("./Resource/sound/goal.mp3");
	sound.select = LoadSoundMem("./Resource/sound/select.mp3");
	sound.decision = LoadSoundMem("./Resource/sound/decision.mp3");

	SoundVolume(sound);
}