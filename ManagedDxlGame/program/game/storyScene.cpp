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

	//�X�g�[���[�w�i
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);

	if (g_messageRun==0 || g_messageRun == 2 || g_messageRun == 3 || g_messageRun == 6) {
		//���������G����
		DrawExtendGraph(100, 100, 500, 500, g_girlNormal, TRUE);
	}
	if (g_messageRun == 1 || g_messageRun==4) {
		//���������G�Ί�
		DrawExtendGraph(100, 100, 500, 500, g_girlSmile, TRUE);
	}
	if (g_messageRun==5) {
		// ���������G����
		DrawExtendGraph(100, 100, 500, 500, g_girlTroubled, TRUE);
	}
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

void leafBottonDrawStory(float delta_time) {

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//�_�ŏ���
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 1.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(1050, 580, 1150, 680, g_bottonEnter, true);
	}
}

//��b���b�Z�[�W
void storyMessage() {

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 0) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���Ȃ��� �L���ȌR�t���܂ł���\n");

	}
	else if (g_messageRun == 1) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�悤���� �l�����ꂽ\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�΂̊C�� ��\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���̓x�� ���ڂ��w�������������\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�F �S�҂��ɂ��Ă����̂ł���\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "������� ������ł����ɂ��܂�\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�����̉p�Y�𓱂��� �`���̌R�t����\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "������������ �y���݂�\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���͒��X�c\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�� ���炢�����܂���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���� �P����ֈē��������܂���\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���Ȃ��l�̍єz�@�y���݂ɂ��Ă��܂���\n");
	}
	else if (g_messageRun == 7) { 
		
		g_messageRun = 0;
		g_gameScene_id = GAME_TUTORIAL; }
}
