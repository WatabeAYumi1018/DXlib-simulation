#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"


int g_select_player_menu = TITLE_MENU_FIRST;//カーソル初期位置をはじめからへ
int g_select_cursor_hdl = 0;				//カーソルを見える化するための変数を作成
tnl::Vector3 g_sel_cursor_pos = TITLE_SELECT_MENU_POSITION[g_select_player_menu];

//ゲームスタート画面
int g_gameStart = 0;

//ゲームスタート画面
int g_gameStartAnim = 0;

//タイトルメニューで選択
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

		//エンターを押した場所によってシーンが変わる
		if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

			if (g_select_player_menu == TITLE_MENU_FIRST) { g_gameScene_id = GAME_MAP; }
			if (g_select_player_menu == TITLE_MENU_CONTINUE) { g_gameScene_id = GAME_MAP; }
			if (g_select_player_menu == TITLE_MENU_CHARACTER) { g_gameScene_id = GAME_OVER; }
		}
		//選択カーソル位置の描画
		DrawRotaGraphF(g_sel_cursor_pos.x, g_sel_cursor_pos.y, 0.25f, 0, g_select_cursor_hdl, true);
}

void rightFlash(float delta_time) {

	float static sin_count = 0;
	float static cos_count = 0;

	sin_count += tnl::ToRadian(2.0f);
	cos_count += tnl::ToRadian(2.0f);

	int alphaSin = static_cast<int>(sin(sin_count) * 255);
	int alphaCos = static_cast<int>(cos(cos_count) * 255);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaSin);
	DrawExtendGraph(60, 120, 80, 140, g_gameStartAnim, true);
	DrawExtendGraph(200,500,300,600, g_gameStartAnim, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCos);
	DrawExtendGraph(560, 300, 660, 400, g_gameStartAnim, true);
	DrawExtendGraph(1000, 700, 1400, 740, g_gameStartAnim, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//タイトル文字描画
void sceneTitle() {

	titleSelect();

	//タイトル文字
	SetFontSize(100);
	DrawStringEx(TITLE_LOGO_NAMEPOS.x, TITLE_LOGO_NAMEPOS.y, 1, TITLE_LOGO_NAME.c_str());

	SetFontSize(50);
	DrawStringEx(TITLE_SELECT_MENU_POSITION[0].x, TITLE_SELECT_MENU_POSITION[0].y, -TEXT_COLOR_WHITE, "NEWGAME START");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[1].x, TITLE_SELECT_MENU_POSITION[1].y, -TEXT_COLOR_WHITE, "LOADGAME");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[2].x, TITLE_SELECT_MENU_POSITION[2].y, -TEXT_COLOR_WHITE, "BACK");
}
