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
int g_tutorialAllyTurnInfoSpeed = 0;
//�����^�[���ړ���I��
int g_tutorialAllyTurnSelect = 0;
//�����^�[���ړ�
int g_tutorialAllyTurnMove = 0;
//�����^�[���G�I��
int g_tutorialAllyTurnSelectEnemy = 0;
//�G�^�[��
int g_tutorialEnemyTurn = 0;
//�G�^�[���I��
int g_tutorialMapEnemyTurnEnd = 0;
//�񕜃X�|�b�g�̐���
int g_tutorialMapHeal = 0;

//�������G
int g_bossNormal=0;

//�`���[�g���A���ł̃��b�Z�[�W������
int g_tutorialRun = 0;

//�`���[�g���A���摜�`��
void tutorialDraw() {

	//�w�i�摜�`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

	const int x_Start = 0;
	const int x_End = 800;
	const int y_Start = 0;
	const int y_End = 500;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_tutorialRun++; }

	if (g_tutorialRun == 2 || g_tutorialRun == 13 || g_tutorialRun == 14) {
	
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMap, false);
	}
	else if (g_tutorialRun == 3 || g_tutorialRun == 4) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapStream, false);}
	
	else if (g_tutorialRun == 5) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnCursor, false);}
	
	else if (g_tutorialRun == 6) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnSelect, false);}
	
	else if (g_tutorialRun == 7) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnMove, false);}
	
	else if (g_tutorialRun == 8 || g_tutorialRun == 9 || g_tutorialRun == 10) {
	
		DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialAllyTurnInfoSpeed, false);
	}
	else if (g_tutorialRun == 11) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialEnemyTurn, false);}

	else if (g_tutorialRun == 12) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapEnemyTurnEnd, false);}

	else if (g_tutorialRun == 16) {DrawExtendGraph(x_Start, y_Start, x_End, y_End, g_tutorialMapHeal, false);}

	//�������G
	DrawExtendGraph(1200, 100, 800, 500, g_bossNormal, TRUE);
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

//�`���[�g���A����b���b�Z�[�W
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

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�܂��́@�S�̂̊T�v����\n");
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
	//��������Y��
	else if (g_tutorialRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���������낤���@�����������悤\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�܂��͒N�ōU�߂邩�@�s�x�I�肹��\n");
	}
	else if (g_tutorialRun == 6) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�e�X�̉^���ʂɂ��Ắ@�f�[�^����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "����o���Ă���@�Q�l�ɂ��Ă���\n");
	}

	else if (g_tutorialRun == 7) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�G�ɑf�����߂Â��@�ꌂ��^����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�킢�̊�{����\n");
	}
	else if (g_tutorialRun == 8) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���ā@���ڂ��ׂ��_�̂ЂƂ�\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�f����������\n");
	}
	else if (g_tutorialRun == 9) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�䂪�ꑰ�́@����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�f�����Ɂ@�d���������Ă���\n");
	}
	else if (g_tutorialRun == 10) {
		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�r�q�ł���΁@����˂��₷�������\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�T�ȏ������΁@�ǌ����\���낤\n");
	}
	else if (g_tutorialRun ==11) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���ā@�S���̍s��������������\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���́@������̔Ԃ�\n");
	}
	else if (g_tutorialRun == 12) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�����炩����@�G�ӂ͌����邪\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�����邩�ǂ����́@�R�t�a�̍єz�ɔC����\n");
	}
	else if (g_tutorialRun == 13) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���ā@�Ō�̓X�R�A�ɂ��Ă���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���R�����قǁ@��V�͒e�܂��Ă��炨��\n");
	}
	else if (g_tutorialRun == 14) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�������ȁ@�Ⴆ�Εs���ȕ���œ|����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "��荂���_���@�����邾�낤\n");
	}
	else if (g_tutorialRun == 15) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�����ɍU�߂邩�@���]����ڎw������\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�R�t�a�̎��R���@�S�͂Ō}�����Ƃ�\n");
	}
	else if (g_tutorialRun == 16) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�Ō�Ɂ@�P����ɂ͋~��ǂ��_�݂��Ă���\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "��肭���p���@�{���𐋂��Ă݂���\n");
	}
	else if (g_tutorialRun == 17) {

		g_tutorialRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
