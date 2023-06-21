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
//�����^�[���U���\��
int g_tutorialPredictionBattle = 0;
//�G�^�[���؂�ւ�
int g_tutorialEnemyTurn = 0;
//�G�^�[������
int g_tutorialMapEnemyTurnMove = 0;
//�񕜃X�|�b�g�̐���
int g_tutorialMapHeal = 0;

//�������G
int g_bossNormal=0;
int g_bossSmile = 0;

//�`���[�g���A���摜�`��
void tutorialDraw() {

	//�w�i�摜�`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

	//�Q�[����ʕ`��ʒu
	const int GAME_X_START = 0;
	const int GAME_Y_START = 0;
	const int GAME_X_END = 800;
	const int GAME_Y_END = 500;

	//�����G�`��ʒu
	const int BOSS_X_START = 1200;
	const int BOSS_Y_START = 100;
	const int BOSS_X_END = 800;
	const int BOSS_Y_END = 500;

	//��b��
	const int WINDOW_X_START = 60;
	const int WINDOW_Y_START = 500;
	const int WINDOW_X_END = 1200;
	const int WINDOW_Y_END = 700;


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	if (g_messageRun == 2 || g_messageRun == 13 || g_messageRun == 14 || g_messageRun == 15) {
		DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMap, false);
	}

	else if (g_messageRun == 3 || g_messageRun == 4) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapStream, false);}
	
	else if (g_messageRun == 5) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnCursor, false);}
	
	else if (g_messageRun == 6) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnSelect, false);}
	
	else if (g_messageRun == 7) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnMove, false);}
	
	else if (g_messageRun == 8) { DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialPredictionBattle, false);}
		
	else if(g_messageRun == 9 || g_messageRun == 10) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialAllyTurnInfoSpeed, false);}
	
	else if (g_messageRun == 11) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialEnemyTurn, false);}

	else if (g_messageRun == 12) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapEnemyTurnMove, false);}

	else if (g_messageRun == 16) {DrawExtendGraph(GAME_X_START, GAME_Y_START, GAME_X_END, GAME_Y_END, g_tutorialMapHeal, false);}

	//�������G	
	if (g_messageRun == 0 || g_messageRun == 4 || g_messageRun == 7 || g_messageRun == 11 || g_messageRun == 15) {
		DrawExtendGraph(BOSS_X_START, BOSS_Y_START, BOSS_X_END, BOSS_Y_END, g_bossSmile, TRUE);
	}
	else {DrawExtendGraph(BOSS_X_START, BOSS_Y_START, BOSS_X_END, BOSS_Y_END, g_bossNormal, TRUE);}
	
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(WINDOW_X_START, WINDOW_Y_START, WINDOW_X_END, WINDOW_Y_END, g_storyWindow, TRUE);
}

//�`���[�g���A����b���b�Z�[�W
void tutorialMessage() {

	const int MESSAGE_X =150;
	const int MESSAGE_Y_UP = 550;
	const int MESSAGE_Y_DOWN = 620;

	SetFontSize(40);

	if (g_messageRun == 0) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���̃}���O���b�g��\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�R�t�a�Ƃ̎荇�킹�@���h�Ɏv��\n");
	}
	else if (g_messageRun == 1) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�������X�������@���Ԃ��ɂ���\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�P���ɂ��ā@���������Ă��炤\n");
	}
	else if (g_messageRun == 2) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�܂��́@�S�̂̊T�v����\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�܂��@���Ă̒ʂ肾\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�R�t�a�ɒb���ė~�����̂́@���̎O�l\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�䂪�ꑰ�́@�퓬������\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�O�l�𓱂��@����|��\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�R�t�a�̍єz������΁@����������낤\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���������낤���@�����������悤\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�܂��͒N�ōU�߂邩�@�s�x�I�肹��\n");
	}
	else if (g_messageRun == 6) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�e�X�̉^���ʂɂ��Ắ@�f�[�^����\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "����o���Ă���@�Q�l�ɂ��Ă���\n");
	}

	else if (g_messageRun == 7) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�G�ɑf�����߂Â��@�ꌂ��^����\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�킢�̊�{����\n");
	}
	else if (g_messageRun == 8) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "��n�ł͑I���ЂƂ��@�����ɂȂ�\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "���O�ɐ틵��c������̂��@�d�v�ȗv�f��\n");
	}
	else if (g_messageRun == 9) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���ā@�䂪�ꑰ�͓���\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�f�����Ɂ@�d���������Ă���\n");
	}
	else if (g_messageRun == 10) {
		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�r�q�ł���΁@����˂��₷�������\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�T�ȏ������΁@�ǌ����\���낤\n");
	}
	else if (g_messageRun ==11) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�S���̍s��������������\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "���́@������̔Ԃ�\n");
	}
	else if (g_messageRun == 12) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "���̋������Ɂ@�����Ă�����\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�߂��܂Ł@�ړ������Ă��炤\n");
	}
	else if (g_messageRun == 13) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�Ō�́@�X�R�A�ɂ��Ă�\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "���R�����قǁ@��V�͒e�܂��Ă��炨��\n");
	}
	else if (g_messageRun == 14) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�������ȁ@�Ⴆ�Εs���ȕ���œ|����\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "��荂���_���@�����邾�낤\n");
	}
	else if (g_messageRun == 15) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�����ɍU�߂邩�@���]����ڎw������\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "�R�t�a�̎��R���@�S�͂Ō}�����Ƃ�\n");
	}
	else if (g_messageRun == 16) {

		DrawStringEx(MESSAGE_X, MESSAGE_Y_UP, -TEXT_COLOR_WHITE, "�Ō�Ɂ@�P����ɂ͋~��ǂ��_�݂��Ă���\n");
		DrawStringEx(MESSAGE_X, MESSAGE_Y_DOWN, -TEXT_COLOR_WHITE, "��肭���p���@�{���𐋂��Ă݂���\n");
	}
	else if (g_messageRun == 17) {

		g_messageRun = 0;
		g_gameScene_id = GAME_MAP;
	}
}
