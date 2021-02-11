#pragma once

//プレイヤー
void Player(int *x, int *y, bool *turn, bool input[], int map[20][30], int blockSize);

//プレイヤーの当たり判定・戻し処理
void  PlayerCollision(int *x, int *y, int width, int heigth, int *memoryX, int *memoryY, int *leftMapnumX, int *rightMapnumX, int *upMapnumY, int *downMapnumY, bool input[], int map[20][30], int blockSize);