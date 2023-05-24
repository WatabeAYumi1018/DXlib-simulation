#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"

//
//�}�b�v��ł̎w���o���R�[�h(�����\�菈���ꗗ)
//
// -----------------------------------------------------------
//�L�����N�^�[�̔z�u����ok
//UI�œG�̃X�e�[�^�X��\��ok
//���j���[��ʂ��J��(���j���[��ʂ̍쐬)���{�f�[�^���I��������
//�v���C���[�^�[���ƓG�̃^�[��
//�����}�X�̐������� OK
//�L�����N�^�[�̌��ݒn��c������֐��K�v�@��y���܂���
//��������̑I��(�U�����ҋ@)�@�U������낤�I�I
//�퓬����	������OK�i�o�O�����j
//�_���[�W�v�Z�ƕ`��	�i������OK�j
//�G�����̃��X�g����	�i������OK�j
//�G����̍U���d�|��	�i������OK�j
// 
// 
//�������S����������^�[���I��
//���G�̃^�[��
//���G�̓���AI�i�{�X�͓����Ȃ��j
//���S���̑ҋ@�m�F
//�������^�[���փt�F�[�Y�`�F���W
//���{�X��		�i������OK�j
//���X�e�[�W�N���A
//�Q�[���I�[�o�[	�i������OK�j

//�T�E���h�炵���iwav.mp3���������j
//��񂾂��Đ����߂��o���i���t���[�����ߏo���Ǝg���Ȃ��j
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

//-------------------------------------------------------------------------------------------
//�n�`�ƍ��W�̊�{���A�萔
//

//�T�C�Y�Ɋւ���萔
const int MAP_HEIGHT = 15;		//�}�b�v��ʍ���
const int MAP_WIDTH = 40;		//�}�b�v��ʕ�
const int CHIP_SIZE = 32;		//�`�b�v�T�C�Y
const int EFFECT_SIZE = 120;	//�G�t�F�N�g�T�C�Y

//�O���X�}�b�v�S�̂�z��Ƃ��Ċi�[
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

//�L�����N�^�[�̃f�[�^�񎟌��z��i�}�b�v�`�b�v�ƃL�����`�b�v�𕪂��čl����j
int charaData[MAP_HEIGHT][MAP_WIDTH];

//�h��Ԃ��̒�`
bool fill[MAP_HEIGHT][MAP_WIDTH];

//�n�`���
enum {
	CELL_GROUND,              //���n0
	CELL_FOREST,             //�X1
	CELL_HOUSE,              //����2
	CELL_FORT,               //��3
	CELL_MOUNTAIN_LEFT_UP,   //�R�i����j4
	CELL_MOUNTAIN_RIGHT_UP,  //�R�i�E��j5
	CELL_MOUNTAIN_LEFT_DOWN, //�R�i�����j6
	CELL_MOUNTAIN_RIGHT_DOWN,//�R�i�E���j7
	CELL_CASTLE_LEFT_UP,     //��i����j8
	CELL_CASTLE_RIGHT_UP,    //��i�E��j9
	CELL_CASTLE_LEFT_DOWN,   //��i�����j10
	CELL_CASTLE_RIGHT_DOWN,   //��i�E���j11
	CELL_MAX
};

//-------------------------------------------------------------------------------------------
//�}�b�v����ł̊�{�T�O
//

//������k
enum {
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_MAX
};

//������k�̃x�N�g�����`�i�����j
int g_directions[][2] = { //�󔒂ɂ���Ə������q�������I�ŗv�f�������肵�Ă����B�����[4][2]�ƂȂ�B
{0,-1}, //DIRECTION_NORTH
{1,0}, //DIRECTION_EAST
{0,1}, //DIRECTION_SOUTH
{-1,0} //DIRECTION_WEST
};

//���݂̏󋵂�������悤�Ƀt�F�[�Y����
enum {
	PHASE_SELECT_CHARACTER,
	PHASE_SET_MOVE_POSITION,
	PHASE_SELECT_ATTACK,
	PHASE_MAX
};

//�t�F�[�Y�ϐ����쐬
int g_phase = PHASE_SELECT_CHARACTER;

//�����G�T�O
enum {
	TEAM_ALLY,
	TEAM_ENEMY,
	TEAM_MAX
};

//�J�[�\�����W���`
int cursorX = 0;
int cursorY = 0;

//-------------------------------------------------------------------------------------------
//�E�Ɗ�{���
//

//�E�Ƃ̎��
enum {
	JOB_SWORDMASTER, //���m
	JOB_SNIPER, //�|
	JOB_MAGICIAN, //����
	JOB_LEADER, //��
	JOB_MAX
};

//�W���u�̖��O�A�ړ�����`
struct JOB {
	std::string job_name;
	int moveCells[CELL_MAX]; //�ړ��Ɏg���}�X��
};

//�W���u�̏ڍ׃f�[�^
JOB jobData[] = {
	//�E��		�� �X �� �� �R(����) �R(�E��) �R(����) �R(�E��) ��(����) ��(�E��) ��(����) ��(�E��)
	{"���m",	{1, 2, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"�|�g��",	{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	},
	{"�����m",	{1, 1, 1, 2,   1,		 1,		 1,		 1,		  1,		  1,		 1,		 1}	},
	{"��",		{1, 1, 1, 2,  -1,		-1,		-1,		-1,		 -1,		 -1,		-1,		-1}	}
};

//-------------------------------------------------------------------------------------------
//�L������{���
//

//�L��������
const int CHARACTER_MAX = 16;

//�I�����ꂽ�L�����N�^�[
int g_selectedChara = 0;

//�U���Ώۂ̑ҋ@���L�����N�^�[
int g_standbyChara = 0;

//�L�����N�^�[�̊e���O�A�p�����[�^
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
	int x; //�����ʒu
	int y;
	bool done; //�s���ς݊T�O
};

//�e�L�����N�^�[�̏��
Character character[] = {
	//�L�������@ �E��				HP�@maxHp decreaseHp�U�� �h�� ���� ���� �ړ�	�`�[��	X	 Y
	{"�O��",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ALLY,	36, 3},
	{"�P��",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ALLY,	34, 4},
	{"�Q��",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ALLY,	38, 5},
	{"���m",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	31, 6},
	{"�|�g��",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	33, 11},
	{"�����m",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	27, 1},
	{"���m",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	15, 10},
	{"�|�g��",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	12, 4},
	{"�����m",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	9,	2},
	{"���m",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	25, 12},
	{"�|�g��",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	24, 6},
	{"�����m",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	10, 10},
	{"���m",	JOB_SWORDMASTER,	300, 300,	300,	100,  60,  20,  10,  5,	TEAM_ENEMY,	5,	6},
	{"�|�g��",	JOB_SNIPER,			200, 200,	200,	150,  70,  15,  10,  4,	TEAM_ENEMY,	5,	10},
	{"�����m",	JOB_MAGICIAN,		100, 100,	100,	200,  50,  10,  10,  4,	TEAM_ENEMY,	20, 8},
	{"��",		JOB_LEADER,			400, 400,	400,	200,  70,  20,  10,  5,	TEAM_ENEMY,	4,	3}
};


//-------------------------------------------------------------------------------------------
//�O���t�B�b�N�̃n���h�����`
//

//�`�b�v�摜
int character_chips[7][12];	//�L�����`�b�v�i�[�z��
int map_chips[1][88];		//�}�b�v�`�b�v�i�[�z��

//�}�b�v�`�b�v
int graphic_cell_ground = 0;

//�s���\�͈͓h��Ԃ�
int fill_map = 0;

//�}�b�v��ʂł̏��`��
int display_map = 0;

//�J�[�\���摜
int g_cursor = 0;

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

//�}�b�v��ʂł̃^�[������
int g_map_turn[1][15];

//�A�C�R���摜�n���h��
int icon_sword = 0;
int icon_magic = 0;
int icon_snip = 0;
int icon_boss = 0;

//�O�����ݖ��摜
int g_relation = 0;
int g_relation_back = 0;

//�G���^�[�����t���O
bool g_flagEnter = false;

//�J�[�\���t���O
bool g_flagCursor = true;

//�o�g���i�s�����ۂ��̔���t���O
int g_CanAttackMove = 0;

//�o�g���\���ۂ��̔���t���O
bool g_flagPhaseAttack = true;

//�퓬�A�j���[�V�����̐����t���O
bool g_flagBattleAnime = true;

//�A�j���[�V������MAX�t���[��
const int MAX_ANIM_FRAM = 14;

//�퓬�̃J�b�g�����t���O
float cnt_next_move = 0;

//HP�^�C���J�E���g
float g_HpTimeCount = 0;

//HP���Z
bool g_flagBattleHp = true;

//------------------------------------
//

//
//��Ճf�[�^---------------------------------------
//

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
		DrawStringEx(100, 530, -1, character[chara].name.c_str());
		DrawStringEx(100, 630, -1, "�E�ƁF%s", jobData[character[chara].job].job_name.c_str());//job
		DrawStringEx(530, 570, -1, "HP�F%s", hp_str.c_str());//hp
		DrawStringEx(630, 570, -1, " / %s", maxHp_str.c_str());//maxHp

		SetFontSize(20);
		if (character[chara].team == TEAM_ALLY && character[chara].done == true) { DrawStringEx(200, 540, -1, "�s���I��"); }
		else if (character[chara].team == TEAM_ALLY && character[chara].done == false) { DrawStringEx(200, 540, -1, "���s��"); }

		DrawStringEx(900, 550, -1, "�U���́F%s", attack_str.c_str());//attack
		DrawStringEx(900, 600, -1, "�h��́F%s", defence_str.c_str());//defence
		DrawStringEx(900, 650, -1, "�f�����F%s", speed_str.c_str());//speed
		DrawStringEx(1100, 550, -1, "�������F%s", hit_str.c_str());//hit
		DrawStringEx(1100, 600, -1, "�ړ��́F%s", move_str.c_str());//move

		//�A�C�R���\��
		if (character[chara].job == JOB_SWORDMASTER) {
			DrawExtendGraph(300, 630, 350, 680, icon_sword, true);//�g��k��draw�֐�
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

//charaDate�ɒ��g�����B1�l�����W��ǂݎ��A���Ȃ��ꏊ�ɂ́[�P��Ԃ�
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

		int y = character[i].y;
		int x = character[i].x;

		if (character[i].hp > 0) {
			
			charaData[character[i].y][character[i].x] = i;
		}
	
	}
}

//�L�����N�^�[���\������
void display() {

	//�J�[�\���ƃL�����`�b�v�̉摜��v�ŏ��
	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (charaData[cursorY][cursorX] == i) { characterMapInfo(i); }
	}
}

//����e�t�F�[�Y�ł̎w�������`�揈���i�����ɓ_�ŏ����������悤�j
void instructions() {

	//�e�t�F�[�Y�ł̎w�����͕`��
	switch (g_phase) {

	case PHASE_SELECT_CHARACTER:
		SetFontSize(30);
		DrawString(700, 10, "�L�����N�^�[��I��ł�������\n", -1);
		break;

	case PHASE_SET_MOVE_POSITION:
		SetFontSize(30);
		DrawString(700, 10, "�ړ����I��ł�������\n", -1);
		break;

	case PHASE_SELECT_ATTACK:
		SetFontSize(30);
		DrawString(700, 10, "�U���Ώۂ�I��ł�������\n", -1);
		break;
	}
}

//����|���ƃG���f�B���O�˃N���A�����˃^�C�g����

//�n�`�̏�ɏ��ƁA���^�[���̗͉�

//�����S����done=true�œG�t�F�[�Y�ֈڍs�i���܂ł̃t�F�[�Y�͑S�������̏����ł���I�j

//if�G��move���̍��W�ɖ�������������˖����̍��W�֌������Ă���˃o�g�����͂��܂�i�֐��ցj

//�G�t�F�[�Y�����B

//
//�퓬---------------------------------------------
//

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
void battleInfo(int attack,int defence) {

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

//�퓬��ʂ̖����L�����A�j��
void battleCharaGraphic(float delta_time,int attack,int defence) {

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

//�퓬�G�t�F�N�g�A�j��
void battleEffectGraphic(float delta_time,int chara) {
	
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
int battleCalculate(int attack,int defence) {

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
void battleMove(float delta_time,int attack, int defence) {

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
bool battleSpeed(float delta_time,int attack, int defence) {

	//attack���T�ȏ㑁���ꍇ
	if (character[attack].speed - character[defence].speed >= 5) {
		battleMove(delta_time,attack,defence);
		
		return true;
	}

	//defence���T�ȏ㑁���ꍇ
	else if (character[defence].speed - character[attack].speed >= 5) {
		battleMove(delta_time, defence, attack);

		return true;
	}
	return false;
}

//
//�}�b�v���----------------------------------------
//

//�U���\���ǂ�������
bool checkCanBattle(int attack, int defence) {

	if (character[attack].team == character[defence].team) { return false; }//�������m�A�G���m�͍U���ł��Ȃ�
	if ((character[attack].hp <= 0) || (character[defence].hp <= 0)) { return false; } //�̗͂O�ȉ����s��

	else {
		int distanceX = abs(character[attack].x - character[defence].x);//absolute value�̗��B��΁@�l�B
		int distanceY = abs(character[attack].y - character[defence].y);
		if ((distanceX == 0 && distanceY == 1)||(distanceX == 1 && distanceY == 0)) { return true; }
		
		return false;
	}
}

//�h��Ԃ��ł��邩�ǂ�ǂ񔻒肵�Ă�
void fillCanMove(int _chara, int _x, int _y, int _move) {//�I�����������L�����A���W�A�ړ���

	//��ʊO�̓X���[
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return; }


	//������ꏊ��cell�����擾�A�E�Ƃ̏��ƍ��킹��moveCells���擾����
	//�Ⴆ�΁A�X�̏�ɂ���ꍇ�́A�E�Ƃɂ���Ă͈ړ��R�X�g�P�A�Q�������肷��B
	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	//�ړ��\�����O�ȉ��A�ړ��\����艺�Ȃ�`��s�ŏI��
	if (moveCost < 0 || _move < moveCost) { return; }

	//��������Ȃ���Γh��Ԃ��\
	fill[_y][_x] = true;

	//�ړ����邲�ƂɃR�X�g���g���Ă���
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		fillCanMove(_chara, x, y, _move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
	}
}

//fill�̏������i��������Ȃ��ƁA���ɑI�����Ă��O�̑I����񂪎c�����܂܂ɂȂ��Ă��܂��j
void resetFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			fill[i][j] = false;

			//�����S��done�œG�t�F�[�Y��
		}
	}
}

//fill�̉摜�`��
void drawFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (fill[i][j]) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, fill_map, TRUE); }//�h��Ԃ��\�Ȃ�`��
		}
	}
}

//�J�[�\���G���^�[�����ɂ���
void phaseMove(float delta_time) {

	switch (g_phase) {

		case PHASE_SELECT_CHARACTER: {

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				resetFill();

				//�I�������L�����N�^�[���͂��ē�����k��1�}�X���h��Ԃ�
				int chara = getCharacter(cursorX, cursorY);
				if (chara < 0) { break; } //�������̒l�������炻���ɃL�����͂��Ȃ����h��Ԃ��Ȃ�

				//�s���ς݂Ȃ���W�����Ȃ�
				//if (character[chara].done) { resetFill(); }

				//�L�����������(����ȊO��)�h��Ԃ�
				else {

					for (int dir = 0; dir < DIRECTION_MAX; dir++)
					{
						int x = character[chara].x + g_directions[dir][0];
						int y = character[chara].y + g_directions[dir][1];
						fillCanMove(chara, x, y, character[chara].move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
					}

					//�`����ɃL������������A�����͕`�悵�Ȃ�
					for (int i = 0; i < MAP_HEIGHT; i++) {
						for (int j = 0; j < MAP_WIDTH; j++) {

							int standChara = getCharacter(j, i);
							
							if (standChara >= 0 && fill[i][j]) {fill[i][j] = false;}
						}
					}

					drawFill();

					//�L������I��������A�ړ��t�F�[�Y��
					if (character[chara].team == TEAM_ALLY) {
						g_selectedChara = chara; //�����L��������
						g_phase = PHASE_SET_MOVE_POSITION;
					}
					break;
				}
			}
		}
		case PHASE_SET_MOVE_POSITION: {

			drawFill();

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				//�ړ���̑I���A����������I���t�F�[�Y�ɖ߂�
				if (fill[cursorY][cursorX]) {

					//�ړ��ɂ����W�̕ω�
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
						//�U���\�L���������Ȃ���΁A�ҋ@
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

					//�퓬��ʉ��O���t�B�b�N�`��
					battleGraph();
					
					//�퓬��ʉ����`��
					battleInfo(g_selectedChara, g_standbyChara);

					//�퓬��ʂ̃L�����A�j���[�V����
					battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);
								
					if (g_CanAttackMove == 1) {

						//attack���̍U���G�t�F�N�g�`��
						battleEffectGraphic(delta_time, g_selectedChara);
					}

					else if (g_CanAttackMove == 2) {//�����̍U��
						
						//HP�v�Z
						battleMove(delta_time, g_selectedChara, g_standbyChara);

						//defence��
						std::string defence_StartHp = std::to_string(character[g_standbyChara].hp);
						DrawStringEx(400, 500, -1, defence_StartHp.c_str());
					}
					
					else if (g_CanAttackMove == 3) {

						//defence���̍U���G�t�F�N�g�`��
						battleEffectGraphic(delta_time, g_standbyChara);
					}
					
					else if(g_CanAttackMove == 4) {

						//HP�v�Z
						battleMove(delta_time, g_standbyChara, g_selectedChara);

						//defence��
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
			//	//������I���őҋ@
			//	character[g_selectedChara].done = true;
			//	resetFill();
			//	g_phase = PHASE_SELECT_CHARACTER;
			//}
		break;
		}
	}
}

//�J�[�\���ړ�
void cursorMove() {
	if (g_flagCursor) {
	
		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1){ cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0)				{ cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1){ cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0)				{ cursorX--; }

		WaitTimer(100);
	}
}

//�}�b�v�S�̂̏���ǂݎ��Aif�Ŋe�����ɑΉ�����`�b�v��`�悷��
void mapPosition() {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			//���n�}�b�v�̕`��i���n�j
			DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][0], TRUE);

			//�}�b�v�`�b�v�`��
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

			//�L�����`�b�v�`��
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
			//�}�b�v��ł̃L��������ʕ`��
			DrawExtendGraph(0, 500, 1400, 730, display_map, true);

			//�O�����݊֘A�摜�`��
			DrawExtendGraph(0, 370, 125, 480, g_relation_back, true);
			DrawGraph(15, 370, g_relation, TRUE);
			DrawExtendGraph(0, 370, 40, 410, icon_sword, true);
			DrawExtendGraph(35, 440, 75, 480, icon_magic, true);
			DrawExtendGraph(85, 390, 125, 430, icon_snip, true);

			
			//���݂̑I���J�[�\���̈ʒu��`��
			if (j == cursorX && i == cursorY) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, g_cursor, TRUE); }
		}
	}
}

void gameStart() {
	srand(time(0));

	SetWindowText("�t�@�C�A�[�G���u�������ۂ�����");

	//���y�̏o��--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlib���t�@�����X�A���[�v�����̈���

	//SE�̏o��
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//�摜�̏o��--------------------------------------------
	//�}�b�v�f�[�^
	LoadDivGraph("graphics/pipo-map001.png", 88, 8, 11, CHIP_SIZE, CHIP_SIZE, map_chips[0]);

	//�L����
	LoadDivGraph("graphics/player1.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[0]);
	LoadDivGraph("graphics/player2.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[1]);
	LoadDivGraph("graphics/player3.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[2]);
	LoadDivGraph("graphics/enemy1.png",	  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[3]);
	LoadDivGraph("graphics/enemy2.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[4]);
	LoadDivGraph("graphics/enemy3.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[5]);
	LoadDivGraph("graphics/enemyBOSS.png",12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[6]);

	//�J�[�\��
	g_cursor = LoadGraph("graphics/cursor.png");
	
	//�}�b�v��ł̏��\���p�i����ʁj
	display_map = LoadGraph("graphics/mapInfo.png"); 
	
	//�}�b�v��ł̍s���\�͈�
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//�U����ʂ̔w�i
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//�U�����̉����
	LoadDivGraph("graphics/battleHp.png",		35, 5, 7, 120, 60, g_battle_hp[0]);
	LoadDivGraph("graphics/battleAttack.png",	42, 3, 14,300, 60, g_battle_attack[0]);
	LoadDivGraph("graphics/battleHit.png",		25, 5, 5, 180, 60, g_battle_hit[0]);
	
	//�U���G�t�F�N�g�A�j���[�V����
	LoadDivGraph("graphics/effect_sword.png", 5, 5, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_sword[0]);
	LoadDivGraph("graphics/effect_snip.png",  9, 9, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_snip[0]);
	LoadDivGraph("graphics/effect_magic.png",14,14, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_magic[0]);
	LoadDivGraph("graphics/effect_leader.png",5, 5, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_leader[0]);

	//�E�ƃA�C�R��
	icon_sword= LoadGraph("graphics/iconSWORD.png");
	icon_magic= LoadGraph("graphics/iconMAGIC.png");
	icon_snip=LoadGraph("graphics/iconSNIP.png");
	icon_boss= LoadGraph("graphics/iconBOSS.png");

	//�O�����݃G�t�F�N�g
	g_relation_back= LoadGraph("graphics/relationBack.png");
	g_relation = LoadGraph("graphics/relation.png");

	//�}�b�v��ʂł̃^�[������
	LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�,60FPS
void gameMain(float delta_time) {

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_BACK); //DXlib���t�@�����X�A���[�v�����̈���
	//}//�T�E���h�őI�Ԃ̂́A���[�v���o�b�N�̂݁I�m�[�}���͑I�΂Ȃ��ŁI�I�i�m�[�}���̓v���O�����������~�߂Ă��܂��j

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
	//	StopSoundMem(sound_bgm_hdl);//A�������ƃT�E���h���~�܂�
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //X�����Ɠr������Đ����͂��܂�
	//}

	//�Ȃ�r������Đ�����
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);

	getCharaPosition();
	mapPosition();
	display();
	cursorMove();//��<resetFill()/drawFill())��getCharacter(,)/return��fillCanMove(,,,)
	instructions();
	phaseMove(delta_time);

}
//
////------------------------------------------------------------------------------------------------------------
//// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


//�_�O���t�ł̃_���[�W���Z�`��
//DrawExtend�ŁA�_���[�W�󂯂���i�t���O�Ǘ��j���̕������炷�i�`��̃T�C�Y��ς���j