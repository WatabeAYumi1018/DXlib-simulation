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

//-------------------------------------------------------------------------------------------
//

//�Q�[���S�̂̃V�[���ڍs
int g_gameScene_id = GAME_START;

//�T�E���h�֘A�n���h��----------------------------------

//�T�E���h�@�^�C�g��
int g_bgmTitle = 0;
//�T�E���h�@�}�b�v
int g_bgmMap = 0;
//�T�E���h�@�G���f�B���O
int g_bgmEnding = 0;
//�T�E���h�@�Q�[���I�[�o�[
int g_bgmGameOver = 0;

//�U��SE�@�|
int g_seEffectAllow = 0;
//�U��SE�@��
int g_seEffectSword = 0;
//�U��SE�@���@
int g_seEffectMagic = 0;
//�U��SE�@��
int g_seEffectBoss = 0;
//�^�[���ڍs�@&&�@�o�g���J�n
int g_seMoveBattle = 0;

//����{�^���摜�n���h��----------------------------------

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

//-------------------------------------------------------------------------------------------
//�N�����Ɉ��̂ݎ��s����܂�
void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//���y�̏o��--------------------------------------------
	// 
	//BGM�̏o��
	g_bgmTitle = LoadSoundMem("sound/title.mp3");
	g_bgmMap = LoadSoundMem("sound/map.mp3");
	g_bgmEnding = LoadSoundMem("sound/ending.mp3");
	g_bgmGameOver = LoadSoundMem("sound/gameOver.mp3");

	//�^�C�g���`�`���[�g���A���ɂčĐ�
	PlaySoundMem(g_bgmTitle, DX_PLAYTYPE_LOOP, TRUE);

	//SE�o��	
	g_seEffectAllow = LoadSoundMem("sound/effectAllow.mp3");
	g_seEffectSword = LoadSoundMem("sound/effectSword.mp3");
	g_seEffectMagic = LoadSoundMem("sound/effectMagic.wav");
	g_seEffectBoss = LoadSoundMem("sound/effectBoss.mp3");
	g_seMoveBattle = LoadSoundMem("sound/battleStart.mp3");

	//�����̏o��--------------------------------------------

	//�����t�H���g
	tnl::AddFontTTF("font/PixelMplus12-Regular.ttf");

	//�摜�̏o��--------------------------------------------

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
	g_title = LoadGraph("graphics/GREEN OCEAN.png");

	//�X�g�[���[�V�[���w�i
	g_storyBack = LoadGraph("graphics/GameStoryBack.png");

	//��b�E�B���h�E
	g_storyWindow = LoadGraph("graphics/storyWindow.png");

	//�}�b�v�f�[�^
	LoadDivGraph("graphics/pipo-map001.png", 88, 8, 11, CHIP_SIZE, CHIP_SIZE, map_chips[0]);

	//�L����
	LoadDivGraph("graphics/player1.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[0]);
	LoadDivGraph("graphics/player2.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[1]);
	LoadDivGraph("graphics/player3.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[2]);
	LoadDivGraph("graphics/enemy1.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[3]);
	LoadDivGraph("graphics/enemy2.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[4]);
	LoadDivGraph("graphics/enemy3.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[5]);
	LoadDivGraph("graphics/enemyBOSS.png", 12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[6]);

	//�J�[�\��
	g_cursor = LoadGraph("graphics/cursor.png");

	//�}�b�v��ł̏��\���p�i����ʁj
	display_map = LoadGraph("graphics/mapInfo.png");

	//�}�b�v��ł̍s���\�͈�
	fill_map = LoadGraph("graphics/canMoveTile.png");

	//�U����ʂ̔w�i
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//�Q�[���I�[�o�[�w�i
	g_gameOver = LoadGraph("graphics/GameOver.jpg");

	//�Q�[���N���A�w�i
	g_gameClear = LoadGraph("graphics/GameClear.png");

	//�U�����̉����
	LoadDivGraph("graphics/battleHp.png", 35, 5, 7, 120, 60, g_battle_hp[0]);
	LoadDivGraph("graphics/battleAttack.png", 42, 3, 14, 300, 60, g_battle_attack[0]);
	LoadDivGraph("graphics/battleHit.png", 25, 5, 5, 180, 60, g_battle_hit[0]);

	//�U���G�t�F�N�g�A�j���[�V����
	LoadDivGraph("graphics/effect_sword.png", 15, 5, 3, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_sword[0]);
	LoadDivGraph("graphics/effect_snip.png", 10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_snip[0]);
	LoadDivGraph("graphics/effect_magic.png", 14, 14, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_magic[0]);
	LoadDivGraph("graphics/effect_leader.png", 10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_leader[0]);

	//�E�ƃA�C�R��
	icon_sword = LoadGraph("graphics/iconSWORD.png");
	icon_magic = LoadGraph("graphics/iconMAGIC.png");
	icon_snip = LoadGraph("graphics/iconSNIP.png");
	icon_boss = LoadGraph("graphics/iconBOSS.png");

	//�O�����݃G�t�F�N�g
	g_relation_back = LoadGraph("graphics/relationBack.png");
	g_relation = LoadGraph("graphics/relation.png");

	//�}�b�v��ʂł̃^�[������
	LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

	//����{�^���֌W-----------------------------

	//�G���^�[�{�^��
	g_bottonEnter = LoadGraph("graphics/leafEnter.png");
	//�J�[�\���{�^��
	g_bottonCursor = LoadGraph("graphics/leafCursor.png");
	//�^�u�{�^��
	g_bottonTab = LoadGraph("graphics/leafTab.png");
	//�X�y�[�X�{�^��
	g_bottonSpace = LoadGraph("graphics/leafSpace.png");

	//�����G�֌W-----------------------------

	//���������G
	g_girlNormal = LoadGraph("graphics/girlNormal.png");
	g_girlSmile = LoadGraph("graphics/girlSmile.png");
	g_girlTroubled = LoadGraph("graphics/girlTroubled.png");

	//�������G
	g_bossNormal = LoadGraph("graphics/bossTutorialNormal.png");
	g_bossSmile = LoadGraph("graphics/bossTutorialSmile.png");

	//�`���[�g���A���֌W-----------------------------
	
	//�}�b�v�S�̐}
	g_tutorialMap = LoadGraph("graphics/tutorialMap.png");
	//�Q�[���ړI
	g_tutorialMapStream = LoadGraph("graphics/tutorialMapStream.png");
	//�����^�[���J�[�\��
	g_tutorialAllyTurnCursor = LoadGraph("graphics/tutorialAllyTurnCursor.png");
	//����ʏ��
	g_tutorialAllyTurnInfoSpeed = LoadGraph("graphics/tutorialAllyTurnInfoSpeed.png");
	//�����^�[���ړ���I��
	g_tutorialAllyTurnSelect = LoadGraph("graphics/tutorialAllyTurnSelect.png");
	//�����^�[���ړ�
	g_tutorialAllyTurnMove = LoadGraph("graphics/tutorialAllyTurnMove.png");
	//�����^�[���U���\��
	g_tutorialPredictionBattle = LoadGraph("graphics/tutorialPredictionBattle.png");
	//�G�^�[��
	g_tutorialEnemyTurn = LoadGraph("graphics/tutorialEnemyTurn.png");
	//�G�^�[���I��
	g_tutorialMapEnemyTurnMove = LoadGraph("graphics/tutorialEnemyTurnMove.png");
	//�񕜃X�|�b�g����
	g_tutorialMapHeal = LoadGraph("graphics/tutorialMapHeal.png");
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�,60FPS
void gameMain(float delta_time) {

	switch (g_gameScene_id) {

		case GAME_START: {

			soundTitle();					//�^�C�g����ʂł̃T�E���h����
			titleBackDraw();				//�^�C�g���w�i�摜
			movieDraw();					//�^�C�g���A�j���[�V��������
			sceneTitle();					//�^�C�g���S��

			break;
		}
		case GAME_STORY: {

			soundTitle();					//�^�C�g����ʂł̃T�E���h����
			storyDraw();					//�X�g�[���[�w�i�`��
			storyMessage();					//�X�g�[���[���b�Z�[�W�`��
			leafBottonDrawStory(delta_time);//�G���^�[�摜�`��

			break;
		}
		case GAME_TUTORIAL: {

			soundTitle();					//�^�C�g����ʂł̃T�E���h����
			tutorialDraw();					//�`���[�g���A���摜�`��
			tutorialMessage();				//�`���[�g���A�����b�Z�[�W�`��
			leafBottonDrawStory(delta_time);//�G���^�[�摜�`��

			break;
		}
		case GAME_MAP: {

			playMusic();					//�����֘A
			getCharaPosition();				//charaData[MAP_HEIGHT][MAP_WIDTH]��`
			mapPosition(delta_time);		//�摜�`��
			display();						//����ʏ��`�搧��
			cellInfoDisplay();				//�n�`�񕜏��\������
			cursorMove(delta_time);			//�J�[�\���ړ����`
			instructions(delta_time);		//�w�������`��
			scoreDraw();					//score�`��
			turnMove(delta_time);			//�Q�[���̗���S��
			
			break;
		}
		case GAME_OVER: {

			soundOver();					//�Q�[���I�[�o�[���y�Đ�
			gameOver(delta_time);			//�Q�[���I�[�o�[�S��	
			scoreResult();					//�X�R�A�`��
				
			break;
		}
		case GAME_CLEAR: {

			soundClear();					//�N���A���y�Đ�
			gameClear(delta_time);			//�Q�[���N���A�S��
			leafBottonDrawStory(delta_time);//�G���^�[�摜�`��
			movieDraw();					//�G���h�A�j���[�V��������

			break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
