#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "mapScene_character.h"
#include "titleScene.h"
#include "mapScene_battle.h"

//----------------------------------------------------------------------------
//�}�b�v�S�ʂ̕ϐ�
//

//�O���X�}�b�v�S�̂�z��Ƃ��Ċi�[
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

//������k�̃x�N�g�����`�i�����j
int g_directions[][2] = {///�󔒂ɂ���Ə������q�������I�ŗv�f�������肵�Ă����B�����[4][2]�B
{0,-1}, //DIRECTION_NORTH
{1,0},	//DIRECTION_EAST
{0,1},	//DIRECTION_SOUTH
{-1,0}	//DIRECTION_WEST
};

//�h��Ԃ��z��
bool fill[MAP_HEIGHT][MAP_WIDTH];

//�J�[�\�����W���`
int cursorX = 0;
int cursorY = 0;

//----------------------------------------------------------------------------
//�}�b�v�`��S�ʂ̉摜�`��Ɋւ���n���h��
//

//�`�b�v�摜
int character_chips[7][12];	//�L�����`�b�v�i�[�z��
int map_chips[1][88];		//�}�b�v�`�b�v�i�[�z��

//�}�b�v�摜�ϐ�
int graphic_cell_ground = 0;

//�}�b�v���摜
int display_map = 0;

//�J�[�\���摜
int g_cursor = 0;

//�s���\�͈͉摜
int fill_map = 0;

//�O�����ݖ��摜
int g_relation = 0;
int g_relation_back = 0;

//�}�b�v��ʂł̃^�[������
int g_map_turn[1][15];

//�����t�F�[�Y�ϐ�
int g_phaseAlly = PHASE_SELECT_CHARACTER;

//�G�t�F�[�Y�ϐ�
int g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;

//�^�[���ϐ�
int g_turnMove = TURN_ALLAY;

//�J�[�\���t���O
bool g_flagCursor = true;

//�G���^�[�����t���O
bool g_flagEnter = false;

//�X�y�[�X�����t���O
bool g_flagEnemy = false;

//�o�g���i�s�����ۂ��̔���t���O
int g_CanAttackMove = 0;

//���ݓG���l�ڂ��i�����l�̓C���f�b�N�X�̂R�j
int currentEnemyNumber = 3;

// �ŏ������̖����擾
int nearDistanceAlly = 0;

//�����^�[���؂�ւ�
bool g_flagTurnAlly = true;

//�G�^�[���؂�ւ�
bool g_flagTurnEnemy = false;

//�X�R�A�ϐ�
int g_score =0;

//�G��Ĉړ��t���O
bool g_enemyCheckFinish = true;

//SE�Đ��t���O
bool g_sePlay = true;

//----------------------------------------------------------------------------
//�}�b�v�S�ʂɊւ��֐�
//

//��A�̗���
void turnMove(float delta_time) {

	const int TELOP_X_END = 700;
	const int TELOP_Y_START = 100;
	const int TELOP_Y_END = 200;
	const int TELOP_SPEED = 700;
	const int TELOP_FRAME_MAX = 1400;

	//�e���b�v�A�j���[�V�����J�E���g
	float static telopTimeCount = 0;

	switch (g_turnMove) {

	case TURN_ALLAY: {

		if (g_flagTurnAlly) {

			//SE�Đ�
			playSeTurnMove();

			//���t���[�������Ă�������
			telopTimeCount += delta_time;

			int telopFrame = telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][10], true);

			cellHeal();

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;			//�e���b�v�̗��ꂽ�������Z�b�g
				telopTimeCount = 0;		//�e���b�v�̃J�E���g���Z�b�g
				g_flagTurnAlly = false; //�����^�[���̃e���b�v�����͈��Ŋ����̂���false
				g_sePlay = true;
			}
		}
		//�����ړ��S�ʂ̊֐�
		phaseAllyMove(delta_time);

		if (!g_flagEnter && g_flagCursor) {

			//�{�^������`��
			leafBottonDrawAllyTurnMap(delta_time);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {

			g_flagTurnEnemy = true;		//�G�^�[���̃e���b�v�𗬂����߂�true
			character[0].done = true;	//�����S���̍s�����s���ς݂�
			character[1].done = true;
			character[2].done = true;
			g_turnMove = TURN_ENEMY;
		}
		break;
	}

	case TURN_ENEMY: {

		if (g_flagTurnEnemy) {

			playSeTurnMove();

			//���t���[�������Ă�������
			telopTimeCount += delta_time;

			int telopFrame = telopTimeCount * TELOP_SPEED;

			DrawExtendGraph(0 + telopFrame, TELOP_Y_START, TELOP_X_END + telopFrame, TELOP_Y_END, g_map_turn[0][9], true);

			if (telopFrame >= TELOP_FRAME_MAX) {

				telopFrame = 0;				//�e���b�v�̗��ꂽ�������Z�b�g
				telopTimeCount = 0;			//�e���b�v�̃J�E���g���Z�b�g
				g_flagTurnEnemy = false;	//�G�^�[���̃e���b�v�����͈��Ŋ����̂���false
				g_sePlay = true;
			}
		}
		//�G�S�����ړ�����
		phaseEnemyMove(delta_time, currentEnemyNumber);

		const int charaAlly0 = 0;
		const int charaAlly1 = 1;
		const int charaAlly2 = 2;

		static int charaEnemy0 = 0;
		static int charaEnemy1 = 0;
		static int charaEnemy2 = 0;

		static int countBattle = 0;

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LSHIFT)) { countBattle++; }

		//���G�����Ȃ��ꍇ�̏������Ȃ��I


		//���󂾂ƃX�y�[�X�������Ȃ��Ɛ퓬�ɓ���Ȃ�
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
			character[0].done = false;			//�����^�[���ڍs�ɍۂ��āA�����S���̍s�������s���Ƀ��Z�b�g�����
			character[1].done = false;
			character[2].done = false;
			g_flagTurnAlly = true;				//�����^�[���̃e���b�v�𗬂����߂�true
			g_turnMove = TURN_ALLAY;
			g_phaseAlly=PHASE_SELECT_CHARACTER;
		}
		//�G�^�[���{�^���`��
		if (!g_flagEnter && g_flagCursor) {leafBottonDrawEnemyTurnMap(delta_time);}
		
		break;
	}
	}
}

//�G�t�F�[�Y�̓���
void phaseEnemyMove(float delta_time, int currentEnemyNumber) {

	//1�l���؂��I��邲�Ƃɑ����Ă���
	const int ENEMY_COUNT = 15;

	//��������Number����
	int enemyNumber = currentEnemyNumber;

	// �ő勗��
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

			//�G�����̍��W�������{�ǂ��炩��HP�[���Ȃ�X���[
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

		//�����܂ł̋����ƓG�L�����̍s���͈͂��r
		if (maxDistance <= character[enemyNumber].move && fill[_enemyY][_enemyX]) {

			g_phaseEnemy = PHASE_AI_MOVE_CHARACTER;
		}
		//�͈͓��Ȃ�L�����N�^�[�ړ�
		else { break; }
	}
	case PHASE_AI_MOVE_CHARACTER: {

		int enemyX = character[enemyNumber].x;
		int enemyY = character[enemyNumber].y;

		int allyX = character[nearDistanceAlly].x;
		int allyY = character[nearDistanceAlly].y;

		if (character[nearDistanceAlly].hp > 0 && character[enemyNumber].hp > 0) {

			// ��ʕ����œG�̍��W���X�V
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
		//�ړ���Ɋ��ɑ��̃L�������W���������ꍇ�͓����Ȃ�
		if (charaData[enemyY][enemyX]==-1) {
			
			//���W�X�V
			character[enemyNumber].x = enemyX;
			character[enemyNumber].y = enemyY;

			charaData[character[enemyNumber].y][character[enemyNumber].x] = enemyNumber;
		}
		break;
	}
	}
	// ���̓G�L�����N�^�[�̃C���f�b�N�X�ݒ�
	enemyNumber++;

	if (enemyNumber >= ENEMY_COUNT) {

		g_enemyCheckFinish = false;
		resetFill();
		return;
	}

	else {//�������̎��̓G�L�����N�^�[����̂��ߍX�V
		g_phaseEnemy = PHASE_AI_SEARCH_CHARACTER;
		phaseEnemyMove(delta_time, enemyNumber);
	}
}

//�J�[�\���G���^�[�����ɂ���
void phaseAllyMove(float delta_time) {

	switch (g_phaseAlly) {

	case PHASE_SELECT_CHARACTER: {
		
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			resetFill();

			//�I�������L�����N�^�[���͂��ē�����k��1�}�X���h��Ԃ�
			int chara = getCharacter(cursorX, cursorY);
			if (chara < 0) { break; } //���̒l�������炢�Ȃ�

			//�s���ς݂Ȃ���W�����Ȃ�
			if (character[chara].done) { resetFill(); }

			//�L�����������(����ȊO��)�h��Ԃ�
			else {

				for (int dir = 0; dir < DIRECTION_MAX; dir++)
				{
					int x = character[chara].x + g_directions[dir][0];
					int y = character[chara].y + g_directions[dir][1];
					fillCanMove(chara, x, y, character[chara].move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
				}
				//�`����ɃL������������A�����͕`�悵�Ȃ�
				for (int i = 0; i < MAP_HEIGHT; i++) {
					for (int j = 0; j < MAP_WIDTH; j++) {

						int standChara = getCharacter(j, i);
						
						//fill�͈͓��ɃL�����N�^�[�������ꍇ�A�����̃L�������������g�łȂ���΂����͕`�悳��Ȃ�
						//�`�悳��Ă���͈́��ړ��ł���ꏊ�ɂȂ��Ă��邽�߁A�������g���`�悷�邱�Ƃł����ֈړ������Ƃ��������ɂȂ�
						if (standChara >= 0 && fill[i][j] && chara!= standChara) { fill[i][j] = false; }
					}
				}
				drawFill();

				//�L������I��������A�ړ��t�F�[�Y��
				if (character[chara].team == TEAM_ALLY) {

					g_selectedChara = chara; //�����L��������					
					g_phaseAlly = PHASE_SET_MOVE_POSITION;
				}
				break;
			}
		}
	}
	case PHASE_SET_MOVE_POSITION: {

		drawFill();

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			//�ړ���̑I���A����������I���t�F�[�Y�ɖ߂�
			if (fill[cursorY][cursorX]) {

				//�ړ��ɂ����W�̕ω�
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
					//�U���\�L���������Ȃ���΁A�ҋ@
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

		//�U���\�L���������Ȃ���΁A�ҋ@
		character[g_selectedChara].done = true;
		resetFill();
		g_phaseAlly = PHASE_SELECT_CHARACTER;
	}
}

//score�\��
void scoreDraw() {

	SetFontSize(40);
	DrawStringEx(100, 0, TEXT_COLOR_WHITE, "SCORE :");
	std::string SCORE = std::to_string(g_score);
	DrawStringEx(260, 0, TEXT_COLOR_WHITE, SCORE.c_str());
}

//fill�̏������i��������Ȃ��ƁA���ɑI�����Ă��O�̑I����񂪎c�����܂܂ɂȂ��Ă��܂��j
void resetFill() {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			fill[i][j] = false;
		}
	}
}

//fill�̉摜�`��
void drawFill() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (fill[i][j]) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, fill_map, TRUE); }//�h��Ԃ��\�Ȃ�`��
		}
	}
}

//�h��Ԃ��ł��邩�ǂ�ǂ񔻒肵�Ă�
void fillCanMove(int _chara, int _x, int _y, int _move) {//�I�����������L�����A���W�A�ړ���

	//��ʊO�̓X���[
	if (_x < 0 || _x >= MAP_WIDTH || _y < 0 || _y >= MAP_HEIGHT) { return; }

	//������ꏊ��cell�����擾�A�E�Ƃ̏��ƍ��킹��moveCells���擾����
	//�Ⴆ�΁A�X�̏�ɂ���ꍇ�́A�E�Ƃɂ���Ă͈ړ��R�X�g�P�A�Q�������肷��B
	int moveCost = jobData[character[_chara].job].moveCells[mapData[_y][_x]];

	//�ړ��\�����O�ȉ��A�ړ��\����艺�Ȃ�`��s�ŏI��
	if (moveCost < 0 || _move < moveCost) { return; }

	//��������Ȃ���Γh��Ԃ��\
	fill[_y][_x] = true;

	//�ړ����邲�ƂɃR�X�g���g���Ă���
	_move -= moveCost;

	for (int dir = 0; dir < DIRECTION_MAX; dir++)
	{
		int x = _x + g_directions[dir][0];
		int y = _y + g_directions[dir][1];
		fillCanMove(_chara, x, y, _move);//�ǂ�ǂ�ׂ荇���ꏊ�𒲍�
	}
}

//�e�t�F�[�Y�ł̎w�������`�揈��
void instructions(float delta_time) {

	//���ߕ��̍��W
	const int INSTRUCTIONS_X = 700;
	const int INSTRUCTIONS_Y = 10;

	float static instructionsTimeCount = 0;
	bool static instructionsDraw = true;

	//�_�ŏ���
	instructionsTimeCount += delta_time;

	if (instructionsTimeCount > 1.0f) {
		instructionsDraw = !instructionsDraw;
		instructionsTimeCount = 0;
	}

	//�e�t�F�[�Y�ł̎w�����͕`��
	switch (g_phaseAlly) {

		case PHASE_SELECT_CHARACTER:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "�L�����N�^�[��I��ł�������\n", TEXT_COLOR_WHITE);
			}
			break;

		case PHASE_SET_MOVE_POSITION:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "�ړ����I��ł�������\n", TEXT_COLOR_WHITE);
			}
			break;

		case PHASE_SELECT_ATTACK:

			if (instructionsDraw) {
				SetFontSize(30);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y, "�U���Ώۂ�I��ł�������\n", TEXT_COLOR_WHITE);
				DrawString(INSTRUCTIONS_X, INSTRUCTIONS_Y+40, "Space�F�ҋ@�{�^��\n", TEXT_COLOR_WHITE);

			}
			break;
	}
}

//�J�[�\���ړ�
void cursorMove(float delta_time) {

	float static cursorWaitCount = 0;

	//���t���[�������Ă�������
	cursorWaitCount += delta_time;

	if (g_flagCursor && cursorWaitCount > 0.1f) {

		if ((tnl::Input::IsKeyDown(eKeys::KB_DOWN)) && cursorY < MAP_HEIGHT - 1) { cursorY++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_UP)) && cursorY > 0) { cursorY--; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) && cursorX < MAP_WIDTH - 1) { cursorX++; }
		if ((tnl::Input::IsKeyDown(eKeys::KB_LEFT)) && cursorX > 0) { cursorX--; }
	
		cursorWaitCount = 0;
	}
}

//�}�b�v�S�̂̏���ǂݎ��Aif�Ŋe�����ɑΉ�����`�b�v��`�悷��
void mapPosition(float delta_time) {

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {

			//���n�}�b�v�̕`��i���n�j
			DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, map_chips[graphic_cell_ground][0], TRUE);

			//�}�b�v�`�b�v�`��
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

			//�L�����`�b�v�`��
			if (charaData[i][j] >= 0) {

				if (charaData[i][j] == 0) {
				
					static float charaSWORD_timeCount = 0;
					static int charaSWORD_vector = 0;
					static int charaSWORD_vectorCount = 0;

					//���t���[�������Ă�������
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

					//���t���[�������Ă�������
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

					//���t���[�������Ă�������
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
			//�}�b�v��ł̃L��������ʕ`��
			DrawExtendGraph(0, 500, 1400, 730, display_map, true);
			
			//�O�����݊֘A�摜�`��
			DrawExtendGraph(0, 370, 125, 480, g_relation_back, true);
			DrawGraph(15, 370, g_relation, TRUE);
			DrawExtendGraph(0, 370, 40, 410, icon_sword, true);
			DrawExtendGraph(35, 440, 75, 480, icon_magic, true);
			DrawExtendGraph(85, 390, 125, 430, icon_snip, true);

			//���݂̑I���J�[�\���̈ʒu��`��
			if (j == cursorX && i == cursorY) { DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, g_cursor, TRUE); }
		}
	}
}

//�����^�[���}�b�v��ʂ̃{�^���\�L
void leafBottonDrawAllyTurnMap(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//���t���[�������Ă�������
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 2.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(890, 400, 970, 480, g_bottonCursor, true);
		DrawStringEx(970, 430, TEXT_COLOR_WHITE, "�ړ�\n");
		DrawExtendGraph(1140, 400, 1220, 480, g_bottonEnter, true);
		DrawStringEx(1220, 430, TEXT_COLOR_WHITE, "����\n");
		DrawExtendGraph(1010, 400, 1090, 480, g_bottonSpace, true);
		DrawStringEx(1090, 430, TEXT_COLOR_WHITE, "�ҋ@\n");
	}
	if (!leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonTab, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "�����^�[���I��\n");
	}
}

//�G�^�[���}�b�v��ʂ̃{�^���\�L
void leafBottonDrawEnemyTurnMap(float delta_time) {

	SetFontSize(20);

	float static leafBottonTimeCount = 0;
	bool static leafBottonDraw = true;

	//���t���[�������Ă�������
	leafBottonTimeCount += delta_time;

	if (leafBottonTimeCount > 2.0f) {
		leafBottonDraw = !leafBottonDraw;
		leafBottonTimeCount = 0;
	}
	if (leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonShift, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "�퓬�Ă�\n");
		DrawExtendGraph(1140, 400, 1220, 480, g_bottonSpace, true);
		DrawStringEx(1220, 430, TEXT_COLOR_WHITE, "�퓬\n");
	}
	if (!leafBottonDraw) {
		DrawExtendGraph(980, 400, 1060, 480, g_bottonTab, true);
		DrawStringEx(1060, 430, TEXT_COLOR_WHITE, "�G�^�[���I��\n");
	}
}

//�퓬�O�̏��\���`��(�U��/�h��)
void predictionBattle(int attack, int defence) {

	//���O�̕\���ʒu
	const int ALLAY_NAME_START_X = 1180;
	const int ENEMY_NAME_START_X = 1050;
	const int NAME_Y = 100;

	//�U���͂̕`��ʒu
	const int ALLAY_ATTACK_X = 1200;
	const int ENEMY_ATTACK_X = 1050;
	const int ATTACK_Y = 150;

	//�������̕`��ʒu
	const int ALLAY_HIT_X = 1200;
	const int ENEMY_HIT_X = 1050;
	const int HIT_Y = 200;

	//���O�`��
	SetFontSize(20);

	DrawStringEx(ALLAY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[attack].name.c_str());	//����
	
	if (defence != 15) {DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());}//�G
	else {
		SetFontSize(15);
		DrawStringEx(ENEMY_NAME_START_X, NAME_Y, TEXT_COLOR_WHITE, character[defence].name.c_str());//��
	}

	//�U���͕`��
	SetFontSize(30);

	//�������`��
	if (ThreeRelation(attack, defence) == 0) {		//�L���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * 2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence) / 2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string((character[defence].attack - character[attack].defence) / 2);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
	}
	else if (ThreeRelation(attack, defence) == 1) {	//�s���̏ꍇ

		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);	//2*0.5=1.0�ł��̂܂�
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence) / 2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * 2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string((character[attack].attack - character[defence].defence) / 2);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "60");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "100");
	}
	else if (ThreeRelation(attack, defence) == 2) {	//����ȊO

		//�����̗^����_���[�W
		if (character[attack].speed - character[defence].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(2 * (character[attack].attack - character[defence].defence));
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else if (character[defence].speed - character[attack].speed >= SPEED_DIFFERENCE) {

			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(2 * (character[defence].attack - character[attack].defence));
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());
		}
		else {
			//�����̗^����_���[�W
			std::string ALLAY_attack = std::to_string(character[attack].attack - character[defence].defence);
			DrawStringEx(ALLAY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ALLAY_attack.c_str());

			//�G�̗^����_���[�W
			std::string ENEMY_attack = std::to_string(character[defence].attack - character[attack].defence);
			DrawStringEx(ENEMY_ATTACK_X, ATTACK_Y, TEXT_COLOR_WHITE, ENEMY_attack.c_str());

		}
		DrawStringEx(ALLAY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
		DrawStringEx(ENEMY_HIT_X, HIT_Y, TEXT_COLOR_WHITE, "80");
	}
}

//�퓬�O���O���t�B�b�N�`��
void predictionDraw(int attack,int defence) {

	const int drawAttackX = 1100;
	const int drawHitX = 1115;
	const int drawAttackY = 150;
	const int drawHitY = 200;

	DrawExtendGraph(1030, 90, 1270, 250, display_map, true);

	SetFontSize(20);

	DrawStringEx(drawAttackX, drawAttackY, TEXT_COLOR_WHITE, "�_���[�W");
	DrawStringEx(drawHitX, drawHitY, TEXT_COLOR_WHITE, "������");

	predictionBattle(attack,defence);
}

//�񕜒n�`�̏�ɂ�����A�^�[���J�n���ɑS��
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

//�񕜏��`��
void cellInfoDisplay() {

	if (g_flagCursor) {

		//����������J���̂��߂̕����`��
		SetFontSize(30);

		if (mapData[cursorY][cursorX] == CELL_FORT && charaData[cursorY][cursorX]==-1) {

			DrawStringEx(100, 530, TEXT_COLOR_WHITE, "�ԁ@�@�F�@�ҋ@�Ŏ��^�[���J�n���ɑS��\n");
		}
		if (mapData[cursorY][cursorX] == CELL_HOUSE && charaData[cursorY][cursorX] == -1) {
		
			DrawStringEx(100, 530, TEXT_COLOR_WHITE, "���Ɓ@�F�@�ҋ@�Ŏ��^�[���J�n���ɑS��\n");
		}
	}
}

//�����֘A
void playMusic() {

	StopSoundMem(g_bgmGameOver);
	StopSoundMem(g_bgmEnding);

	DeleteSoundMem(g_bgmTitle);	//�^�C�g���`�`���[�g���A���܂ł�BGM�폜

	if (CheckSoundMem(g_bgmMap) == 0) { PlaySoundMem(g_bgmMap, DX_PLAYTYPE_LOOP, TRUE); }
}

//�^�[���؂�ւ�se�Đ�
void playSeTurnMove() {

	if (g_sePlay && CheckSoundMem(g_seMoveBattle) == 0) PlaySoundMem(g_seMoveBattle, DX_PLAYTYPE_BACK, TRUE);

	g_sePlay = false;
}