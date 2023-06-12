#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"


//�N���A����/�Q�[���I�[�o�[�����˃^�C�g����
//�n�`�̏�ɏ��ƁA���^�[���̗͉�



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

//�Q�[���I�[�o�[�t���O
bool g_flagGameOver = false;

//�Q�[���I�[�o�[���
int g_gameOver = 0;

//�Q�[���N���A���
int g_gameClear = 0;

//�^�C�g������
int g_title = 0;

//-----------------
// 
//�X�g�[���[�w�i
int g_storyBack = 0;

//�X�g�[���[�E�B���h�E
int g_storyWindow = 0;

void storyDraw() {

	//�X�g�[���[�w�i
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);
	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

void storyMessage() {

	SetFontSize(40);

	static int messageLine = 0;
	static int messageCount = 0;
	const int MESSAGE_LINE = 7;  // �s�̐�
	const int MESSAGE_NUM = 2;   // ��̐�
	const int TEXT_LINE = 7;
	const int TEXT_NUM = 2;
	int addMessageNumber = 1;  // 1�������������邽�߂�1����������
	//�e�L�X�g�i�[���镶����
	std::string text[TEXT_LINE][TEXT_NUM];
	//���b�Z�[�W�i�[���镶����
	std::string message[MESSAGE_LINE][MESSAGE_NUM] = {

		{"���Ȃ����@�L���ȌR�t���܂ł���", "���H�͂�΂�@���肪�Ƃ��������܂�" },
		{"�悤�����@�l�����ꂽ","�V�΂̊C�� ��"},
		{"�܂����R�t���܂Ɂ@���ڂ��w������������Ȃ��","�F�@�{����S�҂��ɂ��Ă����̂ł���"},
		{"������́@������ł����ɂ��܂�","�����̉p�Y�𓱂����@�`���̌R�t����"},
		{"�������������@�y���݂ō��͒��X�c"},
		{"�Ɓ@���炢�����܂���","�����@�P����ֈē��������܂���"},
		{"���Ȃ��l�̍єz","�y���݂ɂ��Ă��܂���"}
	};

	for (int i = 0; i < MESSAGE_LINE; ++i) {
		for (int j = 0; j < MESSAGE_NUM; ++j) {
			if (i < messageLine) {
				text[i][j] = message[i][j];  // ���łɕ`�悳�ꂽ�s�̃��b�Z�[�W���R�s�[
			}
			else if (i == messageLine) {
				text[i][j] = message[i][j].substr(0, messageCount);  // ���ݕ`�撆�̍s�̃��b�Z�[�W�𕔕��I�ɃR�s�[
			}
			else {
				text[i][j] = "";  // ���`��̍s�̃��b�Z�[�W�͋�ɂ���
			}
		}
	}

	if (messageLine < MESSAGE_LINE) {
		if (message[messageLine][0].length() > messageCount) {
			messageCount += addMessageNumber;
		}
		else {
			messageCount = 0;
			messageLine++;
		}
	}

	for (int i = 0; i < TEXT_LINE; ++i) {
		for (int j = 0; j < TEXT_NUM; ++j) {
			DrawStringEx(200, 540 + i * 80, -TEXT_COLOR_WHITE, "%s", text[i][j].c_str());
		}
	}
}

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
	g_titleMovie = LoadGraph("graphics/titleFlower.mp4");
	g_clearCracker = LoadGraph("graphics/clearCracker.mp4");

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
	
	//�}�b�v���̃{�^���`��
	g_bottonLayout = LoadGraph("graphics/bottonLayout.png");

	//�}�b�v��ł̍s���\�͈�
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//�U����ʂ̔w�i
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//�U���~�X�̉摜
	g_battleMiss = LoadGraph("graphics/miss.png");

	//�Q�[���I�[�o�[�w�i
	g_gameOver = LoadGraph("graphics/GameOver.jpg");
	
	//�Q�[���N���A�w�i
	g_gameClear = LoadGraph("graphics/GameClear.jpg");

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
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //X�����Ɠr������Đ����͂��܂�
	//}

	//�Ȃ�r������Đ�����
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);

	switch (g_gameScene_id) {

		case GAME_START: {

			titleBackDraw();			//�^�C�g���w�i�摜
			titleMovie();				//�^�C�g���A�j���[�V��������
			sceneTitle();				//�^�C�g���S��
			
			break;
		}
		case GAME_STORY:

			storyDraw();				//�X�g�[���[�w�i�`��
			storyMessage();				//�X�g�[���[���b�Z�[�W�`��

			break;

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
		case GAME_TUTORIAL: {
		
			break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
