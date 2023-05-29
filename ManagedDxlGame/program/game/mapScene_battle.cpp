#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//�퓬���̉�ʃn���h��
int g_battleGround = 0;
int g_battleParaBack = 0;

//�퓬���̃p���\��
int g_battle_hp[1][35];
int g_battle_attack[1][42];
int g_battle_hit[1][25];

//�L�����A�j���[�V�����֘A
int g_charaAlly_vector = 3;		//�����L�����̌���
int g_charaEnemy_vector = 6;	//�G�L�����̌���
int g_vectorAlly_count = 1;		//�����J�E���g�ϐ�
float g_vectorEnemy_count = 1;	//�G�J�E���g�ϐ�
float g_animAlly_timeCount = 0;	//���ԕ`�摬���̐���
float g_animEnemy_timeCount = 0;//�G�`�摬���̐���

//�퓬���̍U���G�t�F�N�g
int g_battle_effect_sword[1][14];
int g_battle_effect_snip[1][14];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][14];

//�U���G�t�F�N�g�̃A�j���[�V�����n���h��
float g_effectTimeCount = 0;
int g_effectFrame = 0;

//�퓬�A�j���[�V�����̐����t���O
bool g_flagBattleAnime = true;

//HP���Z�t���O
bool g_flagBattleHp = true;

//HP�^�C���J�E���g
float g_HpTimeCount = 0;

//�G��AI�ňړ��\�͈͂ɖ��������邩����i�������j
//bool checkAllyInFill(int enemy,int ally) {
//	
//	int characterX = character[enemy].x;
//	int characterY = character[enemy].y;
//
//	for (int dir = 0; dir < DIRECTION_MAX; dir++)
//	{
//		int x = characterX + g_directions[dir][0];
//		int y = characterY + g_directions[dir][1];
//		fillCanMove(enemy, x, y, character[enemy].move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
//	
//		if (fill[y][x] && charaData[y][x] != -1) {
//				
//			if (character[charaData[y][x]].team == TEAM_ALLY) {
//					
//				return true;  // fill���͈͓̔��ɖ����L���������݂���ꍇ
//			}
//		}
//	}	
//	return false;  // fill���͈͓̔��ɖ����L���������݂��Ȃ��ꍇ
//}

//�U���\���ǂ�������
bool checkCanAllyBattle(int attack, int defence) {

	if (character[attack].team == character[defence].team) { return false; }//�������m�A�G���m�͍U���ł��Ȃ�
	if ((character[attack].hp <= 0) || (character[defence].hp <= 0)) { return false; } //�̗͂O�ȉ����s��

	else {
		int distanceX = abs(character[attack].x - character[defence].x);//absolute value�̗��B��΁@�l�B
		int distanceY = abs(character[attack].y - character[defence].y);
		if ((distanceX == 0 && distanceY == 1) || (distanceX == 1 && distanceY == 0)) { return true; }

		return false;
	}
}

//�퓬����ʂ̃O���t�B�b�N�`��
void battleGraph() {

	//�퓬�w�i���
	DrawExtendGraph(200, 0, 1000, 480, g_battleGround, true);

	//HP,ATTACK,HIT�O���t�B�b�N
	DrawGraph(590, 500, g_battle_hp[0][15], TRUE);
	DrawGraph(500, 580, g_battle_attack[0][34], TRUE);
	DrawGraph(560, 660, g_battle_hit[0][3], TRUE);
}

//�퓬���̏��`��(�U��/�h��)
void battleInfo(int attack, int defence) {

	const int ALLAY_X_START = 1100;
	const int ALLY_X_END = 1150;
	const int ENEMY_X_START = 100;
	const int ENEMY_X_END = 150;

	const int Y_START = 630;
	const int Y_END = 680;

	const int NAME_Y = 530;

	SetFontSize(30);

	//attack���̕`��
	DrawStringEx(ALLAY_X_START, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());

	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_sword, true);//�g��k��draw�֐�
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(ALLAY_X_START, Y_START, ALLY_X_END, Y_END, icon_magic, true);
	}

	//defence���̕`��
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

//�퓬����HP�`�揈��
void battleHp(int attack, int defence) {
	
	SetFontSize(60);

	if (character[attack].hp <= 0) { 
		DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, "0"); 
	}
	else {
		//attack����HP�`��
		std::string attack_Hp = std::to_string(character[attack].hp);
		DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, attack_Hp.c_str());
	}

	if (character[defence].hp <= 0) { DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }
	else {
		//defence����HP�`��
		std::string defence_Hp = std::to_string(character[defence].hp);
		DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, defence_Hp.c_str());
	}
}

//�퓬��ʂ̃L�����A�j��
void battleCharaGraphic(float delta_time, int attack, int defence) {

	//�o�g�����̃L�����A�j���[�V�������W
	const int CHARA_ALLAY_X_START = 750;	//����X�n�_
	const int CHARA_ALLAY_X_END = 850;		//����X�I�_
	const int CHARA_ENEMY_X_START = 350;	//�GX�n�_
	const int CHARA_ENEMY_X_END = 450;		//�GX�I�_
	const int CHARA_Y_START = 250;			//����Y�n�_
	const int CHARA_Y_END = 350;			//����Y�I�_

	//���t���[�������Ă�������
	g_animAlly_timeCount += delta_time;

	//���t���[�������Ă�������
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

//�퓬�G�t�F�N�g�A�j��
void battleEffectGraphic(float delta_time, int chara) {

	//�퓬�G�t�F�N�g�A�j���[�V�������W
	const int EFFECT_ALLAY_X_START = 200;	//����X�n�_
	const int EFFECT_ALLAY_X_END = 600;		//����X�I�_
	const int EFFECT_ENEMY_X_START = 580;	//�GX�n�_
	const int EFFECT_ENEMY_X_END = 980;		//�GX�I�_
	const int EFFECT_Y_START = 150;			//����Y�n�_
	const int EFFECT_Y_END = 450;			//����Y�I�_

	const int HP_ALLAY_X = 800;
	const int HP_ENEMY_X = 400;
	const int HP_Y = 500;


	if (g_flagBattleAnime) {

		//���t���[�������Ă�������
		g_effectTimeCount += delta_time;

		if (g_effectTimeCount > 0.1f) {
			g_effectFrame++;
			g_effectTimeCount = 0;

			if (g_effectFrame >= MAX_EFFECT_FRAM) {
				g_effectFrame = 0;
				g_flagBattleAnime = false;
			}
		}

		//�����{��
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SWORDMASTER) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_sword[0][g_effectFrame], true);
		}
		//�����{�|
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SNIPER) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_snip[0][g_effectFrame], true);
		}
		//�����{��
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_MAGICIAN) {

			DrawExtendGraph(EFFECT_ALLAY_X_START, EFFECT_Y_START, EFFECT_ALLAY_X_END, EFFECT_Y_END, g_battle_effect_magic[0][g_effectFrame], true);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SWORDMASTER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_sword[0][g_effectFrame], true);
		}
		//�G�{�|
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SNIPER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_snip[0][g_effectFrame], true);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_MAGICIAN) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_magic[0][g_effectFrame], true);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_LEADER) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_leader[0][g_effectFrame], true);
		}
	}
}

//���X�g����
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

//�O�����݂̊֌W
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

//�����v�Z����
int battleHit(int attack, int defence) {

	int hit = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack,defence)) {hit =character[attack].hit;}

	//�R�����ݕs���̏ꍇ
	else if (!ThreeRelation(attack, defence)) {hit = 0.1 * character[attack].hit;}

	//����ȊO�i�R�����݂̉e���Ȃ��j
	else {hit= 0.8 * character[attack].hit;}

	return hit;
}

//�o�g���S�ʂ܂Ƃ�
void battleRandom(float delta_time,int attack, int defence) {

	const int HIT_RANDOM_MIN = 0;
	const int HIT_RANDOM_MAX = 100;

	int hitRandom = rand() % (HIT_RANDOM_MAX - HIT_RANDOM_MIN + 1);	//0~100�̗���
	int hit = battleHit(attack, defence);

	//�U���~�X
	if (hit < hitRandom) {
	
		//�U���~�X�̕`��

	}
	//�U������
	else { battleHpMove(delta_time, attack, defence); }
}

//�퓬�v�Z����
int battleDamage(int attack, int defence) {

	int damage = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack, defence)) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}
	//�R�����ݕs���̏ꍇ
	else if (!ThreeRelation(attack, defence)) {

			damage = 0.5 * (character[attack].attack - character[defence].defence);	
	}
	//����ȊO�i�R�����݂̉e���Ȃ��j
	else {damage = character[attack].attack - character[defence].defence;}

	return damage;
}

//�퓬�ɂ��_���[�W�ω��̗���
void battleHpMove(float delta_time, int attack, int defence) {

	if (g_flagBattleHp) {

		//���t���[�������Ă�������
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

//�퓬�����I��
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

		//�퓬��ʉ��O���t�B�b�N�`��
		battleGraph();

		//�����HP�`��
		battleHp(g_selectedChara, g_standbyChara);

		//�퓬��ʉ����`��
		battleInfo(g_selectedChara, g_standbyChara);

		//�퓬��ʂ̃L�����A�j���[�V����
		battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);

		if (g_CanAttackMove == 1) {

			//attack���̍U���G�t�F�N�g�`��
			battleEffectGraphic(delta_time, g_selectedChara);
		}
		else if (g_CanAttackMove == 2) {//�����̍U��

			//�q�b�g�������ɂ��_���[�W����
			battleRandom(delta_time, g_selectedChara, g_standbyChara);

			if (character[g_standbyChara].hp <= 0) {

				battleExit();
				if (battleLost()) { g_gameScene_id = GAME_OVER; }
			}
		}
		else if (g_CanAttackMove == 3) {

			//defence���̍U���G�t�F�N�g�`��
			battleEffectGraphic(delta_time, g_standbyChara);
		}
		else if (g_CanAttackMove == 4) {

			//�q�b�g�������ɂ��_���[�W����
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

				//�q�b�g�������ɂ��_���[�W����
				battleRandom(delta_time, g_selectedChara, g_standbyChara);
			}
			else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

				//�q�b�g�������ɂ��_���[�W����
				battleRandom(delta_time, g_standbyChara, g_selectedChara);
			}
		}
		else if (g_CanAttackMove == 7) {

			battleExit();
			if (battleLost()) { g_gameScene_id = GAME_OVER; }
		}
	}
}
//�X�s�[�h��r
//bool battleSpeed(float delta_time, int attack, int defence) {
//
//	//attack���T�ȏ㑁���ꍇ
//
//	if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {
//
//		battleEffectGraphic(delta_time, attack);
//
//		return true;
//	}
//
//	//defence���T�ȏ㑁���ꍇ
//	else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {
//		
//		battleEffectGraphic(delta_time, defence);
//
//
//		return true;
//	}
//	return false;
//}
