#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"


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
{5,1,6,7,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,6},
{7,4,5,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,4},
{1,6,7,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,1,6},
{4,5,1,1,1,1,4,5,1,0,3,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
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

//ボタン操作描画
int g_bottonLayout=0;

//カーソル画像
int g_cursor = 0;

//行動可能範囲画像
int fill_map = 0;

//三すくみ矢印画像
int g_relation = 0;
int g_relation_back = 0;

//マップ画面でのターン文字
int g_map_turn[1][15];

//----------------------------------------------------------------------------
//マップ全般に関わる関数
//

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

//fill==true　移動可能
//攻撃可能範囲定義　ex山にいる敵の隣から攻撃 int range=1;　range==

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

//情報や各フェーズでの指示文字描画処理（ここに点滅処理を加えよう）
//void instructions(float delta_time) {
//
//	//命令文の座標
//	const int INSTRUCTIONS_X = 700;
//	const int INSTRUCTIONS_Y = 10;
//
//	float static instructionsTimeCount = 0;
//	bool static instructionsDraw = true;
//
//	//毎フレーム足していく処理
//	instructionsTimeCount += delta_time;
//
//	if (instructionsTimeCount > 1.0f) {
//		instructionsDraw = !instructionsDraw;
//		instructionsTimeCount = 0;
//	}
//
//	//各フェーズでの指示文章描画
//	switch (g_phaseAlly) {
//
//		case PHASE_SELECT_CHARACTER:
//
//			if (instructionsDraw) {
//				SetFontSize(30);
//				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "キャラクターを選んでください\n", TEXT_COLOR_WHITE);
//			}
//			break;
//
//		case PHASE_SET_MOVE_POSITION:
//
//			if (instructionsDraw) {
//				SetFontSize(30);
//				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "移動先を選んでください\n", TEXT_COLOR_WHITE);
//			}
//			break;
//
//		case PHASE_SELECT_ATTACK:
//
//			if (instructionsDraw) {
//				SetFontSize(30);
//				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "攻撃対象を選んでください\n", TEXT_COLOR_WHITE);
//			}
//			break;
//	}
//}

//カーソル移動
void cursorMove() {
	if (g_flagCursor) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1) { cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0)				 { cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1) { cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0)				 { cursorX--; }

		WaitTimer(100);
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
			
			//ボタン説明描画
			DrawGraph(1060, 490, g_bottonLayout, TRUE);
			
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

//ゲームオーバー画面描画
void gameOver(float delta_time) {

	const int BACK_START_X_Y = 0;
	const int BACK_END_X = 1300;
	const int BACK_END_Y = 750;

	const int TEXT_START_X_Y = 200;
	const int TEXT_END_X = 1100;
	const int TEXT_END_Y = 400;

	float static g_gameOverTimeCount = 0;
	bool static g_gameOver_write = true;

	// 点滅処理
	g_gameOverTimeCount += delta_time;

	if (g_gameOverTimeCount > 0.5f) {
		g_gameOver_write = !g_gameOver_write;
		g_gameOverTimeCount = 0;
	}

	DrawExtendGraph(BACK_START_X_Y, BACK_START_X_Y, BACK_END_X, BACK_END_Y, g_gameOver, true);
	DrawExtendGraph(TEXT_START_X_Y, TEXT_START_X_Y, TEXT_END_X, TEXT_END_Y, g_map_turn[0][3], true);

	if (g_gameOver_write) {
		SetFontSize(50);
		DrawStringEx(550, 500, TEXT_COLOR_WHITE, "CLOSE");
	}
}