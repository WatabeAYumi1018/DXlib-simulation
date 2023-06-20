#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//�L�����N�^�[�̃f�[�^�񎟌��z��i�}�b�v�`�b�v�ƃL�����`�b�v�𕪂��čl����j
int charaData[MAP_HEIGHT][MAP_WIDTH];

//�W���u�̏ڍ׃f�[�^
JOB jobData[] = {
	//�E��		�� �X �� �� �R(����) �R(�E��) �R(����) �R(�E��) ��(����) ��(�E��) ��(����) ��(�E��)
	{"���m",	{1, 2, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"�|�g��",	{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"�����m",	{1, 1, 1, 2,   1,		 1,		 1,		 1,		  1,		  1,		 1,		 1}	},
	{"��",		{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	}
};

//�I�����ꂽ�L�����N�^�[
int g_selectedChara = 0;

//�ҋ@���G�L�����N�^�[
int g_standbyChara = 0;

//�A�C�R���摜�n���h��
int icon_sword = 0;
int icon_magic = 0;
int icon_snip = 0;
int icon_boss = 0;

//�e�L�����N�^�[�̏��
Character character[] = {
	//�L������		�E��				HP�@maxHp	�U�� �h�� ���� ���� �ړ�	�`�[��		X	 Y
	{"�~���U",		JOB_SWORDMASTER,	300, 300,	150,  80,  15,  100,  6,	TEAM_ALLY,	36, 4},
	{"�A�l���l",	JOB_SNIPER,			250, 250,	100,  90,  20,  100,  5,	TEAM_ALLY,	34, 4},
	{"�A�i�x��",	JOB_MAGICIAN,		200, 200,	250,  70,  10,  100,  4,	TEAM_ALLY,	35, 6},
	{"���m",		JOB_SWORDMASTER,	200, 200,	100,  50,  15,  100,  5,	TEAM_ENEMY,	31, 5},
	{"�|�g��",		JOB_SNIPER,			150, 150,	150,  60,  15,  100,  4,	TEAM_ENEMY,	33, 11},
	{"�����m",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	27, 1},
	{"���m",		JOB_SWORDMASTER,	200, 200,	100,  50,  15,  100,  5,	TEAM_ENEMY,	15, 10},
	{"�|�g��",		JOB_SNIPER,			150, 150,	150,  60,  15,  100,  4,	TEAM_ENEMY,	12, 4},
	{"�����m",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	9,	2},
	{"���m",		JOB_SWORDMASTER,	200, 200,	100,  50,  15,  100,  5,	TEAM_ENEMY,	25, 12},
	{"�|�g��",		JOB_SNIPER,			150, 150,	150,  60,  15,  100,  4,	TEAM_ENEMY,	24, 6},
	{"�����m",		JOB_MAGICIAN,		100, 100,	100,  40,  10,  100,  4,	TEAM_ENEMY,	10, 10},
	{"���m",		JOB_SWORDMASTER,	200, 200,	100,  50,  15,  100,  5,	TEAM_ENEMY,	5,	6},
	{"�|�g��",		JOB_SNIPER,			150, 150,	150,  60,  15,  100,  4,	TEAM_ENEMY,	5,	10},
	{"�����m",		JOB_MAGICIAN,		100, 100,	200,  40,  10,  100,  4,	TEAM_ENEMY,	20, 8},
	{"�}���O���b�g",JOB_BOSS,			300,  300,	200,  70,  15,  100,  0,	TEAM_ENEMY,	4,	3}
};

//charaDate��`�B���Ȃ����-�P
int getCharacter(int x, int y) {

	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[y][x] == i) { return i; }//struct����B�O�Ȃ�v���C���[��ԁA�P�Ȃ��ԁc�ƁA�Ή��L������Ԃ�
	}
	return -1; //-1�Ȃ牽�����Ȃ�
}

//�L�����N�^�[�ɏ�Ɏ����̈ʒu��������������Ԃœ������B
void getCharaPosition() {

	//�]1�������邱�ƂŁA���ׂĂ̗v�f�����������Ă���B
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			charaData[i][j] = -1; //����AcharaData[][]�̒��g�͏������̏�ԂőS�ĂɂO�������Ă�B���̂܂܂��ƁAcharacter[0]�̑�ʔ���
		}						  //�����Ɂ[�P�����邱�ƂŁA�����h���ł���B
	}
	//�L�����N�^�[�e�X�̍��W���K��(�����̍��W����Ɏ����Ŏ��悤�ɂ���(����X�V))
	for (int i = 0; i < CHARACTER_MAX; i++) {

		int x = character[i].x;
		int y = character[i].y;

		if (character[i].hp > 0) {charaData[y][x] = i;}
	}
}

//�L�����N�^�[���\������
void display() {

	//�J�[�\���ƃL�����`�b�v�̉摜��v�ŏ��
	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[cursorY][cursorX] == i) { characterMapInfo(i); }
	}
}

//�J�[�\���ƃL��������v������A���̏���\������悤�ɂ���
void characterMapInfo(int chara) {

	if (g_flagCursor) {

		//�����`��̂��߁Ahp�iint�^�j��const char*�^�֕ϊ�(���̑��e�p�����[�^��)
		std::string hp_str = std::to_string(character[chara].hp);
		std::string maxHp_str = std::to_string(character[chara].maxHp);
		std::string attack_str = std::to_string(character[chara].attack);
		std::string defence_str = std::to_string(character[chara].defence);
		std::string speed_str = std::to_string(character[chara].speed);
		std::string hit_str = std::to_string(character[chara].hit);
		std::string move_str = std::to_string(character[chara].move);

		//����������J���̂��߂̕����`��
		SetFontSize(30);
		DrawStringEx(100, 530, TEXT_COLOR_WHITE, character[chara].name.c_str());
		DrawStringEx(100, 630, TEXT_COLOR_WHITE, "�E�ƁF%s", jobData[character[chara].job].job_name.c_str());//job
		DrawStringEx(540, 580, TEXT_COLOR_WHITE, "HP�F%s", hp_str.c_str());//hp
		DrawStringEx(650, 580, TEXT_COLOR_WHITE, " / %s", maxHp_str.c_str());//maxHp

		SetFontSize(20);
		if (character[chara].team == TEAM_ALLY && character[chara].done == true) { DrawStringEx(250, 540, TEXT_COLOR_WHITE, "�s���I��"); }
		else if (character[chara].team == TEAM_ALLY && character[chara].done == false) { DrawStringEx(250, 540, TEXT_COLOR_WHITE, "���s��"); }

		DrawStringEx(900, 550, TEXT_COLOR_WHITE, "�U���́F%s", attack_str.c_str());//attack
		DrawStringEx(900, 600, TEXT_COLOR_WHITE, "�h��́F%s", defence_str.c_str());//defence
		DrawStringEx(900, 650, TEXT_COLOR_WHITE, "�f�����F%s", speed_str.c_str());//speed
		DrawStringEx(1100, 550, TEXT_COLOR_WHITE, "�������F%s", hit_str.c_str());//hit
		DrawStringEx(1100, 600, TEXT_COLOR_WHITE, "�ړ��́F%s", move_str.c_str());//move

		//�A�C�R���\��
		if (character[chara].job == JOB_SWORDMASTER) {DrawExtendGraph(300, 630, 350, 680, icon_sword, true);}
		else if (character[chara].job == JOB_SNIPER) {DrawExtendGraph(300, 630, 350, 680, icon_snip, true);}
		else if (character[chara].job == JOB_MAGICIAN) {DrawExtendGraph(300, 630, 350, 680, icon_magic, true);}
		else if (character[chara].job == JOB_BOSS) {DrawExtendGraph(300, 630, 350, 680, icon_boss, true);}
	}
}

//�אڂ��Ă���L�����S���̏����i�[���Ă���
std::vector<int> getAdjacentCharacters(int enemy) {

	std::vector<int> adjacentAlly;

	//�אڂ��Ă邩�`�F�b�N���A�Y�����Ă����push
	for (int i = 0; i < CHARACTER_MAX; i++) {

		if (checkCanAllyBattle(enemy, i)) {adjacentAlly.push_back(i);}
	}
	return adjacentAlly;
}