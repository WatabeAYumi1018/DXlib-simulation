#pragma once

//�G�t�F�N�g�T�C�Y
const int EFFECT_SIZE = 120;	

//�X�s�[�h����萔
const int SPEED_DIFFERENCE = 5;

//�퓬���̉�ʃn���h��
extern int g_battleGround ;
extern int g_battleParaBack ;

//�퓬���̃p���\��
extern int g_battle_hp[1][35];
extern int g_battle_attack[1][42];
extern int g_battle_hit[1][25];

//�퓬���̍U���G�t�F�N�g
extern int g_battle_effect_sword[1][14];
extern int g_battle_effect_snip[1][14];
extern int g_battle_effect_magic[1][14];
extern int g_battle_effect_leader[1][14];

//�U���~�X�̉摜
extern int g_battleMiss;

//�퓬�A�j���[�V�����̐����t���O
extern bool g_flagBattleAnime ;

//HP���Z�t���O
extern bool g_flagBattleHp ;

//bool checkAllyInFill(int enemy, int ally);

//�G����̍U������
bool checkCanEnemyBattle(int attack, int defence);

//�U���\���ǂ�������
bool checkCanAllyBattle(int attack, int defence);

//�퓬����ʂ̃O���t�B�b�N�`��
void battleGraph();

//�퓬���̏��`��(�U��/�h��)
void battleInfo(int attack, int defence);

//�J�n����HP�`��
void battleHpDraw(int attack, int defence);

//�퓬��ʂ̃L�����A�j��
void battleCharaGraphic(float delta_time, int attack, int defence);

//�퓬�G�t�F�N�g�A�j��
void battleEffectGraphic(float delta_time, int chara);

//���X�g����
bool battleLost();

//�O�����݂̊֌W
int ThreeRelation(int attack, int defence);

//�����v�Z����
int battleHit(int attack, int defence);

//�o�g���S�ʂ܂Ƃ�(�������ϓ��ɂ��U���̕ω�)
void battleHitRandom(float delta_time, int attack, int defence);

//�퓬�v�Z����
int battleDamage(int attack, int defence);

//�퓬�ɂ��_���[�W�ω��̗���
void battleHpMove(float delta_time, int attack, int defence);

//�퓬�����I��
void battleExit();

//�퓬����
void battle(float delta_time);

//�X�s�[�h��r
//bool battleSpeed(float delta_time, int attack, int defence);