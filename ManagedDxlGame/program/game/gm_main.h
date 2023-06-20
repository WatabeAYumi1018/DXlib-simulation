#pragma once

//ゲームシーン
extern int g_gameScene_id;

//サウンド　タイトル
extern int g_bgmTitle;
//サウンド　マップ
extern int g_bgmMap;
//サウンド　エンディング
extern int g_bgmEnding;
//サウンド　ゲームオーバー
extern int g_bgmGameOver;

//攻撃SE　弓
extern int g_seEffectAllow;
//攻撃SE　剣
extern int g_seEffectSword;
//攻撃SE　魔法
extern int g_seEffectMagic;
//攻撃SE　長
extern int g_seEffectBoss ;
//ターン移行　&&　バトル開始
extern int g_seMoveBattle ;

//ゲームシーン分け
enum {
	GAME_START,
	GAME_STORY,
	GAME_TUTORIAL,
	GAME_MAP,
	GAME_OVER,
	GAME_CLEAR
};

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

//敵のフェーズ
enum {
	PHASE_AI_SEARCH_CHARACTER,
	PHASE_AI_MOVE_CHARACTER,
	PHASE_AI_SELECT_ATTACK,
	PHASE_AI_NEXT_ENEMY
};

//エンターボタン
extern int g_bottonEnter;
//カーソルボタン
extern int g_bottonCursor;
//タブボタン
extern int g_bottonTab;
//スペースボタン
extern int g_bottonSpace;
//シフトボタン
extern int g_bottonShift;


void gameStart();
void gameMain( float delta_time );
void gameEnd();
