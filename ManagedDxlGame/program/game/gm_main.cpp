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

 
//★敵のターン　OK
//★敵の動きAI（ボスは動かない）

//クリア文字/ゲームオーバー文字⇒タイトルへ

//地形の上に乗ると、毎ターン体力回復

//if敵のmove内の座標に味方が入ったら⇒味方の座標へ向かってくる⇒バトルがはじまる（関数へ）


//-------------------------------------------------------------------------------------------
//進行フェーズのフラグ変数
//

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
		//味方移動全般の関数
		phaseAllyMove(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {

			g_flagTurnEnemy = true;		//敵ターンのテロップを流すためにtrue
			character[0].done = true;	//味方全員の行動を行動済みに
			character[1].done = true;
			character[2].done = true;
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
		if (g_flagSpace) {

			phaseEnemyMove(delta_time);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {

			g_flagEnter = false;
			g_flagCursor = true;
			g_flagSpace = false;				//いないから、敵の判断が終了
			character[0].done = false;			//味方ターン移行に際して、味方全員の行動が未行動にリセットされる
			character[1].done = false;			
			character[2].done = false;			
			g_flagTurnAlly = true;				//味方ターンのテロップを流すためにtrue
			g_turnMove = TURN_ALLAY;
		}
		break;
	}
	}
}

//敵キャラ移動可能判定の起点
bool enemyCanMove(int _enemy, int _x, int _y, int _move) {

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		if (enemyCheckMoveCost(_enemy, x, y, _move)) { return true; }
	}
	return false;
}

//敵が移動できるかどんどん判定してく
bool enemyCheckMoveCost(int _enemy, int _x, int _y, int _move) {//選択した味方キャラ、座標、移動数

	//画面外はスルー
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return false; }

	//どのマップチップの上にいるかを判定
	int moveCost = jobData[character[_enemy].job].moveCells[mapData[_y][_x]];

	//移動可能数が０以下、移動可能数より下なら移動不可で終了
	if (moveCost < 0 || _move < moveCost) { return false; }

	//移動するごとにコストを使っていく
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		if (enemyCheckMoveCost(_enemy, x, y, _move)) {return true;}
	}
	return false;
}

//敵フェーズの動き
void phaseEnemyMove(float delta_time) {

	//現在敵何人目か（初期値はインデックスの３）
	static int currentEnemyNumber = 3;

	//1人検証が終わるごとに増えていく
	constexpr int ENEMY_COUNT = 15;

	//調査中のNumberを代入
	int enemyNumber = currentEnemyNumber;

	int spaceCount = 0;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {spaceCount++;}

	while (spaceCount ==1 && currentEnemyNumber <= ENEMY_COUNT) {

		// 最大距離
		int maxDistance = INT_MAX; 

		// 最小距離の味方取得
		int nearDistanceAlly = 0; 

		int _enemyX = 0;
		int _enemyY = 0;

		switch (g_phaseEnemy) {

		case PHASE_AI_SEARCH_CHARACTER: {

			for (int i = 0; i < CHARACTER_ALLAY_MAX; ++i) {
				
				int _allyX = character[i].x; 
				int _allyY = character[i].y; 

				_enemyX = character[enemyNumber].x;
				_enemyY = character[enemyNumber].y;

				if (_allyX == _enemyX && _allyY == _enemyY) continue;

				int distance = abs(_allyX - _enemyX) + abs(_allyY - _enemyY);
				
				if (distance < maxDistance) {
					
					maxDistance = distance;
					nearDistanceAlly = i;
				}
			}
			//総移動可能数
			int enemyMove = character[enemyNumber].move;

			//味方までの距離と敵キャラの行動範囲を比較
			if (maxDistance <= enemyCanMove(enemyNumber, _enemyX, _enemyY, enemyMove)){

				g_phaseEnemy = PHASE_AI_MOVE_CHARACTER;
			}
			//範囲内でなければ次の敵キャラへ
 			else { g_phaseEnemy = PHASE_AI_NEXT_ENEMY; }
		}
		case PHASE_AI_MOVE_CHARACTER: {

			int enemyX = character[enemyNumber].x;
			int enemyY = character[enemyNumber].y;

			int allyX = character[nearDistanceAlly].x;
			int allyY = character[nearDistanceAlly].y;

			// 場面分けで敵の座標を更新
			if (enemyX > allyX &&( enemyY > allyY || enemyY < allyY)) {
					
				enemyX = allyX +1;
				enemyY = allyY;
			}
			else if (enemyX < allyX && (enemyY > allyY || enemyY < allyY)) {
				
				enemyX = allyX -1;
				enemyY = allyY;
			}
			else if (enemyX == allyX && enemyY > allyY) { enemyY = allyY +1; }

			else if (enemyX == allyX && enemyY < allyY) { enemyY = allyY -1; }

			else if (enemyX > allyX && enemyY == allyY) { enemyX = allyX +1; }

			else if (enemyX < allyX && enemyY == allyY) { enemyX = allyX -1; }

			//座標更新
			character[enemyNumber].x = enemyX;
			character[enemyNumber].y = enemyY;
		}							
		case PHASE_AI_SELECT_ATTACK: {

			battle(delta_time);

			g_phaseEnemy = PHASE_AI_NEXT_ENEMY;

		}
		case PHASE_AI_NEXT_ENEMY: {
		
			// 次の敵キャラクターのインデックスを設定
			enemyNumber++;
			spaceCount++;

			// 次の敵キャラ評価へ移動
			if (spaceCount==2) {g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;}
		}
		}
	}
	//敵ターン全員調査完了につき、今ターンは完了。次ターンのためリセット。
	if (enemyNumber >= ENEMY_COUNT) {currentEnemyNumber = 3;}
	
	//未調査の次の敵キャラクター判定のため更新
	else {currentEnemyNumber = enemyNumber;}
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

			//titleMovie();
			sceneTitle();				//タイトル全般

			break;
		}
		case GAME_STORY:

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
	}
}
//
//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


//棒グラフでのダメージ減算
//DrawExtendで、ダメージ受けたら（フラグ管理）その分を減らす（描画のサイズを変える）