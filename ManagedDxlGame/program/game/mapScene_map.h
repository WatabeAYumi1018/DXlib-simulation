#pragma once

//サイズに関する定数
const int MAP_HEIGHT = 15;		//マップ画面高さ
const int MAP_WIDTH = 40;		//マップ画面幅
const int CHIP_SIZE = 32;		//チップサイズ

//命令文の座標
const int INSTRUCTIONS_X = 700;
const int INSTRUCTIONS_Y = 10;

extern int mapData[MAP_HEIGHT][MAP_WIDTH];

//塗りつぶしの定義
extern bool fill[MAP_HEIGHT][MAP_WIDTH];

//行動可能範囲塗りつぶし
extern int fill_map;

//カーソル座標を定義
extern int cursorX ;
extern int cursorY ;

//マップチップ
extern int graphic_cell_ground;

//チップ画像
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

//fillの初期化（これをしないと、次に選択しても前の選択情報が残ったままになってしまう）
void resetFill();

//fillの画像描画
void drawFill();

//塗りつぶしできるかどんどん判定してく
void fillCanMove(int _chara, int _x, int _y, int _move);

//情報や各フェーズでの指示文字描画処理（ここに点滅処理を加えよう）
void instructions();

//カーソル移動
void cursorMove();

//マップ全体の情報を読み取り、ifで各数字に対応するチップを描画する
void mapPosition();
