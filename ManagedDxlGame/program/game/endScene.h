#pragma once

//�Q�[���I�[�o�[���
extern int g_gameOver;

//�Q�[���N���A���
extern int g_gameClear;

//�Q�[���I�[�o�[��ʕ`��
void gameOver(float delta_time);

//�Q�[���N���A��ʕ`��
void gameClear(float delta_time);

//�X�R�A���ʕ\��
void scoreResult();

//�N���A�チ�b�Z�[�W
void clearMessage();

//�N���A���y�Đ�
void soundClear();

//�Q�[���I�[�o�[���y�Đ�
void soundOver();