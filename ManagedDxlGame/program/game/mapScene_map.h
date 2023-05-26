#pragma once

//�T�C�Y�Ɋւ���萔
const int MAP_HEIGHT = 15;		//�}�b�v��ʍ���
const int MAP_WIDTH = 40;		//�}�b�v��ʕ�
const int CHIP_SIZE = 32;		//�`�b�v�T�C�Y

//���ߕ��̍��W
const int INSTRUCTIONS_X = 700;
const int INSTRUCTIONS_Y = 10;

extern int mapData[MAP_HEIGHT][MAP_WIDTH];

//�h��Ԃ��̒�`
extern bool fill[MAP_HEIGHT][MAP_WIDTH];

//�s���\�͈͓h��Ԃ�
extern int fill_map;

//�J�[�\�����W���`
extern int cursorX ;
extern int cursorY ;

//�}�b�v�`�b�v
extern int graphic_cell_ground;

//�`�b�v�摜
extern int character_chips[7][12];	//�L�����`�b�v�i�[�z��
extern int map_chips[1][88];		//�}�b�v�`�b�v�i�[�z��

//�}�b�v��ʂł̏��`��
extern int display_map ;

//�J�[�\���摜
extern int g_cursor ;

//�O�����ݖ��摜
extern int g_relation ;
extern int g_relation_back ;

//�}�b�v��ʂł̃^�[������
extern int g_map_turn[1][15];

//������k�̃x�N�g��
extern int g_directions[][2];

//�n�`���
enum {
	CELL_GROUND,              //���n0
	CELL_FOREST,             //�X1
	CELL_HOUSE,              //����2
	CELL_FORT,               //��3
	CELL_MOUNTAIN_LEFT_UP,   //�R�i����j4
	CELL_MOUNTAIN_RIGHT_UP,  //�R�i�E��j5
	CELL_MOUNTAIN_LEFT_DOWN, //�R�i�����j6
	CELL_MOUNTAIN_RIGHT_DOWN,//�R�i�E���j7
	CELL_CASTLE_LEFT_UP,     //��i����j8
	CELL_CASTLE_RIGHT_UP,    //��i�E��j9
	CELL_CASTLE_LEFT_DOWN,   //��i�����j10
	CELL_CASTLE_RIGHT_DOWN,   //��i�E���j11
	CELL_MAX
};

//������k
enum {
	DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_MAX
};

//fill�̏������i��������Ȃ��ƁA���ɑI�����Ă��O�̑I����񂪎c�����܂܂ɂȂ��Ă��܂��j
void resetFill();

//fill�̉摜�`��
void drawFill();

//�h��Ԃ��ł��邩�ǂ�ǂ񔻒肵�Ă�
void fillCanMove(int _chara, int _x, int _y, int _move);

//����e�t�F�[�Y�ł̎w�������`�揈���i�����ɓ_�ŏ����������悤�j
void instructions();

//�J�[�\���ړ�
void cursorMove();

//�}�b�v�S�̂̏���ǂݎ��Aif�Ŋe�����ɑΉ�����`�b�v��`�悷��
void mapPosition();
