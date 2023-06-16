#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "mapScene_map.h"
#include "tutorialScene.h"

//チュートリアル専用画像----------------
// 
//マップ全体図
int g_tutorialMap = 0;
//ゲーム目的
int g_tutorialMapStream = 0;
//味方ターンカーソル
int g_tutorialAllyTurnCursor = 0;
//下画面情報
int g_tutorialAllyTurnInfo = 0;
//味方ターン移動先選択
int g_tutorialAllyTurnSelect = 0;
//味方ターン移動
int g_tutorialAllyTurnMove = 0;
//味方ターン敵選択
int g_tutorialAllyTurnSelectEnemy = 0;
//敵ターン
int g_tutorialEnemyTurn = 0;
//敵ターン移動
int g_tutorialEnemyTurnMove = 0;
//敵ターン攻撃呼び出し
int g_tutorialMapEnemyTurnAttack = 0;
//敵ターン終了
int g_tutorialMapEnemyTurnEnd = 0;
//戦闘画面攻撃力
int g_tutorialBattleAttack = 0;
//戦闘画面命中率
int g_tutorialBattleHit = 0;
//スコア説明
int g_tutorialScore = 0;

//長立ち絵
int g_bossNormal=0;