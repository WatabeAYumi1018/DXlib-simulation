#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "storyScene.h"
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

//�T�E���h�炵���iwav.mp3���������j
//��񂾂��Đ����߂��o���i���t���[�����ߏo���Ǝg���Ȃ��j
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

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

//-----------------
// 



//void tutorialDraw


//-------------------------------------------------------------------------------------------
//�N�����Ɉ��̂ݎ��s����܂�
void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//���y�̏o��--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlib���t�@�����X�A���[�v�����̈���

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

	g_girl= LoadGraph("graphics/swordGirl.png");
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

			titleBackDraw();			//�^�C�g���w�i�摜
			movieDraw();				//�^�C�g���A�j���[�V��������
			sceneTitle();				//�^�C�g���S��

			break;
		}
		case GAME_STORY: {

			storyDraw();				//�X�g�[���[�w�i�`��
			storyMessage();				//�X�g�[���[���b�Z�[�W�`��
			leafBottonDrawStory(delta_time);

			break;
		}
		case GAME_TUTORIAL: {

			DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_gameScene_id = GAME_MAP; }

			break;
		}
		case GAME_MAP: {

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
