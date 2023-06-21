#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "storyScene.h"
#include "tutorialScene.h"
#include "mapScene_battle.h"

//チュートリアル専用画像----------------
// 
//マップ全体図
int g_tutorialMap = 0;
//ゲーム目的
int g_tutorialMapStream = 0;
//味方ターンカーソル
int g_tutorialAllyTurnCursor = 0;
//下画面情報
int g_tutorialAllyTurnInfoSpeed = 0;
//味方ターン移動先選択
int g_tutorialAllyTurnSelect = 0;
//味方ターン移動
int g_tutorialAllyTurnMove = 0;
//味方ターン攻撃予測
int g_tutorialPredictionBattle = 0;
//敵ターン切り替え
int g_tutorialEnemyTurn = 0;
//敵ターン動き
int g_tutorialMapEnemyTurnMove = 0;
//回復スポットの説明
int g_tutorialMapHeal = 0;

//長立ち絵
int g_bossNormal=0;
int g_bossSmile = 0;

//チュートリアル画像描画
void tutorialDraw() {

	//背景画像描画
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

	//ゲーム画面描画位置
	const int x_Start = 0;
	const int x_End = 800;
	const int y_Start = 0;
	const int y_End = 500;

	//立ち絵描画位置
	const int boss_x_Start = 1200;
	const int boss_y_Start = 100;
	const int boss_x_End = 800;
	const int boss_y_End = 500;

	//会話窓
	const int window_x_Start = 60;
	const int window_y_Start = 500;
	const int window_x_End = 1200;
	const int window_y_End = 700;


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 2 || g_messageRun == 13 || g_messageRun == 14 || g_messageRun == 15) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMap, false);
	}

	else if (g_messageRun == 3 || g_messageRun == 4) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapStream, false);}
	
	else if (g_messageRun == 5) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnCursor, false);}
	
	else if (g_messageRun == 6) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelect, false);}
	
	else if (g_messageRun == 7) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnMove, false);}
	
	else if (g_messageRun == 8) { DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialPredictionBattle, false);}
		
	else if(g_messageRun == 9 || g_messageRun == 10) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnInfoSpeed, false);}
	
	else if (g_messageRun == 11) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurn, false);}

	else if (g_messageRun == 12) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapEnemyTurnMove, false);}

	else if (g_messageRun == 16) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapHeal, false);}

	//長立ち絵	
	if (g_messageRun == 0 || g_messageRun == 4 || g_messageRun == 7 || g_messageRun == 11 || g_messageRun == 15) {
		DrawExtendGraph(boss_x_Start, boss_y_Start, boss_x_End, boss_y_End, g_bossSmile, TRUE);
	}
	else {DrawExtendGraph(boss_x_Start, boss_y_Start, boss_x_End, boss_y_End, g_bossNormal, TRUE);}
	
	//ストーリー会話ウィンドウ
	DrawExtendGraph(window_x_Start, window_y_Start, window_x_End, window_y_End, g_storyWindow, TRUE);
}

//チュートリアル会話メッセージ
void tutorialMessage() {

	const int messageX =150;
	const int messageYUp = 550;
	const int messageYDown = 620;

	SetFontSize(40);

	if (g_messageRun == 0) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "長のマルグリットだ\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "軍師殿との手合わせ　光栄に思う\n");
	}
	else if (g_messageRun == 1) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "到着早々悪いが　時間が惜しい\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "訓練について　説明させてもらう\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "まずは　全体の概要だが\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "まあ　見ての通りだ\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "軍師殿に鍛えて欲しいのは　この三人\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "我が一族の　戦闘隊長だ\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "三人を導き　私を倒せ\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "軍師殿の采配があれば　造作も無かろう\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "ご存じだろうが　流れを説明しよう\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "まずは誰で攻めるか　都度選定せよ\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "各々の運動量については　データ化し\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "割り出してある　参考にしてくれ\n");
	}

	else if (g_messageRun == 7) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "敵に素早く近づき　一撃を与える\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "戦いの基本だな\n");
	}
	else if (g_messageRun == 8) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "戦地では選択ひとつが　命取りになる\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "事前に戦況を把握するのも　重要な要素だ\n");
	}
	else if (g_messageRun == 9) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "さて　我が一族は特に\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "素早さに　重きをおいている\n");
	}
	else if (g_messageRun == 10) {
		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "俊敏であれば　隙を突きやすいからな\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "５以上もあれば　追撃も可能だろう\n");
	}
	else if (g_messageRun ==11) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "全員の行動が完了したら\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "次は　こちらの番だ\n");
	}
	else if (g_messageRun == 12) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "一定の距離内に　入ってきたら\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "近くまで　移動させてもらう\n");
	}
	else if (g_messageRun == 13) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "最後は　スコアについてだ\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "当然高いほど　報酬は弾ませてもらおう\n");
	}
	else if (g_messageRun == 14) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "そうだな　例えば不利な武器で倒せば\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "より高得点を　得られるだろう\n");
	}
	else if (g_messageRun == 15) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "堅実に攻めるか　高評価を目指すかは\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "軍師殿の自由だ　全力で迎え撃とう\n");
	}
	else if (g_messageRun == 16) {

		DrawStringEx(messageX, messageYUp, -TEXT_COLOR_WHITE, "最後に　訓練場には救護班が点在している\n");
		DrawStringEx(messageX, messageYDown, -TEXT_COLOR_WHITE, "上手く活用し　本懐を遂げてみせよ\n");
	}
	else if (g_messageRun == 17) {

		g_messageRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
