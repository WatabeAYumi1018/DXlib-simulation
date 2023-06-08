#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "endScene.h"

//クリアクラッカー動画
int g_clearCracker = 0;

//ゲームオーバー画面描画
void gameOver(float delta_time) {

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

	DrawExtendGraph(BACK_START_X_Y, BACK_START_X_Y, BACK_END_X, BACK_END_Y, g_gameOver, true);
	DrawExtendGraph(TEXT_START_X_Y, TEXT_START_X_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		SetFontSize(50);
		DrawStringEx(550, 500, TEXT_COLOR_WHITE, "CLOSE");
	}
}

void gameClear(float delta_time) {

	//動画の画像サイズを取得
	int size_x;
	int size_y;

	GetGraphSize(g_clearCracker, &size_x, &size_y);

	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	screen_handle = MakeScreen(size_x, size_y, TRUE);

	// 動画の再生開始
	PlayMovieToGraph(g_clearCracker, DX_PLAYTYPE_LOOP);

	//もう一つ透過する方法として明るさクリップフィルターがある　先ほどの置換フィルターはいわゆるGBのように透過に適した素材じゃないとうまくいかない
	//こちらは「一定以上/以下の明るさの色をすべて塗りつぶす」という力強い処理ができる
	//FilterType以降の引数...比較方法（LESS/GREATER),比較する値,該当する色を塗りつぶすか,
	//塗りつぶした後の色,塗りつぶした後の色の不透明度(透明にしたいので0)
	GraphFilterBlt(g_clearCracker, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, TRUE, GetColor(0, 0, 0), 0);

	//透過処理された画像を画面いっぱいに描画
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 500;

	//テロップアニメーションカウント
	float static g_gameClearTimeCount = 0;

	//毎フレーム足していく処理
	g_gameClearTimeCount += delta_time;

	int telopFrame = g_gameClearTimeCount * TELOP_SPEED;

	//高得点ハイスコア！
	if (g_score >= 500) {
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
	}
	//上出来クリア！
	else if (g_score <= 300 && g_score >= 100) {
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
	}

	//クリア！
	else { DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true); }

	if (telopFrame >= TELOP_FRAME_MAX) {

		telopFrame = TELOP_FRAME_MAX;			//テロップの流れた距離リセット
		g_gameClearTimeCount = 0;				//テロップのカウントリセット
		//g_flagTurnAlly = false;					//味方ターンのテロップ流しは一回で完了のためfalse
	}
}