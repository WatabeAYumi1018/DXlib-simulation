#pragma once

//サイズに関する定数
const int MAP_HEIGHT = 15;		//マップ画面高さ
const int MAP_WIDTH = 40;		//マップ画面幅
const int CHIP_SIZE = 32;		//チップサイズ

extern int mapData[MAP_HEIGHT][MAP_WIDTH];

//塗りつぶしの定義
extern bool fill[MAP_HEIGHT][MAP_WIDTH];

//行動可能範囲塗りつぶし
extern int fill_map;

//カーソル座標を定義
extern int cursorX ;
extern int cursorY ;

//マップチップ画像ハンドル
extern int graphic_cell_ground;

//チップ画像ハンドル
extern int character_chips[7][12];	//キャラチップ格納配列
extern int map_chips[1][88];		//マップチップ格納配列

//マップ画面での情報描画
extern int display_map ;

//カーソル画像
extern int g_cursor ;

//三すくみ矢印画像
extern int g_relation ;
extern int g_relation_back ;

//マップ画面でのターン文字
extern int g_map_turn[1][15];

//東西南北のベクトル
extern int g_directions[][2];

//味方フェーズ変数
extern int g_phaseAlly ;

//敵フェーズ変数
extern int g_phaseEnemy;

//ターン変数
extern int g_turnMove ;

//カーソルフラグ
extern bool g_flagCursor;

//エンター押しフラグ
extern bool g_flagEnter ;

//スペース押しフラグ
extern bool g_flagEnemy ;

//バトル進行中か否かの判定フラグ
extern int g_CanAttackMove ;

//現在敵何人目か（初期値はインデックスの３）
extern int currentEnemyNumber ;

// 最小距離の味方取得
extern int nearDistanceAlly ;

//味方ターン切り替え
extern bool g_flagTurnAlly ;

//敵ターン切り替え
extern bool g_flagTurnEnemy;

//スコア変数
extern int g_score ;

//敵一斉移動フラグ
extern bool g_enemyCheckFinish ;

//地形種類
enum {
	CELL_GROUND,              //草地0
	CELL_FOREST,             //森1
	CELL_HOUSE,              //民家2
	CELL_FORT,               //砦3
	CELL_MOUNTAIN_LEFT_UP,   //山（左上）4
	CELL_MOUNTAIN_RIGHT_UP,  //山（右上）5
	CELL_MOUNTAIN_LEFT_DOWN, //山（左下）6
	CELL_MOUNTAIN_RIGHT_DOWN,//山（右下）7
	CELL_CASTLE_LEFT_UP,     //城（左上）8
	CELL_CASTLE_RIGHT_UP,    //城（右上）9
	CELL_CASTLE_LEFT_DOWN,   //城（左下）10
	CELL_CASTLE_RIGHT_DOWN,   //城（右下）11
	CELL_MAX
};

//東西南北
enum {
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_MAX
};

//音声関連
void playMusic();

//一連の流れ
void turnMove(float delta_time);

//敵フェーズの動き
void phaseEnemyMove(float delta_time, int currentEnemyNumber);

//カーソルエンター処理について
void phaseAllyMove(float delta_time);

//score表示
void scoreDraw();

//fillの初期化（これをしないと、次に選択しても前の選択情報が残ったままになってしまう）
void resetFill();

//fillの画像描画
void drawFill();

//塗りつぶしできるかどんどん判定してく
void fillCanMove(int _chara, int _x, int _y, int _move);

//情報や各フェーズでの指示文字描画処理（ここに点滅処理を加えよう）
void instructions(float delta_time);

//カーソル移動
void cursorMove();

//マップ全体の情報を読み取り、ifで各数字に対応するチップを描画する
void mapPosition(float delta_time);

//味方ターンマップ画面のボタン表記
void leafBottonDrawAllyTurnMap(float delta_time);

//敵ターンマップ画面のボタン表記
void leafBottonDrawEnemyTurnMap(float delta_time);

//回復地形の上にいたら、ターン開始時に全回復
void cellHeal();

//回復情報描画
void cellInfoDisplay();

//クラッカー描画
void clearCracker();