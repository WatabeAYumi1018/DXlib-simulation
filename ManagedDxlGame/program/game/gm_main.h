#pragma once

//�Q�[���S��----------------------------------

//�Q�[���V�[��
extern int g_gameScene_id;

//�����̐F
const int TEXT_COLOR_WHITE = -1;

//�T�E���h�֘A----------------------------------

//�T�E���h�@�^�C�g��
extern int g_bgmTitle;
//�T�E���h�@�}�b�v
extern int g_bgmMap;
//�T�E���h�@�G���f�B���O
extern int g_bgmEnding;
//�T�E���h�@�Q�[���I�[�o�[
extern int g_bgmGameOver;

//�U��SE�@�|
extern int g_seEffectAllow;
//�U��SE�@��
extern int g_seEffectSword;
//�U��SE�@���@
extern int g_seEffectMagic;
//�U��SE�@��
extern int g_seEffectBoss ;
//�^�[���ڍs�@&&�@�o�g���J�n
extern int g_seMoveBattle ;

//enum�Ǘ�----------------------------------

//�Q�[���V�[������
enum {
	GAME_START,
	GAME_STORY,
	GAME_TUTORIAL,
	GAME_MAP,
	GAME_OVER,
	GAME_CLEAR
};

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

//����{�^���摜----------------------------------

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

//���C���֐�----------------------------------

void gameStart();
void gameMain( float delta_time );
void gameEnd();
