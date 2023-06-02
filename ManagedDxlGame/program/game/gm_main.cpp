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

//
//マップ上での指示出しコード(実装予定処理一覧)
//
// -----------------------------------------------------------
// 
//★味方全員動いたらターン終了　OK
//★敵のターン　OK
//★敵の動きAI（ボスは動かない）
//★全員の待機確認　OK
//★味方ターンへフェーズチェンジ　OK
//★ボス戦		（下書きOK）
//★ステージクリア
//ゲームオーバー	（下書きOK）


//長を倒すとエンディング⇒クリア文字⇒タイトルへ

//地形の上に乗ると、毎ターン体力回復

//if敵のmove内の座標に味方が入ったら⇒味方の座標へ向かってくる⇒バトルがはじまる（関数へ）


//-------------------------------------------------------------------------------------------
//進行フェーズのフラグ変数
//


//int g_gameScene_id = GAME_START; 本番こっち！！
int g_gameScene_id = GAME_START;

//サウンド鳴らし方（wav.mp3もおっけ）
//一回だけ再生命令を出す（毎フレーム命令出すと使えない）
int sound_bgm_hdl = 0;
int sound_se_hdl = 0;

//フェーズ変数
int g_phase = PHASE_SELECT_CHARACTER;

//ターン変数
int g_turnMove= TURN_ALLAY;

//カーソルフラグ
bool g_flagCursor = true;

//エンター押しフラグ
bool g_flagEnter = false;

//スペース押しフラグ
bool g_flagSpace=false;

//バトル進行中か否かの判定フラグ
int g_CanAttackMove = 0;

//テロップアニメーションカウント
float g_telopTimeCount = 0;

//味方ターン切り替え
bool g_flagTurnAlly = true;

//敵ターン切り替え
bool g_flagTurnEnemy = false;

//ゲームスタート
bool g_flagGameStart = false;

//ゲームオーバーフラグ
bool g_flagGameOver = false;

//ゲームオーバー画面
int g_gameOver = 0;

//ゲームクリア画面
int g_gameClear = 0;

//敵ターンでのバトル進行制御（本当に必要かは思案中）
int g_flagBattle = 0;

//-------------------------------------------------------------------------------------------

//★
//敵からの攻撃判定
bool moveEnemyToAlly(float delta_time,int enemy) {

	int characterX = character[enemy].x;
	int characterY = character[enemy].y;
	//int moveCost = jobData[character[enemy].job].moveCells[mapData[characterY][characterX]];

	// 塗りつぶし範囲内に味方キャラが存在する場合
	// 味方の隣のマスに移動する処理
	for (int dir = 0; dir < DIRECTION_MAX; dir++) {
		int x = characterX + g_directions[dir][0];
		int y = characterY + g_directions[dir][1];

		if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT && charaData[y][x] != -1) {
			
			if (character[charaData[y][x]].team == TEAM_ALLY) {
	
				// 味方の隣のマスに移動
				//character[enemy].x = x;
				//character[enemy].y = y;
				//character[enemy].move -= moveCost;

				return true;
			}
		}
	}
	return false;
}


//一連の流れ
//味方のターンからはじまる→カーソル操作でキャラを動かす（この辺りは問題ないです）→TABキーを押すと、敵のターンへ移行する

//問題は、敵のターンです。まず、一連の流れを説明します。
//
// 敵のターンでしたいこと
//�@待機中の敵キャラ（character[3]〜character[16]）は、それぞれの上下左右一マス隣に味方キャラがいないか判定する
//（ただし、ボスであるcharacter[16]は戦闘を仕掛けてこない予定です。19行：g_standbyChara != 15がそれです。 ）
// （また、これは待機中の敵キャラクター1人ずつ判定する必要があります。for文で回すべきかと思いますが、現状ではその辺りの宣言も不透明）
//�A味方キャラがいた場合は、戦闘に入る
// （ただ、現状隣のマスに複数キャラがいた場合どうするかの処理は出来ていません。予定としては、敵から見て三すくみで有利なキャラを優先して攻撃する予定）
//�B隣マスに味方がいないことが確認出来たら、自動で味方キャラへターン移行する(218行)
//
//エラーが生じてしまうこと。
//★味方ターンの時に、例えば一番近くにいる剣士の隣に味方キャラを配置して、敵ターンへ移行し、スペースキーを押します。
//理想としては、battle(delta_time)が呼び出され、そのあとに味方のターンへ移行してほしいのですが、
//現状battle関数が一瞬しか描画されず、すぐに味方ターンへ移ってしまいます。
//
//もしかしたら途中で呼び出しているmoveEnemyToAlly関数（205行）が間違っているのかと思案中です。
//補足ですが、g_からはじまる変数は全てグローバル変数です。
//コードが分かりにくいと思いますので、ひとまず詳しい内容については明日改めて説明させていただきます！

//★
void turnMove(float delta_time) {

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED=700;
	const int TELOP_FRAME_MAX = 1400;

	switch (g_turnMove) {

	case TURN_ALLAY: {

		if (g_flagTurnAlly) {

			//毎フレーム足していく処理
			g_telopTimeCount += delta_time;

			int telopFrame = g_telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][10], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;			//テロップの流れた距離リセット
				g_telopTimeCount = 0;	//テロップのカウントリセット
				g_flagTurnAlly = false; //味方ターンのテロップ流しは一回で完了のためfalse
			}
		}
		phaseMove(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
			
			g_flagTurnEnemy = true;		//敵ターンのテロップを流すためにtrue
			g_turnMove = TURN_ENEMY;
		}
	break;
	}

	case TURN_ENEMY: {

		if (g_flagTurnEnemy) {

			//毎フレーム足していく処理
			g_telopTimeCount += delta_time;

			int telopFrame = g_telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][9], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;				//テロップの流れた距離リセット
				g_telopTimeCount = 0;		//テロップのカウントリセット
				g_flagTurnEnemy = false;	//敵ターンのテロップ流しは一回で完了のためfalse
				g_flagSpace = true;			//敵が自分の隣に味方がいるかを判断するためのフラグ
			}
		}
		//敵のAIここから
		//if (g_flagSpace) {

 	//		//for (int enemy = CHARACTER_MAX - 1; enemy >= 0; enemy--) {

		//		if (g_standbyChara != 15 && character[g_standbyChara].team == TEAM_ENEMY && character[g_standbyChara].hp > 0) {

 	//				if (moveEnemyToAlly(delta_time, g_standbyChara)) {	//隣のマスに味方がいた場合

 	//					if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		//				
		//					g_CanAttackMove++;
		//					g_flagEnter = true;			//エンターキーが押せるかどうか（戦闘中は戦闘送りのために動かせるようにtrue）
		//					g_flagCursor = false;		//カーソルが動かせるか否か（戦闘中は動かせないようにfalse）
		//					g_flagBattleAnime = true;	//エフェクトアニメーションの変化フラグ（true→falseで１セット）
		//					g_flagBattleHp = true;		//ダメージHP変化のフラグ（true→falseで１セット）
		//					g_flagBattle = 1;
		//				}
		//				else if (g_flagBattle==1) {
		//						battle(delta_time);
		//					}	

		//				g_turnMove = TURN_ALLAY;

		//			}
		//			if (!moveEnemyToAlly(delta_time, g_standbyChara)){

		//				g_flagEnter = false;
		//				g_flagCursor = true;
		//				g_flagSpace = false;				//いないから、敵の判断が終了
		//				character[0].done = false;
		//				character[1].done = false;			//味方ターン移行に際して、味方の行動が未行動にリセットされる
		//				character[2].done = false;			//味方ターン移行に際して、味方の行動が未行動にリセットされる
		//				g_flagTurnAlly = true;				//味方ターンのテロップを流すためにtrue
		//				g_turnMove = TURN_ALLAY;
		//				g_flagBattle = 0;
		//			}
		//		}
		//}
		break;
	}

	}
}

//カーソルエンター処理について
void phaseMove(float delta_time) {

	switch (g_phase) {

		case PHASE_SELECT_CHARACTER: {

			//回復地形の上にいたら、ターン開始時に１００回復
			for (int i = 0; i < MAP_HEIGHT; i++) {
				for (int j = 0; j < MAP_WIDTH; j++) {
				
					int startChara = getCharacter(j, i);
					if (startChara == CELL_HOUSE || startChara == CELL_FORT) {
						
						if (character[startChara].hp > 0 && character[startChara].hp < character[startChara].maxHp) {

							character[startChara].hp += 100;

							if (character[startChara].hp > character[startChara].maxHp) {

								character[startChara].hp = character[startChara].maxHp;
							}
						}
					}
				}
			}
			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				resetFill();

				//選択したキャラクターを囲って東西南北に1マスずつ塗りつぶし
				int chara = getCharacter(cursorX, cursorY);
				if (chara < 0) { break; } //負の値だったらいない
				
				//行動済みなら座標動かない
				//if (character[chara].done) {

				//	//もしキャラクター0〜２のいずれかの座標が（3,3）になったらクリア
				//	if (character[chara].x == 3 && character[chara].y == 3) {

				//		g_gameScene_id = GAME_CLEAR;
				//	}
				//	resetFill();
				//}
				//キャラがいれば(それ以外は)塗りつぶし
				else {

					for (int dir = 0; dir < DIRECTION_MAX; dir++)
					{
						int x = character[chara].x + g_directions[dir][0];
						int y = character[chara].y + g_directions[dir][1];
						fillCanMove(chara, x, y, character[chara].move);//どんどん隣り合う場所を調査
					}

					//描画内にキャラがいたら、そこは描画しない
					for (int i = 0; i < MAP_HEIGHT; i++) {
						for (int j = 0; j < MAP_WIDTH; j++) {

							int standChara = getCharacter(j, i);
							if (standChara >= 0 && fill[i][j]) {fill[i][j] = false;}
						}
					}
					drawFill();

					//キャラを選択したら、移動フェーズへ
					if (character[chara].team == TEAM_ALLY) {

						g_selectedChara = chara; //味方キャラを代入
						g_phase = PHASE_SET_MOVE_POSITION;
					}
				break;
				}
			}		
		}
		case PHASE_SET_MOVE_POSITION: {

			drawFill();

			if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {

				//移動先の選択、完了したら選択フェーズに戻る
				if (fill[cursorY][cursorX]) {

					//移動による座標の変化
					character[g_selectedChara].x = cursorX;
					character[g_selectedChara].y = cursorY;
				
					bool checkBattleFlag = false;
				
					for (int i = 0; i < CHARACTER_MAX; i++) {

						if (checkCanAllyBattle(g_selectedChara, i)) {

							g_standbyChara = i;
							checkBattleFlag = true;
							break;
						}
					}
				
					if (checkBattleFlag) {g_phase = PHASE_SELECT_ATTACK;}
				
					else {
						//攻撃可能キャラがいなければ、待機
						character[g_selectedChara].done = true;
						resetFill();
						g_phase = PHASE_SELECT_CHARACTER;
					}
				}
			}
			break;
		}
		case PHASE_SELECT_ATTACK: {

			if (character[g_standbyChara].x == cursorX && character[g_standbyChara].y == cursorY) {

				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

					g_flagEnter = true;
					g_flagCursor= false;
					g_flagBattleAnime = true;
					g_flagBattleHp = true;
					g_CanAttackMove ++;
				}	
				battle(delta_time);
			}
		break;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		//攻撃可能キャラがいなければ、待機
		character[g_selectedChara].done = true;
		resetFill();
		g_phase = PHASE_SELECT_CHARACTER;
	}
}


void gameStart() {
	srand(time(0));

	SetWindowText("GREEN OCEAN");

	//音楽の出力--------------------------------------------
	//sound_bgm_hdl = LoadSoundMem("sound/test_bgm.wav");
	//PlaySoundMem(sound_bgm_hdl, DX_PLAYTYPE_LOOP); //DXlibリファレンス、ループ処理の引数

	//SEの出力
	//sound_se_hdl = LoadSoundMem("sound/test_se.wav");

	//画像の出力--------------------------------------------

	//ゲームスタート画面
	g_gameStart = LoadGraph("graphics/GameStart.jpg");
	
	//ゲームスタート画面アニメーション
	g_gameStartAnim = LoadGraph("graphics/titleSakura.png");

	//タイトル選択画像
	g_select_cursor_hdl = LoadGraph("graphics/flowerSelect.png");

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

			DrawExtendGraph(0, 0, 1300, 750, g_gameStart, true);
			rightFlash(delta_time);
			sceneTitle();

			//PlayMovieToGraph(confetti);

			break;
		}
		case GAME_STORY:

			break;

		case GAME_MAP: {

			getCharaPosition();
			mapPosition(delta_time);
			display();
			cursorMove();//＜<resetFill()/drawFill())＜getCharacter(,)/return→fillCanMove(,,,)
			instructions(delta_time);
			turnMove(delta_time);

			break;
		}
		case GAME_OVER: {

			gameOver(delta_time);
			
			break;
		}
		case GAME_CLEAR:
			
			const int BACK_START_X_Y = 0;
			const int BACK_END_X = 1300;
			const int BACK_END_Y = 750;

			DrawExtendGraph(BACK_START_X_Y, BACK_START_X_Y, BACK_END_X, BACK_END_Y, g_gameClear, true);

			break;
	}
}
//
//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


//棒グラフでのダメージ減算
//DrawExtendで、ダメージ受けたら（フラグ管理）その分を減らす（描画のサイズを変える）