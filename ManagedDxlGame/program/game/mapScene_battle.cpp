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

//�퓬���̍U���G�t�F�N�g
int g_battle_effect_sword[1][14];
int g_battle_effect_snip[1][14];
int g_battle_effect_magic[1][14];
int g_battle_effect_leader[1][14];

//�U���~�X�̉摜
int g_battleMiss;

//�퓬�A�j���[�V�����̐����t���O
bool g_flagBattleAnime = true;

//HP���Z�t���O
bool g_flagBattleHp = true;

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
	
	//�퓬�w�i���
	DrawExtendGraph(BACK_GRAPH_START_X, BACK_GRAPH_START_Y, BACK_GRAPH_END_X, BACK_GRAPH_END_Y, g_battleGround, true);

	//HP,ATTACK,HIT�O���t�B�b�N
	DrawGraph(BATTLE_HP_X, BATTLE_HP_Y, g_battle_hp[0][15], TRUE);
	DrawGraph(BATTLE_ATTACK_X, BATTLE_ATTACK_Y, g_battle_attack[0][34], TRUE);
	DrawGraph(BATTLE_HIT_X, BATTLE_HIT_Y, g_battle_hit[0][3], TRUE);
}

//�퓬���̏��`��(�U��/�h��)
void battleInfo(int attack, int defence) {

	//���O�̕\���ʒu
	const int ALLAY_NAME_START_X = 1100;
	const int ENEMY_NAME_START_X = 100;
	const int NAME_Y = 530;

	//�U���͂̕`��ʒu
	const int ALLAY_ATTACK_X = 800;
	const int ENEMY_ATTACK_X = 400;
	const int ATTACK_Y = 580;

	//�������̕`��ʒu
	const int ALLAY_HIT_X = 800;
	const int ENEMY_HIT_X = 400;
	const int HIT_Y = 660;

	//�E�ƃA�C�R���̕`��ʒu
	const int ALLAY_ICON_START_X = 1100;
	const int ALLY_ICON_END_X = 1150;
	const int ENEMY_ICON_START_X = 100;
	const int ENEMY_ICON_END_X= 150;
	const int ICON_START_Y = 630;
	const int ICON_END_Y = 680;

	//���O�`��
	SetFontSize(30);

	DrawStringEx(ALLAY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());	//����
	DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());//�G

	//�U���͕`��
	SetFontSize(60);
	
	//�������`��
	if (ThreeRelation(attack, defence) == 0) {		//�L���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {
		
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * 2 *(character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if(character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE){
		
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
	}
	else if (ThreeRelation(attack, defence) == 1) {	//�s���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * 2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
	}
	else if (ThreeRelation(attack, defence) == 2) {	//����ȊO

		//�����̗^����_���[�W
		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());

		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
	}

	//attack���̐E�ƃA�C�R��
	if (character[attack].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_sword, true);//�g��k��draw�֐�
	}
	else if (character[attack].job == JOB_SNIPER) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_snip, true);
	}
	else if (character[attack].job == JOB_MAGICIAN) {
		DrawExtendGraph(ALLAY_NAME_START_X, ICON_START_Y, ALLY_ICON_END_X, ICON_END_Y, icon_magic, true);
	}

	//defence���̐E�ƃA�C�R��
	if (character[defence].job == JOB_SWORDMASTER) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_sword, true);
	}
	else if (character[defence].job == JOB_SNIPER) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_snip, true);
	}
	else if (character[defence].job == JOB_MAGICIAN) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_magic, true);
	}
	else if (character[defence].job == JOB_LEADER) {
		DrawExtendGraph(ENEMY_ICON_START_X, ICON_START_Y, ENEMY_ICON_END_X, ICON_END_Y, icon_boss, true);
	}
}

//�퓬����HP�`�揈��
void battleHpDraw(int attack, int defence) {
	
	const int HP_ALLAY_X = 800;
	const int HP_ENEMY_X = 400;
	const int HP_Y = 500;

	SetFontSize(60);

	//attack����HP�`��	
	std::string attack_Hp = std::to_string(character[attack].hp);
	DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, attack_Hp.c_str());
	
	if (character[attack].hp <= 0) { DrawStringEx(HP_ALLAY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }

	//defence����HP�`��
	std::string defence_Hp = std::to_string(character[defence].hp);
	DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, defence_Hp.c_str());
	
	if (character[defence].hp <= 0) { DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, "0"); }
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

	//�L�����A�j���[�V�����֘A
	int static charaAlly_vector = 3;		//�����L�����̌���
	int static charaEnemy_vector = 6;		//�G�L�����̌���
	int static vectorAlly_count = 1;		//�����J�E���g�ϐ�
	float static vectorEnemy_count = 1;		//�G�J�E���g�ϐ�
	float static animAlly_timeCount = 0;	//���ԕ`�摬���̐���
	float static animEnemy_timeCount = 0;	//�G�`�摬���̐���

	//���t���[�������Ă�������
	animAlly_timeCount += delta_time;

	//���t���[�������Ă�������
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

	//�A�j���[�V������MAX�t���[��
	const int MAX_EFFECT_FRAM = 10;

	//�U���G�t�F�N�g�̃A�j���[�V�����n���h��
	float static g_effectTimeCount = 0;
	int static g_effectFrame = 0;

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
int ThreeRelation(int attack, int defence) {

	//�L���̏ꍇ
	if ((character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_MAGICIAN) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SNIPER)) {
	
		return 0;
	}
	//�s���̏ꍇ
	if ((character[attack].job == JOB_MAGICIAN && character[defence].job == JOB_SWORDMASTER) ||
		(character[attack].job == JOB_SWORDMASTER && character[defence].job == JOB_SNIPER) ||
		(character[attack].job == JOB_SNIPER && character[defence].job == JOB_MAGICIAN)) {

		return 1;
	}
	//����ȊO
	return 2;
}

//�����v�Z����
int battleHit(int attack, int defence) {

	int hit = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack,defence)==0) {hit = character[attack].hit;}

	//�R�����ݕs���̏ꍇ
	else if (ThreeRelation(attack, defence)==1) {hit = character[attack].hit / 2;}

	//����ȊO�i�R�����݂̉e���Ȃ��j
	else if (ThreeRelation(attack, defence) == 2) {hit= character[attack].hit * 4 / 5 ;}

	return hit;
}

//�o�g���S�ʂ܂Ƃ�(�������ϓ��ɂ��U���̕ω�)
void battleHitRandom(float delta_time,int attack, int defence) {

	const int HIT_RANDOM_MIN = 0;
	const int HIT_RANDOM_MAX = 100;

	int hitRandom = rand() % (HIT_RANDOM_MAX - HIT_RANDOM_MIN + 1);	//0~100�̗���
	int hit = battleHit(attack, defence);

	//�U���~�X
	if (hit < hitRandom) {

		//�U���~�X�̕`��
		DrawRotaGraph(800, 300, 1.0f, 45, g_battleMiss, TRUE);
		
		g_CanAttackMove++;
	}
	//�U������
	else { 
		battleHpMove(delta_time, attack, defence); 
		g_CanAttackMove++;
	}
}

//�퓬�v�Z����
int battleDamage(int attack, int defence) {

	int damage = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack, defence)==0) {

		damage = 2 * (character[attack].attack - character[defence].defence);
	}
	//�R�����ݕs���̏ꍇ
	else if (ThreeRelation(attack, defence)==1) {

		damage =(character[attack].attack - character[defence].defence)/2;	
	}
	//����ȊO�i�R�����݂̉e���Ȃ��j
	else if(ThreeRelation(attack, defence) == 2){damage = character[attack].attack - character[defence].defence;}

	return damage;
}

//�퓬�ɂ��_���[�W�ω��̗���
void battleHpMove(float delta_time, int attack, int defence) {

	//HP�^�C���J�E���g
	float static g_HpTimeCount = 0;

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

//�X�R�A�ϓ�����
void scoreMove() {

	if (character[g_standbyChara].team == TEAM_ENEMY) {
		if (ThreeRelation(g_selectedChara, g_standbyChara) == 0) { g_score += 30; }
		else if (ThreeRelation(g_selectedChara, g_standbyChara) == 1) { g_score += 100; }
		else if (ThreeRelation(g_selectedChara, g_standbyChara) == 2) { g_score += 70; }
	}
	if (character[g_selectedChara].team == TEAM_ALLY ) {
	
		if (character[g_selectedChara].hp <= 0 && character[g_selectedChara].team == TEAM_ALLY) { g_score -= 50; }
	}
}

//-------------------------------------------------------------------------------------------------
//���o�g���֐��i�X�y�[�X�L�[��������g_CanAttackMove++�ŃC���N�������g����Ă����܂��B�j
//��A�̗���
//�����L�����̍U���G�t�F�N�g���_���[�W�v�Z���G�̍U���G�t�F�N�g���_���[�W�v�Z���f�������T�ȏ㑁����΁������L�����̍U���G�t�F�N�g���_���[�W�v�Z���퓬�I��
//�����A�r����HP���O�ɂȂ�@�b�b�@�f�������T�ȏ㑁���Ȃ���΁A���̎��_�Ő퓬�͏I������

void battle(float delta_time) {

	if (g_flagEnter && !g_flagCursor) {

		//�퓬��ʉ��O���t�B�b�N�`��
		battleGraph();

		//�퓬��ʉ����`��
		battleInfo(g_selectedChara, g_standbyChara);

		//�����HP�`��i�ϓ�����l�̕`��j
		battleHpDraw(g_selectedChara, g_standbyChara);

		//�퓬��ʂ̃L�����A�j���[�V����
		battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);

		if (g_CanAttackMove == 1) {

			//attack���̍U���G�t�F�N�g�`��
			battleEffectGraphic(delta_time, g_selectedChara);
		}
		else if (g_CanAttackMove == 2) {//�����̍U��

			//�q�b�g�������ɂ��_���[�W����
			battleHitRandom(delta_time, g_selectedChara, g_standbyChara);

			if (character[g_standbyChara].hp <= 0) {

				scoreMove();
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
			battleHitRandom(delta_time, g_standbyChara, g_selectedChara);

			if (character[g_selectedChara].hp <= 0) {

				scoreMove();
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
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) ||
					tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
					battleExit();
				}
			}
		}
		else if (g_CanAttackMove == 6) {

			if (character[g_selectedChara].speed - character[g_standbyChara].speed >= SPEED_DIFFERENCE) {

				//�q�b�g�������ɂ��_���[�W����
				battleHitRandom(delta_time, g_selectedChara, g_standbyChara);
			}
			else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

				//�q�b�g�������ɂ��_���[�W����
				battleHitRandom(delta_time, g_standbyChara, g_selectedChara);
			}
		}
		else {

			if (character[g_selectedChara].hp <= 0) {scoreMove();}
			battleExit();
			if (battleLost()) { g_gameScene_id = GAME_OVER; }
		}
	}
}
