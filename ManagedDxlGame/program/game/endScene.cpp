#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "storyScene.h"
#include "mapScene_map.h"
#include "mapScene_battle.h"
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

	const int TEXT_START_X = 300;
	const int TEXT_END_X = 1000;
	const int TEXT_START_Y = 100;
	const int TEXT_END_Y = 200;

	float static g_gameOverTimeCount = 0;
	bool static g_gameOver_write = true;

	// 点滅処理
	g_gameOverTimeCount += delta_time;

	if (g_gameOverTimeCount > 0.5f) {
		g_gameOver_write = !g_gameOver_write;
		g_gameOverTimeCount = 0;
	}

	DrawExtendGraph(TEXT_START_X, TEXT_START_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		
		SetFontSize(50);
		DrawStringEx(580, 500, TEXT_COLOR_WHITE, "CLOSE");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {DxLib_End();}
}

//ゲームクリア画面描画
void gameClear(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameClear, TRUE);

	const int TELOP_Y_START =100;
	const int TELOP_X_END = 700;
	const int TELOP_Y_END = 200;
	int TELOP_SPEED = 200;
	const int TELOP_FRAME_MAX = 300;

	//テロップアニメーションカウント
	float static g_gameClearTimeCount = 0;

	bool static animEnd = false;

	int telopFrame = 0;

	if (!animEnd) {

		//毎フレーム足していく処理
		g_gameClearTimeCount += delta_time;

		telopFrame = g_gameClearTimeCount * TELOP_SPEED;
	}

	if (telopFrame >= TELOP_FRAME_MAX) {

		TELOP_SPEED = 1000;						//テロップの動きストップ
		g_gameClearTimeCount = 0;				//テロップのカウントリセット	
		animEnd = true;
	}
	//高得点ハイスコア！
	if (g_score >= 1000) {
		
		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
		}
		else {
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][12], true);
			scoreResult();
		}

		movieDraw();
	}
	//上出来クリア！
	else if (g_score <= 999 && g_score >= 500) {

		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
		}
		else { 
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][1], true); 
			scoreResult();
		}
		movieDraw();
	}
	//クリア！
	else {

		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true);
		}
		else { 
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][7], true); 
			scoreResult();
		}
	}
	clearMessage();
}

//スコア結果表示
void scoreResult() {

	DrawGraph(700, 400, g_battle_attack[0][17], TRUE);

	SetFontSize(80);

	std::string SCORE = std::to_string(g_score);
	DrawStringEx(1050, 390, GetColor(255, 175, 40), SCORE.c_str());

}

//クリア後メッセージ
void clearMessage() {

	//少女立ち絵笑顔
	if (g_messageRun == 0 || g_messageRun == 1 || g_messageRun == 5) {
	
		DrawExtendGraph(100, 100, 500, 500, g_girlSmile, TRUE);
	}
	
	//少女立ち絵普通
	else{DrawExtendGraph(100, 100, 500, 500, g_girlNormal, TRUE);}

	//ストーリー会話ウィンドウ
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	//高得点ハイスコア！
	if (g_score >= 1000) {
	
		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "素晴らしいです！\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "こんなにも高い評価　はじめてですわ！\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "あなた様こそ\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "唯一無二の　軍師様ですわね！\n");
		}
	}
	//上出来クリア！
	else if (g_score <= 999 && g_score >= 500) {

		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "あなた様の采配　流石の言葉しかございません\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "大変　勉強になりましたわ\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "この名誉に　恥じぬよう\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "私たちも　精進を重ねますわね！\n");
		}
	}
	else {

		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "おめでとうございます！\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "まさか　マルグリット様に打ち勝つとは\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "御見それいたしました\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "ご一緒できて　光栄でしたわ\n");
		}
	}
	if(g_messageRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "私たちの訓練は　いかがでしたでしょうか\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "何か得るものがありましたら　うれしいです\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "私たちも　今回の教えを糧として\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "これからも精進できるよう\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "一族の皆と共に　頑張りますね\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "あなたにお会いできて　本当によかった\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "またいつでも　お越しくださいね\n");
	}
	else if (g_messageRun == 6) {
	
		DxLib_End();// DXlibの終了処理
	}
}

//クリア音楽再生
void soundClear() {

	DeleteSoundMem(g_bgmMap);	//タイトル～チュートリアルまでのBGM削除

	if (CheckSoundMem(g_bgmEnding) == 0) { PlaySoundMem(g_bgmEnding, DX_PLAYTYPE_LOOP, TRUE); }
}

//ゲームオーバー音楽再生
void soundOver() {

	DeleteSoundMem(g_bgmMap);	//タイトル～チュートリアルまでのBGM削除

	if (CheckSoundMem(g_bgmGameOver) == 0) { PlaySoundMem(g_bgmGameOver, DX_PLAYTYPE_LOOP, TRUE); }


}