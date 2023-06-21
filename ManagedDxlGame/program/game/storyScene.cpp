#include "DxLib.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "storyScene.h"

//ストーリー背景
int g_storyBack = 0;

//ストーリーウィンドウ
int g_storyWindow = 0;

//メッセージ流し
int g_messageRun = 0;

//少女立ち絵普通
int g_girlNormal = 0;
//少女立ち絵笑顔
int g_girlSmile = 0;
//少女立ち絵困り
int g_girlTroubled = 0;

//ストーリーシーンでの背景描画
void storyDraw() {

	//会話窓
	const int WINDOW_X_START = 60;
	const int WINDOW_Y_START = 500;
	const int WINDOW_X_END = 1200;
	const int WINDOW_Y_END = 700;

	//立ち絵描画位置
	const int GIRL_START = 100;
	const int GIRL_END = 500;

	//ストーリー背景
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);

	if (g_messageRun==0 || g_messageRun == 2 || g_messageRun == 3 || g_messageRun == 6) {
		//少女立ち絵普通
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlNormal, TRUE);
	}
	if (g_messageRun == 1 || g_messageRun==4) {
		//少女立ち絵笑顔
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlSmile, TRUE);
	}
	if (g_messageRun==5) {
		// 少女立ち絵困り
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlTroubled, TRUE);
	}
	//ストーリー会話ウィンドウ
	DrawExtendGraph(WINDOW_X_START, WINDOW_Y_START, WINDOW_X_END, WINDOW_Y_END, g_storyWindow, TRUE);
}

//エンターマーク描画
void leafBottonDrawStory(float delta_time) {

	const int BOTTON_X_START = 1050;
	const int BOTTON_Y_START = 580;
	const int BOTTON_X_END = 1150;
	const int BOTTON_Y_END = 680;
	const int PLUS = 5;

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//点滅処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 0.5f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {DrawExtendGraph(BOTTON_X_START, BOTTON_Y_START, BOTTON_X_END, BOTTON_Y_END, g_bottonEnter, true);}
	else {DrawExtendGraph(BOTTON_X_START, BOTTON_Y_START + PLUS, BOTTON_X_END, BOTTON_Y_END + PLUS, g_bottonEnter, true);}
}

//会話メッセージ
void storyMessage() {

	const int MESSAGE_X = 150;
	const int MESSAGE_Y_UP = 550;
	const int MESSAGE_Y_DOWN = 620;

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 0) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "あなた様が　かの偉大なる\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "有名な　軍師様ですね\n");
	}
	else if (g_messageRun == 1) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "ようこそ　人里離れた\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "緑の海原　へ\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "この度は　直接ご指導いただけると\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "皆　心待ちにしていたのですよ\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "ご活躍は　こちらでも耳にします\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "数多の英雄を導いた　伝説の軍師様\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "かく言う私も　楽しみで\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "昨夜は中々…\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "と　失礼いたしました\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "早速　訓練場へ案内いたしますね\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "あなた様の采配　楽しみにしていますわ\n");
	}
	else if (g_messageRun == 7) { 
		
		g_messageRun = 0;
		g_gameScene_id = GAME_TUTORIAL;
	}
}
