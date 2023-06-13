#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "storyScene.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"
#include "endScene.h"


//クリア文字/ゲームオーバー文字⇒タイトルへ

//-------------------------------------------------------------------------------------------
//進行フェーズのフラグ変数
//

//ゲーム全体のシーン移行
int g_gameScene_id = GAME_START;

//サウンド鳴らし方（wav.mp3もおっけ）
//一回だけ再生命令を出す（毎フレーム命令出すと使えない）
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

//ゲームスタート
bool g_flagGameStart = false;

//タイトル文字
int g_title = 0;

//エンターボタン
int g_bottonEnter = 0;
//カーソルボタン
int g_bottonCursor = 0;
//タブボタン
int g_bottonTab = 0;
//スペースボタン
int g_bottonSpace = 0;
//シフトボタン
int g_bottonShift = 0;

//-----------------
// 



//void tutorialDraw


//-------------------------------------------------------------------------------------------
//起動時に一回のみ実行されます
void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//音楽の出力--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlibリファレンス、ループ処理の引数

	//SEの出力
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//画像の出力--------------------------------------------


	//文字フォント
	tnl::AddFontTTF("font/PixelMplus12-Regular.ttf");

	//ゲームスタート画面
	g_gameStart = LoadGraph("graphics/GameStartBack.jpg");
	
	//ゲームスタート画面アニメーション
	g_titleRight = LoadGraph("graphics/titleAnim.png");

	//動画のロード
	g_titleMovie = LoadGraph("graphics/titleLeaf.mp4");
	g_clearFlower = LoadGraph("graphics/clearEndFlower.mp4");

	//タイトル選択画像
	g_select_cursor = LoadGraph("graphics/flowerSelect.png");

	//タイトル文字画像
	g_title= LoadGraph("graphics/GREEN OCEAN.png");

	//ストーリーシーン背景
	g_storyBack= LoadGraph("graphics/GameStoryBack.png");

	//ストーリーシーン会話ウィンドウ
	g_storyWindow = LoadGraph("graphics/storyWindow.png");

	//マップデータ
	LoadDivGraph("graphics/pipo-map001.png", 88, 8, 11, CHIP_SIZE, CHIP_SIZE, map_chips[0]);

	//キャラ
	LoadDivGraph("graphics/player1.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[0]);
	LoadDivGraph("graphics/player2.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[1]);
	LoadDivGraph("graphics/player3.png",  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[2]);
	LoadDivGraph("graphics/enemy1.png",	  12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[3]);
	LoadDivGraph("graphics/enemy2.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[4]);
	LoadDivGraph("graphics/enemy3.png",   12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[5]);
	LoadDivGraph("graphics/enemyBOSS.png",12, 3, 4, CHIP_SIZE, CHIP_SIZE, character_chips[6]);

	//カーソル
	g_cursor = LoadGraph("graphics/cursor.png");
	
	//マップ上での情報表示用（下画面）
	display_map = LoadGraph("graphics/mapInfo.png"); 

	//マップ上での行動可能範囲
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//攻撃画面の背景
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//攻撃ミスの画像
	g_battleMiss = LoadGraph("graphics/miss.png");

	//ゲームオーバー背景
	g_gameOver = LoadGraph("graphics/GameOver.jpg");
	
	//ゲームクリア背景
	g_gameClear = LoadGraph("graphics/GameClear.png");

	//攻撃中の下画面
	LoadDivGraph("graphics/battleHp.png",		35, 5, 7, 120, 60, g_battle_hp[0]);
	LoadDivGraph("graphics/battleAttack.png",	42, 3, 14,300, 60, g_battle_attack[0]);
	LoadDivGraph("graphics/battleHit.png",		25, 5, 5, 180, 60, g_battle_hit[0]);
	
	//攻撃エフェクトアニメーション
	LoadDivGraph("graphics/effect_sword.png", 15, 5, 3, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_sword[0]);
	LoadDivGraph("graphics/effect_snip.png",  10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_snip[0]);
	LoadDivGraph("graphics/effect_magic.png",14,14, 1, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_magic[0]);
	LoadDivGraph("graphics/effect_leader.png",10, 5, 2, EFFECT_SIZE, EFFECT_SIZE, g_battle_effect_leader[0]);

	//職業アイコン
	icon_sword= LoadGraph("graphics/iconSWORD.png");
	icon_magic= LoadGraph("graphics/iconMAGIC.png");
	icon_snip=LoadGraph("graphics/iconSNIP.png");
	icon_boss= LoadGraph("graphics/iconBOSS.png");

	//三すくみエフェクト
	g_relation_back= LoadGraph("graphics/relationBack.png");
	g_relation = LoadGraph("graphics/relation.png");

	//マップ画面でのターン文字
	LoadDivGraph("graphics/mapTurn.png", 15, 1, 15, 600, 60, g_map_turn[0]);

	//エンターボタン
	g_bottonEnter = LoadGraph("graphics/leafEnter.png");
	//カーソルボタン
	g_bottonCursor = LoadGraph("graphics/leafCursor.png");
	//タブボタン
	g_bottonTab= LoadGraph("graphics/leafTab.png");
	//スペースボタン
	g_bottonSpace= LoadGraph("graphics/leafSpace.png");
	//シフトボタン
	g_bottonShift= LoadGraph("graphics/leafShift.png");

	g_girl= LoadGraph("graphics/swordGirl.png");
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます,60FPS
void gameMain(float delta_time) {

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_BACK); //DXlibリファレンス、ループ処理の引数
	//}//サウンドで選ぶのは、ループかバックのみ！ノーマルは選ばないで！！（ノーマルはプログラム処理を止めてしまう）

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
	//	StopSoundMem(sound_bgm_hdl);//Aを押すとサウンドが止まる
	//}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
	//	PlaySoundMem(sound_bgm_hl, DX_PLAYTYPE_LOOP); //X押すと途中から再生がはじまる
	//}

	//曲を途中から再生する
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);

	switch (g_gameScene_id) {

		case GAME_START: {

			titleBackDraw();			//タイトル背景画像
			movieDraw();				//タイトルアニメーション動画
			sceneTitle();				//タイトル全般

			break;
		}
		case GAME_STORY: {

			storyDraw();				//ストーリー背景描画
			storyMessage();				//ストーリーメッセージ描画
			leafBottonDrawStory(delta_time);

			break;
		}
		case GAME_TUTORIAL: {

			DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_battleGround, TRUE);

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) { g_gameScene_id = GAME_MAP; }

			break;
		}
		case GAME_MAP: {

			getCharaPosition();			//charaData[MAP_HEIGHT][MAP_WIDTH]定義
			mapPosition(delta_time);	//画像描画
			display();					//下画面情報描画制御
			cursorMove();				//カーソル移動手定義
			instructions(delta_time);	//指示文字描画
			scoreDraw();				//score描画
			turnMove(delta_time);		//ゲームの流れ全般
			
			break;
		}
		case GAME_OVER: {

			gameOver(delta_time);		//ゲームオーバー全般
			

			break;
		}
		case GAME_CLEAR: {

			gameClear(delta_time);		//ゲームクリア全般

			break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
