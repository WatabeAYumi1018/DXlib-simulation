#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "titleScene.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "mapScene_battle.h"


//クリア文字/ゲームオーバー文字⇒タイトルへ
//地形の上に乗ると、毎ターン体力回復



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

//ゲームオーバーフラグ
bool g_flagGameOver = false;

//ゲームオーバー画面
int g_gameOver = 0;

//ゲームクリア画面
int g_gameClear = 0;

//タイトル文字
int g_title = 0;

//-----------------
// 
//ストーリー背景
int g_storyBack = 0;

//ストーリーウィンドウ
int g_storyWindow = 0;

void storyDraw() {

	//ストーリー背景
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, g_storyBack, TRUE);
	//ストーリー会話ウィンドウ
	DrawExtendGraph(60, 500, 1200, 700, g_storyWindow, TRUE);
}

void storyMessage() {

	SetFontSize(40);

	static int messageLine = 0;
	static int messageCount = 0;
	const int MESSAGE_LINE = 7;  // 行の数
	const int MESSAGE_NUM = 2;   // 列の数
	const int TEXT_LINE = 7;
	const int TEXT_NUM = 2;
	int addMessageNumber = 1;  // 1文字ずつ処理するために1文字ずつ増加
	//テキスト格納する文字列
	std::string text[TEXT_LINE][TEXT_NUM];
	//メッセージ格納する文字列
	std::string message[MESSAGE_LINE][MESSAGE_NUM] = {

		{"あなたが　有名な軍師さまですね", "遠路はるばる　ありがとうございます" },
		{"ようこそ　人里離れた","新緑の海原 へ"},
		{"まさか軍師さまに　直接ご指導いただけるなんて","皆　本日を心待ちにしていたのですよ"},
		{"ご活躍は　こちらでも耳にします","数多の英雄を導いた　伝説の軍師さま"},
		{"かく言う私も　楽しみで昨夜は中々…"},
		{"と　失礼いたしました","早速　訓練場へ案内いたしますね"},
		{"あなた様の采配","楽しみにしていますわ"}
	};

	for (int i = 0; i < MESSAGE_LINE; ++i) {
		for (int j = 0; j < MESSAGE_NUM; ++j) {
			if (i < messageLine) {
				text[i][j] = message[i][j];  // すでに描画された行のメッセージをコピー
			}
			else if (i == messageLine) {
				text[i][j] = message[i][j].substr(0, messageCount);  // 現在描画中の行のメッセージを部分的にコピー
			}
			else {
				text[i][j] = "";  // 未描画の行のメッセージは空にする
			}
		}
	}

	if (messageLine < MESSAGE_LINE) {
		if (message[messageLine][0].length() > messageCount) {
			messageCount += addMessageNumber;
		}
		else {
			messageCount = 0;
			messageLine++;
		}
	}

	for (int i = 0; i < TEXT_LINE; ++i) {
		for (int j = 0; j < TEXT_NUM; ++j) {
			DrawStringEx(200, 540 + i * 80, -TEXT_COLOR_WHITE, "%s", text[i][j].c_str());
		}
	}
}

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
	g_titleMovie = LoadGraph("graphics/titleFlower.mp4");
	g_clearCracker = LoadGraph("graphics/clearCracker.mp4");

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
	
	//マップ下のボタン描画
	g_bottonLayout = LoadGraph("graphics/bottonLayout.png");

	//マップ上での行動可能範囲
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//攻撃画面の背景
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//攻撃ミスの画像
	g_battleMiss = LoadGraph("graphics/miss.png");

	//ゲームオーバー背景
	g_gameOver = LoadGraph("graphics/GameOver.jpg");
	
	//ゲームクリア背景
	g_gameClear = LoadGraph("graphics/GameClear.jpg");

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
	//	PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //X押すと途中から再生がはじまる
	//}

	//曲を途中から再生する
	//PlaySoundMem(sound_bgm_hdl,DX_PLAYTYPE_LOOP,false);

	switch (g_gameScene_id) {

		case GAME_START: {

			titleBackDraw();			//タイトル背景画像
			titleMovie();				//タイトルアニメーション動画
			sceneTitle();				//タイトル全般
			
			break;
		}
		case GAME_STORY:

			storyDraw();				//ストーリー背景描画
			storyMessage();				//ストーリーメッセージ描画

			break;

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
		case GAME_TUTORIAL: {
		
			break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
