#pragma once

//�^�C�g����ʂł̃��j���[��
enum {
	TITLE_MENU_FIRST,
	TITLE_MENU_CONTINUE,
	TITLE_MENU_CHARACTER,
	TITLE_MENU_MAX
};

//���j���[�̈ʒu��z�񉻂���
const tnl::Vector3 TITLE_SELECT_MENU_POSITION[TITLE_MENU_MAX] = {
	{450,400,0},
	{500,500,0},
	{550,600,0}
};

//�Q�[���X�^�[�g���
extern int g_gameStart;

//�Q�[���X�^�[�g��ʃ��C�g
extern int g_gameStartAnim;

const std::string TITLE_LOGO_NAME = "GREEN OCEAN";
const tnl::Vector3 TITLE_LOGO_NAMEPOS = { 350,100,0 };

extern int g_select_player_menu;//�J�[�\�������ʒu���͂��߂����
extern int g_select_cursor_hdl;				//�J�[�\���������鉻���邽�߂̕ϐ����쐬
extern tnl::Vector3 g_sel_cursor_pos ;

void titleSelect();

void rightFlash(float delta_time);

void sceneTitle();
