#include "DxLib.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "storyScene.h"

//�X�g�[���[�w�i
int g_storyBack = 0;

//�X�g�[���[�E�B���h�E
int g_storyWindow = 0;

//���b�Z�[�W����
int g_messageRun = 0;

//���������G����
int g_girlNormal = 0;
//���������G�Ί�
int g_girlSmile = 0;
//���������G����
int g_girlTroubled = 0;

//�X�g�[���[�V�[���ł̔w�i�`��
void storyDraw() {

	//��b��
	const int WINDOW_X_START = 60;
	const int WINDOW_Y_START = 500;
	const int WINDOW_X_END = 1200;
	const int WINDOW_Y_END = 700;

	//�����G�`��ʒu
	const int GIRL_START = 100;
	const int GIRL_END = 500;

	//�X�g�[���[�w�i
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);

	if (g_messageRun==0 || g_messageRun == 2 || g_messageRun == 3 || g_messageRun == 6) {
		//���������G����
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlNormal, TRUE);
	}
	if (g_messageRun == 1 || g_messageRun==4) {
		//���������G�Ί�
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlSmile, TRUE);
	}
	if (g_messageRun==5) {
		// ���������G����
		DrawExtendGraph(GIRL_START, GIRL_START, GIRL_END, GIRL_END, g_girlTroubled, TRUE);
	}
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(WINDOW_X_START, WINDOW_Y_START, WINDOW_X_END, WINDOW_Y_END, g_storyWindow, TRUE);
}

//�G���^�[�}�[�N�`��
void leafBottonDrawStory(float delta_time) {

	const int BOTTON_X_START = 1050;
	const int BOTTON_Y_START = 580;
	const int BOTTON_X_END = 1150;
	const int BOTTON_Y_END = 680;
	const int PLUS = 5;

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//�_�ŏ���
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 0.5f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {DrawExtendGraph(BOTTON_X_START, BOTTON_Y_START, BOTTON_X_END, BOTTON_Y_END, g_bottonEnter, true);}
	else {DrawExtendGraph(BOTTON_X_START, BOTTON_Y_START + PLUS, BOTTON_X_END, BOTTON_Y_END + PLUS, g_bottonEnter, true);}
}

//��b���b�Z�[�W
void storyMessage() {

	const int MESSAGE_X = 150;
	const int MESSAGE_Y_UP = 550;
	const int MESSAGE_Y_DOWN = 620;

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 0) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���Ȃ��l���@���̈̑�Ȃ�\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�L���ȁ@�R�t�l�ł���\n");
	}
	else if (g_messageRun == 1) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�悤�����@�l�����ꂽ\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�΂̊C���@��\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���̓x�́@���ڂ��w�������������\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�F�@�S�҂��ɂ��Ă����̂ł���\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "������́@������ł����ɂ��܂�\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�����̉p�Y�𓱂����@�`���̌R�t�l\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�������������@�y���݂�\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "���͒��X�c\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�Ɓ@���炢�����܂���\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�����@�P����ֈē��������܂���\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���Ȃ��l�̍єz�@�y���݂ɂ��Ă��܂���\n");
	}
	else if (g_messageRun == 7) { 
		
		g_messageRun = 0;
		g_gameScene_id = GAME_TUTORIAL;
	}
}
