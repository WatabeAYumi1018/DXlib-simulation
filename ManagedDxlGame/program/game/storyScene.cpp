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

	//ストーリー背景
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);

	if (g_messageRun==0 || g_messageRun == 2 || g_messageRun == 3 || g_messageRun == 6) {
		//少女立ち絵普通
		DrawExtendGraph(100, 100, 500, 500, g_girlNormal, TRUE);
	}
	if (g_messageRun == 1 || g_messageRun==4) {
		//少女立ち絵笑顔
		DrawExtendGraph(100, 100, 500, 500, g_girlSmile, TRUE);
	}
	if (g_messageRun==5) {
		// 少女立ち絵困り
		DrawExtendGraph(100, 100, 500, 500, g_girlTroubled, TRUE);
	}
	//ストーリー会話ウィンドウ
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

void leafBottonDrawStory(float delta_time) {

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//点滅処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 1.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(1050, 580, 1150, 680, g_bottonEnter, true);
	}
}

//会話メッセージ
void storyMessage() {

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 0) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "あなたが 有名な軍師さまですね\n");

	}
	else if (g_messageRun == 1) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "ようこそ 人里離れた\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "緑の海原 へ\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "この度は 直接ご指導いただけると\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "皆 心待ちにしていたのですよ\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "ご活躍は こちらでも耳にします\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "数多の英雄を導いた 伝説の軍師さま\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "かく言う私も 楽しみで\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "昨夜は中々…\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "と 失礼いたしました\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "早速 訓練場へ案内いたしますね\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "あなた様の采配　楽しみにしていますわ\n");
	}
	else if (g_messageRun == 7) { 
		
		g_messageRun = 0;
		g_gameScene_id = GAME_TUTORIAL; }
}
