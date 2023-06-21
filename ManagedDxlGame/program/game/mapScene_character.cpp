#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//概念--------------------------------------------------

//キャラクターのデータ二次元配列（マップチップとキャラチップを分けて考える）
int charaData[MAP_HEIGHT][MAP_WIDTH];

//ジョブの詳細データ
JOB jobData[] = {
	//職業		草 森 家 砦 山(左上) 山(右上) 山(左下) 山(右下) 城(左上) 城(右上) 城(左下) 城(右下)
	{"剣士",	{1, 2, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"弓使い",	{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"魔道士",	{1, 1, 1, 2,   1,		 1,		 1,		 1,		  1,		  1,		 1,		 1}	},
	{"長",		{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	}
};

//各キャラクターの情報
Character character[] = {
	//キャラ名		職業				HP　maxHp	攻撃 防御 速さ 命中 移動	チーム		X	 Y
	{"ミモザ",		JOB_SWORDMASTER,	10, 300,	150,  70,  15,  100,  6,	TEAM_ALLY,	36, 4 },
	{"アネモネ",	JOB_SNIPER,			10, 250,	100,  80,  20,  100,  5,	TEAM_ALLY,	34, 4 },
	{"アナベル",	JOB_MAGICIAN,		10, 200,	300,  60,  10,  100,  4,	TEAM_ALLY,	35, 6 },
	{"剣士",		JOB_SWORDMASTER,	200, 200,	150,  50,  15,  100,  5,	TEAM_ENEMY,	31, 6 },
	{"弓使い",		JOB_SNIPER,			150, 150,	100,  60,  20,  100,  4,	TEAM_ENEMY,	33, 11},
	{"魔道士",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	27, 1 },
	{"剣士",		JOB_SWORDMASTER,	200, 200,	150,  50,  15,  100,  5,	TEAM_ENEMY,	15, 10},
	{"弓使い",		JOB_SNIPER,			150, 150,	100,  60,  20,  100,  4,	TEAM_ENEMY,	12, 4 },
	{"魔道士",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	9,	2 },
	{"剣士",		JOB_SWORDMASTER,	200, 200,	150,  50,  15,  100,  5,	TEAM_ENEMY,	25, 12},
	{"弓使い",		JOB_SNIPER,			150, 150,	100,  60,  20,  100,  4,	TEAM_ENEMY,	24, 6 },
	{"魔道士",		JOB_MAGICIAN,		100, 100,	100,  40,  10,  100,  4,	TEAM_ENEMY,	10, 10},
	{"剣士",		JOB_SWORDMASTER,	200, 200,	150,  50,  15,  100,  5,	TEAM_ENEMY,	5,	6 },
	{"弓使い",		JOB_SNIPER,			150, 150,	100,  60,  20,  100,  4,	TEAM_ENEMY,	5,	10},
	{"魔道士",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	20, 8 },
	{"マルグリット",JOB_BOSS,			10, 300,	210,  60,  20,  100,  0,	TEAM_ENEMY,	4,	3 }
};

//変数--------------------------------------------------

//選択されたキャラクター
int g_selectedChara = 0;

//待機中敵キャラクター
int g_standbyChara = 0;

//画像ハンドル------------------------------------------

//アイコン画像ハンドル
int icon_sword = 0;
int icon_magic = 0;
int icon_snip = 0;
int icon_boss = 0;

//関数--------------------------------------------------

//charaDate定義。いなければ-１
int getCharacter(int x, int y) {

	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[y][x] == i) { return i; }//structから。０ならプレイヤー一番、１なら二番…と、対応キャラを返す
	}
	return -1; //-1なら何もいない
}

//キャラクターに常に自分の位置情報を持たせた状態で動かす。
void getCharaPosition() {

	//‐1を代入することで、すべての要素を初期化している。
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			charaData[i][j] = -1; //現状、charaData[][]の中身は初期化の状態で全てに０が入ってる。このままだと、character[0]の大量発生
		}						  //そこにー１を入れることで、それを防いでいる。
	}
	//キャラクター各々の座標を習得(自分の座標を常に自分で持つようにする(毎回更新))
	for (int i = 0; i < CHARACTER_MAX; i++) {

		int x = character[i].x;
		int y = character[i].y;

		if (character[i].hp > 0) {charaData[y][x] = i;}
	}
}

//キャラクター情報表示処理
void display() {

	//カーソルとキャラチップの画像一致で情報
	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[cursorY][cursorX] == i) { characterMapInfo(i); }
	}
}

//カーソルとキャラが一致したら、その情報を表示するようにする
void characterMapInfo(int chara) {

	//移動情報
	const int DONE_X = 250;
	const int DONE_Y = 540;
	//パラメーター情報
	const int PARAMETER_X_UP = 900;
	const int PARAMETER_X_DOWN = 1100;
	const int PARAMETER_Y_UP = 550;
	const int PARAMETER_Y_CENTER = 600;
	const int PARAMETER_Y_DOWN = 650;
	//職業アイコン
	const int ICON_X_START = 300;
	const int ICON_Y_START = 630;
	const int ICON_X_END = 350;
	const int ICON_Y_END = 680;

	if (g_flagCursor) {

		//文字描画のため、hp（int型）をconst char*型へ変換(その他各パラメータも)
		std::string hp_str = std::to_string(character[chara].hp);
		std::string maxHp_str = std::to_string(character[chara].maxHp);
		std::string attack_str = std::to_string(character[chara].attack);
		std::string defence_str = std::to_string(character[chara].defence);
		std::string speed_str = std::to_string(character[chara].speed);
		std::string hit_str = std::to_string(character[chara].hit);
		std::string move_str = std::to_string(character[chara].move);

		//ここから情報開示のための文字描画
		SetFontSize(30);
		DrawStringEx(100, 530, TEXT_COLOR_WHITE, character[chara].name.c_str());
		DrawStringEx(100, 630, TEXT_COLOR_WHITE, "職業：%s", jobData[character[chara].job].job_name.c_str());//job
		DrawStringEx(540, 580, TEXT_COLOR_WHITE, "HP：%s", hp_str.c_str());//hp
		DrawStringEx(650, 580, TEXT_COLOR_WHITE, " / %s", maxHp_str.c_str());//maxHp

		SetFontSize(20);

		if (character[chara].team == TEAM_ALLY && character[chara].done == true) { 
			DrawStringEx(DONE_X, DONE_Y, TEXT_COLOR_WHITE, "行動終了"); 
		}
		else if (character[chara].team == TEAM_ALLY && character[chara].done == false) { 
			DrawStringEx(DONE_X, DONE_Y, TEXT_COLOR_WHITE, "未行動"); 
		}

		DrawStringEx(PARAMETER_X_UP, PARAMETER_Y_UP, TEXT_COLOR_WHITE, "攻撃力：%s", attack_str.c_str());//attack
		DrawStringEx(PARAMETER_X_UP, PARAMETER_Y_CENTER, TEXT_COLOR_WHITE, "防御力：%s", defence_str.c_str());//defence
		DrawStringEx(PARAMETER_X_UP, PARAMETER_Y_DOWN, TEXT_COLOR_WHITE, "素早さ：%s", speed_str.c_str());//speed
		DrawStringEx(PARAMETER_X_DOWN, PARAMETER_Y_UP, TEXT_COLOR_WHITE, "命中率：%s", hit_str.c_str());//hit
		DrawStringEx(PARAMETER_X_DOWN, PARAMETER_Y_CENTER, TEXT_COLOR_WHITE, "移動力：%s", move_str.c_str());//move

		//アイコン表示
		if (character[chara].job == JOB_SWORDMASTER) {
			DrawExtendGraph(ICON_X_START, ICON_Y_START, ICON_X_END, ICON_Y_END, icon_sword, true);
		}
		else if (character[chara].job == JOB_SNIPER) {
			DrawExtendGraph(ICON_X_START, ICON_Y_START, ICON_X_END, ICON_Y_END, icon_snip, true);
		}
		else if (character[chara].job == JOB_MAGICIAN) {
			DrawExtendGraph(ICON_X_START, ICON_Y_START, ICON_X_END, ICON_Y_END, icon_magic, true);
		}
		else if (character[chara].job == JOB_BOSS) {
			DrawExtendGraph(ICON_X_START, ICON_Y_START, ICON_X_END, ICON_Y_END, icon_boss, true);
		}
	}
}

//隣接しているキャラ全員の情報を格納していく
std::vector<int> getAdjacentCharacters(int chara) {

	std::vector<int> adjacentAlly;

	//隣接してるかチェックし、該当していればpush
	for (int i = 0; i < CHARACTER_MAX; i++) {

		if (checkCanAllyBattle(chara, i)) {adjacentAlly.push_back(i);}
	}
	return adjacentAlly;
}