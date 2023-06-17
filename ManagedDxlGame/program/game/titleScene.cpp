#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"

//タイトル文字
int g_title = 0;

//カーソル初期位置をはじめからへ
int g_select_player_menu = TITLE_MENU_FIRST;

//カーソルを見える化するための変数を作成
int g_select_cursor = 0;				

//選択カーソルのポジション
tnl::Vector3 g_sel_cursor_pos = TITLE_SELECT_MENU_POSITION[g_select_player_menu];

//ゲームスタート画面
int g_gameStart = 0;

//ゲームスタート画面
int g_gameStartAnim = 0;

//タイトル動画ハンドル
int g_titleMovie = 0;

//スクリーン(フィルター処理した画像を保存する用)ハンドル
int screen_handle = 0;	

//明るさクリップフィルターに使用する閾値
int bright_border = 150; 

//ストーリー日差しブレンド
int g_titleRight = 0;

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

			if (g_select_player_menu == TITLE_MENU_FIRST) { g_gameScene_id = GAME_STORY; }
			if (g_select_player_menu == TITLE_MENU_CONTINUE) { g_gameScene_id = GAME_MAP; }
			if (g_select_player_menu == TITLE_MENU_CHARACTER) { g_gameScene_id = GAME_TUTORIAL; }
		}
		//選択カーソル位置の描画
		DrawRotaGraphF(g_sel_cursor_pos.x, g_sel_cursor_pos.y, 0.25f, 0, g_select_cursor, true);
}

//タイトル画像
void titleBackDraw() {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_gameStart, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	DrawGraph(0, 0, g_titleRight, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//タイトルでの動画流し
void movieDraw() {

	//動画の画像サイズを取得
	int size_x = 0;
	int size_y = 0;

	if (g_gameScene_id == GAME_START) {
		
		GetGraphSize(g_titleMovie, &size_x, &size_y);

		//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
		screen_handle = MakeScreen(size_x, size_y, TRUE);

		//動画の再生開始
		PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);

		//透過する方法として明るさクリップフィルターがある
		//「一定以上/以下の明るさの色をすべて塗りつぶす」という力強い処理ができる
		//FilterType以降の引数...比較方法（LESS/GREATER),比較する値,該当する色を塗りつぶすか,
		//塗りつぶした後の色,塗りつぶした後の色の不透明度(透明にしたいので0)
		GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, true, GetColor(0, 0, 0), 0);

		//透過処理された画像を画面いっぱいに描画
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);
	}

	if (g_gameScene_id == GAME_CLEAR) {
	
		GetGraphSize(g_clearFlower, &size_x, &size_y);

		//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
		screen_handle = MakeScreen(size_x, size_y, TRUE);

		//動画の再生開始
		PlayMovieToGraph(g_clearFlower, DX_PLAYTYPE_LOOP);

		//透過処理
		GraphFilterBlt(g_clearFlower, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, true, GetColor(0, 0, 0), 0);

		//透過処理された画像を画面いっぱいに描画
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);
	}
}

//タイトル文字描画
void sceneTitle() {

	titleSelect();

	//タイトル文字
	DrawExtendGraph(200, 50, 1100, 300, g_title, TRUE);

	ChangeFont("PixelMplus12", DX_CHARSET_DEFAULT);

	SetFontSize(70);
	DrawStringEx(TITLE_SELECT_MENU_POSITION[0].x, TITLE_SELECT_MENU_POSITION[0].y, -TEXT_COLOR_WHITE, "NEWGAME START");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[1].x, TITLE_SELECT_MENU_POSITION[1].y, -TEXT_COLOR_WHITE, "MAP GAME");
	DrawStringEx(TITLE_SELECT_MENU_POSITION[2].x, TITLE_SELECT_MENU_POSITION[2].y, -TEXT_COLOR_WHITE, "TUTORIAL");
}
