#pragma once

//�G�t�F�N�g�T�C�Y
const int EFFECT_SIZE = 120;	

//�A�j���[�V������MAX�t���[��
const int MAX_EFFECT_FRAM = 10;

const int SPEED_DIFFERENCE = 5;

const int HP_ALLAY_X = 800;
const int HP_ENEMY_X = 400;
const int HP_Y = 500;

//�퓬���̉�ʃn���h��
extern int g_battleGround ;
extern int g_battleParaBack ;

//�퓬���̃p���\��
extern int g_battle_hp[1][35];
extern int g_battle_attack[1][42];
extern int g_battle_hit[1][25];

//�L�����A�j���[�V�����֘A
extern int g_charaAlly_vector ;		//�����L�����̌���
extern int g_charaEnemy_vector;		//�G�L�����̌���
extern int g_vectorAlly_count ;		//�����J�E���g�ϐ�
extern float g_vectorEnemy_count ;	//�G�J�E���g�ϐ�
extern float g_animAlly_timeCount;	//���ԕ`�摬���̐���
extern float g_animEnemy_timeCount;	//�G�`�摬���̐���

//�퓬���̍U���G�t�F�N�g
extern int g_battle_effect_sword[1][14];
extern int g_battle_effect_snip[1][14];
extern int g_battle_effect_magic[1][14];
extern int g_battle_effect_leader[1][14];

//�U���G�t�F�N�g�̃A�j���[�V�����n���h��
extern float g_effectTimeCount ;
extern int g_effectFrame ;

//�퓬�A�j���[�V�����̐����t���O
extern bool g_flagBattleAnime ;

//HP���Z�t���O
extern bool g_flagBattleHp ;

//HP�^�C���J�E���g
extern float g_HpTimeCount ;

//�U���\���ǂ�������
bool checkCanBattle(int attack, int defence);

//�퓬����ʂ̃O���t�B�b�N�`��
void battleGraph();

//�퓬���̏��`��(�U��/�h��)
void battleInfo(int attack, int defence);

//�J�n����HP�`��
void battleHp(int attack, int defence);

//�퓬��ʂ̃L�����A�j��
void battleCharaGraphic(float delta_time, int attack, int defence);

//�퓬�G�t�F�N�g�A�j��
void battleEffectGraphic(float delta_time, int chara);

//���X�g����
void battleLost(int chara);

//�O�����݂̊֌W
bool ThreeRelation(int attack, int defence);

//�퓬�v�Z����
int battleCalculate(int attack, int defence);

//�퓬�ɂ��_���[�W�ω��̗���
void battleHpMove(float delta_time, int attack, int defence);

//�퓬�����I��
void battleExit();

//�X�s�[�h��r
//bool battleSpeed(float delta_time, int attack, int defence);