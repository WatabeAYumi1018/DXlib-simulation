#pragma once

//キャラクターのデータ二次元配列（マップチップとキャラチップを分けて考える）
extern int charaData[MAP_HEIGHT][MAP_WIDTH];

//味方敵概念
enum {
	TEAM_ALLY,
	TEAM_ENEMY,
	TEAM_MAX
};

//職業の種類
enum {
	JOB_SWORDMASTER, //剣士
	JOB_SNIPER, //弓
	JOB_MAGICIAN, //魔道
	JOB_LEADER, //長
	JOB_MAX
};

//ジョブの名前、移動数定義
struct JOB {
	std::string job_name;
	int moveCells[CELL_MAX]; //移動に使うマス数(CELLの種類によって移動量が変わる)
};

//ジョブの詳細データ
extern JOB jobData[];

//キャラ総数
const int CHARACTER_MAX = 16;
const int CHARACTER_ALLAY_MAX = 3;

//選択されたキャラクター
extern int g_selectedChara ;

//待機中敵キャラクター
extern int g_standbyChara ;

//アイコン画像ハンドル
extern int icon_sword;
extern int icon_magic;
extern int icon_snip ;
extern int icon_boss ;

//キャラクターの各名前、パラメータ
struct Character {
	std::string name;
	int job;
	int hp;
	int maxHp;
	int attack;
	int defence;
	int speed;
	int hit;
	int move;
	int team;
	int x; //初期位置
	int y;
	bool done; //行動済み概念
};

//struct Ally {
//
//	int job;
//	int move;
//	int x;		//座標
//	int y;
//};
//
////味方キャラの情報をvectorにて配列管理
//std::vector<Ally> allyMapList;
//
//struct Enemy {
//
//	int job;
//	int move;
//	int x;		//座標
//	int y;
//};
//
////敵キャラの情報をvectorにて配列管理
//std::vector<Enemy> enemyMapList;

//各キャラクターの情報
extern Character character[];

void mapCharaSwordAnim(float delta_time);

int getCharacter(int x, int y);

void getCharaPosition();

void characterMapInfo(int chara);

void display();

void characterMapInfo(int chara);
