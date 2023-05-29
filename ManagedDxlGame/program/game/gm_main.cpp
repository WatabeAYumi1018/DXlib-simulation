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

//-------------------------------------------------------------------------------------------


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

				telopFrame = 0;
				g_telopTimeCount = 0;
				g_flagTurnAlly = false;
			}
		}
		phaseMove(delta_time);

		if ((tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB))) {
			g_flagTurnEnemy = true;
			g_turnMove = TURN_ENEMY;
		}
	}

	case TURN_ENEMY: {

		if (g_flagTurnEnemy) {

			//毎フレーム足していく処理
			g_telopTimeCount += delta_time;

			int telopFrame = g_telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][9], true);

			if (telopFrame == TELOP_FRAME_MAX) {

				telopFrame = 0;
				g_telopTimeCount = 0;
				g_flagSpace = true;
				g_flagTurnEnemy = false;
			}
		}
		//敵のAIここから
		if (g_flagSpace) {

			for (int enemy = CHARACTER_MAX - 1; enemy >= 0; enemy--) {

				//if (character[c].team == TEAM_ALLY && character[c].hp <= 0)	continue;	//ロストキャラはスルー

				if (enemy != 15 && character[enemy].team == TEAM_ENEMY && character[enemy].hp > 0) {

					if (moveEnemyToAlly(delta_time, enemy)) {

						battle(delta_time);

						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

							g_flagEnter = true;
							g_flagCursor = false;
							g_flagBattleAnime = true;
							g_flagBattleHp = true;
							g_CanAttackMove++;
						}
					}
				}
			}
		}
		//やりたいこと！一連の流れ！！
		//敵のターンになったら、すぐに敵が周りの判定をはじめ、戦闘に入る。
		//戦闘に入ったら、スペースを押すとバトルが進行していく。
		//全てのバトルが終わると自動で味方のターンへ移動する。

		else {
		
			g_flagTurnAlly = true;
			g_flagSpace = false;
			character[g_selectedChara].done = false;
			g_turnMove = TURN_ALLAY;

		}
		//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {}
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
	g_gameStartAnim = LoadGraph("graphics/titleAnim.png");

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
	
	//マップ上での行動可能範囲
	fill_map = LoadGraph("graphics/canMoveTile.png"); 

	//攻撃画面の背景
	g_battleGround = LoadGraph("graphics/battleback.jpg");

	//ゲームオーバー背景
	g_gameOver = LoadGraph("graphics/GameOver.jpg");


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

			break;
		}
		case GAME_STORY:

			break;

		case GAME_MAP: {

			getCharaPosition();
			mapPosition();
			display();
			cursorMove();//＜<resetFill()/drawFill())＜getCharacter(,)/return→fillCanMove(,,,)
			instructions();
			turnMove(delta_time);

			break;
		}
		case GAME_OVER: {

			float static g_gameOverTimeCount = 0;
			bool static g_gameOver_write = true;

			// 点滅処理
			g_gameOverTimeCount += delta_time;

			if (g_gameOverTimeCount > 0.5f) {
				g_gameOver_write = !g_gameOver_write;
				g_gameOverTimeCount = 0;
			}

			DrawExtendGraph(0, 0, 1300, 750, g_gameOver, true);
			DrawExtendGraph(200, 200, 1100, 400, g_map_turn[0][3], true);

			if (g_gameOver_write) {
				SetFontSize(50);
				DrawStringEx(430, 500, TEXT_COLOR_WHITE, "CLOSE");
			}
			break;
		}
		case GAME_CLEAR:

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