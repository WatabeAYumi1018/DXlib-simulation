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
	const int GAME_X_START = 0;
	const int GAME_Y_START = 0;
	const int GAME_X_END = 800;
	const int GAME_Y_END = 500;

	//立ち絵描画位置
	const int BOSS_X_START = 1200;
	const int BOSS_Y_START = 100;
	const int BOSS_X_END = 800;
	const int BOSS_Y_END = 500;

	//会話窓
	const int WINDOW_X_START = 60;
	const int WINDOW_Y_START = 500;
	const int WINDOW_X_END = 1200;
	const int WINDOW_Y_END = 700;


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 2 || g_messageRun == 13 || g_messageRun == 14 || g_messageRun == 15) {
		DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMap, false);
	}

	else if (g_messageRun == 3 || g_messageRun == 4) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapStream, false);}
	
	else if (g_messageRun == 5) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnCursor, false);}
	
	else if (g_messageRun == 6) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnSelect, false);}
	
	else if (g_messageRun == 7) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnMove, false);}
	
	else if (g_messageRun == 8) { DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialPredictionBattle, false);}
		
	else if(g_messageRun == 9 || g_messageRun == 10) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnInfoSpeed, false);}
	
	else if (g_messageRun == 11) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialEnemyTurn, false);}

	else if (g_messageRun == 12) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapEnemyTurnMove, false);}

	else if (g_messageRun == 16) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapHeal, false);}

	//長立ち絵	
	if (g_messageRun == 0 || g_messageRun == 4 || g_messageRun == 7 || g_messageRun == 11 || g_messageRun == 15) {
		DrawExtendGraph(BOSS_X_START, BOSS_Y_START, BOSS_X_END, BOSS_Y_END, g_bossSmile, TRUE);
	}
	else {DrawExtendGraph(BOSS_X_START, BOSS_Y_START, BOSS_X_END, BOSS_Y_END, g_bossNormal, TRUE);}
	
	//ストーリー会話ウィンドウ
	DrawExtendGraph(WINDOW_X_START, WINDOW_Y_START, WINDOW_X_END, WINDOW_Y_END, g_storyWindow, TRUE);
}

//チュートリアル会話メッセージ
void tutorialMessage() {

	const int MESSAGE_X =150;
	const int MESSAGE_Y_UP = 550;
	const int MESSAGE_Y_DOWN = 620;

	SetFontSize(40);

	if (g_messageRun == 0) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "長のマルグリットだ\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "軍師殿との手合わせ　光栄に思う\n");
	}
	else if (g_messageRun == 1) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "到着早々悪いが　時間が惜しい\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "訓練について　説明させてもらう\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "まずは　全体の概要だが\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "まあ　見ての通りだ\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "軍師殿に鍛えて欲しいのは　この三人\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "我が一族の　戦闘隊長だ\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "三人を導き　私を倒せ\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "軍師殿の采配があれば　造作も無かろう\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "ご存じだろうが　流れを説明しよう\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "まずは誰で攻めるか　都度選定せよ\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "各々の運動量については　データ化し\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "割り出してある　参考にしてくれ\n");
	}

	else if (g_messageRun == 7) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "敵に素早く近づき　一撃を与える\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "戦いの基本だな\n");
	}
	else if (g_messageRun == 8) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "戦地では選択ひとつが　命取りになる\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "事前に戦況を把握するのも　重要な要素だ\n");
	}
	else if (g_messageRun == 9) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "さて　我が一族は特に\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "素早さに　重きをおいている\n");
	}
	else if (g_messageRun == 10) {
		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "俊敏であれば　隙を突きやすいからな\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "５以上もあれば　追撃も可能だろう\n");
	}
	else if (g_messageRun ==11) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "全員の行動が完了したら\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "次は　こちらの番だ\n");
	}
	else if (g_messageRun == 12) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "一定の距離内に　入ってきたら\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "近くまで　移動させてもらう\n");
	}
	else if (g_messageRun == 13) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "最後は　スコアについてだ\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "当然高いほど　報酬は弾ませてもらおう\n");
	}
	else if (g_messageRun == 14) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "そうだな　例えば不利な武器で倒せば\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "より高得点を　得られるだろう\n");
	}
	else if (g_messageRun == 15) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "堅実に攻めるか　高評価を目指すかは\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "軍師殿の自由だ　全力で迎え撃とう\n");
	}
	else if (g_messageRun == 16) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "最後に　訓練場には救護班が点在している\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "上手く活用し　本懐を遂げてみせよ\n");
	}
	else if (g_messageRun == 17) {

		g_messageRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
