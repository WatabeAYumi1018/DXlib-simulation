#pragma once

//�^�C�g������
extern int g_title;

//�^�C�g����ʂł̃��j���[��
enum {
	TITLE_MENU_FIRST,
	TITLE_MENU_CONTINUE,
	TITLE_MENU_CHARACTER,
	TITLE_MENU_MAX
};

//���j���[�̈ʒu��z��
const tnl::Vector3 TITLE_SELECT_MENU_POSITION[TITLE_MENU_MAX] = {
	{400,400,0},
	{490,500,0},
	{490,600,0}
};

//�Q�[���X�^�[�g���
extern int g_gameStart;

//�^�C�g�����̓���
extern int g_titleMovie;

//�N���A���̓���
extern int g_clearFlower;

//�X�N���[��(�t�B���^�[���������摜��ۑ�����p)�n���h��
extern int screen_handle;

//���邳�N���b�v�t�B���^�[�Ɏg�p����臒l
extern int bright_border;

// �J�[�\�������ʒu���͂��߂����
extern int g_select_player_menu;

//�J�[�\���������鉻���邽�߂̕ϐ����쐬
extern int g_select_cursor;			

extern tnl::Vector3 g_sel_cursor_pos ;

//�X�g�[���[�������u�����h
extern int g_titleRight;

//�^�C�g������Đ�
void movieDraw();

//�I���J�[�\��
void titleSelect();

//�^�C�g�������`��
void sceneTitle();

//�^�C�g���摜�u�����h
void titleBackDraw();

//�^�C�g����ʂł̃T�E���h����
void soundTitle();