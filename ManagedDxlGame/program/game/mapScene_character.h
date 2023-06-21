#pragma once

//�T�O��`-----------------------------------------------

//�L�����N�^�[�̃f�[�^�񎟌��z��i�}�b�v�`�b�v�ƃL�����`�b�v�𕪂��čl����j
extern int charaData[MAP_HEIGHT][MAP_WIDTH];

//�����G�T�O
enum {
	TEAM_ALLY,
	TEAM_ENEMY,
	TEAM_MAX
};

//�E�Ƃ̎��
enum {
	JOB_SWORDMASTER, //���m
	JOB_SNIPER, //�|
	JOB_MAGICIAN, //����
	JOB_BOSS, //��
	JOB_MAX
};

//�W���u�̏ڍ׃f�[�^
extern JOB jobData[];

//�W���u�̖��O�A�ړ�����`
struct JOB {
	std::string job_name;
	int moveCells[CELL_MAX]; //�ړ��Ɏg���}�X��(CELL�̎�ނɂ���Ĉړ��ʂ��ς��)
};

//�e�L�����N�^�[�̏��
extern Character character[];

//�L�����N�^�[�̊e���O�A�p�����[�^
struct Character {
	std::string name;
	int job;
	int hp;
	int maxHp;
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

//�萔-----------------------------------------------

//�L��������
const int CHARACTER_MAX = 16;
const int CHARACTER_ALLAY_MAX = 3;

//�ϐ�-----------------------------------------------

//�I�����ꂽ�L�����N�^�[
extern int g_selectedChara ;

//�ҋ@���G�L�����N�^�[
extern int g_standbyChara ;

//�摜�n���h��--------------------------------------

//�A�C�R���摜�n���h��
extern int icon_sword;
extern int icon_magic;
extern int icon_snip ;
extern int icon_boss ;

//�֐�-----------------------------------------------

//charaData[][]��`
int getCharacter(int x, int y);

//�L�������W�𖈃t���[���擾
void getCharaPosition();

//����ʏ��`��
void characterMapInfo(int chara);

//����ʕ`�掞�̐���
void display();

//�אڂ��Ă���L�����S���̏����i�[���Ă���
std::vector<int> getAdjacentCharacters(int ally);