#pragma once

//文字の色
const int TEXT_COLOR_WHITE = -1;

//敵味方のターン分け
enum {
	TURN_ALLAY,
	TURN_ENEMY,
	TURN_MAX
};

//現在の状況が分かるようにフェーズ分け
enum {
	PHASE_SELECT_CHARACTER,
	PHASE_SET_MOVE_POSITION,
	PHASE_SELECT_ATTACK,
	PHASE_MAX
};

//フェーズ変数を作成
extern int g_phase ;

//カーソルフラグ
extern bool g_flagCursor ;

//エンター押しフラグ
extern bool g_flagEnter ;

//バトル進行中か否かの判定フラグ
extern int g_CanAttackMove;

//ターン変数
extern int g_turnMove ;

//テロップアニメーションカウント
extern float g_telopTimeCount;

//ターン切り替えフラグ
extern int g_turnFlag;

//サウンド
extern int sound_bgm_hdl;
extern int sound_se_hdl;

void phaseEnd();

void phaseMove(float delta_time);

void gameStart();
void gameMain( float delta_time );
void gameEnd();
