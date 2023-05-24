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
int g_battle_effect_sword[1][5];
int g_battle_effect_snip[1][9];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][5];

//攻撃エフェクトのアニメーションハンドル
float g_effectTimeCount = 0;
int g_effectFrame = 0;

//戦闘アニメーションの生存フラグ
bool g_flagBattleAnime = true;

//HP減算フラグ
bool g_flagBattleHp = true;

//HPタイムカウント
float g_HpTimeCount = 0;

//攻撃可能かどうか判定
bool checkCanBattle(int attack, int defence) {

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

//戦闘画面のキャラアニメ
void battleCharaGraphic(float delta_time, int attack, int defence) {

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

	if (character[defence].team == TEAM_ENEMY) {

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
void battleEffectGraphic(float delta_time, int chara) {

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
int battleCalculate(int attack, int defence) {

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
void battleMove(float delta_time, int attack, int defence) {

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
bool battleSpeed(float delta_time, int attack, int defence) {

	//attackが５以上早い場合
	if (character[attack].speed - character[defence].speed >= 5) {
		battleMove(delta_time, attack, defence);

		return true;
	}

	//defenceが５以上早い場合
	else if (character[defence].speed - character[attack].speed >= 5) {
		battleMove(delta_time, defence, attack);

		return true;
	}
	return false;
}
