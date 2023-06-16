#pragma once

//�Q�[���V�[��
extern int g_gameScene_id;

//�T�E���h�@�^�C�g��
extern int g_bgmTitle_hdl;
//�T�E���h�@�}�b�v
extern int g_bgmMap_hdl;

extern int sound_se_hdl;

//�Q�[���V�[������
enum {
	GAME_START,
	GAME_STORY,
	GAME_TUTORIAL,
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

//�G�̃t�F�[�Y
enum {
	PHASE_AI_SEARCH_CHARACTER,
	PHASE_AI_MOVE_CHARACTER,
	PHASE_AI_SELECT_ATTACK,
	PHASE_AI_NEXT_ENEMY
};

//�G���^�[�{�^��
extern int g_bottonEnter;
//�J�[�\���{�^��
extern int g_bottonCursor;
//�^�u�{�^��
extern int g_bottonTab;
//�X�y�[�X�{�^��
extern int g_bottonSpace;
//�V�t�g�{�^��
extern int g_bottonShift;

//----------------------------

//----------------------------
void phaseAllyMove(float delta_time);

void phaseEnemyMove(float delta_time, int enemyNumber);

void enemyAttack(float delta_time, int ally, int enemy);

void gameStart();
void gameMain( float delta_time );
void gameEnd();
