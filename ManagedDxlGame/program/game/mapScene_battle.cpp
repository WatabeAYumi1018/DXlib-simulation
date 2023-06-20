#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//�퓬���̉�ʃn���h��
int g_battleGround = 0;

//�퓬���̃p���\��
int g_battle_hp[1][35];
int g_battle_attack[1][42];
int g_battle_hit[1][25];

//�퓬���̍U���G�t�F�N�g
int g_battle_effect_sword[1][10];
int g_battle_effect_snip[1][10];
int g_battle_effect_magic[1][10];
int g_battle_effect_leader[1][10];

//�퓬�A�j���[�V�����̐����t���O
bool g_flagBattleAnime = true;

//HP���Z�t���O
bool g_flagBattleHp = true;

//------------------------------------------------------

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

	//�w�i
	const int BACK_GRAPH_START_X = 200;
	const int BACK_GRAPH_START_Y = 0;
	const int BACK_GRAPH_END_X = 1000;
	const int BACK_GRAPH_END_Y = 480;

	//�p�����[�^�[�����O���t�B�b�N
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
	
	if (ThreeRelation(attack, defence) == 0) {		//�������L���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {//�L���̏ꍇ�{�����ǌ�����
		
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * 2*(character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if(character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE){//�L���̏ꍇ�{�G�ǌ�����
		
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {	//�ǌ��Ȃ�

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence)/2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		//������
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
	}
	else if (ThreeRelation(attack, defence) == 1) {	//�������s���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {//�����ǌ�

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {//�G�ǌ�

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * 2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {																			//�ǌ�����
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence)/2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		//������
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
	}
	else if (ThreeRelation(attack, defence) == 2) {	//�L���s���Ȃ�

		//�����̗^����_���[�W
		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {	//�����ǌ�

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {//�G�ǌ�

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {																			//�ǌ�����
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
	else if (character[defence].job == JOB_BOSS) {
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
	
	//defence����HP�`��
	std::string defence_Hp = std::to_string(character[defence].hp);
	DrawStringEx(HP_ENEMY_X, HP_Y, TEXT_COLOR_WHITE, defence_Hp.c_str());
}

//�퓬��ʂ̃L�����A�j��
void battleCharaGraph(float delta_time, int attack, int defence) {

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
void battleEffectGraph(float delta_time, int chara) {

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
		if (character[chara].team == TEAM_ENEMY && character[chara].job == JOB_BOSS) {

			DrawExtendGraph(EFFECT_ENEMY_X_START, EFFECT_Y_START, EFFECT_ENEMY_X_END, EFFECT_Y_END, g_battle_effect_leader[0][g_effectFrame], true);
		}
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
	//�L���s���Ȃ�
	return 2;
}

//�����v�Z����
int battleHit(int attack, int defence) {

	int hit = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack,defence)==0) {hit = character[attack].hit;}

	//�R�����ݕs���̏ꍇ
	else if (ThreeRelation(attack, defence)==1) {hit = character[attack].hit / 2;}

	//�L���s���Ȃ�
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
	if (hit < hitRandom) {}
	//�U������
	else { 
		battleHpMove(delta_time, attack, defence); }
}

//�퓬�v�Z����
int battleDamage(int attack, int defence) {

	int damage = 0;

	//�R�����ݗL���̏ꍇ
	if (ThreeRelation(attack, defence)==0) {damage = 2 * (character[attack].attack - character[defence].defence);}
	//�R�����ݕs���̏ꍇ
	else if (ThreeRelation(attack, defence)==1) {damage =(character[attack].attack - character[defence].defence)/2;}
	//�L���s���Ȃ�
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

			if (character[defence].hp <= 0) { 
				character[defence].hp = 0; }

			g_HpTimeCount = 0;
			g_flagBattleHp = false;
		}
	}
}

//�Q�[���I�[�o�[�t���O����
bool battleLost() {

	if (character[0].hp <= 0 && character[1].hp <= 0 && character[2].hp <= 0) {return true;}

	return false;
}

//�퓬�����I��
void allyBattleExit(int chara) {

	if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

		character[chara].done = true;
		g_flagEnter = false;
		g_flagCursor = true;
		g_CanAttackMove = 0;
		g_phaseAlly = PHASE_SELECT_CHARACTER;
	}
}

//�X�R�A�ϓ�����
void scoreMove(int attack,int defence) {

	if (character[defence].team == TEAM_ENEMY && character[defence].hp <=0) {
		
		if (ThreeRelation(attack, defence) == 0) { g_score += 30; }
		else if (ThreeRelation(attack, defence) == 1) { g_score += 100; }
		else if (ThreeRelation(attack, defence) == 2) {	g_score += 70; }
	}
	else if (character[attack].team == TEAM_ALLY && character[attack].hp <= 0) { g_score -= 50; }
}

//�퓬�I�������i���܂Ƃ߁j
void battleExit(int attack,int defence) {

	scoreMove(attack, defence);
	allyBattleExit(attack);
	//g_battled = true;

	if (battleLost()) { g_gameScene_id = GAME_OVER; }
	if (character[15].hp <= 0) { g_gameScene_id = GAME_CLEAR; }
}

//�����o�g���֐�
void battleAlly(float delta_time,int attack,int defence) {

	if (g_flagEnter && !g_flagCursor) {

		//�퓬��ʉ��O���t�B�b�N�`��
		battleGraph();

		//�퓬��ʉ����`��
		battleInfo(attack, defence);

		//�����HP�`��i�ϓ�����l�̕`��j
		battleHpDraw(attack, defence);

		//�퓬��ʂ̃L�����A�j���[�V����
		battleCharaGraph(delta_time, attack, defence);

		//�{�^���`��
		leafBottonDrawAllyBattle(delta_time);

		if (g_CanAttackMove == 1) {
			
			//attack���̍U���G�t�F�N�g�`��
			battleEffectGraph(delta_time, attack);
			seBattle(attack);
		}
		else if (g_CanAttackMove == 2) {//�����̍U��

			//�q�b�g�������ɂ��_���[�W����
			battleHitRandom(delta_time, attack, defence);

			if (character[defence].hp <= 0) {battleExit(attack, defence);}
		}
		else if (g_CanAttackMove == 3) {

			//defence���̍U���G�t�F�N�g�`��
			battleEffectGraph(delta_time, defence);
			seBattle(defence);
		}
		else if (g_CanAttackMove == 4) {

			//�q�b�g�������ɂ��_���[�W����
			battleHitRandom(delta_time, defence, attack);

			if (character[attack].hp <= 0) { battleExit(attack, defence); }
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

				//�q�b�g�������ɂ��_���[�W����
				battleHitRandom(delta_time, attack, defence);

				if (character[defence].hp <= 0) { battleExit(attack, defence); }
			}
			else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

				//�q�b�g�������ɂ��_���[�W����
				battleHitRandom(delta_time, defence, attack);

				if (character[attack].hp <= 0) { battleExit(attack, defence);}
			}
		}
		else {battleExit(attack, defence);}
	}
}

//�����퓬���{�^���`��
void leafBottonDrawAllyBattle(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//���t���[�������Ă�������
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 1.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(1050, 400, 1130, 480, g_bottonEnter, true);
		DrawStringEx(1130, 430, TEXT_COLOR_WHITE, "�퓬������\n");
	}
	else {
		DrawExtendGraph(1050, 400+5, 1130, 480+5, g_bottonEnter, true);
		DrawStringEx(1130, 430 + 5, TEXT_COLOR_WHITE, "�퓬������\n");
	}
}

//�o�g������SE
void seBattle(int chara) {

	if (g_sePlay && character[chara].job == JOB_SWORDMASTER) {
	
		StopSoundMem(g_seEffectSword);
		if (CheckSoundMem(g_seEffectSword) == 0) {PlaySoundMem(g_seEffectSword, DX_PLAYTYPE_BACK, TRUE);}
	}
	if (g_sePlay && character[chara].job == JOB_SNIPER) {

		StopSoundMem(g_seEffectAllow);
		if (CheckSoundMem(g_seEffectAllow) == 0) {PlaySoundMem(g_seEffectAllow, DX_PLAYTYPE_BACK, TRUE);}
	}
	if (g_sePlay && character[chara].job == JOB_MAGICIAN) {
		
		StopSoundMem(g_seEffectMagic);
		if (CheckSoundMem(g_seEffectMagic) == 0) {PlaySoundMem(g_seEffectMagic, DX_PLAYTYPE_BACK, TRUE);}
	}
	if (g_sePlay && character[chara].job == JOB_BOSS) {

		StopSoundMem(g_seEffectBoss);
		if (CheckSoundMem(g_seEffectBoss) == 0) {PlaySoundMem(g_seEffectBoss, DX_PLAYTYPE_BACK, TRUE);}
	}
	g_sePlay = false;
}

//se�Đ�
void playSeBattle() {

	if (g_sePlay && CheckSoundMem(g_seMoveBattle) == 0) PlaySoundMem(g_seMoveBattle, DX_PLAYTYPE_BACK, TRUE);

	g_sePlay = false;
}
