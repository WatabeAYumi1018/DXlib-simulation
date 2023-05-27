#pragma once

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
	JOB_LEADER, //��
	JOB_MAX
};

//�W���u�̖��O�A�ړ�����`
struct JOB {
	std::string job_name;
	int moveCells[CELL_MAX]; //�ړ��Ɏg���}�X��
};

//�W���u�̏ڍ׃f�[�^
extern JOB jobData[];

//�L��������
const int CHARACTER_MAX = 16;
const int CHARACTER_ALLAY_MAX = 3;

//�I�����ꂽ�L�����N�^�[
extern int g_selectedChara ;

//�ҋ@���G�L�����N�^�[
extern int g_standbyChara ;

//�A�C�R���摜�n���h��
extern int icon_sword;
extern int icon_magic;
extern int icon_snip ;
extern int icon_boss ;

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

//�e�L�����N�^�[�̏��
extern Character character[];

int getCharacter(int x, int y);

void getCharaPosition();

void characterMapInfo(int chara);

void display();

void characterMapInfo(int chara);
