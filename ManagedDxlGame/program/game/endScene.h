#pragma once

//クリアクラッカー動画
extern int g_clearFlower;

//ゲームオーバー画面
extern int g_gameOver;

//ゲームクリア画面
extern int g_gameClear;

//ゲームオーバー画面描画
void gameOver(float delta_time);

void gameClear(float delta_time);

void scoreResult(float delta_time);