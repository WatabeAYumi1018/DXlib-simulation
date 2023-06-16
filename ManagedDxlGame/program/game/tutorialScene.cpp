#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "storyScene.h"
#include "tutorialScene.h"
#include "mapScene_battle.h"

//�`���[�g���A����p�摜----------------
// 
//�}�b�v�S�̐}
int g_tutorialMap = 0;
//�Q�[���ړI
int g_tutorialMapStream = 0;
//�����^�[���J�[�\��
int g_tutorialAllyTurnCursor = 0;
//����ʏ��
int g_tutorialAllyTurnInfo = 0;
//�����^�[���ړ���I��
int g_tutorialAllyTurnSelect = 0;
//�����^�[���ړ�
int g_tutorialAllyTurnMove = 0;
//�����^�[���G�I��
int g_tutorialAllyTurnSelectEnemy = 0;
//�G�^�[��
int g_tutorialEnemyTurn = 0;
//�G�^�[���ړ�
int g_tutorialEnemyTurnMove = 0;
//�G�^�[���U���Ăяo��
int g_tutorialMapEnemyTurnAttack = 0;
//�G�^�[���I��
int g_tutorialMapEnemyTurnEnd = 0;
//�퓬��ʍU����
int g_tutorialBattleAttack = 0;
//�퓬��ʖ�����
int g_tutorialBattleHit = 0;
//�X�R�A����
int g_tutorialScore = 0;

//�������G
int g_bossNormal=0;

//�`���[�g���A���ł̃��b�Z�[�W������
int g_tutorialRun = 0;

void tutorialDraw() {

	//�w�i�摜�`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

	const int x_Start = 0;
	const int x_End = 800;
	const int y_Start = 0;
	const int y_End = 500;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_tutorialRun++; }

	if (g_tutorialRun == 2) {

		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMap, false);
	}
	else if (g_tutorialRun == 3) {

		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapStream, false);

	}
	else if (g_tutorialRun == 4) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnCursor, false);

	}
	else if (g_tutorialRun == 5) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelect, false);

	}
	else if (g_tutorialRun == 6) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnMove, false);

	}
	else if (g_tutorialRun == 7) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelectEnemy, false);

	}
	else if (g_tutorialRun == 8) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnInfo, false);

	}
	else if (g_tutorialRun == 9) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurn, false);

	}
	else if (g_tutorialRun == 10) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurnMove, false);

	}
	else if (g_tutorialRun == 11) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapEnemyTurnEnd, false);

	}
	else if (g_tutorialRun == 12) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialBattleAttack, false);

	}
	else if (g_tutorialRun == 13) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialBattleHit, false);

	}
	else if (g_tutorialRun == 13) {
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialScore, false);

	}
	else if (g_tutorialRun == 14) {

		g_tutorialRun = 0;
		g_gameScene_id = GAME_MAP;
	}

	//�������G
	DrawExtendGraph(1200, 100, 800, 500, g_bossNormal, TRUE);
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

//��b���b�Z�[�W
void tutorialMessage() {

	SetFontSize(40);

	if (g_tutorialRun == 0) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���̃}���O���b�g��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�R�t�a�Ƃ̎荇�킹�@���h�Ɏv��\n");
	}
	else if (g_tutorialRun == 1) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�������X�������@���Ԃ��ɂ���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�P���ɂ��ā@���������Ă��炤\n");
	}
	else if (g_tutorialRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�܂��́@�S�̗̂��ꂾ���c\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�܂��@���Ă̒ʂ肾\n");
	}
	else if (g_tutorialRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�R�t�a�ɒb���ė~�����̂́@���̎O�l\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�䂪�ꑰ�́@�퓬������\n");
	}
	else if (g_tutorialRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�O�l�𓱂��@����|��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�R�t�a�̍єz������΁@����������낤\n");
	}
	else if (g_tutorialRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�^���ʂɂ��Ă����@�f�[�^����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�S���̈ړ��ʂ��@����o����\n");
	}
	else if (g_tutorialRun == 6) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�P������ɐڋ߂����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�퓬�ɓ���\n");
	}
	else if (g_tutorialRun == 7) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "����̑������@�d�v����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���ڂ��ׂ��́@�f�������낤��\n");
	}
	else if (g_tutorialRun == 8) {
		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�r�q�Ȏ҂́@����˂��₷��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�T�ȏ������΁@�ǌ����\���낤\n");
	}
	else if (g_tutorialRun == 9) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�S���̍s��������������\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���́@������̔�\n");
	}
	else if (g_tutorialRun == 10) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�G�ӂɉ�����ꍇ��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "����@ShiftEnter�ō��}��\n");
	}
	else if (g_tutorialRun == 11) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�P����́@����]�������Ă���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�X�R�A�������قǁ@��V���e�܂��Ă��炤\n");
	}
	else if (g_tutorialRun == 12) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�������ȁc�@�Ⴆ�Εs���ȕ���œ|����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�X�R�A�𓾂₷�����낤��\n");
	}
	else if (g_tutorialRun == 13) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�ǂ��U�߂邩�́@�R�t�a�̎��R��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�S�͂ł������Ă���\n");
	}
	else if (g_tutorialRun == 13) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�Ō�Ɂ@�P����ɂ͋~��ǂ��_�݂��Ă���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "��肭���p���@�{���𐋂��Ă݂���\n");
	}
	else if (g_tutorialRun == 14) {

		g_tutorialRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
