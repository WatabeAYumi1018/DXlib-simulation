#pragma once

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

void gameStart();
void gameMain( float delta_time );
void gameEnd();
