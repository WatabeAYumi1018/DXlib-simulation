#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "endScene.h"

//ゲームオーバー画面
int g_gameOver = 0;

//ゲームクリア画面
int g_gameClear = 0;

//クリアクラッカー動画
int g_clearFlower = 0;

//ゲームオーバー画面描画
void gameOver(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameOver, TRUE);

	const int BACK_START_X_Y = 0;
	const int BACK_END_X = 1300;
	const int BACK_END_Y = 750;

	const int TEXT_START_X_Y = 200;
	const int TEXT_END_X = 1100;
	const int TEXT_END_Y = 400;

	float static g_gameOverTimeCount = 0;
	bool static g_gameOver_write = true;

	// 点滅処理
	g_gameOverTimeCount += delta_time;

	if (g_gameOverTimeCount > 0.5f) {
		g_gameOver_write = !g_gameOver_write;
		g_gameOverTimeCount = 0;
	}

	DrawExtendGraph(TEXT_START_X_Y, TEXT_START_X_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		SetFontSize(50);
		DrawStringEx(550, 500, TEXT_COLOR_WHITE, "CLOSE");
	}
}

//ゲームクリア画面描画
void gameClear(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameClear, TRUE);

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 300;

	//テロップアニメーションカウント
	float static g_gameClearTimeCount = 0;

	//毎フレーム足していく処理
	g_gameClearTimeCount += delta_time;

	int telopFrame = g_gameClearTimeCount * TELOP_SPEED;

	if (telopFrame >= TELOP_FRAME_MAX) {

		telopFrame = TELOP_FRAME_MAX;			//テロップの流れた距離リセット
		g_gameClearTimeCount = 0;				//テロップのカウントリセット	
	}

	//高得点ハイスコア！
	if (g_score >= 500) {
		
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][12], true);

		movieDraw();
	}
	//上出来クリア！
	else if (g_score <= 300 && g_score >= 100) {

		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][1], true); 

		movieDraw();
	}
	//クリア！
	else {

		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][7], true); 
	}
}
