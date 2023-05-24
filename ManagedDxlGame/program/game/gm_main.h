#pragma once

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

void gameStart();
void gameMain( float delta_time );
void gameEnd();
