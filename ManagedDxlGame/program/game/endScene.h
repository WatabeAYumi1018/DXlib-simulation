#pragma once

//ゲームオーバー----------------------------------------------------------
//
// 
//ゲームオーバー画面
extern int g_gameOver;

//ゲームオーバー画面描画
void gameOver(float delta_time);


//ゲームクリア------------------------------------------------------------
//
// 
//ゲームクリア画面
extern int g_gameClear;

//ゲームクリア画面描画
void gameClear(float delta_time);

//スコア結果表示
void scoreResult();

//クリア後メッセージ
void clearMessage();

//クリア音楽再生
void soundClear();

//ゲームオーバー音楽再生
void soundOver();