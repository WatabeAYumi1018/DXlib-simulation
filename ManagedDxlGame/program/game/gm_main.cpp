#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"

//
//�}�b�v��ł̎w���o���R�[�h(�����\�菈���ꗗ)
//
// -----------------------------------------------------------
// 
//�������S����������^�[���I��
//���G�̃^�[��
//���G�̓���AI�i�{�X�͓����Ȃ��j
//���S���̑ҋ@�m�F
//�������^�[���փt�F�[�Y�`�F���W
//���{�X��		�i������OK�j
//���X�e�[�W�N���A
//�Q�[���I�[�o�[	�i������OK�j


//����|���ƃG���f�B���O�˃N���A�����˃^�C�g����

//�n�`�̏�ɏ��ƁA���^�[���̗͉�

//�����S����done=true�œG�t�F�[�Y�ֈڍs�i���܂ł̃t�F�[�Y�͑S�������̏����ł���I�j

//if�G��move���̍��W�ɖ�������������˖����̍��W�֌������Ă���˃o�g�����͂��܂�i�֐��ցj

//�G�t�F�[�Y�����B

//-------------------------------------------------------------------------------------------
//�i�s�t�F�[�Y�̃t���O�ϐ�
//



//�T�E���h�炵���iwav.mp3���������j
//��񂾂��Đ����߂��o���i���t���[�����ߏo���Ǝg���Ȃ��j
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;


//�t�F�[�Y�ϐ����쐬
int g_phase = PHASE_SELECT_CHARACTER;

//�J�[�\���t���O
bool g_flagCursor = true;

//�G���^�[�����t���O
bool g_flagEnter = false;

//�o�g���i�s�����ۂ��̔���t���O
int g_CanAttackMove = 0;

//-------------------------------------------------------------------------------------------

//�J�[�\���G���^�[�����ɂ���
void phaseMove(float delta_time) {

	switch (g_phase) {

		case PHASE_SELECT_CHARACTER: {

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				resetFill();

				//�I�������L�����N�^�[���͂��ē�����k��1�}�X���h��Ԃ�
				int chara = getCharacter(cursorX, cursorY);
				if (chara < 0) { break; } //�������̒l�������炻���ɃL�����͂��Ȃ����h��Ԃ��Ȃ�

				//�s���ς݂Ȃ���W�����Ȃ�
				//if (character[chara].done) { resetFill(); }

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

						if (checkCanBattle(g_selectedChara, i)) {
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

				if (g_flagEnter && !g_flagCursor) {

					//�퓬��ʉ��O���t�B�b�N�`��
					battleGraph();
					
					//HP�`��
					battleHp(g_selectedChara, g_standbyChara);

					//�퓬��ʉ����`��
					battleInfo(g_selectedChara, g_standbyChara);

					//�퓬��ʂ̃L�����A�j���[�V����
					battleCharaGraphic(delta_time, g_selectedChara, g_standbyChara);			

					if (g_CanAttackMove == 1) {

						//attack���̍U���G�t�F�N�g�`��
						battleEffectGraphic(delta_time, g_selectedChara);
					}

					else if (g_CanAttackMove == 2) {//�����̍U��
						
						//HP�v�Z
						battleMove(delta_time, g_selectedChara, g_standbyChara);

						 if (character[g_standbyChara].hp <= 0) {battleExit();}
					}
					
					else if (g_CanAttackMove == 3) {

						//defence���̍U���G�t�F�N�g�`��
						battleEffectGraphic(delta_time, g_standbyChara);
					}
					
					else if(g_CanAttackMove == 4) {

						//HP�v�Z
						battleMove(delta_time, g_standbyChara, g_selectedChara);

						if(character[g_selectedChara].hp <= 0){battleExit();}
					}

					else if (g_CanAttackMove == 5) {

						if (character[g_selectedChara].speed - character[g_standbyChara].speed >= SPEED_DIFFERENCE) {

							battleEffectGraphic(delta_time, g_selectedChara);
						}

						else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

							battleEffectGraphic(delta_time, g_standbyChara);
						}

						else {battleExit();}
					}

					else if (g_CanAttackMove == 6) {

						if (character[g_selectedChara].speed - character[g_standbyChara].speed >= SPEED_DIFFERENCE) {

							//HP�v�Z
							battleMove(delta_time, g_selectedChara, g_standbyChara);
						}

						else if (character[g_standbyChara].speed - character[g_selectedChara].speed >= SPEED_DIFFERENCE) {

							//HP�v�Z
							battleMove(delta_time, g_standbyChara, g_selectedChara);
						}
					}

					else if (g_CanAttackMove == 7) { battleExit(); }
				}

			}
			//else if (character[g_selectedChara].x == cursorX && character[g_selectedChara].y == cursorY) {
			//	//������I���őҋ@
			//	character[g_selectedChara].done = true;
			//	resetFill();
			//	g_phase = PHASE_SELECT_CHARACTER;
			//}
		break;
		}
	}
}


void gameStart() {
	srand(time(0));

	SetWindowText("�t�@�C�A�[�G���u�������ۂ�����");

	//���y�̏o��--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlib���t�@�����X�A���[�v�����̈���

	//SE�̏o��
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//�摜�̏o��--------------------------------------------
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
	//LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

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

	getCharaPosition();
	mapPosition();
	display();
	cursorMove();//��<resetFill()/drawFill())��getCharacter(,)/return��fillCanMove(,,,)
	instructions();
	phaseMove(delta_time);

}
//
//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}


//�_�O���t�ł̃_���[�W���Z�`��
//DrawExtend�ŁA�_���[�W�󂯂���i�t���O�Ǘ��j���̕������炷�i�`��̃T�C�Y��ς���j