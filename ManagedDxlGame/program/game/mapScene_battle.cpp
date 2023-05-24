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
int g_battle_effect_sword[1][5];
int g_battle_effect_snip[1][9];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][5];

//�U���G�t�F�N�g�̃A�j���[�V�����n���h��
float g_effectTimeCount = 0;
int g_effectFrame = 0;

//�퓬�A�j���[�V�����̐����t���O
bool g_flagBattleAnime = true;

//HP���Z�t���O
bool g_flagBattleHp = true;

//HP�^�C���J�E���g
float g_HpTimeCount = 0;

//�U���\���ǂ�������
bool checkCanBattle(int attack, int defence) {

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

	SetFontSize(30);

	//attack���̕`��
	DrawStringEx(1100, 530, -1, character[attack].name.c_str());

	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_sword, true);//�g��k��draw�֐�
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(1100, 630, 1150, 680, icon_magic, true);
	}

	//defence���̕`��
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

	//attack����HP�`��
	std::string attack_StartHp = std::to_string(character[attack].hp);
	DrawStringEx(800, 500, -1, attack_StartHp.c_str());

	//defence����HP�`��
	std::string defence_StartHp = std::to_string(character[defence].hp);
	DrawStringEx(400, 500, -1, defence_StartHp.c_str());
}

//�퓬��ʂ̃L�����A�j��
void battleCharaGraphic(float delta_time, int attack, int defence) {

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

//�퓬�G�t�F�N�g�A�j��
void battleEffectGraphic(float delta_time, int chara) {

	if (g_flagBattleAnime) {

		//���t���[�������Ă�������
		g_effectTimeCount += delta_time;
		if (g_effectTimeCount > 0.1f) {
			g_effectFrame++;
			g_effectTimeCount = 0;

			if (g_effectFrame >= MAX_ANIM_FRAM) {
				g_effectFrame = 0;
				g_flagBattleAnime = false;
			}
		}

		//�����{��
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SWORDMASTER) {

			DrawGraph(350, 250, g_battle_effect_sword[0][g_effectFrame], TRUE);
		}
		//�����{�|
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_SNIPER) {

			DrawGraph(350, 250, g_battle_effect_snip[0][g_effectFrame], TRUE);
		}
		//�����{��
		if (character[chara].team == TEAM_ALLY && character[chara].job == JOB_MAGICIAN) {

			DrawGraph(350, 250, g_battle_effect_magic[0][g_effectFrame], TRUE);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SWORDMASTER) {

			DrawGraph(750, 250, g_battle_effect_sword[0][g_effectFrame], TRUE);
		}
		//�G�{�|
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_SNIPER) {

			DrawGraph(750, 250, g_battle_effect_snip[0][g_effectFrame], TRUE);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_MAGICIAN) {

			DrawGraph(750, 250, g_battle_effect_magic[0][g_effectFrame], TRUE);
		}
		//�G�{��
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_LEADER) {

			DrawGraph(750, 250, g_battle_effect_leader[0][g_effectFrame], TRUE);
		}
	}
}

//���X�g����
void battleLost(int chara) {

	if (charaData[character[0].y][character[0].x] == -1 &&
		charaData[character[1].y][character[1].x] == -1 &&
		charaData[character[2].y][character[2].x] == -1) {

		//�Q�[���I�[�o�[�����`��
		DrawGraph(400, 100, g_map_turn[0][4], TRUE);

		//�^�C�g���V�[���ցi���x������j

	}
}

//�퓬�v�Z����
int battleCalculate(int attack, int defence) {

	int damage = 0;

	//�R�����ݗL���̏ꍇ
	if ((character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_MAGICIAN) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SNIPER)) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}

	//�R�����ݕs���̏ꍇ
	else if ((character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_SNIPER) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_MAGICIAN)) {

		damage = 0.5 * (character[attack].attack - character[defence].defence);
	}

	//����ȊO�i�R�����݂̉e���Ȃ��j
	else {

		damage = character[attack].attack - character[defence].defence;
	}

	return damage;
}

//�퓬�ɂ��_���[�W�ω��̗���
void battleMove(float delta_time, int attack, int defence) {

	SetFontSize(60);

	if (g_flagBattleHp) {

		//HP0�ɂȂ�����I��
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

		//���t���[�������Ă�������
		g_HpTimeCount += delta_time;

		if (g_HpTimeCount > 0.005f) {

			int damage = battleCalculate(attack, defence);
			character[defence].hp -= damage;

			g_HpTimeCount = 0;
			g_flagBattleHp = false;
		}
	}
}

//�X�s�[�h��r
bool battleSpeed(float delta_time, int attack, int defence) {

	//attack���T�ȏ㑁���ꍇ
	if (character[attack].speed - character[defence].speed >= 5) {
		battleMove(delta_time, attack, defence);

		return true;
	}

	//defence���T�ȏ㑁���ꍇ
	else if (character[defence].speed - character[attack].speed >= 5) {
		battleMove(delta_time, defence, attack);

		return true;
	}
	return false;
}
