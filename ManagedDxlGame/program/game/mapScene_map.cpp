#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "titleScene.h"
#include "mapScene_battle.h"

//----------------------------------------------------------------------------
//マップ全般の変数
//

//グラスマップ全体を配列として格納
int mapData[MAP_HEIGHT][MAP_WIDTH] = {
{4,5,1,1,1,4,5,4,5,4,5,4,5,4,5,4,5,6,7,6,7,4,5,6,7,4,5,6,7,1,6,7,6,7,4,5,4,5,6,7},
{6,7,1,8,9,6,7,6,7,6,7,6,7,6,7,6,7,1,1,1,1,6,7,4,5,6,7,1,1,1,1,4,5,1,6,7,6,7,4,5},
{5,4,5,10,11,4,5,4,5,1,4,5,4,5,4,5,1,1,1,4,5,4,5,6,7,1,1,1,1,1,1,6,7,1,1,1,2,1,6,7},
{7,6,7,0,0,6,7,6,7,1,6,7,6,7,6,7,1,4,5,6,7,6,7,1,1,1,1,3,0,0,0,1,1,1,0,0,0,0,1,4},
{4,5,1,1,0,0,0,0,0,0,1,1,1,4,5,4,5,6,7,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,6},
{6,7,4,5,0,0,0,0,0,0,0,0,0,6,7,6,7,1,1,2,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,4},
{5,1,6,7,0,0,0,3,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,6},
{7,4,5,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,4},
{1,6,7,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,1,6},
{4,5,1,1,1,1,4,5,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
{6,7,1,4,5,1,6,7,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1},
{5,4,5,6,7,4,5,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,2,1,1,1,4},
{7,6,7,1,1,6,7,4,5,1,1,2,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,4,5,1,1,4,5,4,5,4,5,4,5,6},
{5,4,5,4,5,1,1,6,7,4,5,1,1,1,1,1,1,4,5,4,5,4,5,1,3,1,1,6,7,4,5,6,7,6,7,6,7,6,7,4},
{7,6,7,6,7,4,5,4,5,6,7,4,5,1,1,4,5,6,7,6,7,6,7,4,5,4,5,4,5,6,7,4,5,4,5,4,5,4,5,6}
};

//東西南北のベクトルを定義（向き）
int g_directions[][2] = {///空白にすると初期化子が自動的で要素数を決定してくれる。今回は[4][2]。
{0,-1}, //DIRECTION_NORTH
{1,0},	//DIRECTION_EAST
{0,1},	//DIRECTION_SOUTH
{-1,0}	//DIRECTION_WEST
};

//塗りつぶし配列
bool fill[MAP_HEIGHT][MAP_WIDTH];

//カーソル座標を定義
int cursorX = 0;
int cursorY = 0;

//----------------------------------------------------------------------------
//マップ描画全般の画像描画に関するハンドル
//

//チップ画像
int character_chips[7][12];	//キャラチップ格納配列
int map_chips[1][88];		//マップチップ格納配列

//マップ画像変数
int graphic_cell_ground = 0;

//マップ下画像
int display_map = 0;

//カーソル画像
int g_cursor = 0;

//行動可能範囲画像
int fill_map = 0;

//三すくみ矢印画像
int g_relation = 0;
int g_relation_back = 0;

//マップ画面でのターン文字
int g_map_turn[1][15];

//味方フェーズ変数
int g_phaseAlly = PHASE_SELECT_CHARACTER;

//敵フェーズ変数
int g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;

//ターン変数
int g_turnMove = TURN_ALLAY;

//カーソルフラグ
bool g_flagCursor = true;

//エンター押しフラグ
bool g_flagEnter = false;

//スペース押しフラグ
bool g_flagEnemy = false;

//バトル進行中か否かの判定フラグ
int g_CanAttackMove = 0;

//現在敵何人目か（初期値はインデックスの３）
int currentEnemyNumber = 3;

// 最小距離の味方取得
int nearDistanceAlly = 0;

//味方ターン切り替え
bool g_flagTurnAlly = true;

//敵ターン切り替え
bool g_flagTurnEnemy = false;

//スコア変数
int g_score =0;

//敵一斉移動フラグ
bool g_enemyCheckFinish = true;

//SE再生フラグ
bool g_sePlay = true;

//----------------------------------------------------------------------------
//マップ全般に関わる関数
//

//一連の流れ
void turnMove(float delta_time) {

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 1400;

	//テロップアニメーションカウント
	float static telopTimeCount = 0;

	switch (g_turnMove) {

	case TURN_ALLAY: {

		if (g_flagTurnAlly) {

			//SE再生
			playSeTurnMove();

			//毎フレーム足していく処理
			telopTimeCount += delta_time;

			int telopFrame = telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][10], true);

			cellHeal();

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;			//テロップの流れた距離リセット
				telopTimeCount = 0;		//テロップのカウントリセット
				g_flagTurnAlly = false; //味方ターンのテロップ流しは一回で完了のためfalse
				g_sePlay = true;
			}
		}
		//味方移動全般の関数
		phaseAllyMove(delta_time);

		if (!g_flagEnter && g_flagCursor) {

			//ボタン操作描画
			leafBottonDrawAllyTurnMap(delta_time);
		}
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

			playSeTurnMove();

			//毎フレーム足していく処理
			telopTimeCount += delta_time;

			int telopFrame = telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][9], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;				//テロップの流れた距離リセット
				telopTimeCount = 0;			//テロップのカウントリセット
				g_flagTurnEnemy = false;	//敵ターンのテロップ流しは一回で完了のためfalse
				g_sePlay = true;
			}
		}
		//敵全員が移動する
		phaseEnemyMove(delta_time, currentEnemyNumber);

		const int charaAlly0 = 0;
		const int charaAlly1 = 1;
		const int charaAlly2 = 2;

		static int charaEnemy0 = 0;
		static int charaEnemy1 = 0;
		static int charaEnemy2 = 0;

		static int countBattle = 0;

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LSHIFT)) { countBattle++; }

		//★敵がいない場合の処理がない！


		//現状だとスペースを押さないと戦闘に入らない
		if (countBattle == 1) {

			enemyAttack(delta_time, charaAlly0, charaEnemy0);

			if (!checkCanAllyBattle(charaAlly0, charaEnemy0)) { break; }
		}
		else if (countBattle == 2) {

			enemyAttack(delta_time, charaAlly1, charaEnemy1);
		}
		else if (countBattle == 3) {

			enemyAttack(delta_time, charaAlly2, charaEnemy2);
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {

			countBattle = 0;
			g_enemyCheckFinish = true;
			g_flagEnter = false;
			g_flagCursor = true;
			character[0].done = false;			//味方ターン移行に際して、味方全員の行動が未行動にリセットされる
			character[1].done = false;
			character[2].done = false;
			g_flagTurnAlly = true;				//味方ターンのテロップを流すためにtrue
			g_turnMove = TURN_ALLAY;
			g_phaseAlly=PHASE_SELECT_CHARACTER;
		}
		//敵ターンボタン描画
		if (!g_flagEnter && g_flagCursor) {leafBottonDrawEnemyTurnMap(delta_time);}
		
		break;
	}
	}
}

//敵フェーズの動き
void phaseEnemyMove(float delta_time, int currentEnemyNumber) {

	//1人検証が終わるごとに増えていく
	const int ENEMY_COUNT = 15;

	//調査中のNumberを代入
	int enemyNumber = currentEnemyNumber;

	// 最大距離
	int maxDistance = INT_MAX;

	int _enemyX = 0;
	int _enemyY = 0;

	int _allyX = 0;
	int _allyY = 0;

	switch (g_phaseEnemy) {

	case PHASE_AI_SEARCH_CHARACTER: {

		for (int i = 0; i < CHARACTER_ALLAY_MAX; ++i) {

			_allyX = character[i].x;
			_allyY = character[i].y;

			_enemyX = character[enemyNumber].x;
			_enemyY = character[enemyNumber].y;

			//敵味方の座標が同じ＋どちらかがHPゼロならスルー
			if (_allyX == _enemyX && _allyY == _enemyY ||
				character[i].hp <= 0 || character[enemyNumber].hp <= 0) continue;

			int distance = abs(_allyX - _enemyX) + abs(_allyY - _enemyY);

			if (distance < maxDistance) {

				maxDistance = distance;
				nearDistanceAlly = i;
			}
		}

		for (int dir = 0; dir < DIRECTION_MAX; dir++)
		{
			int _x = character[enemyNumber].x + g_directions[dir][0];
			int _y = character[enemyNumber].y + g_directions[dir][1];
			fillCanMove(enemyNumber, _x, _y, character[enemyNumber].move);
		}

		//味方までの距離と敵キャラの行動範囲を比較
		if (maxDistance <= character[enemyNumber].move && fill[_enemyY][_enemyX]) {

			g_phaseEnemy = PHASE_AI_MOVE_CHARACTER;
		}
		//範囲内ならキャラクター移動
		else { break; }
	}
	case PHASE_AI_MOVE_CHARACTER: {

		int enemyX = character[enemyNumber].x;
		int enemyY = character[enemyNumber].y;

		int allyX = character[nearDistanceAlly].x;
		int allyY = character[nearDistanceAlly].y;

		if (character[nearDistanceAlly].hp > 0 && character[enemyNumber].hp > 0) {

			// 場面分けで敵の座標を更新
			if (enemyX > allyX && (enemyY > allyY || enemyY < allyY)) {

				enemyX = allyX + 1;
				enemyY = allyY;
			}
			else if (enemyX < allyX && (enemyY > allyY || enemyY < allyY)) {

				enemyX = allyX - 1;
				enemyY = allyY;
			}
			else if (enemyX == allyX && enemyY > allyY) { enemyY = allyY + 1; }

			else if (enemyX == allyX && enemyY < allyY) { enemyY = allyY - 1; }

			else if (enemyX > allyX && enemyY == allyY) { enemyX = allyX + 1; }

			else if (enemyX < allyX && enemyY == allyY) { enemyX = allyX - 1; }
		}
		//移動先に既に他のキャラ座標があった場合は動かない
		if (charaData[enemyY][enemyX]==-1) {
			
			//座標更新
			character[enemyNumber].x = enemyX;
			character[enemyNumber].y = enemyY;

			charaData[character[enemyNumber].y][character[enemyNumber].x] = enemyNumber;
		}
		break;
	}
	}
	// 次の敵キャラクターのインデックス設定
	enemyNumber++;

	if (enemyNumber >= ENEMY_COUNT) {

		g_enemyCheckFinish = false;
		resetFill();
		return;
	}

	else {//未調査の次の敵キャラクター判定のため更新
		g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;
		phaseEnemyMove(delta_time, enemyNumber);
	}
}

//カーソルエンター処理について
void phaseAllyMove(float delta_time) {

	switch (g_phaseAlly) {

	case PHASE_SELECT_CHARACTER: {
		
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			resetFill();

			//選択したキャラクターを囲って東西南北に1マスずつ塗りつぶし
			int chara = getCharacter(cursorX, cursorY);
			if (chara < 0) { break; } //負の値だったらいない

			//行動済みなら座標動かない
			if (character[chara].done) { resetFill(); }

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
						
						//fill範囲内にキャラクターがいた場合、かつそのキャラが自分自身でなければそこは描画されない
						//描画されている範囲＝移動できる場所になっているため、自分自身も描画することでそこへ移動したという処理になる
						if (standChara >= 0 && fill[i][j] && chara!= standChara) { fill[i][j] = false; }
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

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

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
				if (checkBattleFlag) { g_phaseAlly = PHASE_SELECT_ATTACK; }

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
	
		std::vector<int> adjacentEnemies = getAdjacentCharacters(g_selectedChara);
		
		for (int enemy : adjacentEnemies) {
		
			if (character[enemy].x == cursorX && character[enemy].y == cursorY) {
			
				predictionDraw(g_selectedChara, enemy);
				
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
					g_flagEnter = true;
					g_flagCursor = false;
					g_flagBattleAnime = true;
					g_flagBattleHp = true;
					g_CanAttackMove++;
					g_sePlay = true;
				}
				battleAlly(delta_time, g_selectedChara, enemy);
			}
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

//score表示
void scoreDraw() {

	SetFontSize(40);
	DrawStringEx(100, 0, TEXT_COLOR_WHITE, "SCORE :");
	std::string SCORE = std::to_string(g_score);
	DrawStringEx(260, 0, TEXT_COLOR_WHITE, SCORE.c_str());
}

//fillの初期化（これをしないと、次に選択しても前の選択情報が残ったままになってしまう）
void resetFill() {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			fill[i][j] = false;
		}
	}
}

//fillの画像描画
void drawFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (fill[i][j]) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, fill_map, TRUE); }//塗りつぶし可能なら描画
		}
	}
}

//塗りつぶしできるかどんどん判定してく
void fillCanMove(int _chara, int _x, int _y, int _move) {//選択した味方キャラ、座標、移動数

	//画面外はスルー
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return; }

	//今いる場所のcell情報を取得、職業の情報と合わせてmoveCellsを取得する
	//例えば、森の上にいる場合は、職業によっては移動コスト１、２だったりする。
	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	//移動可能数が０以下、移動可能数より下なら描画不可で終了
	if (moveCost < 0 || _move < moveCost) { return; }

	//そうじゃなければ塗りつぶし可能
	fill[_y][_x] = true;

	//移動するごとにコストを使っていく
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		fillCanMove(_chara, x, y, _move);//どんどん隣り合う場所を調査
	}
}

//各フェーズでの指示文字描画処理
void instructions(float delta_time) {

	//命令文の座標
	const int INSTRUCTIONS_X = 700;
	const int INSTRUCTIONS_Y = 10;

	float static instructionsTimeCount = 0;
	bool static instructionsDraw = true;

	//点滅処理
	instructionsTimeCount += delta_time;

	if (instructionsTimeCount > 1.0f) {
		instructionsDraw = !instructionsDraw;
		instructionsTimeCount = 0;
	}

	//各フェーズでの指示文章描画
	switch (g_phaseAlly) {

		case PHASE_SELECT_CHARACTER:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "キャラクターを選んでください\n", TEXT_COLOR_WHITE);
			}
			break;

		case PHASE_SET_MOVE_POSITION:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "移動先を選んでください\n", TEXT_COLOR_WHITE);
			}
			break;

		case PHASE_SELECT_ATTACK:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "攻撃対象を選んでください\n", TEXT_COLOR_WHITE);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y+40, "Space：待機ボタン\n", TEXT_COLOR_WHITE);

			}
			break;
	}
}

//カーソル移動
void cursorMove(float delta_time) {

	float static cursorWaitCount = 0;

	//毎フレーム足していく処理
	cursorWaitCount += delta_time;

	if (g_flagCursor && cursorWaitCount > 0.1f) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1) { cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0) { cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1) { cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0) { cursorX--; }
	
		cursorWaitCount = 0;
	}
}

//マップ全体の情報を読み取り、ifで各数字に対応するチップを描画する
void mapPosition(float delta_time) {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			//草地マップの描画（下地）
			DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][0], TRUE);

			//マップチップ描画
			if (mapData[i][j] == 1) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][9], TRUE);}
			else if (mapData[i][j] == 2) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][56], TRUE);}
			else if (mapData[i][j] == 3) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][73], TRUE);}
			else if (mapData[i][j] == 4) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][32], TRUE);}
			else if (mapData[i][j] == 5) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][33], TRUE);}
			else if (mapData[i][j] == 6) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][40], TRUE);}
			else if (mapData[i][j] == 7) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][41], TRUE);}
			else if (mapData[i][j] == 8) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][51], TRUE);}
			else if (mapData[i][j] == 9) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][52], TRUE);}
			else if (mapData[i][j] == 10){ DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][59], TRUE);}
			else if (mapData[i][j] == 11){ DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][60], TRUE);}

			//キャラチップ描画
			if (charaData[i][j] >= 0) {

				if (charaData[i][j] == 0) {
				
					static float charaSWORD_timeCount = 0;
					static int charaSWORD_vector = 0;
					static int charaSWORD_vectorCount = 0;

					//毎フレーム足していく処理
					charaSWORD_timeCount += delta_time;

					if (charaSWORD_timeCount > 0.5f) {

						if (charaSWORD_vector == 2) { charaSWORD_vectorCount = -1; }
						else if (charaSWORD_vector == 0) { charaSWORD_vectorCount = 1; }

						charaSWORD_vector += charaSWORD_vectorCount;

						charaSWORD_timeCount = 0;
					}
					if (character[0].done) {DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[0][1], TRUE);}
					else if (!character[0].done) {DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[0][charaSWORD_vector], TRUE);}
				}
				else if (charaData[i][j] == 1) {
				
					static float charaSNIP_timeCount = 0;
					static int charaSNIP_vector = 0;
					static int charaSNIP_vectorCount = 0;

					//毎フレーム足していく処理
					charaSNIP_timeCount += delta_time;

					if (charaSNIP_timeCount > 0.5f) {

						if (charaSNIP_vector == 2) { charaSNIP_vectorCount = -1; }
						else if (charaSNIP_vector == 0) { charaSNIP_vectorCount = 1; }

						charaSNIP_vector += charaSNIP_vectorCount;

						charaSNIP_timeCount = 0;
					}
					if (character[1].done) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[1][1], TRUE); }
					else if (!character[1].done) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[1][charaSNIP_vector], TRUE); }
				}
				else if (charaData[i][j] == 2) { 
				
					static float charaMAGIC_timeCount = 0;
					static int charaMAGIC_vector = 0;
					static int charaMAGIC_vectorCount = 0;

					//毎フレーム足していく処理
					charaMAGIC_timeCount += delta_time;

					if (charaMAGIC_timeCount > 0.5f) {

						if (charaMAGIC_vector == 2) { charaMAGIC_vectorCount = -1; }
						else if (charaMAGIC_vector == 0) { charaMAGIC_vectorCount = 1; }

						charaMAGIC_vector += charaMAGIC_vectorCount;

						charaMAGIC_timeCount = 0;
					}
					if (character[2].done) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[2][1], TRUE); }
					else if (!character[2].done) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[2][charaMAGIC_vector], TRUE); }
				}
				else if (charaData[i][j] == 3 || charaData[i][j] == 6 || charaData[i][j] == 9 || charaData[i][j] == 12)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[3][1], TRUE);
				}
				else if (charaData[i][j] == 4 || charaData[i][j] == 7 || charaData[i][j] == 10 || charaData[i][j] == 13)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[4][1], TRUE);
				}
				else if (charaData[i][j] == 5 || charaData[i][j] == 8 || charaData[i][j] == 11 || charaData[i][j] == 14)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[5][1], TRUE);
				}
				else if (charaData[i][j] == 15)
				{
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, character_chips[6][1], TRUE);
				}
			}
			//マップ上でのキャラ情報画面描画
			DrawExtendGraph(0, 500, 1400, 730, display_map, true);
			
			//三すくみ関連画像描画
			DrawExtendGraph(0, 370, 125, 480, g_relation_back, true);
			DrawGraph(15, 370, g_relation, TRUE);
			DrawExtendGraph(0, 370, 40, 410, icon_sword, true);
			DrawExtendGraph(35, 440, 75, 480, icon_magic, true);
			DrawExtendGraph(85, 390, 125, 430, icon_snip, true);

			//現在の選択カーソルの位置を描画
			if (j == cursorX && i == cursorY) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, g_cursor, TRUE); }
		}
	}
}

//味方ターンマップ画面のボタン表記
void leafBottonDrawAllyTurnMap(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//毎フレーム足していく処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 2.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(890, 400, 970, 480, g_bottonCursor, true);
		DrawStringEx(970, 430, TEXT_COLOR_WHITE, "移動\n");
		DrawExtendGraph(1140, 400, 1220, 480, g_bottonEnter, true);
		DrawStringEx(1220, 430, TEXT_COLOR_WHITE, "決定\n");
		DrawExtendGraph(1010, 400, 1090, 480, g_bottonSpace, true);
		DrawStringEx(1090, 430, TEXT_COLOR_WHITE, "待機\n");
	}
	if (!leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonTab, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "味方ターン終了\n");
	}
}

//敵ターンマップ画面のボタン表記
void leafBottonDrawEnemyTurnMap(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//毎フレーム足していく処理
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 2.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonShift, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "戦闘呼び\n");
		DrawExtendGraph(1140, 400, 1220, 480, g_bottonSpace, true);
		DrawStringEx(1220, 430, TEXT_COLOR_WHITE, "戦闘\n");
	}
	if (!leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonTab, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "敵ターン終了\n");
	}
}

//戦闘前の情報予測描画(攻撃/防御)
void predictionBattle(int attack, int defence) {

	//名前の表示位置
	const int ALLAY_NAME_START_X = 1180;
	const int ENEMY_NAME_START_X = 1050;
	const int NAME_Y = 100;

	//攻撃力の描画位置
	const int ALLAY_ATTACK_X = 1200;
	const int ENEMY_ATTACK_X = 1050;
	const int ATTACK_Y = 150;

	//命中率の描画位置
	const int ALLAY_HIT_X = 1200;
	const int ENEMY_HIT_X = 1050;
	const int HIT_Y = 200;

	//名前描画
	SetFontSize(20);

	DrawStringEx(ALLAY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());	//味方
	
	if (defence != 15) {DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());}//敵
	else {
		SetFontSize(15);
		DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());//長
	}

	//攻撃力描画
	SetFontSize(30);

	//命中率描画
	if (ThreeRelation(attack, defence) == 0) {		//有利の場合

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * 2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence) / 2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);	//2*0.5=1.0でそのまま
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence) / 2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
	}
	else if (ThreeRelation(attack, defence) == 1) {	//不利の場合

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);	//2*0.5=1.0でそのまま
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence) / 2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * 2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence) / 2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
	}
	else if (ThreeRelation(attack, defence) == 2) {	//それ以外

		//味方の与えるダメージ
		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//味方の与えるダメージ
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//敵の与えるダメージ
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());

		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
	}
}

//戦闘前情報グラフィック描画
void predictionDraw(int attack,int defence) {

	const int drawAttackX = 1100;
	const int drawHitX = 1115;
	const int drawAttackY = 150;
	const int drawHitY = 200;

	DrawExtendGraph(1030, 90, 1270, 250, display_map, true);

	SetFontSize(20);

	DrawStringEx(drawAttackX, drawAttackY, TEXT_COLOR_WHITE, "ダメージ");
	DrawStringEx(drawHitX, drawHitY, TEXT_COLOR_WHITE, "命中率");

	predictionBattle(attack,defence);
}

//回復地形の上にいたら、ターン開始時に全回復
void cellHeal() {

	for (int i = 0; i < CHARACTER_ALLAY_MAX; i++) {

		if (mapData[character[i].y][character[i].x] == CELL_HOUSE ||
			mapData[character[i].y][character[i].x] == CELL_FORT) {

			if (character[i].hp > 0 && character[i].hp < character[i].maxHp) {

				character[i].hp = character[i].maxHp;

				if (character[i].hp >= character[i].maxHp) { character[i].hp = character[i].maxHp; }
			}
		}
	}
}

//回復情報描画
void cellInfoDisplay() {

	if (g_flagCursor) {

		//ここから情報開示のための文字描画
		SetFontSize(30);

		if (mapData[cursorY][cursorX] == CELL_FORT && charaData[cursorY][cursorX]==-1) {

			DrawStringEx(100, 530, TEXT_COLOR_WHITE, "砦　　：　待機で次ターン開始時に全回復\n");
		}
		if (mapData[cursorY][cursorX] == CELL_HOUSE && charaData[cursorY][cursorX] == -1) {
		
			DrawStringEx(100, 530, TEXT_COLOR_WHITE, "民家　：　待機で次ターン開始時に全回復\n");
		}
	}
}

//音声関連
void playMusic() {

	StopSoundMem(g_bgmGameOver);
	StopSoundMem(g_bgmEnding);

	DeleteSoundMem(g_bgmTitle);	//タイトル～チュートリアルまでのBGM削除

	if (CheckSoundMem(g_bgmMap) == 0) { PlaySoundMem(g_bgmMap, DX_PLAYTYPE_LOOP, TRUE); }
}

//ターン切り替えse再生
void playSeTurnMove() {

	if (g_sePlay && CheckSoundMem(g_seMoveBattle) == 0) PlaySoundMem(g_seMoveBattle, DX_PLAYTYPE_BACK, TRUE);

	g_sePlay = false;
}