#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"

//�J�[�\�������ʒu���͂��߂����
int g_select_player_menu = TITLE_MENU_FIRST;

//�J�[�\���������鉻���邽�߂̕ϐ����쐬
int g_select_cursor_hdl = 0;				

//�I���J�[�\���̃|�W�V����
tnl::Vector3 g_sel_cursor_pos = TITLE_SELECT_MENU_POSITION[g_select_player_menu];

//�Q�[���X�^�[�g���
int g_gameStart = 0;

//�Q�[���X�^�[�g���
int g_gameStartAnim = 0;

//�^�C�g������n���h��
int g_titleMovie = 0;

//�X�N���[��(�t�B���^�[���������摜��ۑ�����p)�n���h��
int screen_handle = 0;	

//���邳�N���b�v�t�B���^�[�Ɏg�p����臒l
int bright_border = 150; 

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

			if (g_select_player_menu == TITLE_MENU_FIRST) { g_gameScene_id = GAME_MAP; }
			if (g_select_player_menu == TITLE_MENU_CONTINUE) { g_gameScene_id = GAME_MAP; }
			if (g_select_player_menu == TITLE_MENU_CHARACTER) { g_gameScene_id = GAME_OVER; }
		}
		//�I���J�[�\���ʒu�̕`��
		DrawRotaGraphF(g_sel_cursor_pos.x, g_sel_cursor_pos.y, 0.25f, 0, g_select_cursor_hdl, true);
}

//void rightFlash(float delta_time) {
//
//	float static sin_count = 0;
//	float static cos_count = 0;
//
//	sin_count += tnl::ToRadian(2.0f);
//	cos_count += tnl::ToRadian(2.0f);
//
//	int alphaSin = static_cast<int>(sin(sin_count) * 255);
//	int alphaCos = static_cast<int>(cos(cos_count) * 255);
//
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaSin);
//	DrawExtendGraph(60, 120, 80, 140, g_gameStartAnim, true);
//	DrawExtendGraph(200,500,300,600, g_gameStartAnim, true);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCos);
//	DrawExtendGraph(560, 300, 660, 400, g_gameStartAnim, true);
//	DrawExtendGraph(1000, 700, 1400, 740, g_gameStartAnim, true);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
//}

void titleMovie() {

	//����̉摜�T�C�Y���擾
	int size_x = 0;
	int size_y = 0;

	GetGraphSize(g_titleMovie, &size_x, &size_y);

	//����Ɠ��T�C�Y�̃X�N���[�����쐬(�����ȃs�N�Z�����������ߎO�ڂ̈�����TRUE)
	screen_handle = MakeScreen(size_x, size_y, TRUE);

	//����̍Đ��J�n
	PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);

	//��������߂�����@�Ƃ��Ė��邳�N���b�v�t�B���^�[������@��قǂ̒u���t�B���^�[�͂�����GB�̂悤�ɓ��߂ɓK�����f�ނ���Ȃ��Ƃ��܂������Ȃ�
	//������́u���ȏ�/�ȉ��̖��邳�̐F�����ׂēh��Ԃ��v�Ƃ����͋����������ł���
	//FilterType�ȍ~�̈���...��r���@�iLESS/GREATER),��r����l,�Y������F��h��Ԃ���,
	//�h��Ԃ�����̐F,�h��Ԃ�����̐F�̕s�����x(�����ɂ������̂�0)
	GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, false, GetColor(255, 255, 255), 255);
	GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_REPLACEMENT, 0, 0, 0, 255, 0, 0, 0, 0);

	//���ߏ������ꂽ�摜����ʂ����ς��ɕ`��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);

	//����̍Đ��J�n
	PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);
}

//�^�C�g�������`��
void sceneTitle() {

	titleSelect();

	//�^�C�g������
	SetFontSize(100);
	DrawStringEx(TITLE_LOGO_NAMEPOS.x, TITLE_LOGO_NAMEPOS.y, 1, TITLE_LOGO_NAME.c_str());

	SetFontSize(50);
	DrawStringEx(TITLE_SELECT_MENU_POSITION[0].x, TITLE_SELECT_MENU_POSITION[0].y, -TEXT_COLOR_WHITE, "NEWGAME START");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[1].x, TITLE_SELECT_MENU_POSITION[1].y, -TEXT_COLOR_WHITE, "LOADGAME");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[2].x, TITLE_SELECT_MENU_POSITION[2].y, -TEXT_COLOR_WHITE, "BACK");
}
