#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"

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

//選択されたキャラクター
int g_selectedChara = 0;

//攻撃対象の待機中キャラクター
int g_standbyChara = 0;

//アイコン画像ハンドル
int icon_sword = 0;
int icon_magic = 0;
int icon_snip = 0;
int icon_boss = 0;

//各キャラクターの情報
Character character[] = {
	//キャラ名　 職業				HP　maxHp	攻撃 防御 速さ 命中 移動	チーム	X	 Y
	{"０番",	JOB_SWORDMASTER,	300, 300,	100,  60,  20,  100,  5,	TEAM_ALLY,	36, 3},
	{"１番",	JOB_SNIPER,			200, 200,	150,  70,  15,  100,  4,	TEAM_ALLY,	34, 4},
	{"２番",	JOB_MAGICIAN,		100, 100,	200,  50,  10,  100,  4,	TEAM_ALLY,	38, 5},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	100,  60,  20,  100,  5,	TEAM_ENEMY,	31, 6},
	{"弓使い",	JOB_SNIPER,			200, 200,	150,  70,  15,  100,  4,	TEAM_ENEMY,	33, 11},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	200,  50,  10,  100,  4,	TEAM_ENEMY,	27, 1},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	100,  60,  20,  100,  5,	TEAM_ENEMY,	15, 10},
	{"弓使い",	JOB_SNIPER,			200, 200,	150,  70,  15,  100,  4,	TEAM_ENEMY,	12, 4},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	200,  50,  10,  100,  4,	TEAM_ENEMY,	9,	2},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	100,  60,  20,  100,  5,	TEAM_ENEMY,	25, 12},
	{"弓使い",	JOB_SNIPER,			200, 200,	150,  70,  15,  100,  4,	TEAM_ENEMY,	24, 6},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	100,  50,  10,  100,  4,	TEAM_ENEMY,	10, 10},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	100,  60,  20,  100,  5,	TEAM_ENEMY,	5,	6},
	{"弓使い",	JOB_SNIPER,			200, 200,	150,  70,  15,  100,  4,	TEAM_ENEMY,	5,	10},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	200,  50,  10,  100,  4,	TEAM_ENEMY,	20, 8},
	{"長",		JOB_LEADER,			400, 400,	200,  70,  20,  150,  5,	TEAM_ENEMY,	4,	3}
};

//charaDateに中身入れる。1人ずつ座標を読み取り、いない場所にはー１を返す
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

		int y = character[i].y;
		int x = character[i].x;

		if (character[i].hp > 0) {charaData[character[i].y][character[i].x] = i;}
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
		DrawStringEx(530, 570, TEXT_COLOR_WHITE, "HP：%s", hp_str.c_str());//hp
		DrawStringEx(630, 570, TEXT_COLOR_WHITE, " / %s", maxHp_str.c_str());//maxHp

		SetFontSize(20);
		if (character[chara].team == TEAM_ALLY && character[chara].done == true) { DrawStringEx(200, 540, -1, "行動終了"); }
		else if (character[chara].team == TEAM_ALLY && character[chara].done == false) { DrawStringEx(200, 540, -1, "未行動"); }

		DrawStringEx(900, 550, TEXT_COLOR_WHITE, "攻撃力：%s", attack_str.c_str());//attack
		DrawStringEx(900, 600, TEXT_COLOR_WHITE, "防御力：%s", defence_str.c_str());//defence
		DrawStringEx(900, 650, TEXT_COLOR_WHITE, "素早さ：%s", speed_str.c_str());//speed
		DrawStringEx(1100, 550, TEXT_COLOR_WHITE, "命中率：%s", hit_str.c_str());//hit
		DrawStringEx(1100, 600, TEXT_COLOR_WHITE, "移動力：%s", move_str.c_str());//move

		//アイコン表示
		if (character[chara].job == JOB_SWORDMASTER) {
			DrawExtendGraph(300, 630, 350, 680, icon_sword, true);//拡大縮小draw関数
		}
		else if (character[chara].job == JOB_SNIPER) {
			DrawExtendGraph(300, 630, 350, 680, icon_snip, true);
		}
		else if (character[chara].job == JOB_MAGICIAN) {
			DrawExtendGraph(300, 630, 350, 680, icon_magic, true);
		}
		else if (character[chara].job == JOB_LEADER) {
			DrawExtendGraph(300, 630, 350, 680, icon_boss, true);
		}
	}
}

