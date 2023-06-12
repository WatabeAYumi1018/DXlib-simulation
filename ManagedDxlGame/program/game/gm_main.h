#pragma once

//�Q�[���V�[��
extern int g_gameScene_id;

//�Q�[���V�[������
enum {
	GAME_START,
	GAME_STORY,
	GAME_MAP,
	GAME_OVER,
	GAME_CLEAR,
	GAME_TUTORIAL
};

//�����̐F
const int TEXT_COLOR_WHITE = -1;

//�G�����̃^�[������
enum {
	TURN_ALLAY,
	TURN_ENEMY,
	TURN_MAX
};

//���݂̏󋵂�������悤�Ƀt�F�[�Y����
enum {
	PHASE_SELECT_CHARACTER,
	PHASE_SET_MOVE_POSITION,
	PHASE_SELECT_ATTACK,
	PHASE_MAX
};

//�G�̃t�F�[�Y
enum {
	PHASE_AI_SEARCH_CHARACTER,
	PHASE_AI_MOVE_CHARACTER,
	PHASE_AI_SELECT_ATTACK,
	PHASE_AI_NEXT_ENEMY
};

//�t�F�[�Y�ϐ����쐬
extern int g_allyPhase ;

//�����t�F�[�Y�ϐ�
extern int g_phaseAlly;

//�G�t�F�[�Y�ϐ�
extern int g_phaseEnemy;

//�J�[�\���t���O
extern bool g_flagCursor ;

//�G���^�[�����t���O
extern bool g_flagEnter ;

//�X�y�[�X�����t���O
extern bool g_flagEnemy;

//�o�g���i�s�����ۂ��̔���t���O
extern int g_CanAttackMove;

//���ݓG���l�ڂ��i�����l�̓C���f�b�N�X�̂R�j
extern int currentEnemyNumber;

//�^�[���ϐ�
extern int g_turnMove ;

//�^�[���؂�ւ��t���O
extern bool g_flagTurnAlly;

//���݂̓G�ԍ�
extern int currentEnemyNumber;

//�Q�[���X�^�[�g
extern bool g_flagGameStart;

//�Q�[���I�[�o�[�t���O
extern bool g_flagGameOver;

//�Q�[���I�[�o�[��ʃn���h��
extern int g_gameOver ;

//�T�E���h
extern int sound_bgm_hdl;
extern int sound_se_hdl;

//�X�R�A�ϐ�
extern int g_score;

//�^�C�g������
extern int g_title;

//----------------------------
//�X�g�[���[�w�i
extern int g_storyBack;

//�X�g�[���[�E�B���h�E
extern int g_storyWindow;

void storyDraw();

void storyMessage();

//----------------------------
void phaseAllyMove(float delta_time);

void phaseEnemyMove(float delta_time, int enemyNumber);

void enemyAttack(float delta_time, int ally, int enemy);

void gameStart();
void gameMain( float delta_time );
void gameEnd();
