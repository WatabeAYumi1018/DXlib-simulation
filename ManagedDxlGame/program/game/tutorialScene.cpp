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
int g_tutorialAllyTurnInfo = 0;
//味方ターン移動先選択
int g_tutorialAllyTurnSelect = 0;
//味方ターン移動
int g_tutorialAllyTurnMove = 0;
//味方ターン敵選択
int g_tutorialAllyTurnSelectEnemy = 0;
//敵ターン
int g_tutorialEnemyTurn = 0;
//敵ターン移動
int g_tutorialEnemyTurnMove = 0;
//敵ターン攻撃呼び出し
int g_tutorialMapEnemyTurnAttack = 0;
//敵ターン終了
int g_tutorialMapEnemyTurnEnd = 0;
//戦闘画面攻撃力
int g_tutorialBattleAttack = 0;
//戦闘画面命中率
int g_tutorialBattleHit = 0;
//スコア説明
int g_tutorialScore = 0;

//長立ち絵
int g_bossNormal=0;

//チュートリアルでのメッセージおくり
int g_tutorialRun = 0;

void tutorialDraw() {

	//背景画像描画
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

	const int x_Start = 0;
	const int x_End = 800;
	const int y_Start = 0;
	const int y_End = 500;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_tutorialRun++; }

	if (g_tutorialRun == 2) {

		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMap, false);
	}
	else if (g_tutorialRun == 3) {

		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapStream, false);

	}
	else if (g_tutorialRun == 4) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnCursor, false);

	}
	else if (g_tutorialRun == 5) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelect, false);

	}
	else if (g_tutorialRun == 6) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnMove, false);

	}
	else if (g_tutorialRun == 7) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelectEnemy, false);

	}
	else if (g_tutorialRun == 8) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnInfo, false);

	}
	else if (g_tutorialRun == 9) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurn, false);

	}
	else if (g_tutorialRun == 10) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurnMove, false);

	}
	else if (g_tutorialRun == 11) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapEnemyTurnEnd, false);

	}
	else if (g_tutorialRun == 12) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialBattleAttack, false);

	}
	else if (g_tutorialRun == 13) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialBattleHit, false);

	}
	else if (g_tutorialRun == 13) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialScore, false);

	}
	else if (g_tutorialRun == 14) {

		g_tutorialRun = 0;
		g_gameScene_id = GAME_MAP;
	}

	//長立ち絵
	DrawExtendGraph(1200, 100, 800, 500, g_bossNormal, TRUE);
	//ストーリー会話ウィンドウ
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

//会話メッセージ
void tutorialMessage() {

	SetFontSize(40);

	if (g_tutorialRun == 0) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "長のマルグリットだ\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "軍師殿との手合わせ　光栄に思う\n");
	}
	else if (g_tutorialRun == 1) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "到着早々悪いが　時間が惜しい\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "訓練について　説明させてもらう\n");
	}
	else if (g_tutorialRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "まずは　全体の流れだが…\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "まあ　見ての通りだ\n");
	}
	else if (g_tutorialRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "軍師殿に鍛えて欲しいのは　この三人\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "我が一族の　戦闘隊長だ\n");
	}
	else if (g_tutorialRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "三人を導き　私を倒せ\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "軍師殿の采配があれば　造作も無かろう\n");
	}
	else if (g_tutorialRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "運動量についてだが　データ化し\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "全員の移動量を　割り出した\n");
	}
	else if (g_tutorialRun == 6) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "訓練相手に接近すれば\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "戦闘に入る\n");
	}
	else if (g_tutorialRun == 7) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "武器の相性も　重要だが\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "注目すべきは　素早さだろうな\n");
	}
	else if (g_tutorialRun == 8) {
		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "俊敏な者は　隙を突きやすい\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "５以上もあれば　追撃が可能だろう\n");
	}
	else if (g_tutorialRun == 9) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "全員の行動が完了したら\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "次は　こちらの番\n");
	}
	else if (g_tutorialRun == 10) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "敵意に応える場合は\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "逐一　ShiftEnterで合図だ\n");
	}
	else if (g_tutorialRun == 11) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "訓練後は　毎回評価をつけている\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "スコアが高いほど　報酬も弾ませてもらう\n");
	}
	else if (g_tutorialRun == 12) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "そうだな…　例えば不利な武器で倒せば\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "スコアを得やすいだろうな\n");
	}
	else if (g_tutorialRun == 13) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "どう攻めるかは　軍師殿の自由だ\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "全力でかかってこい\n");
	}
	else if (g_tutorialRun == 13) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "最後に　訓練場には救護班が点在している\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "上手く活用し　本懐を遂げてみせよ\n");
	}
	else if (g_tutorialRun == 14) {

		g_tutorialRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
