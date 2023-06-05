#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <climits>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//
//�}�b�v��ł̎w���o���R�[�h(�����\�菈���ꗗ)
//
// -----------------------------------------------------------
// 
//�������S����������^�[���I���@OK
//���G�̃^�[���@OK
//���G�̓���AI�i�{�X�͓����Ȃ��j
//���S���̑ҋ@�m�F�@OK
//�������^�[���փt�F�[�Y�`�F���W�@OK
//���{�X��		�i������OK�j
//���X�e�[�W�N���A
//�Q�[���I�[�o�[	�i������OK�j


//����|���ƃG���f�B���O�˃N���A�����˃^�C�g����

//�n�`�̏�ɏ��ƁA���^�[���̗͉�

//if�G��move���̍��W�ɖ�������������˖����̍��W�֌������Ă���˃o�g�����͂��܂�i�֐��ցj


//-------------------------------------------------------------------------------------------
//�i�s�t�F�[�Y�̃t���O�ϐ�
//


//int g_gameScene_id = GAME_START; �{�Ԃ������I�I
int g_gameScene_id = GAME_START;

//�T�E���h�炵���iwav.mp3���������j
//��񂾂��Đ����߂��o���i���t���[�����ߏo���Ǝg���Ȃ��j
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

//�t�F�[�Y�ϐ�
int g_phase = PHASE_SELECT_CHARACTER;

//�^�[���ϐ�
int g_turnMove= TURN_ALLAY;

//�J�[�\���t���O
bool g_flagCursor = true;

//�G���^�[�����t���O
bool g_flagEnter = false;

//�X�y�[�X�����t���O
bool g_flagSpace=false;

//�o�g���i�s�����ۂ��̔���t���O
int g_CanAttackMove = 0;

//�����^�[���؂�ւ�
bool g_flagTurnAlly = true;

//�G�^�[���؂�ւ�
bool g_flagTurnEnemy = false;

//�Q�[���X�^�[�g
bool g_flagGameStart = false;

//�Q�[���I�[�o�[�t���O
bool g_flagGameOver = false;

//�Q�[���I�[�o�[���
int g_gameOver = 0;

//�Q�[���N���A���
int g_gameClear = 0;

//�X�R�A�ϐ�
int g_score = 0;

//-------------------------------------------------------------------------------------------

//���܂��m�F���ĂȂ��I����ɁA�O�����ݗL����D��U���t������
//�G����̍U������
bool moveEnemyToAlly(float delta_time, int enemy) {

	int enemyX = character[enemy].x;
	int enemyY = character[enemy].y;
	int moveCost = jobData[character[enemy].job].moveCells[mapData[enemyY][enemyX]];

	int ally = 0;
	int allyX = -1; // �ł��߂������L������X���W
	int allyY = -1; // �ł��߂������L������Y���W
	int maxDistance = INT_MAX; // �ő勗��

	// �}�b�v��̑S�Ă̍��W��T������
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			
			ally = getCharacter(j, i);
			
			if (ally != -1 && character[ally].team == TEAM_ALLY) {
			
				// �G�L�����Ƃ̋������v�Z
				int distance = abs(character[ally].x - enemyX) + abs(character[ally].y - enemyY);

				// �ŏ��������X�V���ꂽ�ꍇ�i���߂��ɂ���ꍇ�A���̋������ŏ��l�Ƃ���j
				if (distance < maxDistance) {
					allyX = character[ally].x;
					allyY = character[ally].y;
					maxDistance = distance;
				}
			}
		}
	}
	// �ł��߂������ׂ̗Ɉړ�
	if (allyX != -1 && allyY != -1 &&(ThreeRelation(enemy,ally))) {
		int distanceX = allyX - enemyX;
		int distanceY = allyY - enemyY;
		//int cellType = mapData[enemyY][enemyX];
		int moveRange = jobData[character[enemy].job].moveCells[cellType];

		// �ړ��\�͈͓�����ԋ߂��̖����ׂ̗Ɉړ�����
		if ((abs(distanceX) + abs(distanceY)) <= maxDistance &&
				(abs(distanceX) <= maxDistance && abs(distanceY) <= maxDistance  )) {
			enemyX = allyX;
			enemyY = allyY;

			// �G�̍��W���ړ���ׂ̗̃}�X�ɒ���
			if (distanceX < 0)
				enemyX--;
			else if (distanceX > 0)
				enemyX++;

			if (distanceY < 0)
				enemyY--;
			else if (distanceY > 0)
				enemyY++;
		}
	}
	// �ړ���̍��W��ݒ�
	character[enemy].x = enemyX;
	character[enemy].y = enemyY;

	return true; // �ړ�����
}

//--------------------------------------------------------------------------
//������
//���䂷����@�I�I
//ENEMYCHARACTER_MAX�萔�����B
//����character[3]==�ה���true�Ȃ�c�ŁA14�܂őS�č���Ĕ��肷��ifor�����g�킸�ɁA�S�ẴL�����̔��������j
//if else if�ŊǗ�����΁A���ԂɌ��Ă����̂ł́H�H


//��A�̗���
void turnMove(float delta_time) {

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED=700;
	const int TELOP_FRAME_MAX = 1400;

	//�e���b�v�A�j���[�V�����J�E���g
	float static g_telopTimeCount = 0;

	switch (g_turnMove) {

	case TURN_ALLAY: {

		if (g_flagTurnAlly) {

			//���t���[�������Ă�������
			g_telopTimeCount += delta_time;

			int telopFrame = g_telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][10], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;			//�e���b�v�̗��ꂽ�������Z�b�g
				g_telopTimeCount = 0;	//�e���b�v�̃J�E���g���Z�b�g
				g_flagTurnAlly = false; //�����^�[���̃e���b�v�����͈��Ŋ����̂���false
			}
		}
		phaseMove(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
			
			g_flagTurnEnemy = true;		//�G�^�[���̃e���b�v�𗬂����߂�true
			g_turnMove = TURN_ENEMY;
		}
	break;
	}

	case TURN_ENEMY: {

		if (g_flagTurnEnemy) {

			//���t���[�������Ă�������
			g_telopTimeCount += delta_time;

			int telopFrame = g_telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][9], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;				//�e���b�v�̗��ꂽ�������Z�b�g
				g_telopTimeCount = 0;		//�e���b�v�̃J�E���g���Z�b�g
				g_flagTurnEnemy = false;	//�G�^�[���̃e���b�v�����͈��Ŋ����̂���false
				g_flagSpace = true;			//�G�������ׂ̗ɖ��������邩�𔻒f���邽�߂̃t���O
			}
		}
		//�G��AI��������
		if (g_flagSpace) {

			while (g_standbyChara < CHARACTER_MAX) {
			
				if (g_standbyChara != 15 && character[g_standbyChara].team == TEAM_ENEMY && character[g_standbyChara].hp > 0) {

					if (moveEnemyToAlly(delta_time, g_standbyChara)) {	//�ׂ̃}�X�ɖ����������ꍇ

						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

							g_CanAttackMove++;
							g_flagEnter = true;			//�G���^�[�L�[�������邩�ǂ����i�퓬���͐퓬����̂��߂ɓ�������悤��true�j
							g_flagCursor = false;		//�J�[�\�����������邩�ۂ��i�퓬���͓������Ȃ��悤��false�j
							g_flagBattleAnime = true;	//�G�t�F�N�g�A�j���[�V�����̕ω��t���O�itrue��false�łP�Z�b�g�j
							g_flagBattleHp = true;		//�_���[�WHP�ω��̃t���O�itrue��false�łP�Z�b�g
						}
						battle(delta_time);
					}
				}
				g_standbyChara++;
			}
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
					
				if (!moveEnemyToAlly(delta_time, g_standbyChara)) {

					g_flagEnter = false;
					g_flagCursor = true;
					g_flagSpace = false;				//���Ȃ�����A�G�̔��f���I��
					character[0].done = false;
					character[1].done = false;			//�����^�[���ڍs�ɍۂ��āA�����̍s�������s���Ƀ��Z�b�g�����
					character[2].done = false;			//�����^�[���ڍs�ɍۂ��āA�����̍s�������s���Ƀ��Z�b�g�����
					g_flagTurnAlly = true;				//�����^�[���̃e���b�v�𗬂����߂�true
					g_turnMove = TURN_ALLAY;
				}
			}
		}
	break;
	}

	}
}

//�J�[�\���G���^�[�����ɂ���
void phaseMove(float delta_time) {

	switch (g_phase) {

		case PHASE_SELECT_CHARACTER: {

			//�񕜒n�`�̏�ɂ�����A�^�[���J�n���ɂP�O�O��
			for (int i = 0; i < MAP_HEIGHT; i++) {
				for (int j = 0; j < MAP_WIDTH; j++) {
				
					int startChara = getCharacter(j, i);
					if (startChara == CELL_HOUSE || startChara == CELL_FORT) {
						
						if (character[startChara].hp > 0 && character[startChara].hp < character[startChara].maxHp) {

							character[startChara].hp += 100;

							if (character[startChara].hp >= character[startChara].maxHp) {

								character[startChara].hp = character[startChara].maxHp;
							}
						}
					}
				}
			}
			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				resetFill();

				//�I�������L�����N�^�[���͂��ē�����k��1�}�X���h��Ԃ�
				int chara = getCharacter(cursorX, cursorY);
				if (chara < 0) { break; } //���̒l�������炢�Ȃ�
				
				//�s���ς݂Ȃ���W�����Ȃ�
				//if (character[chara].done) {resetFill();}
				
				//�L�����������(����ȊO��)�h��Ԃ�
				else {

					for (int dir = 0; dir < DIRECTION_MAX; dir++)
					{
						int x = character[chara].x + g_directions[dir][0];
						int y = character[chara].y + g_directions[dir][1];
						fillCanMove(chara, x, y, character[chara].move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
					}

					//�`����ɃL������������A�����͕`�悵�Ȃ�
					for (int i = 0; i < MAP_HEIGHT; i++) {
						for (int j = 0; j < MAP_WIDTH; j++) {

							int standChara = getCharacter(j, i);
							if (standChara >= 0 && fill[i][j]) {fill[i][j] = false;}
						}
					}
					drawFill();

					//�L������I��������A�ړ��t�F�[�Y��
					if (character[chara].team == TEAM_ALLY) {

						g_selectedChara = chara; //�����L��������
						g_phase = PHASE_SET_MOVE_POSITION;
					}
				break;
				}
			}		
		}
		case PHASE_SET_MOVE_POSITION: {

			drawFill();

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				//�ړ���̑I���A����������I���t�F�[�Y�ɖ߂�
				if (fill[cursorY][cursorX]) {

					//�ړ��ɂ����W�̕ω�
					character[g_selectedChara].x = cursorX;
					character[g_selectedChara].y = cursorY;
				
					bool checkBattleFlag = false;
				
					for (int i = 0; i < CHARACTER_MAX; i++) {

						if (checkCanAllyBattle(g_selectedChara, i)) {

							g_standbyChara = i;
							checkBattleFlag = true;
							break;
						}
					}
				
					if (checkBattleFlag) {g_phase = PHASE_SELECT_ATTACK;}
				
					else {
						//�U���\�L���������Ȃ���΁A�ҋ@
						character[g_selectedChara].done = true;
						resetFill();
						g_phase = PHASE_SELECT_CHARACTER;
					}
				}
			}
			break;
		}
		case PHASE_SELECT_ATTACK: {

			if (character[g_standbyChara].x == cursorX && character[g_standbyChara].y == cursorY) {

				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

					g_flagEnter = true;
					g_flagCursor= false;
					g_flagBattleAnime = true;
					g_flagBattleHp = true;
					g_CanAttackMove ++;
				}	
				battle(delta_time);
			}
		break;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		//�U���\�L���������Ȃ���΁A�ҋ@
		character[g_selectedChara].done = true;
		resetFill();
		g_phase = PHASE_SELECT_CHARACTER;
	}
}

void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//���y�̏o��--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlib���t�@�����X�A���[�v�����̈���

	//SE�̏o��
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//�摜�̏o��--------------------------------------------

	//�Q�[���X�^�[�g���
	g_gameStart = LoadGraph("graphics/GameStart.jpg");
	
	//�Q�[���X�^�[�g��ʃA�j���[�V����
	g_gameStartAnim = LoadGraph("graphics/titleSakura.png");

	//�^�C�g���I���摜
	g_select_cursor_hdl = LoadGraph("graphics/flowerSelect.png");

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

			DrawExtendGraph(0, 0, 1300, 750, g_gameStart, true);
			rightFlash(delta_time);
			sceneTitle();

			//PlayMovieToGraph(confetti);

			break;
		}
		case GAME_STORY:

			break;

		case GAME_MAP: {

			getCharaPosition();
			mapPosition(delta_time);
			display();
			cursorMove();//��<resetFill()/drawFill())��getCharacter(,)/return��fillCanMove(,,,)
			instructions(delta_time);
			scoreDraw();
			turnMove(delta_time);
			
			break;
		}
		case GAME_OVER: {

			gameOver(delta_time);
			
			break;
		}
		case GAME_CLEAR:
			
			const int BACK_START_X_Y = 0;
			const int BACK_END_X = 1300;
			const int BACK_END_Y = 750;

			DrawExtendGraph(BACK_START_X_Y, BACK_START_X_Y, BACK_END_X, BACK_END_Y, g_gameClear, true);

			break;
	}
}
//
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


//�_�O���t�ł̃_���[�W���Z
//DrawExtend�ŁA�_���[�W�󂯂���i�t���O�Ǘ��j���̕������炷�i�`��̃T�C�Y��ς���j