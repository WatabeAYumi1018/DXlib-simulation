#pragma once

//�Q�[���V�[��
extern int g_gameScene_id;

//�Q�[���V�[������
enum {
	GAME_START,
	GAME_STORY,
	GAME_MAP,
	GAME_OVER,
	GAME_CLEAR
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

//�t�F�[�Y�ϐ����쐬
extern int g_phase ;

//�J�[�\���t���O
extern bool g_flagCursor ;

//�G���^�[�����t���O
extern bool g_flagEnter ;

//�o�g���i�s�����ۂ��̔���t���O
extern int g_CanAttackMove;

//�^�[���ϐ�
extern int g_turnMove ;

//�e���b�v�A�j���[�V�����J�E���g
extern float g_telopTimeCount;

//�^�[���؂�ւ��t���O
extern int g_flagTurn;

//�Q�[���I�[�o�[�t���O
extern int g_flagGameOver;

//�Q�[���I�[�o�[��ʃn���h��
extern int g_gameOver ;

//�T�E���h
extern int sound_bgm_hdl;
extern int sound_se_hdl;

void phaseEnd();

void phaseMove(float delta_time);

void gameStart();
void gameMain( float delta_time );
void gameEnd();
