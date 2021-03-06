#pragma once

//ステージ選択
void Select(int *stageSelectX, int *stageSelectY, int *scene, int *stageNo, bool input[], bool oldInput[], int inputCount[], struct Sound sound);

//メニュー選択
void MenuSelect(int *scene, int *menuSelectY, bool input[], bool oldInput[], int inputCount[], struct Sound sound);

void MusicSelect(int *musicSelectY, int *seVolume, int *bgmVolume, bool input[], bool oldInput[], int inputCount[], struct Sound sound);