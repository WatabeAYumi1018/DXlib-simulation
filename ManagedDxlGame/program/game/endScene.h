#pragma once

//クリアクラッカー動画
extern int g_clearFlower;

//ゲームオーバー画面
extern int g_gameOver;

//ゲームクリア画面
extern int g_gameClear;

//ゲームオーバー画面描画
void gameOver(float delta_time);

//ゲームクリア画面描画
void gameClear(float delta_time);

//スコア結果表示
void scoreResult(float delta_time);

//クリア後メッセージ
void clearMessage();