#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"

//
//マップ上での指示出しコード(実装予定処理一覧)
//
// -----------------------------------------------------------
//キャラクターの配置決定ok
//UIで敵のステータスを表示ok
//メニュー画面を開く(メニュー画面の作成)→本データが終わった後で
//プレイヤーターンと敵のターン
//動くマスの数を決定 OK
//キャラクターの現在地を把握する関数必要　先輩さまさま
//動いた後の選択(攻撃か待機)　攻撃を作ろう！！
//戦闘処理	下書きOK（バグ直し）
//ダメージ計算と描画	（下書きOK）
//敵味方のロスト処理	（下書きOK）
//敵からの攻撃仕掛け	（下書きOK）
// 
// 
//★味方全員動いたらターン終了
//★敵のターン
//★敵の動きAI（ボスは動かない）
//★全員の待機確認
//★味方ターンへフェーズチェンジ
//★ボス戦		（下書きOK）
//★ステージクリア
//ゲームオーバー	（下書きOK）

//サウンド鳴らし方（wav.mp3もおっけ）
//一回だけ再生命令を出す（毎フレーム命令出すと使えない）
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

//-------------------------------------------------------------------------------------------
//地形と座標の基本情報、定数
//

//サイズに関する定数
const int MAP_HEIGHT = 15;		//マップ画面高さ
const int MAP_WIDTH = 40;		//マップ画面幅
const int CHIP_SIZE = 32;		//チップサイズ
const int EFFECT_SIZE = 120;	//エフェクトサイズ

//グラスマップ全体を配列として格納
int mapData[MAP_HEIGHT][MAP_WIDTH] = {
{4,5,1,1,1,4,5,4,5,4,5,4,5,4,5,4,5,6,7,6,7,4,5,6,7,4,5,6,7,1,6,7,6,7,4,5,4,5,6,7},
{6,7,1,8,9,6,7,6,7,6,7,6,7,6,7,6,7,1,1,1,1,6,7,4,5,6,7,1,1,1,1,4,5,1,6,7,6,7,4,5},
{5,4,5,10,11,4,5,4,5,1,4,5,4,5,4,5,1,1,1,4,5,4,5,6,7,1,1,1,1,1,1,6,7,1,1,1,2,1,6,7},
{7,6,7,0,0,6,7,6,7,1,6,7,6,7,6,7,1,4,5,6,7,6,7,1,1,1,1,3,0,0,0,1,1,1,0,0,0,0,1,4},
{4,5,1,1,0,0,0,0,0,0,1,1,1,4,5,4,5,6,7,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,6},
{6,7,4,5,0,0,0,0,0,0,0,0,0,6,7,6,7,1,1,2,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,4},
{5,1,6,7,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,6},
{7,4,5,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,4},
{1,6,7,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,1,6},
{4,5,1,1,1,1,4,5,1,0,3,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
{6,7,1,4,5,1,6,7,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1},
{5,4,5,6,7,4,5,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,2,1,1,1,4},
{7,6,7,1,1,6,7,4,5,1,1,2,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,4,5,1,1,4,5,4,5,4,5,4,5,6},
{5,4,5,4,5,1,1,6,7,4,5,1,1,1,1,1,1,4,5,4,5,4,5,1,3,1,1,6,7,4,5,6,7,6,7,6,7,6,7,4},
{7,6,7,6,7,4,5,4,5,6,7,4,5,1,1,4,5,6,7,6,7,6,7,4,5,4,5,4,5,6,7,4,5,4,5,4,5,4,5,6}
};

//キャラクターのデータ二次元配列（マップチップとキャラチップを分けて考える）
int charaData[MAP_HEIGHT][MAP_WIDTH];

//塗りつぶしの定義
bool fill[MAP_HEIGHT][MAP_WIDTH];

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

//-------------------------------------------------------------------------------------------
//マップ操作での基本概念
//

//東西南北
enum {
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_MAX
};

//東西南北のベクトルを定義（向き）
int g_directions[][2] = { //空白にすると初期化子が自動的で要素数を決定してくれる。今回は[4][2]となる。
{0,-1}, //DIRECTION_NORTH
{1,0}, //DIRECTION_EAST
{0,1}, //DIRECTION_SOUTH
{-1,0} //DIRECTION_WEST
};

//現在の状況が分かるようにフェーズ分け
enum {
	PHASE_SELECT_CHARACTER,
	PHASE_SET_MOVE_POSITION,
	PHASE_SELECT_ATTACK,
	PHASE_MAX
};

//フェーズ変数を作成
int g_phase = PHASE_SELECT_CHARACTER;

//味方敵概念
enum {
	TEAM_ALLY,
	TEAM_ENEMY,
	TEAM_MAX
};

//カーソル座標を定義
int cursorX = 0;
int cursorY = 0;

//-------------------------------------------------------------------------------------------
//職業基本情報
//

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
	int moveCells[CELL_MAX]; //移動に使うマス数
};

//ジョブの詳細データ
JOB jobData[] = {
	//職業		草 森 家 砦 山(左上) 山(右上) 山(左下) 山(右下) 城(左上) 城(右上) 城(左下) 城(右下)
	{"剣士",	{1, 2, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"弓使い",	{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"魔道士",	{1, 1, 1, 2,   1,		 1,		 1,		 1,		  1,		  1,		 1,		 1}	},
	{"長",		{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	}
};

//-------------------------------------------------------------------------------------------
//キャラ基本情報
//

//キャラ総数
const int CHARACTER_MAX = 16;

//選択されたキャラクター
int g_selectedChara = 0;

//攻撃対象の待機中キャラクター
int g_standbyChara = 0;

//キャラクターの各名前、パラメータ
struct Character {
	std::string name;
	int job;
	int hp;
	int maxHp;
	int decreaseHp;
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

//各キャラクターの情報
Character character[] = {
	//キャラ名　 職業				HP　maxHp decreaseHp攻撃 防御 速さ 命中 移動	チーム	X	 Y
	{"０番",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ALLY,	36, 3},
	{"１番",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ALLY,	34, 4},
	{"２番",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ALLY,	38, 5},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	31, 6},
	{"弓使い",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	33, 11},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	27, 1},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	15, 10},
	{"弓使い",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	12, 4},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	9,	2},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	25, 12},
	{"弓使い",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	24, 6},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	10, 10},
	{"剣士",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	5,	6},
	{"弓使い",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	5,	10},
	{"魔道士",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	20, 8},
	{"長",		JOB_LEADER,			400, 400,	400,	200,  70,  20,  10,  5,	TEAM_ENEMY,	4,	3}
};


//-------------------------------------------------------------------------------------------
//グラフィックのハンドルを定義
//

//チップ画像
int character_chips[7][12];	//キャラチップ格納配列
int map_chips[1][88];		//マップチップ格納配列

//マップチップ
int graphic_cell_ground = 0;

//行動可能範囲塗りつぶし
int fill_map = 0;

//マップ画面での情報描画
int display_map = 0;

//カーソル画像
int g_cursor = 0;

//戦闘中の画面ハンドル
int g_battleGround = 0;
int g_battleParaBack = 0;

//戦闘中のパラ表示
int g_battle_hp[1][35];
int g_battle_attack[1][42];
int g_battle_hit[1][25];

//キャラアニメーション関連
int g_charaAlly_vector = 3;		//味方キャラの向き
int g_charaEnemy_vector = 6;	//敵キャラの向き
int g_vectorAlly_count = 1;		//味方カウント変数
float g_vectorEnemy_count = 1;	//敵カウント変数
float g_animAlly_timeCount = 0;	//仲間描画速さの制御
float g_animEnemy_timeCount = 0;//敵描画速さの制御

//戦闘中の攻撃エフェクト
int g_battle_effect_sword[1][5];
int g_battle_effect_snip[1][9];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][5];

//攻撃エフェクトのアニメーションハンドル
float g_effectTimeCount = 0;
int g_effectFrame = 0;

//マップ画面でのターン文字
int g_map_turn[1][15];

//アイコン画像ハンドル
int icon_sword = 0;
int icon_magic = 0;
int icon_snip = 0;
int icon_boss = 0;

//三すくみ矢印画像
int g_relation = 0;
int g_relation_back = 0;

//エンター押しフラグ
bool g_flagEnter = false;

//カーソルフラグ
bool g_flagCursor = true;

//バトル進行中か否かの判定フラグ
int g_CanAttackMove = 0;

//バトル可能か否かの判定フラグ
bool g_flagPhaseAttack = true;

//戦闘アニメーションの生存フラグ
bool g_flagBattleAnime = true;

//アニメーションのMAXフレーム
const int MAX_ANIM_FRAM = 14;

//戦闘のカット分けフラグ
float cnt_next_move = 0;

//HPタイムカウント
float g_HpTimeCount = 0;

//HP減算
bool g_flagBattleHp = true;

//------------------------------------
//

//
//基盤データ---------------------------------------
//

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
		DrawStringEx(100, 530, -1, character[chara].name.c_str());
		DrawStringEx(100, 630, -1, "職業：%s", jobData[character[chara].job].job_name.c_str());//job
		DrawStringEx(530, 570, -1, "HP：%s", hp_str.c_str());//hp
		DrawStringEx(630, 570, -1, " / %s", maxHp_str.c_str());//maxHp

		SetFontSize(20);
		if (character[chara].team == TEAM_ALLY && character[chara].done == true) { DrawStringEx(200, 540, -1, "行動終了"); }
		else if (character[chara].team == TEAM_ALLY && character[chara].done == false) { DrawStringEx(200, 540, -1, "未行動"); }

		DrawStringEx(900, 550, -1, "攻撃力：%s", attack_str.c_str());//attack
		DrawStringEx(900, 600, -1, "防御力：%s", defence_str.c_str());//defence
		DrawStringEx(900, 650, -1, "素早さ：%s", speed_str.c_str());//speed
		DrawStringEx(1100, 550, -1, "命中率：%s", hit_str.c_str());//hit
		DrawStringEx(1100, 600, -1, "移動力：%s", move_str.c_str());//move

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

		if (character[i].hp > 0) {
			
			charaData[character[i].y][character[i].x] = i;
		}
	
	}
}

//キャラクター情報表示処理
void display() {

	//カーソルとキャラチップの画像一致で情報
	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[cursorY][cursorX] == i) { characterMapInfo(i); }
	}
}

//情報や各フェーズでの指示文字描画処理（ここに点滅処理を加えよう）
void instructions() {

	//各フェーズでの指示文章描画
	switch (g_phase) {

	case PHASE_SELECT_CHARACTER:
		SetFontSize(30);
		DrawString(700, 10, "キャラクターを選んでください\n", -1);
		break;

	case PHASE_SET_MOVE_POSITION:
		SetFontSize(30);
		DrawString(700, 10, "移動先を選んでください\n", -1);
		break;

	case PHASE_SELECT_ATTACK:
		SetFontSize(30);
		DrawString(700, 10, "攻撃対象を選んでください\n", -1);
		break;
	}
}

//長を倒すとエンディング⇒クリア文字⇒タイトルへ

//地形の上に乗ると、毎ターン体力回復

//味方全員がdone=trueで敵フェーズへ移行（今までのフェーズは全部味方の処理である！）

//if敵のmove内の座標に味方が入ったら⇒味方の座標へ向かってくる⇒バトルがはじまる（関数へ）

//敵フェーズを作る。

//
//戦闘---------------------------------------------
//

//戦闘下画面のグラフィック描画
void battleGraph() {

	//戦闘背景画面
	DrawExtendGraph(200, 0, 1000, 480, g_battleGround, true);

	//HP,ATTACK,HITグラフィック
	DrawGraph(590, 500, g_battle_hp[0][15], TRUE);
	DrawGraph(500, 580, g_battle_attack[0][34], TRUE);
	DrawGraph(560, 660, g_battle_hit[0][3], TRUE);
}

//戦闘中の情報描画(攻撃/防御)
void battleInfo(int attack,int defence) {

	SetFontSize(30);

	//attack側の描画
	DrawStringEx(1100, 530, -1, character[attack].name.c_str());

	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_sword, true);//拡大縮小draw関数
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_magic, true);
	}

	//defence側の描画
	DrawStringEx(100, 530, -1, character[defence].name.c_str());

	if (character[defence].job == JOB_SWORDMASTER) {
		DrawExtendGraph(100, 630, 150, 680, icon_sword, true);
	}
	else if (character[defence].job == JOB_SNIPER) {
		DrawExtendGraph(100, 630, 150, 680, icon_snip, true);
	}
	else if (character[defence].job == JOB_MAGICIAN) {
		DrawExtendGraph(100, 630, 150, 680, icon_magic, true);
	}
	else if (character[defence].job == JOB_LEADER) {
		DrawExtendGraph(100, 630, 150, 680, icon_boss, true);
	}

	SetFontSize(60);

	//attack側のHP描画
	std::string attack_StartHp = std::to_string(character[attack].hp);
	DrawStringEx(800, 500, -1, attack_StartHp.c_str());

	//defence側のHP描画
	std::string defence_StartHp = std::to_string(character[defence].hp);
	DrawStringEx(400, 500, -1, defence_StartHp.c_str());
}

//戦闘画面の味方キャラアニメ
void battleCharaGraphic(float delta_time,int attack,int defence) {

	//毎フレーム足していく処理
	g_animAlly_timeCount += delta_time;

	//毎フレーム足していく処理
	g_animEnemy_timeCount += delta_time;

	if (character[attack].team == TEAM_ALLY) {
		
		if (g_animAlly_timeCount > 0.5f) {

			if (g_charaAlly_vector == 5) { g_vectorAlly_count = -1; }
			else if (g_charaAlly_vector == 3) { g_vectorAlly_count = 1; }

			g_charaAlly_vector += g_vectorAlly_count;

			g_animAlly_timeCount = 0;

		}
		DrawExtendGraph(750, 250, 850, 350, character_chips[attack][g_charaAlly_vector], true);
	}

	if(character[defence].team == TEAM_ENEMY) {

		if (g_animEnemy_timeCount > 0.5f) {

			if (g_charaEnemy_vector == 8) { g_vectorEnemy_count = -1; }
			else if (g_charaEnemy_vector == 6) { g_vectorEnemy_count = 1; }

			g_charaEnemy_vector += g_vectorEnemy_count;

			g_animEnemy_timeCount = 0;
		}
		DrawExtendGraph(350, 250, 450, 350, character_chips[defence][g_charaEnemy_vector], true);
	}
}

//戦闘エフェクトアニメ
void battleEffectGraphic(float delta_time,int chara) {
	
	if (g_flagBattleAnime) {

		//毎フレーム足していく処理
		g_effectTimeCount += delta_time;
		if (g_effectTimeCount > 0.1f) {
			g_effectFrame++;
			g_effectTimeCount = 0;

			if (g_effectFrame >= MAX_ANIM_FRAM) {
				g_effectFrame = 0;
				g_flagBattleAnime = false;
			}
		}

		//味方＋剣
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SWORDMASTER) {

			DrawGraph(350, 250, g_battle_effect_sword[0][g_effectFrame], TRUE);
		}
		//味方＋弓
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SNIPER) {

			DrawGraph(350, 250, g_battle_effect_snip[0][g_effectFrame], TRUE);
		}
		//味方＋魔
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_MAGICIAN) {

			DrawGraph(350, 250, g_battle_effect_magic[0][g_effectFrame], TRUE);
		}
		//敵＋剣
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SWORDMASTER) {

			DrawGraph(750, 250, g_battle_effect_sword[0][g_effectFrame], TRUE);
		}
		//敵＋弓
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SNIPER) {

			DrawGraph(750, 250, g_battle_effect_snip[0][g_effectFrame], TRUE);
		}
		//敵＋魔
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_MAGICIAN) {

			DrawGraph(750, 250, g_battle_effect_magic[0][g_effectFrame], TRUE);
		}
		//敵＋長
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_LEADER) {

			DrawGraph(750, 250, g_battle_effect_leader[0][g_effectFrame], TRUE);
		}		
	}
}

//ロスト処理
void battleLost(int chara) {

	if (charaData[character[0].y][character[0].x] == -1 &&
		charaData[character[1].y][character[1].x] == -1 &&
		charaData[character[2].y][character[2].x] == -1) {
			
		//ゲームオーバー文字描画
		DrawGraph(400, 100, g_map_turn[0][4], TRUE);

		//タイトルシーンへ（今度書くよ）

	}
}

//戦闘計算処理
int battleCalculate(int attack,int defence) {

	int damage = 0;

	//３すくみ有利の場合
	if ((character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_MAGICIAN) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SNIPER)) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}

	//３すくみ不利の場合
	else if ((character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_SNIPER) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_MAGICIAN)) {

		damage = 0.5 * (character[attack].attack - character[defence].defence);
	}

	//それ以外（３すくみの影響なし）
	else {

		damage = character[attack].attack - character[defence].defence;
	}

	return damage;
}

//戦闘によるダメージ変化の流れ
void battleMove(float delta_time,int attack, int defence) {

	SetFontSize(60);

	if (g_flagBattleHp) {

		//HP0になったら終了
		if (character[attack].hp <= 0) {
			
			character[attack].hp == 0;

			g_phase = PHASE_SELECT_CHARACTER;

			g_flagEnter = false;
			g_flagCursor = true;
			g_CanAttackMove = 0;
		}

		else if (character[defence].hp <= 0) {
		
			character[defence].hp == 0;

			g_phase = PHASE_SELECT_CHARACTER;

			g_flagEnter = false;
			g_flagCursor = true;
			g_CanAttackMove = 0;
		}

		//毎フレーム足していく処理
		g_HpTimeCount += delta_time;

		if (g_HpTimeCount > 0.005f) {
			
			int damage = battleCalculate(attack, defence);
			character[defence].hp -= damage;
			
			g_HpTimeCount = 0;
			g_flagBattleHp = false;
		}
	}
}

//スピード比較
bool battleSpeed(float delta_time,int attack, int defence) {

	//attackが５以上早い場合
	if (character[attack].speed - character[defence].speed >= 5) {
		battleMove(delta_time,attack,defence);
		
		return true;
	}

	//defenceが５以上早い場合
	else if (character[defence].speed - character[attack].speed >= 5) {
		battleMove(delta_time, defence, attack);

		return true;
	}
	return false;
}

//
//マップ画面----------------------------------------
//

//攻撃可能かどうか判定
bool checkCanBattle(int attack, int defence) {

	if (character[attack].team == character[defence].team) { return false; }//味方同士、敵同士は攻撃できない
	if ((character[attack].hp <= 0) || (character[defence].hp <= 0)) { return false; } //体力０以下も不可

	else {
		int distanceX = abs(character[attack].x - character[defence].x);//absolute valueの略。絶対　値。
		int distanceY = abs(character[attack].y - character[defence].y);
		if ((distanceX == 0 && distanceY == 1)||(distanceX == 1 && distanceY == 0)) { return true; }
		
		return false;
	}
}

//塗りつぶしできるかどんどん判定してく
void fillCanMove(int _chara, int _x, int _y, int _move) {//選択した味方キャラ、座標、移動数

	//画面外はスルー
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return; }


	//今いる場所のcell情報を取得、職業の情報と合わせてmoveCellsを取得する
	//例えば、森の上にいる場合は、職業によっては移動コスト１、２だったりする。
	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	//移動可能数が０以下、移動可能数より下なら描画不可で終了
	if (moveCost < 0 || _move < moveCost) { return; }

	//そうじゃなければ塗りつぶし可能
	fill[_y][_x] = true;

	//移動するごとにコストを使っていく
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		fillCanMove(_chara, x, y, _move);//どんどん隣り合う場所を調査
	}
}

//fillの初期化（これをしないと、次に選択しても前の選択情報が残ったままになってしまう）
void resetFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			fill[i][j] = false;

			//味方全員doneで敵フェーズへ
		}
	}
}

//fillの画像描画
void drawFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (fill[i][j]) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, fill_map, TRUE); }//塗りつぶし可能なら描画
		}
	}
}

//カーソルエンター処理について
void phaseMove(float delta_time) {

	switch (g_phase) {

		case PHASE_SELECT_CHARACTER: {

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				resetFill();

				//選択したキャラクターを囲って東西南北に1マスずつ塗りつぶし
				int chara = getCharacter(cursorX, cursorY);
				if (chara < 0) { break; } //もし負の値だったらそこにキャラはいない→塗りつぶさない

				//行動済みなら座標動かない
				//if (character[chara].done) { resetFill(); }

				//キャラがいれば(それ以外は)塗りつぶし
				else {

					for (int dir = 0; dir < DIRECTION_MAX; dir++)
					{
						int x = character[chara].x + g_directions[dir][0];
						int y = character[chara].y + g_directions[dir][1];
						fillCanMove(chara, x, y, character[chara].move);//どんどん隣り合う場所を調査
					}

					//描画内にキャラがいたら、そこは描画しない
					for (int i = 0; i < MAP_HEIGHT; i++) {
						for (int j = 0; j < MAP_WIDTH; j++) {

							int standChara = getCharacter(j, i);
							
							if (standChara >= 0 && fill[i][j]) {fill[i][j] = false;}
						}
					}

					drawFill();

					//キャラを選択したら、移動フェーズへ
					if (character[chara].team == TEAM_ALLY) {
						g_selectedChara = chara; //味方キャラを代入
						g_phase = PHASE_SET_MOVE_POSITION;
					}
					break;
				}
			}
		}
		case PHASE_SET_MOVE_POSITION: {

			drawFill();

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				//移動先の選択、完了したら選択フェーズに戻る
				if (fill[cursorY][cursorX]) {

					//移動による座標の変化
					character[g_selectedChara].x = cursorX;
					character[g_selectedChara].y = cursorY;
				
					bool checkBattleFlag = false;
				
					for (int i = 0; i < CHARACTER_MAX; i++) {

						if (checkCanBattle(g_selectedChara, i)) {
							g_standbyChara = i;
							checkBattleFlag = true;
							break;
						}
					}
				
					if (checkBattleFlag) {g_phase = PHASE_SELECT_ATTACK;}
				
					else {
						//攻撃可能キャラがいなければ、待機
						character[g_selectedChara].done = true;
						resetFill();
						g_phase = PHASE_SELECT_CHARACTER;
					}
				}
			}
			break;
		}
		case PHASE_SELECT_ATTACK: {

			if (character[g_standbyChara].x == cursorX && character[g_standbyChara].y == cursorY) {

				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

					g_flagEnter = true;
					g_flagCursor= false;
					g_flagBattleAnime = true;
					g_flagBattleHp = true;
					g_CanAttackMove ++;
				}

				if (g_flagEnter && !g_flagCursor) {

					//戦闘画面下グラフィック描画
					battleGraph();
					
					//戦闘画面下情報描画
					battleInfo(g_selectedChara, g_standbyChara);

					//戦闘画面のキャラアニメーション
					battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);
								
					if (g_CanAttackMove == 1) {

						//attack側の攻撃エフェクト描画
						battleEffectGraphic(delta_time, g_selectedChara);
					}

					else if (g_CanAttackMove == 2) {//味方の攻撃
						
						//HP計算
						battleMove(delta_time, g_selectedChara, g_standbyChara);

						//defence側
						std::string defence_StartHp = std::to_string(character[g_standbyChara].hp);
						DrawStringEx(400, 500, -1, defence_StartHp.c_str());
					}
					
					else if (g_CanAttackMove == 3) {

						//defence側の攻撃エフェクト描画
						battleEffectGraphic(delta_time, g_standbyChara);
					}
					
					else if(g_CanAttackMove == 4) {

						//HP計算
						battleMove(delta_time, g_standbyChara, g_selectedChara);

						//defence側
						std::string attack_StartHp = std::to_string(character[g_selectedChara].hp);
						DrawStringEx(800, 500, -1, attack_StartHp.c_str());

					}
					else if (g_CanAttackMove == 5) {
					
						if (character[g_selectedChara].speed - character[g_standbyChara].speed >= 5) {
							
							battleMove(delta_time, g_selectedChara, g_standbyChara);
						}

						else if(character[g_standbyChara].speed - character[g_selectedChara].speed >= 5){

								battleMove(delta_time, g_standbyChara, g_selectedChara);
						}

						character[g_selectedChara].done = true;
						g_phase = PHASE_SELECT_CHARACTER;

						g_flagEnter = false;
						g_flagCursor = true;
						g_CanAttackMove = 0;

						break;
					}
				}

			}
			//else if (character[g_selectedChara].x == cursorX && character[g_selectedChara].y == cursorY) {
			//	//自分を選択で待機
			//	character[g_selectedChara].done = true;
			//	resetFill();
			//	g_phase = PHASE_SELECT_CHARACTER;
			//}
		break;
		}
	}
}

//カーソル移動
void cursorMove() {
	if (g_flagCursor) {
	
		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1){ cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0)				{ cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1){ cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0)				{ cursorX--; }

		WaitTimer(100);
	}
}

//マップ全体の情報を読み取り、ifで各数字に対応するチップを描画する
void mapPosition() {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			//草地マップの描画（下地）
			DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][0], TRUE);

			//マップチップ描画
			if (mapData[i][j] == 1) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][9], TRUE); }
			else if (mapData[i][j] == 2)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][56], TRUE); }
			else if (mapData[i][j] == 3)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][73], TRUE); }
			else if (mapData[i][j] == 4)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][32], TRUE); }
			else if (mapData[i][j] == 5)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][33], TRUE); }
			else if (mapData[i][j] == 6)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][40], TRUE); }
			else if (mapData[i][j] == 7)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][41], TRUE); }
			else if (mapData[i][j] == 8)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][51], TRUE); }
			else if (mapData[i][j] == 9)  { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][52], TRUE); }
			else if (mapData[i][j] == 10) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][59], TRUE); }
			else if (mapData[i][j] == 11) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][60], TRUE); }

			//キャラチップ描画
			if(charaData[i][j] >= 0){

				if (charaData[i][j] == 0) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[0][1], TRUE); }
				else if (charaData[i][j] == 1) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[1][1], TRUE); }
				else if (charaData[i][j] == 2) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[2][1], TRUE); }

				else if (charaData[i][j] == 3 || charaData[i][j] == 6 || charaData[i][j] == 9 || charaData[i][j] == 12)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[3][1], TRUE);
				}
				else if (charaData[i][j] == 4 || charaData[i][j] == 7 || charaData[i][j] == 10 || charaData[i][j] == 13)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[4][1], TRUE);
				}
				else if (charaData[i][j] == 5 || charaData[i][j] == 8 || charaData[i][j] == 11 || charaData[i][j] == 14)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[5][1], TRUE);
				}
				else if (charaData[i][j] == 15)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[6][1], TRUE);
				}
			}
			//マップ上でのキャラ情報画面描画
			DrawExtendGraph(0, 500, 1400, 730, display_map, true);

			//三すくみ関連画像描画
			DrawExtendGraph(0, 370, 125, 480, g_relation_back, true);
			DrawGraph(15, 370, g_relation, TRUE);
			DrawExtendGraph(0, 370, 40, 410, icon_sword, true);
			DrawExtendGraph(35, 440, 75, 480, icon_magic, true);
			DrawExtendGraph(85, 390, 125, 430, icon_snip, true);

			
			//現在の選択カーソルの位置を描画
			if (j == cursorX && i == cursorY) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, g_cursor, TRUE); }
		}
	}
}

void gameStart() {
	srand(time(0));

	SetWindowText("ファイアーエムブレムっぽいもの");

	//音楽の出力--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlibリファレンス、ループ処理の引数

	//SEの出力
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//画像の出力--------------------------------------------
	//マップデータ
	LoadDivGraph("graphics/pipo-map001.png", 88, 8, 11, CHIP_SIZE, CHIP_SIZE, map_chips[0]);

	//キャラ
	LoadDivGraph("graphics/player1.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[0]);
	LoadDivGraph("graphics/player2.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[1]);
	LoadDivGraph("graphics/player3.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[2]);
	LoadDivGraph("graphics/enemy1.png",	  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[3]);
	LoadDivGraph("graphics/enemy2.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[4]);
	LoadDivGraph("graphics/enemy3.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[5]);
	LoadDivGraph("graphics/enemyBOSS.png",12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[6]);

	//カーソル
	g_cursor = LoadGraph("graphics/cursor.png");
	
	//マップ上での情報表示用（下画面）
	display_map = LoadGraph("graphics/mapInfo.png"); 
	
	//マップ上での行動可能範囲
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//攻撃画面の背景
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//攻撃中の下画面
	LoadDivGraph("graphics/battleHp.png",		35, 5, 7, 120, 60, g_battle_hp[0]);
	LoadDivGraph("graphics/battleAttack.png",	42, 3, 14,300, 60, g_battle_attack[0]);
	LoadDivGraph("graphics/battleHit.png",		25, 5, 5, 180, 60, g_battle_hit[0]);
	
	//攻撃エフェクトアニメーション
	LoadDivGraph("graphics/effect_sword.png", 5, 5, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_sword[0]);
	LoadDivGraph("graphics/effect_snip.png",  9, 9, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_snip[0]);
	LoadDivGraph("graphics/effect_magic.png",14,14, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_magic[0]);
	LoadDivGraph("graphics/effect_leader.png",5, 5, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_leader[0]);

	//職業アイコン
	icon_sword= LoadGraph("graphics/iconSWORD.png");
	icon_magic= LoadGraph("graphics/iconMAGIC.png");
	icon_snip=LoadGraph("graphics/iconSNIP.png");
	icon_boss= LoadGraph("graphics/iconBOSS.png");

	//三すくみエフェクト
	g_relation_back= LoadGraph("graphics/relationBack.png");
	g_relation = LoadGraph("graphics/relation.png");

	//マップ画面でのターン文字
	LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます,60FPS
void gameMain(float delta_time) {

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_BACK); //DXlibリファレンス、ループ処理の引数
	//}//サウンドで選ぶのは、ループかバックのみ！ノーマルは選ばないで！！（ノーマルはプログラム処理を止めてしまう）

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
	//	StopSoundMem(sound_bgm_hdl);//Aを押すとサウンドが止まる
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //X押すと途中から再生がはじまる
	//}

	//曲を途中から再生する
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);

	getCharaPosition();
	mapPosition();
	display();
	cursorMove();//＜<resetFill()/drawFill())＜getCharacter(,)/return→fillCanMove(,,,)
	instructions();
	phaseMove(delta_time);

}
//
////------------------------------------------------------------------------------------------------------------
//// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


//棒グラフでのダメージ減算描画
//DrawExtendで、ダメージ受けたら（フラグ管理）その分を減らす（描画のサイズを変える）