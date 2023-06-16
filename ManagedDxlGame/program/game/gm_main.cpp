#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "storyScene.h"
#include "tutorialScene.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"
#include "endScene.h"

//�N���A����/�Q�[���I�[�o�[�����˃^�C�g����

//-------------------------------------------------------------------------------------------
//�i�s�t�F�[�Y�̃t���O�ϐ�
//

//�Q�[���S�̂̃V�[���ڍs
int g_gameScene_id = GAME_START;

//�T�E���h�@�^�C�g��
int g_bgmTitle_hdl = 0;
//�T�E���h�@�}�b�v
int g_bgmMap_hdl = 0;

//int sound_se_hdl = 0;

//�Q�[���X�^�[�g
bool g_flagGameStart = false;

//�^�C�g������
int g_title = 0;

//�G���^�[�{�^��
int g_bottonEnter = 0;
//�J�[�\���{�^��
int g_bottonCursor = 0;
//�^�u�{�^��
int g_bottonTab = 0;
//�X�y�[�X�{�^��
int g_bottonSpace = 0;
//�V�t�g�{�^��
int g_bottonShift = 0;

int g_tutorialRun = 0;
//-----------------
// 

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


//-------------------------------------------------------------------------------------------
//�N�����Ɉ��̂ݎ��s����܂�
void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//���y�̏o��--------------------------------------------
	g_bgmTitle_hdl = LoadSoundMem("sound/title.mp3");
	g_bgmMap_hdl = LoadSoundMem("sound/map.mp3");

	//�^�C�g���`�`���[�g���A���ɂčĐ�
	PlaySoundMem(g_bgmTitle_hdl, DX_PLAYTYPE_LOOP, TRUE); //DXlib���t�@�����X�A���[�v�����̈���

	//SE�̏o��
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//�摜�̏o��--------------------------------------------

	//�����t�H���g
	tnl::AddFontTTF("font/PixelMplus12-Regular.ttf");

	//�Q�[���X�^�[�g���
	g_gameStart = LoadGraph("graphics/GameStartBack.jpg");

	//�Q�[���X�^�[�g��ʃA�j���[�V����
	g_titleRight = LoadGraph("graphics/titleAnim.png");

	//����̃��[�h
	g_titleMovie = LoadGraph("graphics/titleLeaf.mp4");
	g_clearFlower = LoadGraph("graphics/clearEndFlower.mp4");

	//�^�C�g���I���摜
	g_select_cursor = LoadGraph("graphics/flowerSelect.png");

	//�^�C�g�������摜
	g_title= LoadGraph("graphics/GREEN OCEAN.png");

	//�X�g�[���[�V�[���w�i
	g_storyBack= LoadGraph("graphics/GameStoryBack.png");

	//�X�g�[���[�V�[����b�E�B���h�E
	g_storyWindow = LoadGraph("graphics/storyWindow.png");

	//�}�b�v�f�[�^
	LoadDivGraph("graphics/pipo-map001.png", 88, 8, 11, CHIP_SIZE, CHIP_SIZE, map_chips[0]);

	//�L����
	LoadDivGraph("graphics/player1.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[0]);
	LoadDivGraph("graphics/player2.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[1]);
	LoadDivGraph("graphics/player3.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[2]);
	LoadDivGraph("graphics/enemy1.png",	  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[3]);
	LoadDivGraph("graphics/enemy2.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[4]);
	LoadDivGraph("graphics/enemy3.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[5]);
	LoadDivGraph("graphics/enemyBOSS.png",12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[6]);

	//�J�[�\��
	g_cursor = LoadGraph("graphics/cursor.png");
	
	//�}�b�v��ł̏��\���p�i����ʁj
	display_map = LoadGraph("graphics/mapInfo.png"); 

	//�}�b�v��ł̍s���\�͈�
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//�U����ʂ̔w�i
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//�U���~�X�̉摜
	g_battleMiss = LoadGraph("graphics/miss.png");

	//�Q�[���I�[�o�[�w�i
	g_gameOver = LoadGraph("graphics/GameOver.jpg");
	
	//�Q�[���N���A�w�i
	g_gameClear = LoadGraph("graphics/GameClear.png");

	//�U�����̉����
	LoadDivGraph("graphics/battleHp.png",		35, 5, 7, 120, 60, g_battle_hp[0]);
	LoadDivGraph("graphics/battleAttack.png",	42, 3, 14,300, 60, g_battle_attack[0]);
	LoadDivGraph("graphics/battleHit.png",		25, 5, 5, 180, 60, g_battle_hit[0]);
	
	//�U���G�t�F�N�g�A�j���[�V����
	LoadDivGraph("graphics/effect_sword.png", 15, 5, 3, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_sword[0]);
	LoadDivGraph("graphics/effect_snip.png",  10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_snip[0]);
	LoadDivGraph("graphics/effect_magic.png",14,14, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_magic[0]);
	LoadDivGraph("graphics/effect_leader.png",10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_leader[0]);

	//�E�ƃA�C�R��
	icon_sword= LoadGraph("graphics/iconSWORD.png");
	icon_magic= LoadGraph("graphics/iconMAGIC.png");
	icon_snip=LoadGraph("graphics/iconSNIP.png");
	icon_boss= LoadGraph("graphics/iconBOSS.png");

	//�O�����݃G�t�F�N�g
	g_relation_back= LoadGraph("graphics/relationBack.png");
	g_relation = LoadGraph("graphics/relation.png");

	//�}�b�v��ʂł̃^�[������
	LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

	//�G���^�[�{�^��
	g_bottonEnter = LoadGraph("graphics/leafEnter.png");
	//�J�[�\���{�^��
	g_bottonCursor = LoadGraph("graphics/leafCursor.png");
	//�^�u�{�^��
	g_bottonTab= LoadGraph("graphics/leafTab.png");
	//�X�y�[�X�{�^��
	g_bottonSpace= LoadGraph("graphics/leafSpace.png");
	//�V�t�g�{�^��
	g_bottonShift= LoadGraph("graphics/leafShift.png");

	//���������G
	g_girlNormal= LoadGraph("graphics/swordGirl.png");
	g_girlSmile= LoadGraph("graphics/girlSmile.png");
	g_girlTroubled= LoadGraph("graphics/girl_troubled.png");

	//�������G
	g_bossNormal = LoadGraph("graphics/boss_tutorial.png");

	//�`���[�g���A���֌W-----------------------------
	//
	//�}�b�v�S�̐}
	g_tutorialMap = LoadGraph("graphics/tutorialMap.png");;
	//�Q�[���ړI
	g_tutorialMapStream = LoadGraph("graphics/tutorialMapStream.png");;
	//�����^�[���J�[�\��
	g_tutorialAllyTurnCursor = LoadGraph("graphics/tutorialAllyTurnCursor.png");;
	//����ʏ��
	g_tutorialAllyTurnInfo = LoadGraph("graphics/tutorialAllyTurnInfo.png");;
	//�����^�[���ړ���I��
	g_tutorialAllyTurnSelect = LoadGraph("graphics/tutorialAllyTurnSelect.png");;
	//�����^�[���ړ�
	g_tutorialAllyTurnMove = LoadGraph("graphics/tutorialAllyTurnMove.png");;
	//�����^�[���G�I��
	g_tutorialAllyTurnSelectEnemy = LoadGraph("graphics/tutorialAllyTurnSelectEnemy.png");;
	//�G�^�[��
	g_tutorialEnemyTurn = LoadGraph("graphics/tutorialEnemyTurn.png");;
	//�G�^�[���ړ�
	g_tutorialEnemyTurnMove = LoadGraph("graphics/tutorialEnemyTurnMove.png");;
	//�G�^�[���U���Ăяo��
	g_tutorialMapEnemyTurnAttack = LoadGraph("graphics/tutorialMapEnemyTurnAttack.png");;
	//�G�^�[���I��
	g_tutorialMapEnemyTurnEnd = LoadGraph("graphics/tutorialMapEnemyTurnEnd.png");;
	//�퓬��ʍU����
	g_tutorialBattleAttack = LoadGraph("graphics/tutorialBattleAttack.png");;
	//�퓬��ʖ�����
	g_tutorialBattleHit = LoadGraph("graphics/tutorialBattleHit.png");;
	//�X�R�A����
	g_tutorialScore = LoadGraph("graphics/Score.png");;


}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�,60FPS
void gameMain(float delta_time) {

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_BACK); //DXlib���t�@�����X�A���[�v�����̈���
	//}//�T�E���h�őI�Ԃ̂́A���[�v���o�b�N�̂݁I�m�[�}���͑I�΂Ȃ��ŁI�I�i�m�[�}���̓v���O�����������~�߂Ă��܂��j

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
	//	StopSoundMem(sound_bgm_hdl);//A�������ƃT�E���h���~�܂�
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
	//	PlaySoundMem(sound_bgm_hl, DX_PLAYTYPE_LOOP); //X�����Ɠr������Đ����͂��܂�
	//}

	//�Ȃ�r������Đ�����
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);


	switch (g_gameScene_id) {

		case GAME_START: {

			StopSoundMem(g_bgmMap_hdl);

			titleBackDraw();			//�^�C�g���w�i�摜
			movieDraw();				//�^�C�g���A�j���[�V��������
			sceneTitle();				//�^�C�g���S��

			break;
		}
		case GAME_STORY: {

			StopSoundMem(g_bgmMap_hdl);

			storyDraw();				//�X�g�[���[�w�i�`��
			storyMessage();				//�X�g�[���[���b�Z�[�W�`��
			leafBottonDrawStory(delta_time);

			break;
		}
		case GAME_TUTORIAL: {

			StopSoundMem(g_bgmMap_hdl);

			tutorialDraw();
			tutorialMessage();

			break;
		}
		case GAME_MAP: {

			DeleteSoundMem(g_bgmTitle_hdl);	//�^�C�g���`�`���[�g���A���܂ł�BGM�폜
			
			if (CheckSoundMem(g_bgmMap_hdl) == 0) {PlaySoundMem(g_bgmMap_hdl, DX_PLAYTYPE_LOOP, TRUE);}

			getCharaPosition();			//charaData[MAP_HEIGHT][MAP_WIDTH]��`
			mapPosition(delta_time);	//�摜�`��
			display();					//����ʏ��`�搧��
			cursorMove();				//�J�[�\���ړ����`
			instructions(delta_time);	//�w�������`��
			scoreDraw();				//score�`��
			turnMove(delta_time);		//�Q�[���̗���S��
			
			break;
		}
		case GAME_OVER: {

			gameOver(delta_time);		//�Q�[���I�[�o�[�S��	

			break;
		}
		case GAME_CLEAR: {

			gameClear(delta_time);		//�Q�[���N���A�S��

			break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
