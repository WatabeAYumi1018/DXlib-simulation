#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"


//----------------------------------------------------------------------------
//�}�b�v�S�ʂ̕ϐ�
//

//�O���X�}�b�v�S�̂�z��Ƃ��Ċi�[
int mapData[MAP_HEIGHT][MAP_WIDTH] = {
{4,5,1,1,1,4,5,4,5,4,5,4,5,4,5,4,5,6,7,6,7,4,5,6,7,4,5,6,7,1,6,7,6,7,4,5,4,5,6,7},
{6,7,1,8,9,6,7,6,7,6,7,6,7,6,7,6,7,1,1,1,1,6,7,4,5,6,7,1,1,1,1,4,5,1,6,7,6,7,4,5},
{5,4,5,10,11,4,5,4,5,1,4,5,4,5,4,5,1,1,1,4,5,4,5,6,7,1,1,1,1,1,1,6,7,1,1,1,2,1,6,7},
{7,6,7,0,0,6,7,6,7,1,6,7,6,7,6,7,1,4,5,6,7,6,7,1,1,1,1,3,0,0,0,1,1,1,0,0,0,0,1,4},
{4,5,1,1,0,0,0,0,0,0,1,1,1,4,5,4,5,6,7,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,6},
{6,7,4,5,0,0,0,0,0,0,0,0,0,6,7,6,7,1,1,2,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,4},
{5,1,6,7,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,6},
{7,4,5,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,4},
{1,6,7,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,1,6},
{4,5,1,1,1,1,4,5,1,0,3,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
{6,7,1,4,5,1,6,7,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1},
{5,4,5,6,7,4,5,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,2,1,1,1,4},
{7,6,7,1,1,6,7,4,5,1,1,2,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,4,5,1,1,4,5,4,5,4,5,4,5,6},
{5,4,5,4,5,1,1,6,7,4,5,1,1,1,1,1,1,4,5,4,5,4,5,1,3,1,1,6,7,4,5,6,7,6,7,6,7,6,7,4},
{7,6,7,6,7,4,5,4,5,6,7,4,5,1,1,4,5,6,7,6,7,6,7,4,5,4,5,4,5,6,7,4,5,4,5,4,5,4,5,6}
};

//������k�̃x�N�g�����`�i�����j
int g_directions[][2] = {///�󔒂ɂ���Ə������q�������I�ŗv�f�������肵�Ă����B�����[4][2]�B
{0,-1}, //DIRECTION_NORTH
{1,0},	//DIRECTION_EAST
{0,1},	//DIRECTION_SOUTH
{-1,0}	//DIRECTION_WEST
};

//�h��Ԃ��z��
bool fill[MAP_HEIGHT][MAP_WIDTH];

//�J�[�\�����W���`
int cursorX = 0;
int cursorY = 0;


//----------------------------------------------------------------------------
//�}�b�v�`��S�ʂ̉摜�`��Ɋւ���n���h��
//

//�`�b�v�摜
int character_chips[7][12];	//�L�����`�b�v�i�[�z��
int map_chips[1][88];		//�}�b�v�`�b�v�i�[�z��

//�}�b�v�摜�ϐ�
int graphic_cell_ground = 0;

//�}�b�v���摜
int display_map = 0;

//�J�[�\���摜
int g_cursor = 0;

//�s���\�͈͉摜
int fill_map = 0;

//�O�����ݖ��摜
int g_relation = 0;
int g_relation_back = 0;

//�}�b�v��ʂł̃^�[������
int g_map_turn[1][15];

//----------------------------------------------------------------------------
//�}�b�v�S�ʂɊւ��֐�
//

//fill�̏������i��������Ȃ��ƁA���ɑI�����Ă��O�̑I����񂪎c�����܂܂ɂȂ��Ă��܂��j
void resetFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			fill[i][j] = false;

			//�����S��done�œG�t�F�[�Y��
		}
	}
}

//fill�̉摜�`��
void drawFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (fill[i][j]) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, fill_map, TRUE); }//�h��Ԃ��\�Ȃ�`��
		}
	}
}

//�h��Ԃ��ł��邩�ǂ�ǂ񔻒肵�Ă�
void fillCanMove(int _chara, int _x, int _y, int _move) {//�I�����������L�����A���W�A�ړ���

	//��ʊO�̓X���[
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return; }


	//������ꏊ��cell�����擾�A�E�Ƃ̏��ƍ��킹��moveCells���擾����
	//�Ⴆ�΁A�X�̏�ɂ���ꍇ�́A�E�Ƃɂ���Ă͈ړ��R�X�g�P�A�Q�������肷��B
	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	//�ړ��\�����O�ȉ��A�ړ��\����艺�Ȃ�`��s�ŏI��
	if (moveCost < 0 || _move < moveCost) { return; }

	//��������Ȃ���Γh��Ԃ��\
	fill[_y][_x] = true;

	//�ړ����邲�ƂɃR�X�g���g���Ă���
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		fillCanMove(_chara, x, y, _move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
	}
}

//����e�t�F�[�Y�ł̎w�������`�揈���i�����ɓ_�ŏ����������悤�j
void instructions() {

	//�e�t�F�[�Y�ł̎w�����͕`��
	switch (g_phase) {

	case PHASE_SELECT_CHARACTER:
		SetFontSize(30);
		DrawString(700, 10, "�L�����N�^�[��I��ł�������\n", -1);
		break;

	case PHASE_SET_MOVE_POSITION:
		SetFontSize(30);
		DrawString(700, 10, "�ړ����I��ł�������\n", -1);
		break;

	case PHASE_SELECT_ATTACK:
		SetFontSize(30);
		DrawString(700, 10, "�U���Ώۂ�I��ł�������\n", -1);
		break;
	}
}

//�J�[�\���ړ�
void cursorMove() {
	if (g_flagCursor) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1) { cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0)				 { cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1) { cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0)				 { cursorX--; }

		WaitTimer(100);
	}
}

//�}�b�v�S�̂̏���ǂݎ��Aif�Ŋe�����ɑΉ�����`�b�v��`�悷��
void mapPosition() {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			//���n�}�b�v�̕`��i���n�j
			DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][0], TRUE);

			//�}�b�v�`�b�v�`��
			if (mapData[i][j] == 1) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][9], TRUE); }
			else if (mapData[i][j] == 2) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][56], TRUE); }
			else if (mapData[i][j] == 3) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][73], TRUE); }
			else if (mapData[i][j] == 4) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][32], TRUE); }
			else if (mapData[i][j] == 5) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][33], TRUE); }
			else if (mapData[i][j] == 6) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][40], TRUE); }
			else if (mapData[i][j] == 7) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][41], TRUE); }
			else if (mapData[i][j] == 8) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][51], TRUE); }
			else if (mapData[i][j] == 9) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][52], TRUE); }
			else if (mapData[i][j] == 10) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][59], TRUE); }
			else if (mapData[i][j] == 11) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][60], TRUE); }

			//�L�����`�b�v�`��
			if (charaData[i][j] >= 0) {

				if (charaData[i][j] == 0) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[0][1], TRUE); }
				else if (charaData[i][j] == 1) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[1][1], TRUE); }
				else if (charaData[i][j] == 2) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[2][1], TRUE); }

				else if (charaData[i][j] == 3 || charaData[i][j] == 6 || charaData[i][j] == 9 || charaData[i][j] == 12)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[3][1], TRUE);
				}
				else if (charaData[i][j] == 4 || charaData[i][j] == 7 || charaData[i][j] == 10 || charaData[i][j] == 13)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[4][1], TRUE);
				}
				else if (charaData[i][j] == 5 || charaData[i][j] == 8 || charaData[i][j] == 11 || charaData[i][j] == 14)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[5][1], TRUE);
				}
				else if (charaData[i][j] == 15)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[6][1], TRUE);
				}
			}
			//�}�b�v��ł̃L��������ʕ`��
			DrawExtendGraph(0, 500, 1400, 730, display_map, true);

			//�O�����݊֘A�摜�`��
			DrawExtendGraph(0, 370, 125, 480, g_relation_back, true);
			DrawGraph(15, 370, g_relation, TRUE);
			DrawExtendGraph(0, 370, 40, 410, icon_sword, true);
			DrawExtendGraph(35, 440, 75, 480, icon_magic, true);
			DrawExtendGraph(85, 390, 125, 430, icon_snip, true);


			//���݂̑I���J�[�\���̈ʒu��`��
			if (j == cursorX && i == cursorY) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, g_cursor, TRUE); }
		}
	}
}