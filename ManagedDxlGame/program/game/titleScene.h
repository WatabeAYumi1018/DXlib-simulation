#pragma once

//タイトル画面でのメニュー数
enum {
	TITLE_MENU_FIRST,
	TITLE_MENU_CONTINUE,
	TITLE_MENU_CHARACTER,
	TITLE_MENU_MAX
};

//メニューの位置を配列化
const tnl::Vector3 TITLE_SELECT_MENU_POSITION[TITLE_MENU_MAX] = {
	{450,400,0},
	{500,500,0},
	{550,600,0}
};

//ゲームスタート画面
extern int g_gameStart;

//ゲームスタート画面ライト
extern int g_gameStartAnim;

//タイトル動画ハンドル
extern int g_titleMovie;

//クリアクラッカー動画
extern int g_clearCracker;

//スクリーン(フィルター処理した画像を保存する用)ハンドル
extern int screen_handle;

//明るさクリップフィルターに使用する閾値
extern int bright_border;

const std::string TITLE_LOGO_NAME = "GREEN OCEAN";
const tnl::Vector3 TITLE_LOGO_NAMEPOS = { 350,100,0 };

// カーソル初期位置をはじめからへ
extern int g_select_player_menu;

//カーソルを見える化するための変数を作成
extern int g_select_cursor_hdl;			

extern tnl::Vector3 g_sel_cursor_pos ;

//タイトル動画再生
void titleMovie();

//選択カーソル
void titleSelect();

//タイトル文字描画
void sceneTitle();

//void rightFlash(float delta_time);