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

//キャラアニメーション関連
int g_charaAlly_vector = 3;		//味方キャラの向き
int g_charaEnemy_vector = 6;	//敵キャラの向き
int g_vectorAlly_count = 1;		//味方カウント変数
float g_vectorEnemy_count = 1;	//敵カウント変数
float g_animAlly_timeCount = 0;	//仲間描画速さの制御
float g_animEnemy_timeCount = 0;//敵描画速さの制御

//戦闘中の攻撃エフェクト
int g_battle_effect_sword[1][14];
int g_battle_effect_snip[1][14];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][14];

//攻撃エフェクトのアニメーションハンドル
float g_effectTimeCount = 0;
int g_effectFrame = 0;

//戦闘アニメーションの生存フラグ
bool g_flagBattleAnime = true;

//HP減算フラグ
bool g_flagBattleHp = true;

//HPタイムカウント
float g_HpTimeCount = 0;

//敵のAIで移動可能範囲に味方がいるか判定（未完成）
//bool checkAllyInFill(int enemy,int ally) {
//	
//	int characterX = character[enemy].x;
//	int characterY = character[enemy].y;
//
//	for (int dir = 0; dir < DIRECTION_MAX; dir++)
//	{
//		int x = characterX + g_directions[dir][0];
//		int y = characterY + g_directions[dir][1];
//		fillCanMove(enemy, x, y, character[enemy].move);//どんどん隣り合う場所を調査
//	
//		if (fill[y][x] && charaData[y][x] != -1) {
//				
//			if (character[charaData[y][x]].team == TEAM_ALLY) {
//					
//				return true;  // fill内の範囲内に味方キャラが存在する場合
//			}
//		}
//	}	
//	return false;  // fill内の範囲内に味方キャラが存在しない場合
//}

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

	//戦闘背景画面
	DrawExtendGraph(200, 0, 1000, 480, g_battleGround, true);

	//HP,ATTACK,HITグラフィック
	DrawGraph(590, 500, g_battle_hp[0][15], TRUE);
	DrawGraph(500, 580, g_battle_attack[0][34], TRUE);
	DrawGraph(560, 660, g_battle_hit[0][3], TRUE);
}

//戦闘中の情報描画(攻撃/防御)
void battleInfo(int attack, int defence) {

	const int ALLAY_X_START = 1100;
	const int ALLY_X_END = 1150;
	const int ENEMY_X_START = 100;
	const int ENEMY_X_END = 150;

	const int Y_START = 630;
	const int Y_END = 680;

	const int NAME_Y = 530;

	SetFontSize(30);

	//attack側の描画
	DrawStringEx(ALLAY_X_START, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());

	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_sword, true);//拡大縮小draw関数
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_magic, true);
	}

	//defence側の描画
	DrawStringEx(ENEMY_X_START, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());

	if (character[defence].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ENEMY_X_START, Y_START, ENEMY_X_END, Y_END, icon_sword, true);
	}
	else if (character[defence].job == JOB_SNIPER) {
		DrawExtendGraph(ENEMY_X_START, Y_START, ENEMY_X_END, Y_END, icon_snip, true);
	}
	else if (character[defence].job == JOB_MAGICIAN) {
		DrawExtendGraph(ENEMY_X_START, Y_START, ENEMY_X_END, Y_END, icon_magic, true);
	}
	else if (character[defence].job == JOB_LEADER) {
		DrawExtendGraph(ENEMY_X_START, Y_START, ENEMY_X_END, Y_END, icon_boss, true);
	}
}

//戦闘中のHP描画処理
void battleHp(int attack, int defence) {
	
	SetFontSize(60);

	if (character[attack].hp <= 0) { 
		DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, "0"); 
	}
	else {
		//attack側のHP描画
		std::string attack_Hp = std::to_string(character[attack].hp);
		DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, attack_Hp.c_str());
	}

	if (character[defence].hp <= 0) { DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }
	else {
		//defence側のHP描画
		std::string defence_Hp = std::to_string(character[defence].hp);
		DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, defence_Hp.c_str());
	}
}

//戦闘画面のキャラアニメ
void battleCharaGraphic(float delta_time, int attack, int defence) {

	//バトル中のキャラアニメーション座標
	const int CHARA_ALLAY_X_START = 750;	//味方X始点
	const int CHARA_ALLAY_X_END = 850;		//味方X終点
	const int CHARA_ENEMY_X_START = 350;	//敵X始点
	const int CHARA_ENEMY_X_END = 450;		//敵X終点
	const int CHARA_Y_START = 250;			//共通Y始点
	const int CHARA_Y_END = 350;			//共通Y終点

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
		DrawExtendGraph(CHARA_ALLAY_X_START, CHARA_Y_START, CHARA_ALLAY_X_END, CHARA_Y_END, character_chips[attack][g_charaAlly_vector], true);
	}

	if (character[defence].team == TEAM_ENEMY) {

		if (g_animEnemy_timeCount > 0.5f) {

			if (g_charaEnemy_vector == 8) { g_vectorEnemy_count = -1; }
			else if (g_charaEnemy_vector == 6) { g_vectorEnemy_count = 1; }

			g_charaEnemy_vector += g_vectorEnemy_count;

			g_animEnemy_timeCount = 0;
		}

		if (defence == 3 || defence == 6 || defence == 9 || defence == 12)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[3][g_charaEnemy_vector], true);
		}
		else if (defence == 4 || defence == 7 || defence == 10 || defence == 13)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[4][g_charaEnemy_vector], true);
		}
		else if (defence == 5 || defence == 8 || defence == 11 || defence == 14)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[5][g_charaEnemy_vector], true);
		}
		else if (defence == 15)
		{
			DrawExtendGraph(CHARA_ENEMY_X_START, CHARA_Y_START, CHARA_ENEMY_X_END, CHARA_Y_END, character_chips[6][g_charaEnemy_vector], true);
		}

	}
}

//戦闘エフェクトアニメ
void battleEffectGraphic(float delta_time, int chara) {

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
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_LEADER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_leader[0][g_effectFrame], true);
		}
	}
}

//ロスト処理
bool battleLost() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		int static lostCount = 0;

		if (character[g_selectedChara].hp <= 0 && character[g_selectedChara].team == TEAM_ALLY) {

			lostCount++;

			if (lostCount == CHARACTER_ALLAY_MAX) {

				g_flagGameOver = true;
				return true;
			}
		}
		return false;
	}
}

//三すくみの関係
bool ThreeRelation(int attack, int defence) {

	if ((character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_MAGICIAN) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SNIPER)) {
	
		return true;
	}

	if ((character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_SNIPER) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_MAGICIAN)) {

		return false;
	}
}

//命中計算処理
int battleHit(int attack, int defence) {

	int hit = 0;

	//３すくみ有利の場合
	if (ThreeRelation(attack,defence)) {hit =character[attack].hit;}

	//３すくみ不利の場合
	else if (!ThreeRelation(attack, defence)) {hit = 0.1 * character[attack].hit;}

	//それ以外（３すくみの影響なし）
	else {hit= 0.8 * character[attack].hit;}

	return hit;
}

//バトル全般まとめ
void battleRandom(float delta_time,int attack, int defence) {

	const int HIT_RANDOM_MIN = 0;
	const int HIT_RANDOM_MAX = 100;

	int hitRandom = rand() % (HIT_RANDOM_MAX - HIT_RANDOM_MIN + 1);	//0~100の乱数
	int hit = battleHit(attack, defence);

	//攻撃ミス
	if (hit < hitRandom) {
	
		//攻撃ミスの描画

	}
	//攻撃判定
	else { battleHpMove(delta_time, attack, defence); }
}

//戦闘計算処理
int battleDamage(int attack, int defence) {

	int damage = 0;

	//３すくみ有利の場合
	if (ThreeRelation(attack, defence)) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}
	//３すくみ不利の場合
	else if (!ThreeRelation(attack, defence)) {

			damage = 0.5 * (character[attack].attack - character[defence].defence);	
	}
	//それ以外（３すくみの影響なし）
	else {damage = character[attack].attack - character[defence].defence;}

	return damage;
}

//戦闘によるダメージ変化の流れ
void battleHpMove(float delta_time, int attack, int defence) {

	if (g_flagBattleHp) {

		//毎フレーム足していく処理
		g_HpTimeCount += delta_time;

		if (g_HpTimeCount > 0.005f) {

			int damage = battleDamage(attack, defence);
			character[defence].hp -= damage;
			if (character[defence].hp <= 0) { character[defence].hp = 0; }

			g_HpTimeCount = 0;
			g_flagBattleHp = false;
		}
	}
}

//戦闘処理終了
void battleExit() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		character[g_selectedChara].done = true;
		g_phase = PHASE_SELECT_CHARACTER;

		g_flagEnter = false;
		g_flagCursor = true;
		g_CanAttackMove = 0;
	}
}

void battle(float delta_time) {

	if (g_flagEnter && !g_flagCursor) {

		//戦闘画面下グラフィック描画
		battleGraph();

		//下画面HP描画
		battleHp(g_selectedChara, g_standbyChara);

		//戦闘画面下情報描画
		battleInfo(g_selectedChara, g_standbyChara);

		//戦闘画面のキャラアニメーション
		battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);

		if (g_CanAttackMove == 1) {

			//attack側の攻撃エフェクト描画
			battleEffectGraphic(delta_time, g_selectedChara);
		}
		else if (g_CanAttackMove == 2) {//味方の攻撃

			//ヒット率乱数によるダメージ判定
			battleRandom(delta_time, g_selectedChara, g_standbyChara);

			if (character[g_standbyChara].hp <= 0) {

				battleExit();
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
			}
		}
		else if (g_CanAttackMove == 3) {

			//defence側の攻撃エフェクト描画
			battleEffectGraphic(delta_time, g_standbyChara);
		}
		else if (g_CanAttackMove == 4) {

			//ヒット率乱数によるダメージ判定
			battleRandom(delta_time, g_standbyChara, g_selectedChara);

			if (character[g_selectedChara].hp <= 0) {

				battleExit();
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
			}
		}
		else if (g_CanAttackMove == 5) {

			if (character[g_selectedChara].speed - character[g_standbyChara].speed >= SPEED_DIFFERENCE) {

				battleEffectGraphic(delta_time, g_selectedChara);
			}
			else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

				battleEffectGraphic(delta_time, g_standbyChara);
			}
			else {
				if(tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || 
					tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) { battleExit(); }
			}
		}
		else if (g_CanAttackMove == 6) {

			if (character[g_selectedChara].speed - character[g_standbyChara].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleRandom(delta_time, g_selectedChara, g_standbyChara);
			}
			else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

				//ヒット率乱数によるダメージ判定
				battleRandom(delta_time, g_standbyChara, g_selectedChara);
			}
		}
		else if (g_CanAttackMove == 7) {

			battleExit();
			if (battleLost()) { g_gameScene_id = GAME_OVER; }
		}
	}
}
//スピード比較
//bool battleSpeed(float delta_time, int attack, int defence) {
//
//	//attackが５以上早い場合
//
//	if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {
//
//		battleEffectGraphic(delta_time, attack);
//
//		return true;
//	}
//
//	//defenceが５以上早い場合
//	else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {
//		
//		battleEffectGraphic(delta_time, defence);
//
//
//		return true;
//	}
//	return false;
//}
