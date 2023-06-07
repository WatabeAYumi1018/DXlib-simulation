#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <climits>
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

//味方フェーズ変数
int g_phaseAlly = PHASE_SELECT_CHARACTER;

//敵フェーズ変数
int g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;

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

//スコア変数
int g_score = 0;

//-------------------------------------------------------------------------------------------

//敵からの攻撃判定
bool moveEnemyToAlly(int enemy) {

	int enemyX = character[enemy].x;
	int enemyY = character[enemy].y;
	int enemyMove = character[enemy].move;	//	各キャラの移動数

	int ally = 0;	// 最も近くにいる味方キャラの番号
	int allyX = -1; // 最も近い味方キャラのX座標
	int allyY = -1; // 最も近い味方キャラのY座標
	
	int maxDistance = INT_MAX; // 最大距離

	// マップ上の全ての座標を探索する
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			
			int allyChara = getCharacter(j, i);
			
			if (allyChara != -1 && character[allyChara].team == TEAM_ALLY) {
			
				//-------------------------------------------

				// 敵キャラとの距離を計算
				int distance = abs(character[allyChara].x - enemyX) + 
								abs(character[allyChara].y - enemyY);

				//地形情報を取り、移動範囲内か判定…？
				int moveCost = jobData[character[enemy].job].moveCells[mapData[i][j]];
				character[enemy].move -= moveCost;

				//--------------------------------------------
				//現在地点から目標へ向かっていく

				// 最小距離が更新された場合（より近くにいる場合、その距離を最小値とする）
				if (distance < maxDistance && moveCost< character[enemy].move) {

					ally = allyChara;
					allyX = character[allyChara].x;
					allyY = character[allyChara].y;
					maxDistance = distance;
				}
			}
		}
	}
	// 最も近い味方の隣に移動
	if (allyX != -1 && allyY != -1 &&(ThreeRelation(enemy, ally))) {
		int distanceX = allyX - enemyX;
		int distanceY = allyY - enemyY;

		// 移動可能範囲内かつ一番近くの味方の隣に移動する（これだと地形効果が無視されてる？）
		if ((abs(distanceX) + abs(distanceY)) <= enemyMove &&
				(abs(distanceX) <= enemyMove && abs(distanceY) <= enemyMove)) {
			enemyX = allyX;
			enemyY = allyY;

			// ★敵の座標を移動先の隣のマスに調整
			if (distanceX < 0)
				enemyX--;
			else if (distanceX > 0)
				enemyX++;
			else if (distanceY < 0)
				enemyY--;
			else if (distanceY > 0)
				enemyY++;
		}
	}
	// 移動後の座標を設定
	character[enemy].x = enemyX;
	character[enemy].y = enemyY;

	return true; // 移動成功
}

 bool checkCanMoveEnemy(int _chara, int _x, int _y, int _move) {
	
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return false; }

	int chara = getCharacter(_x, _y);
	if (chara >= 0 && character[chara].team != character[_chara].team)	return false;

	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	if (moveCost < 0)	return false;

	// 移動するごとにコストを使っていく
	if (_move < moveCost)	return false;

	return true;
}

//--------------------------------------------------------------------------
//★★★
//制御する方法！！
//ENEMYCHARACTER_MAX定数を作る。
//もしcharacter[3]==隣判定trueなら…で、14まで全て作って判定する（for分を使わずに、全てのキャラの判定をする）
//if else ifで管理すれば、順番に見てくれるのでは？？

//一連の流れ
void turnMove(float delta_time) {

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED=700;
	const int TELOP_FRAME_MAX = 1400;

	//テロップアニメーションカウント
	float static g_telopTimeCount = 0;

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
		phaseAllyMove(delta_time);

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
				g_flagSpace = true;		//敵が自分の隣に味方がいるかを判断するためのフラグ
			}
		}

#if 0
		//敵のAIここから
		if (g_flagSpace) {//毎回移動してる

			//ターゲットのキャラクターを決める
			int target[2] = { character[0].x,character[0].y };

			for (int i = CHARACTER_MAX - 1; i >= 0; i--) {

				if (i == 15 && character[i].team == TEAM_ALLY && character[i].hp <= 0) { continue; }

				int move = character[i].move;

				while (1) {

					int enemy = i;

					if (checkCanAllyBattle(enemy, g_selectedChara)) {

						if (enemy >= 0)
							battle(delta_time);
						break;
					}
					else {

						int x = character[i].x;
						int y = character[i].y;

						if (x < character[0].x)	x++;
						if (x > character[0].x)	x--;
						if (y < character[0].y)	y++;
						if (y < character[0].y)	y--;

						if (checkCanMoveEnemy(i, x, y, move)) {

							int chara = getCharacter(x, y);
							if (chara < 0) {}

							else { break; }
						}
						else { break; }
					}
				}
				if (moveEnemyToAlly(i)) {	//行動範囲内に味方がいた場合

					if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

						g_CanAttackMove++;
						g_flagEnter = true;			//エンターキーが押せるかどうか（戦闘中は戦闘送りのために動かせるようにtrue）
						g_flagCursor = false;		//カーソルが動かせるか否か（戦闘中は動かせないようにfalse）
						g_flagBattleAnime = true;	//エフェクトアニメーションの変化フラグ（true→falseで１セット）
						g_flagBattleHp = true;		//ダメージHP変化のフラグ（true→falseで１セット
					}
					battle(delta_time);
				}
			}
		}
#endif
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {

			if (!moveEnemyToAlly(g_standbyChara)) {

				g_flagEnter = false;
				g_flagCursor = true;
				g_flagSpace = false;				//いないから、敵の判断が終了
				character[0].done = false;
				character[1].done = false;			//味方ターン移行に際して、味方の行動が未行動にリセットされる
				character[2].done = false;			//味方ターン移行に際して、味方の行動が未行動にリセットされる
				g_flagTurnAlly = true;				//味方ターンのテロップを流すためにtrue
				g_turnMove = TURN_ALLAY;
			}
		}
		break;
	}
	}
}

//敵フェーズの動き
void phaseEnemyMove(float delta_time) {

	static int currentEnemyNumber = 0;
	constexpr int ENEMY_COUNT = 12;

	while (delta_time <= 0.0f && currentEnemyCount < ENEMY_COUNT) {

		int enemyNumber = currentEnemyNumber;

		switch (g_phaseEnemy) {

		case PHASE_AI_MOVE_CHARACTER: {

			int maxDistance = INT_MAX; // 最大距離
			int nearDistanceAlly = -1; // 最小距離

			for (int i = 0; i < CHARACTER_ALLAY_MAX; ++i) {
				
				int allyX = character[i].x; // / 32;
				int allyY = character[i].y; // / 32;

				int enemyX = character[enemyNumber].x;
				int enemyY = character[enemyNumber].y;

				//int emx = enemyX / 32;
				//int emy = enemyY / 32;

				if (allyX == enemyX && allyY == enemyY) continue;

				int distance = abs(allyX - enemyX) + abs(allyY - enemyY);
				
				if (distance < maxDistance) {
					nearDistanceAlly = i;
				}
			}

			g_phaseEnemy = PHASE_AI_MOVE_CHARACTER;

			break;
		}
		case PHASE_AI_MOVE_CHARACTER: {

			int enemyMove = character[enemyNumber].move;

			if(nearDistanceAlly<= enemyMove)


			break;
		}							//敵と味方の座標比較。移動可動範囲内なら
		case PHASE_AI_SELECT_ATTACK: {

			//g_phaseEnemy = PHASE_AI_MOVE_CHARACTER;

			break;
		}
		}
	}
}

//カーソルエンター処理について
void phaseAllyMove(float delta_time) {

	switch (g_phaseAlly) {

		case PHASE_SELECT_CHARACTER: {

			//回復地形の上にいたら、ターン開始時に１００回復
			for (int i = 0; i < MAP_HEIGHT; i++) {
				for (int j = 0; j < MAP_WIDTH; j++) {
				
					int startChara = getCharacter(j, i);
					if (startChara == CELL_HOUSE || startChara == CELL_FORT) {
						
						if (character[startChara].hp > 0 && character[startChara].hp < character[startChara].maxHp) {

							character[startChara].hp += 100;

							if (character[startChara].hp >= character[startChara].maxHp) {

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
				//if (character[chara].done) {resetFill();}
				
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
						g_phaseAlly = PHASE_SET_MOVE_POSITION;
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
				
					if (checkBattleFlag) { g_phaseAlly = PHASE_SELECT_ATTACK;}
				
					else {
						//攻撃可能キャラがいなければ、待機
						character[g_selectedChara].done = true;
						resetFill();
						g_phaseAlly = PHASE_SELECT_CHARACTER;
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
		g_phaseAlly = PHASE_SELECT_CHARACTER;
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

	//動画のロード
	g_titleMovie = LoadGraph("graphics/titleMovie.mp4");
	g_clearCracker = LoadGraph("graphics/clearCracker.mp4");

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

			//動画の画像サイズを取得
			//int size_x=0;
			//int size_y=0;

			//GetGraphSize(g_titleMovie, &size_x, &size_y);

			//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
			//screen_handle = MakeScreen(size_x, size_y, TRUE);

			// 動画の再生開始
			//PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);

			//もう一つ透過する方法として明るさクリップフィルターがある　先ほどの置換フィルターはいわゆるGBのように透過に適した素材じゃないとうまくいかない
			//こちらは「一定以上/以下の明るさの色をすべて塗りつぶす」という力強い処理ができる
			//FilterType以降の引数...比較方法（LESS/GREATER),比較する値,該当する色を塗りつぶすか,
			//塗りつぶした後の色,塗りつぶした後の色の不透明度(透明にしたいので0)
			//GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, bright_border, false, GetColor(255, 255, 255), 255);
			//GraphFilterBlt(g_titleMovie, screen_handle, DX_GRAPH_FILTER_REPLACEMENT, 0, 0, 0, 255, 0, 0, 0, 0);

			//透過処理された画像を画面いっぱいに描画
			//DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, screen_handle, TRUE);

			// 動画の再生開始
			//PlayMovieToGraph(g_titleMovie, DX_PLAYTYPE_LOOP);

			sceneTitle();

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
			scoreDraw();
			turnMove(delta_time);
			
			break;
		}
		case GAME_OVER: {

			gameOver(delta_time);
			
			break;
		}
		case GAME_CLEAR: {

			gameClear(delta_time);

		break;
		}
	}
}
//
//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


//棒グラフでのダメージ減算
//DrawExtendで、ダメージ受けたら（フラグ管理）その分を減らす（描画のサイズを変える）