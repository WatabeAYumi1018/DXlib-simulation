#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"

//�^�C�g������
int g_title = 0;

//�J�[�\�������ʒu���͂��߂����
int g_select_player_menu = TITLE_MENU_FIRST;

//�J�[�\���������鉻���邽�߂̕ϐ����쐬
int g_select_cursor = 0;				

//�I���J�[�\���̃|�W�V����
tnl::Vector3 g_sel_cursor_pos = TITLE_SELECT_MENU_POSITION[g_select_player_menu];

//�Q�[���X�^�[�g���
int g_gameStart = 0;

//�Q�[���X�^�[�g���
int g_gameStartAnim = 0;

//�^�C�g�����̓���
int g_titleMovie = 0;

//�N���A���̓���
int g_clearFlower=0;

//�X�N���[��(�t�B���^�[���������摜��ۑ�����p)�n���h��
int screen_handle = 0;	

//���邳�N���b�v�t�B���^�[�Ɏg�p����臒l
int bright_border = 150; 

//�X�g�[���[�������u�����h
int g_titleRight = 0;

//�^�C�g�����j���[�őI��
void titleSelect() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		g_select_player_menu--;
		if (g_select_player_menu < 0)g_select_player_menu = TITLE_MENU_CHARACTER;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		g_select_player_menu++;
		if (g_select_player_menu >= TITLE_MENU_MAX)g_select_player_menu = TITLE_MENU_FIRST;
	}
	g_sel_cursor_pos = TITLE_SELECT_MENU_POSITION[g_select_player_menu];

	//�G���^�[���������ꏊ�ɂ���ăV�[�����ς��
	if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

		if (g_select_player_menu == TITLE_MENU_FIRST) { g_gameScene_id = GAME_STORY; }
		if (g_select_player_menu == TITLE_MENU_CONTINUE) { g_gameScene_id = GAME_MAP; }
		if (g_select_player_menu == TITLE_MENU_CHARACTER) { g_gameScene_id = GAME_TUTORIAL; }
	}
	//�I���J�[�\���ʒu�̕`��
	DrawRotaGraphF(g_sel_cursor_pos.x, g_sel_cursor_pos.y, 0.25f, 0, g_select_cursor, true);
}

//�^�C�g���摜
void titleBackDraw() {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameStart, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	DrawGraph(0, 0, g_titleRight, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//���旬��
void movieDraw() {

	//����̉摜�T�C�Y���擾
	int size_x = 0;
	int size_y = 0;

	if (g_gameScene_id == GAME_START) {
		
		GetGraphSize(g_titleMovie, &size_x, &size_y);

		//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
		screen_handle = MakeScreen(size_x, size_y, TRUE);

		//����̍Đ��J�n
		PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);

		//���߂�����@�Ƃ��Ė��邳�N���b�v�t�B���^�[������
		//�u���ȏ�/�ȉ��̖��邳�̐F�����ׂēh��Ԃ��v�Ƃ����͋����������ł���
		//FilterType�ȍ~�̈���...��r���@�iLESS/GREATER),��r����l,�Y������F��h��Ԃ���,
		//�h��Ԃ�����̐F,�h��Ԃ�����̐F�̕s�����x(�����ɂ������̂�0)
		GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, true, GetColor(0, 0, 0), 0);

		//���ߏ������ꂽ�摜����ʂ����ς��ɕ`��
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);
	}

	if (g_gameScene_id == GAME_CLEAR) {
	
		GetGraphSize(g_clearFlower, &size_x, &size_y);

		//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
		screen_handle = MakeScreen(size_x, size_y, TRUE);

		//����̍Đ��J�n
		PlayMovieToGraph(g_clearFlower, DX_PLAYTYPE_LOOP);

		//���ߏ���
		GraphFilterBlt(g_clearFlower, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, true, GetColor(0, 0, 0), 0);

		//���ߏ������ꂽ�摜����ʂ����ς��ɕ`��
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);
	}
}

//�^�C�g�������`��
void sceneTitle() {

	titleSelect();

	//�^�C�g������
	DrawExtendGraph(200, 50, 1100, 300, g_title, TRUE);

	ChangeFont("PixelMplus12", DX_CHARSET_DEFAULT);

	SetFontSize(70);
	DrawStringEx(TITLE_SELECT_MENU_POSITION[0].x, TITLE_SELECT_MENU_POSITION[0].y, -TEXT_COLOR_WHITE, "NEWGAME START");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[1].x, TITLE_SELECT_MENU_POSITION[1].y, -TEXT_COLOR_WHITE, "MAP GAME");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[2].x, TITLE_SELECT_MENU_POSITION[2].y, -TEXT_COLOR_WHITE, "TUTORIAL");
}

//�^�C�g����ʂł̃T�E���h����
void soundTitle() {

	StopSoundMem(g_bgmMap);
	StopSoundMem(g_bgmGameOver);
}