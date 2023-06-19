#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"


//戦闘中の画面ハンドル
int g_battleGround = 0;
int g_battleParaBack = 0;

//戦闘中のパラ表示
int g_battle_hp[1][35];
int g_battle_attack[1][42];
int g_battle_hit[1][25];

//戦闘中の攻撃エフェクト
int g_battle_effect_sword[1][14];
int g_battle_effect_snip[1][14];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][14];

//攻撃ミスの画像
int g_battleMiss;

//戦闘アニメーションの生存フラグ
bool g_flagBattleAnime = true;

//HP減算フラグ
bool g_flagBattleHp = true;

// バトルフラグ
bool g_battleInProgress = false;

//------------------------------------------------------

//攻撃可能かどうか判定
bool checkCanAllyBattle(int attack, int defence) {

	if (character[attack].team == character[defence].team) { return false; }//味方同士、敵同士は攻撃できない
	if ((character[attack].hp <= 0) || (character[defence].hp <= 0)) { return false; } //体力０以下も不可

	else {
		int distanceX = abs(character[attack].x - character[defence].x);//absolute valueの略。絶対　値。
		int distanceY = abs(character[attack].y - character[defence].y);
		
		if ((distanceX == 0 && distanceY == 1) || (distanceX == 1 && distanceY == 0)) { return true; }
	
		return false;
	}
}

//戦闘下画面のグラフィック描画
void battleGraph() {

	const int BACK_GRAPH_START_X = 200;
	const int BACK_GRAPH_START_Y = 0;
	const int BACK_GRAPH_END_X = 1000;
	const int BACK_GRAPH_END_Y = 480;
	
	const int BATTLE_HP_X = 590;
	const int BATTLE_HP_Y = 500;
	const int BATTLE_ATTACK_X = 500;
	const int BATTLE_ATTACK_Y = 580;
	const int BATTLE_HIT_X = 560;
	const int BATTLE_HIT_Y = 660;
	
	//戦闘背景画面
	DrawExtendGraph(BACK_GRAPH_START_X, BACK_GRAPH_START_Y, BACK_GRAPH_END_X, BACK_GRAPH_END_Y, g_battleGround, true);

	//HP,ATTACK,HITグラフィック
	DrawGraph(BATTLE_HP_X, BATTLE_HP_Y, g_battle_hp[0][15], TRUE);
	DrawGraph(BATTLE_ATTACK_X, BATTLE_ATTACK_Y, g_battle_attack[0][34], TRUE);
	DrawGraph(BATTLE_HIT_X, BATTLE_HIT_Y, g_battle_hit[0][3], TRUE);
}

//戦闘中の情報描画(攻撃/防御)
void battleInfo(int attack, int defence) {

	//名前の表示位置
	const int ALLAY_NAME_START_X = 1100;
	const int ENEMY_NAME_START_X = 100;
	const int NAME_Y = 530;

	//攻撃力の描画位置
	const int ALLAY_ATTACK_X = 800;
	const int ENEMY_ATTACK_X = 400;
	const int ATTACK_Y = 580;

	//命中率の描画位置
	const int ALLAY_HIT_X = 800;
	const int ENEMY_HIT_X = 400;
	const int HIT_Y = 660;

	//職業アイコンの描画位置
	const int ALLAY_ICON_START_X = 1100;
	const int ALLY_ICON_END_X = 1150;
	const int ENEMY_ICON_START_X = 100;
	const int ENEMY_ICON_END_X= 150;
	const int ICON_START_Y = 630;
	const int ICON_END_Y = 680;

	//名前描画
	SetFontSize(30);

	DrawStringEx(ALLAY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());	//味方
	DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());//敵

	//攻撃力描画
	SetFontSize(60);
	
	//命中率描画
	if (ThreeRelation(attack, defence) == 0) {		//有利の場合

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {//有利の場合＋味方追撃あり
		
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * 2*(character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if(character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE){//有利の場合＋敵追撃あり
		
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);	//2*0.5=1.0でそのまま
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {	//追撃なし

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
	}
	else if (ThreeRelation(attack, defence) == 1) {	//不利の場合

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);	//2*0.5=1.0でそのまま
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * 2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
	}
	else if (ThreeRelation(attack, defence) == 2) {	//それ以外

		//味方の与えるダメージ
		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());

		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
	}

	//attack側の職業アイコン
	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_sword, true);//拡大縮小draw関数
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_magic, true);
	}

	//defence側の職業アイコン
	if (character[defence].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_sword, true);
	}
	else if (character[defence].job == JOB_SNIPER) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_snip, true);
	}
	else if (character[defence].job == JOB_MAGICIAN) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_magic, true);
	}
	else if (character[defence].job == JOB_BOSS) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_boss, true);
	}
}

//戦闘中のHP描画処理
void battleHpDraw(int attack, int defence) {
	
	const int HP_ALLAY_X = 800;
	const int HP_ENEMY_X = 400;
	const int HP_Y = 500;

	SetFontSize(60);

	//attack側のHP描画	
	std::string attack_Hp = std::to_string(character[attack].hp);
	DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, attack_Hp.c_str());
	
	if (character[attack].hp <= 0) { DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }

	//defence側のHP描画
	std::string defence_Hp = std::to_string(character[defence].hp);
	DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, defence_Hp.c_str());
	
	if (character[defence].hp <= 0) { DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }
}

//戦闘画面のキャラアニメ
void battleCharaGraph(float delta_time, int attack, int defence) {

	//バトル中のキャラアニメーション座標
	const int CHARA_ALLAY_X_START = 750;	//味方X始点
	const int CHARA_ALLAY_X_END = 850;		//味方X終点
	const int CHARA_ENEMY_X_START = 350;	//敵X始点
	const int CHARA_ENEMY_X_END = 450;		//敵X終点
	const int CHARA_Y_START = 250;			//共通Y始点
	const int CHARA_Y_END = 350;			//共通Y終点

	//キャラアニメーション関連
	int static charaAlly_vector = 3;		//味方キャラの向き
	int static charaEnemy_vector = 6;		//敵キャラの向き
	int static vectorAlly_count = 1;		//味方カウント変数
	float static vectorEnemy_count = 1;		//敵カウント変数
	float static animAlly_timeCount = 0;	//仲間描画速さの制御
	float static animEnemy_timeCount = 0;	//敵描画速さの制御

	//毎フレーム足していく処理
	animAlly_timeCount += delta_time;

	//毎フレーム足していく処理
	animEnemy_timeCount += delta_time;

	if (character[attack].team == TEAM_ALLY) {

		if (animAlly_timeCount > 0.5f) {

			if (charaAlly_vector == 5) { vectorAlly_count = -1; }
			else if (charaAlly_vector == 3) { vectorAlly_count = 1; }

			charaAlly_vector += vectorAlly_count;

			animAlly_timeCount = 0;

		}
		DrawExtendGraph(CHARA_ALLAY_X_START, CHARA_Y_START, CHARA_ALLAY_X_END, CHARA_Y_END, character_chips[attack][charaAlly_vector], true);
	}

	if (character[defence].team == TEAM_ENEMY) {

		if (animEnemy_timeCount > 0.5f) {

			if (charaEnemy_vector == 8) { vectorEnemy_count = -1; }
			else if (charaEnemy_vector == 6) { vectorEnemy_count = 1; }

			charaEnemy_vector += vectorEnemy_count;

			animEnemy_timeCount = 0;
		}

		if (defence == 3 || defence == 6 || defence == 9 || defence == 12)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[3][charaEnemy_vector], true);
		}
		else if (defence == 4 || defence == 7 || defence == 10 || defence == 13)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[4][charaEnemy_vector], true);
		}
		else if (defence == 5 || defence == 8 || defence == 11 || defence == 14)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[5][charaEnemy_vector], true);
		}
		else if (defence == 15)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[6][charaEnemy_vector], true);
		}
	}
}

//戦闘エフェクトアニメ
void battleEffectGraph(float delta_time, int chara) {

	//戦闘エフェクトアニメーション座標
	const int EFFECT_ALLAY_X_START = 200;	//味方X始点
	const int EFFECT_ALLAY_X_END = 600;		//味方X終点
	const int EFFECT_ENEMY_X_START = 580;	//敵X始点
	const int EFFECT_ENEMY_X_END = 980;		//敵X終点
	const int EFFECT_Y_START = 150;			//共通Y始点
	const int EFFECT_Y_END = 450;			//共通Y終点

	const int HP_ALLAY_X = 800;
	const int HP_ENEMY_X = 400;
	const int HP_Y = 500;

	//アニメーションのMAXフレーム
	const int MAX_EFFECT_FRAM = 10;

	//攻撃エフェクトのアニメーションハンドル
	float static g_effectTimeCount = 0;
	int static g_effectFrame = 0;

	if (g_flagBattleAnime) {

		//毎フレーム足していく処理
		g_effectTimeCount += delta_time;

		if (g_effectTimeCount > 0.1f) {
			g_effectFrame++;
			g_effectTimeCount = 0;

			if (g_effectFrame >= MAX_EFFECT_FRAM) {
				g_effectFrame = 0;
				g_flagBattleAnime = false;
			}
		}
		//味方＋剣
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SWORDMASTER) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_sword[0][g_effectFrame], true);
		}
		//味方＋弓
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SNIPER) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_snip[0][g_effectFrame], true);
		}
		//味方＋魔
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_MAGICIAN) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_magic[0][g_effectFrame], true);
		}
		//敵＋剣
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SWORDMASTER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_sword[0][g_effectFrame], true);
		}
		//敵＋弓
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SNIPER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_snip[0][g_effectFrame], true);
		}
		//敵＋魔
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_MAGICIAN) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_magic[0][g_effectFrame], true);
		}
		//敵＋長
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_BOSS) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_leader[0][g_effectFrame], true);
		}
	}
}

//ロスト処理
bool battleLost() {

	if (character[0].hp <= 0 && character[1].hp <= 0 && character[2].hp <= 0) {return true;}

	return false;
}

//三すくみの関係
int ThreeRelation(int attack, int defence) {

	//有利の場合
	if ((character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_MAGICIAN) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SNIPER)) {
	
		return 0;
	}
	//不利の場合
	if ((character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_SNIPER) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_MAGICIAN)) {

		return 1;
	}
	//それ以外
	return 2;
}

//命中計算処理
int battleHit(int attack, int defence) {

	int hit = 0;

	//３すくみ有利の場合
	if (ThreeRelation(attack,defence)==0) {hit = character[attack].hit;}

	//３すくみ不利の場合
	else if (ThreeRelation(attack, defence)==1) {hit = character[attack].hit / 2;}

	//それ以外（３すくみの影響なし）
	else if (ThreeRelation(attack, defence) == 2) {hit= character[attack].hit * 4 / 5 ;}

	return hit;
}

//バトル全般まとめ(命中率変動による攻撃の変化)
void battleHitRandom(float delta_time,int attack, int defence) {

	const int HIT_RANDOM_MIN = 0;
	const int HIT_RANDOM_MAX = 100;

	int hitRandom = rand() % (HIT_RANDOM_MAX - HIT_RANDOM_MIN + 1);	//0~100の乱数
	int hit = battleHit(attack, defence);

	//攻撃ミス
	if (hit < hitRandom) {

		//攻撃ミスのSE
	}
	//攻撃判定
	else { battleHpMove(delta_time, attack, defence); }
}

//戦闘計算処理
int battleDamage(int attack, int defence) {

	int damage = 0;

	//３すくみ有利の場合
	if (ThreeRelation(attack, defence)==0) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}
	//３すくみ不利の場合
	else if (ThreeRelation(attack, defence)==1) {

		damage =(character[attack].attack - character[defence].defence)/2;	
	}
	//それ以外（３すくみの影響なし）
	else if(ThreeRelation(attack, defence) == 2){
	
		damage = character[attack].attack - character[defence].defence;
	}
	return damage;
}

//戦闘によるダメージ変化の流れ
void battleHpMove(float delta_time, int attack, int defence) {

	//HPタイムカウント
	float static g_HpTimeCount = 0;

	if (g_flagBattleHp) {

		//毎フレーム足していく処理
		g_HpTimeCount += delta_time;

		if (g_HpTimeCount > 0.005f) {

			int damage = battleDamage(attack, defence);
			character[defence].hp -= damage;

			if (character[defence].hp <= 0) { 
				character[defence].hp = 0; }

			g_HpTimeCount = 0;
			g_flagBattleHp = false;
		}
	}
}

//戦闘処理終了
void allyBattleExit(int chara) {

	if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

		character[chara].done = true;
		g_flagEnter = false;
		g_flagCursor = true;
		g_CanAttackMove = 0;
		g_phaseAlly = PHASE_SELECT_CHARACTER;
	}
}

//敵からの戦闘終了
void enemyBattleExit(int attack,int defence){

	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {

		g_flagEnter = false;
		g_flagCursor = true;
		g_CanAttackMove = 0;
	}
}

//スコア変動処理
void scoreMove(int attack,int defence) {

	if (character[defence].team == TEAM_ENEMY && character[defence].hp <=0) {
		
		if (ThreeRelation(attack, defence) == 0) { g_score += 30; }
		else if (ThreeRelation(attack, defence) == 1) { g_score += 100; }
		else if (ThreeRelation(attack, defence) == 2) { g_score += 70; }
	}
	else if (character[attack].team == TEAM_ALLY && character[attack].hp <= 0) { g_score -= 50; }
}

//味方バトル関数
void battleAlly(float delta_time,int attack,int defence) {

	if (g_flagEnter && !g_flagCursor) {

		//戦闘画面下グラフィック描画
		battleGraph();

		//戦闘画面下情報描画
		battleInfo(attack, defence);

		//下画面HP描画（変動する値の描画）
		battleHpDraw(attack, defence);

		//戦闘画面のキャラアニメーション
		battleCharaGraph(delta_time, attack, defence);

		//ボタン描画
		leafBottonDrawAllyBattle(delta_time);

		if (g_CanAttackMove == 1) {
			
			//attack側の攻撃エフェクト描画
			battleEffectGraph(delta_time, attack);
			seBattle(attack);
		}
		else if (g_CanAttackMove == 2) {//味方の攻撃

			//ヒット率乱数によるダメージ判定
			battleHitRandom(delta_time, attack, defence);

			if (character[defence].hp <= 0) {

				scoreMove(attack,defence);
				allyBattleExit(attack);
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
				if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
			}
		}
		else if (g_CanAttackMove == 3) {

			//defence側の攻撃エフェクト描画
			battleEffectGraph(delta_time, defence);
			seBattle(defence);
		}
		else if (g_CanAttackMove == 4) {

			//ヒット率乱数によるダメージ判定
			battleHitRandom(delta_time, defence, attack);

			if (character[attack].hp <= 0) {

				scoreMove(attack, defence);
				allyBattleExit(attack);
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
				if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
			}
		}
		else if (g_CanAttackMove == 5) {

			if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

				battleEffectGraph(delta_time, attack);
				seBattle(attack);
			}
			else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

				battleEffectGraph(delta_time, defence);
				seBattle(defence);
			}
			else {allyBattleExit(attack);}
		}
		else if (g_CanAttackMove == 6) {

			if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleHitRandom(delta_time, attack, defence);
			}
			else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleHitRandom(delta_time, defence, attack);
			}
		}
		else {

			scoreMove(attack, defence);
			allyBattleExit(attack);
			if (battleLost()) { g_gameScene_id = GAME_OVER; }
			if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
		}
	}
}

//敵からのバトル関数
void battleEnemy(float delta_time, int attack, int defence) {

	if (g_flagEnter && !g_flagCursor) {

		//戦闘画面下グラフィック描画
		battleGraph();

		//戦闘画面下情報描画
		battleInfo(attack, defence);

		//下画面HP描画（変動する値の描画）
		battleHpDraw(attack, defence);

		//戦闘画面のキャラアニメーション
		battleCharaGraph(delta_time, attack, defence);

		//ボタン描画
		leafBottonDrawEnemyBattle(delta_time);

		if (g_CanAttackMove == 1) {

			//attack側の攻撃エフェクト描画
			battleEffectGraph(delta_time, attack);
			seBattle(attack);
		}
		else if (g_CanAttackMove == 2) {//味方の攻撃

			//ヒット率乱数によるダメージ判定
			battleHitRandom(delta_time, attack, defence);

			if (character[defence].hp <= 0) {

				scoreMove(attack, defence);
				enemyBattleExit(attack, defence);
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
				if (character[15].hp <= 0) {g_gameScene_id = GAME_CLEAR; }			
			}
		}
		else if (g_CanAttackMove == 3) {

			//defence側の攻撃エフェクト描画
			battleEffectGraph(delta_time, defence);
			seBattle(defence);
		}
		else if (g_CanAttackMove == 4) {

			//ヒット率乱数によるダメージ判定
			battleHitRandom(delta_time, defence, attack);

			if (character[attack].hp <= 0) {

				scoreMove(attack, defence);
				enemyBattleExit(attack, defence);
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
				if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
			}
		}
		else if (g_CanAttackMove == 5) {

			if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

				battleEffectGraph(delta_time, attack);
				seBattle(attack);
			}
			else if (character[defence].speed - character[defence].speed >= SPEED_DIFFERENCE) {

				battleEffectGraph(delta_time, defence);
				seBattle(defence);
			}
			else {enemyBattleExit(attack, defence);}
		}
		else if (g_CanAttackMove == 6) {

			if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleHitRandom(delta_time, attack, defence);
			}
			else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleHitRandom(delta_time, defence, attack);
			}
		}
		else {

			scoreMove(attack, defence);
			enemyBattleExit(attack, defence);
			if (battleLost()) { g_gameScene_id = GAME_OVER; }
			if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
		}
	}
}

//敵フェーズの攻撃流れ
void enemyAttack(float delta_time, int ally, int enemy) {

	for (int i = 3; i < CHARACTER_MAX; i++) {

		if (checkCanAllyBattle(ally, i)) { enemy = i; }
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		g_flagEnter = true;
		g_flagCursor = false;
		g_flagBattleAnime = true;
		g_flagBattleHp = true;
		g_CanAttackMove++;
		g_sePlay = true;
	}
	battleEnemy(delta_time, ally, enemy);
}

//味方戦闘中ボタン描画
void leafBottonDrawAllyBattle(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//毎フレーム足していく処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 1.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(1050, 400, 1130, 480, g_bottonEnter, true);
		DrawStringEx(1130, 430, TEXT_COLOR_WHITE, "戦闘おくり\n");
	}
	else {
		DrawExtendGraph(1050, 400+5, 1130, 480+5, g_bottonEnter, true);
		DrawStringEx(1130, 430 + 5, TEXT_COLOR_WHITE, "戦闘おくり\n");
	}
}

//敵戦闘中ボタン描画
void leafBottonDrawEnemyBattle(float delta_time) {
	
	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//毎フレーム足していく処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 1.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(1050, 400, 1130, 480, g_bottonSpace, true);
		DrawStringEx(1130, 430, TEXT_COLOR_WHITE, "戦闘おくり\n");
	}
	else { 
		DrawExtendGraph(1050, 400 + 5, 1130, 480 + 5, g_bottonSpace, true);
		DrawStringEx(1130, 430 + 5, TEXT_COLOR_WHITE, "戦闘おくり\n");
	}

}

//バトル中のSE
void seBattle(int chara) {

	if (g_sePlay && character[chara].job == JOB_SWORDMASTER) {
		if (CheckSoundMem(g_seEffectSword) == 0)  PlaySoundMem(g_seEffectSword, DX_PLAYTYPE_BACK, TRUE); 
	}
	if (g_sePlay && character[chara].job == JOB_SNIPER) {

		if (CheckSoundMem(g_seEffectAllow) == 0) PlaySoundMem(g_seEffectAllow, DX_PLAYTYPE_BACK, TRUE); 
	}
	if (g_sePlay && character[chara].job == JOB_MAGICIAN) {

		if (CheckSoundMem(g_seEffectMagic) == 0) PlaySoundMem(g_seEffectMagic, DX_PLAYTYPE_BACK, TRUE); 
	}
	if (g_sePlay && character[chara].job == JOB_BOSS) {

		if (CheckSoundMem(g_seEffectBoss) == 0) PlaySoundMem(g_seEffectBoss, DX_PLAYTYPE_BACK, TRUE);
	}
	g_sePlay = false;
}

//se再生
void playSeBattle() {

	if (g_sePlay && CheckSoundMem(g_seMoveBattle) == 0) PlaySoundMem(g_seMoveBattle, DX_PLAYTYPE_BACK, TRUE);

	g_sePlay = false;
}
