#pragma once

//タイトル文字
extern int g_title;

//タイトル画面でのメニュー数
enum {
	TITLE_MENU_FIRST,
	TITLE_MENU_CONTINUE,
	TITLE_MENU_CHARACTER,
	TITLE_MENU_MAX
};

//メニューの位置を配列化
const tnl::Vector3 TITLE_SELECT_MENU_POSITION[TITLE_MENU_MAX] = {
	{400,400,0},
	{490,500,0},
	{490,600,0}
};

//ゲームスタート画面
extern int g_gameStart;

//タイトル動画ハンドル
extern int g_titleMovie;

//クリアクラッカー動画
extern int g_clearFlower;

//スクリーン(フィルター処理した画像を保存する用)ハンドル
extern int screen_handle;

//明るさクリップフィルターに使用する閾値
extern int bright_border;

// カーソル初期位置をはじめからへ
extern int g_select_player_menu;

//カーソルを見える化するための変数を作成
extern int g_select_cursor;			

extern tnl::Vector3 g_sel_cursor_pos ;

//ストーリー日差しブレンド
extern int g_titleRight;

//タイトル動画再生
void movieDraw();

//選択カーソル
void titleSelect();

//タイトル文字描画
void sceneTitle();

//タイトル画像ブレンド
void titleBackDraw();

//タイトル画面でのサウンド制御
void soundTitle();