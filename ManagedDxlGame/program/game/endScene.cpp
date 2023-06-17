#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "storyScene.h"
#include "mapScene_map.h"
#include "mapScene_battle.h"
#include "endScene.h"

//�Q�[���I�[�o�[���
int g_gameOver = 0;

//�Q�[���N���A���
int g_gameClear = 0;

//�N���A�N���b�J�[����
int g_clearFlower = 0;

//�Q�[���I�[�o�[��ʕ`��
void gameOver(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameOver, TRUE);

	const int BACK_START_X_Y = 0;
	const int BACK_END_X = 1300;
	const int BACK_END_Y = 750;

	const int TEXT_START_X = 300;
	const int TEXT_END_X = 1000;
	const int TEXT_START_Y = 100;
	const int TEXT_END_Y = 200;

	float static g_gameOverTimeCount = 0;
	bool static g_gameOver_write = true;

	// �_�ŏ���
	g_gameOverTimeCount += delta_time;

	if (g_gameOverTimeCount > 0.5f) {
		g_gameOver_write = !g_gameOver_write;
		g_gameOverTimeCount = 0;
	}

	DrawExtendGraph(TEXT_START_X, TEXT_START_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		
		SetFontSize(50);
		DrawStringEx(580, 500, TEXT_COLOR_WHITE, "CLOSE");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {DxLib_End();}
}

//�Q�[���N���A��ʕ`��
void gameClear(float delta_time) {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameClear, TRUE);

	const int TELOP_Y_START =100;
	const int TELOP_X_END = 700;
	const int TELOP_Y_END = 200;
	int TELOP_SPEED = 200;
	const int TELOP_FRAME_MAX = 300;

	//�e���b�v�A�j���[�V�����J�E���g
	float static g_gameClearTimeCount = 0;

	bool static animEnd = false;

	int telopFrame = 0;

	if (!animEnd) {

		//���t���[�������Ă�������
		g_gameClearTimeCount += delta_time;

		telopFrame = g_gameClearTimeCount * TELOP_SPEED;
	}

	if (telopFrame >= TELOP_FRAME_MAX) {

		TELOP_SPEED = 1000;						//�e���b�v�̓����X�g�b�v
		g_gameClearTimeCount = 0;				//�e���b�v�̃J�E���g���Z�b�g	
		animEnd = true;
	}
	//�����_�n�C�X�R�A�I
	if (g_score >= 1000) {
		
		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][12], true);
		}
		else {
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][12], true);
			scoreResult();
		}

		movieDraw();
	}
	//��o���N���A�I
	else if (g_score <= 999 && g_score >= 500) {

		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][1], true);
		}
		else { 
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][1], true); 
			scoreResult();
		}
		movieDraw();
	}
	//�N���A�I
	else {

		if (!animEnd) {
			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][7], true);
		}
		else { 
			DrawExtendGraph(300, TELOP_Y_START, 1000, TELOP_Y_END, g_map_turn[0][7], true); 
			scoreResult();
		}
	}
	clearMessage();
}

//�X�R�A���ʕ\��
void scoreResult() {

	DrawGraph(700, 400, g_battle_attack[0][17], TRUE);

	SetFontSize(80);

	std::string SCORE = std::to_string(g_score);
	DrawStringEx(1050, 390, GetColor(255, 175, 40), SCORE.c_str());

}

//�N���A�チ�b�Z�[�W
void clearMessage() {

	//���������G�Ί�
	if (g_messageRun == 0 || g_messageRun == 1 || g_messageRun == 5) {
	
		DrawExtendGraph(100, 100, 500, 500, g_girlSmile, TRUE);
	}
	
	//���������G����
	else{DrawExtendGraph(100, 100, 500, 500, g_girlNormal, TRUE);}

	//�X�g�[���[��b�E�B���h�E
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);

	SetFontSize(40);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_messageRun++; }

	//�����_�n�C�X�R�A�I
	if (g_score >= 1000) {
	
		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�f���炵���ł��I\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "����Ȃɂ������]���@�͂��߂Ăł���I\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���Ȃ��l����\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�B�ꖳ��́@�R�t�l�ł���ˁI\n");
		}
	}
	//��o���N���A�I
	else if (g_score <= 999 && g_score >= 500) {

		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���Ȃ��l�̍єz�@���΂̌��t�����������܂���\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "��ρ@�׋��ɂȂ�܂�����\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���̖��_�Ɂ@�p���ʂ悤\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���������@���i���d�˂܂���ˁI\n");
		}
	}
	else {

		if (g_messageRun == 0) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���߂łƂ��������܂��I\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�܂����@�}���O���b�g�l�ɑł����Ƃ�\n");
		}
		else if (g_messageRun == 1) {

			DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�䌩���ꂢ�����܂���\n");
			DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "���ꏏ�ł��ā@���h�ł�����\n");
		}
	}
	if(g_messageRun == 2) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "�������̌P���́@�������ł����ł��傤��\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "����������̂�����܂�����@���ꂵ���ł�\n");
	}
	else if (g_messageRun == 3) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���������@����̋�����ƂƂ���\n");
	}
	else if (g_messageRun == 4) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���ꂩ������i�ł���悤\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�ꑰ�̊F�Ƌ��Ɂ@�撣��܂���\n");
	}
	else if (g_messageRun == 5) {

		DrawStringEx(150, 550, -TEXT_COLOR_WHITE, "���Ȃ��ɂ���ł��ā@�{���ɂ悩����\n");
		DrawStringEx(150, 620, -TEXT_COLOR_WHITE, "�܂����ł��@���z������������\n");
	}
	else if (g_messageRun == 6) {
	
		DxLib_End();// DXlib�̏I������
	}
}

//�N���A���y�Đ�
void soundClear() {

	DeleteSoundMem(g_bgmMap);	//�^�C�g���`�`���[�g���A���܂ł�BGM�폜

	if (CheckSoundMem(g_bgmEnding) == 0) { PlaySoundMem(g_bgmEnding, DX_PLAYTYPE_LOOP, TRUE); }
}

//�Q�[���I�[�o�[���y�Đ�
void soundOver() {

	DeleteSoundMem(g_bgmMap);	//�^�C�g���`�`���[�g���A���܂ł�BGM�폜

	if (CheckSoundMem(g_bgmGameOver) == 0) { PlaySoundMem(g_bgmGameOver, DX_PLAYTYPE_LOOP, TRUE); }


}