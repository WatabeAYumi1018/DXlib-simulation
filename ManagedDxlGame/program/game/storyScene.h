#pragma once

//�X�g�[���[�w�i
extern int g_storyBack;

//�X�g�[���[�E�B���h�E
extern int g_storyWindow;

//���b�Z�[�W����
extern int g_messageRun;

//�������ʗ����G
extern int g_girlNormal;
//�����Ί痧���G
extern int g_girlSmile ;
//��������痧���G
extern int g_girlTroubled;

//�X�g�[���[�V�[���ł̔w�i�`��
void storyDraw();

//�X�g�[���[��ʃG���^�[�A�C�R��
void leafBottonDrawStory(float delta_time);

//��b���b�Z�[�W
void storyMessage();