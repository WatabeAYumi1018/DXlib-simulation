#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "endScene.h"

//�N���A�N���b�J�[����
int g_clearCracker = 0;

//�Q�[���I�[�o�[��ʕ`��
void gameOver(float delta_time) {

	const int BACK_START_X_Y = 0;
	const int BACK_END_X = 1300;
	const int BACK_END_Y = 750;

	const int TEXT_START_X_Y = 200;
	const int TEXT_END_X = 1100;
	const int TEXT_END_Y = 400;

	float static g_gameOverTimeCount = 0;
	bool static g_gameOver_write = true;

	// �_�ŏ���
	g_gameOverTimeCount += delta_time;

	if (g_gameOverTimeCount > 0.5f) {
		g_gameOver_write = !g_gameOver_write;
		g_gameOverTimeCount = 0;
	}

	DrawExtendGraph(BACK_START_X_Y, BACK_START_X_Y, BACK_END_X, BACK_END_Y, g_gameOver, true);
	DrawExtendGraph(TEXT_START_X_Y, TEXT_START_X_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		SetFontSize(50);
		DrawStringEx(550, 500, TEXT_COLOR_WHITE, "CLOSE");
	}
}

void gameClear(float delta_time) {

	//����̉摜�T�C�Y���擾
	int size_x;
	int size_y;

	GetGraphSize(g_clearCracker, &size_x, &size_y);

	//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
	screen_handle = MakeScreen(size_x, size_y, TRUE);

	// ����̍Đ��J�n
	PlayMovieToGraph(g_clearCracker, DX_PLAYTYPE_LOOP);

	//��������߂�����@�Ƃ��Ė��邳�N���b�v�t�B���^�[������@��قǂ̒u���t�B���^�[�͂�����GB�̂悤�ɓ��߂ɓK�����f�ނ���Ȃ��Ƃ��܂������Ȃ�
	//������́u���ȏ�/�ȉ��̖��邳�̐F�����ׂēh��Ԃ��v�Ƃ����͋����������ł���
	//FilterType�ȍ~�̈���...��r���@�iLESS/GREATER),��r����l,�Y������F��h��Ԃ���,
	//�h��Ԃ�����̐F,�h��Ԃ�����̐F�̕s�����x(�����ɂ������̂�0)
	GraphFilterBlt(g_clearCracker, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, TRUE, GetColor(0, 0, 0), 0);

	//���ߏ������ꂽ�摜����ʂ����ς��ɕ`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 500;

	//�e���b�v�A�j���[�V�����J�E���g
	float static g_gameClearTimeCount = 0;

	//���t���[�������Ă�������
	g_gameClearTimeCount += delta_time;

	int telopFrame = g_gameClearTimeCount * TELOP_SPEED;

	//�����_�n�C�X�R�A�I
	if (g_score >= 500) {
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
	}
	//��o���N���A�I
	else if (g_score <= 300 && g_score >= 100) {
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
	}

	//�N���A�I
	else { DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true); }

	if (telopFrame >= TELOP_FRAME_MAX) {

		telopFrame = TELOP_FRAME_MAX;			//�e���b�v�̗��ꂽ�������Z�b�g
		g_gameClearTimeCount = 0;				//�e���b�v�̃J�E���g���Z�b�g
		//g_flagTurnAlly = false;					//�����^�[���̃e���b�v�����͈��Ŋ����̂���false
	}
}