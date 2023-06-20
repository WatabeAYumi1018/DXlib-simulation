#pragma once

//�T�C�Y�Ɋւ���萔
const int MAP_HEIGHT = 15;		//�}�b�v��ʍ���
const int MAP_WIDTH = 40;		//�}�b�v��ʕ�
const int CHIP_SIZE = 32;		//�`�b�v�T�C�Y

extern int mapData[MAP_HEIGHT][MAP_WIDTH];

//�h��Ԃ��̒�`
extern bool fill[MAP_HEIGHT][MAP_WIDTH];

//�s���\�͈͓h��Ԃ�
extern int fill_map;

//�J�[�\�����W���`
extern int cursorX ;
extern int cursorY ;

//�}�b�v�`�b�v�摜�n���h��
extern int graphic_cell_ground;

//�`�b�v�摜�n���h��
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

//�����t�F�[�Y�ϐ�
extern int g_phaseAlly ;

//�G�t�F�[�Y�ϐ�
extern int g_phaseEnemy;

//�^�[���ϐ�
extern int g_turnMove ;

//�J�[�\���t���O
extern bool g_flagCursor;

//�G���^�[�����t���O
extern bool g_flagEnter ;

//�X�y�[�X�����t���O
extern bool g_flagEnemy ;

//�o�g���i�s�����ۂ��̔���t���O
extern int g_CanAttackMove ;

//���ݓG���l�ڂ��i�����l�̓C���f�b�N�X�̂R�j
extern int currentEnemyNumber ;

// �ŏ������̖����擾
extern int nearDistanceAlly ;

//�����^�[���؂�ւ�
extern bool g_flagTurnAlly ;

//�G�^�[���؂�ւ�
extern bool g_flagTurnEnemy;

//�X�R�A�ϐ�
extern int g_score ;

//�G��Ĉړ��t���O
extern bool g_enemyCheckFinish ;

//SE�Đ��t���O
extern bool g_sePlay;

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

//��A�̗���
void turnMove(float delta_time);

//�����^�[���̏���
void phaseAllyMove(float delta_time);

//�G�^�[���̏���
void phaseEnemyMove(float delta_time, int currentEnemyNumber);

//score�\��
void scoreDraw();

//fill�̏������i��������Ȃ��ƁA���ɑI�����Ă��O�̑I����񂪎c�����܂܂ɂȂ��Ă��܂��j
void resetFill();

//fill�̉摜�`��
void drawFill();

//�h��Ԃ��ł��邩�ǂ�ǂ񔻒肵�Ă�
void fillCanMove(int _chara, int _x, int _y, int _move);

//����e�t�F�[�Y�ł̎w�������`�揈���i�����ɓ_�ŏ����������悤�j
void instructions(float delta_time);

//�J�[�\���ړ�
void cursorMove(float delta_time);

//�}�b�v�S�̂̏���ǂݎ��Aif�Ŋe�����ɑΉ�����`�b�v��`�悷��
void mapPosition(float delta_time);

//�����^�[���}�b�v��ʂ̃{�^���\�L
void leafBottonDrawAllyTurnMap(float delta_time);

//�퓬�O�̏��\���`��(�U��/�h��)
void prediction(int attack, int defence);

//�퓬�O���O���t�B�b�N�`��
void predictionDraw(int attack, int defence);

//�񕜒n�`�̏�ɂ�����A�^�[���J�n���ɑS��
void cellHeal();

//�񕜏��`��
void cellInfoDisplay();

//�����֘A
void playMusic();

//se�Đ�
void playSeTurnMove();
