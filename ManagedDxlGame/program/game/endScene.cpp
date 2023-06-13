#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "endScene.h"

//�Q�[���I�[�o�[���
int g_gameOver = 0;

//�Q�[���N���A���
int g_gameClear = 0;

//�N���A�N���b�J�[����
int g_clearFlower = 0;

//�Q�[���I�[�o�[��ʕ`��
void gameOver(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameOver, TRUE);

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

	DrawExtendGraph(TEXT_START_X_Y, TEXT_START_X_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		SetFontSize(50);
		DrawStringEx(550, 500, TEXT_COLOR_WHITE, "CLOSE");
	}
}

//�Q�[���N���A��ʕ`��
void gameClear(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameClear, TRUE);

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 300;

	//�e���b�v�A�j���[�V�����J�E���g
	float static g_gameClearTimeCount = 0;

	//���t���[�������Ă�������
	g_gameClearTimeCount += delta_time;

	int telopFrame = g_gameClearTimeCount * TELOP_SPEED;

	if (telopFrame >= TELOP_FRAME_MAX) {

		telopFrame = TELOP_FRAME_MAX;			//�e���b�v�̗��ꂽ�������Z�b�g
		g_gameClearTimeCount = 0;				//�e���b�v�̃J�E���g���Z�b�g	
	}

	//�����_�n�C�X�R�A�I
	if (g_score >= 500) {
		
		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][12], true);

		movieDraw();
	}
	//��o���N���A�I
	else if (g_score <= 300 && g_score >= 100) {

		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][1], true); 

		movieDraw();
	}
	//�N���A�I
	else {

		DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true);
		DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][7], true); 
	}
}
