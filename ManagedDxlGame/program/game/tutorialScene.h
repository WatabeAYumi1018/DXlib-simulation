#pragma once

//チュートリアル専用画像----------------
// 

//マップ全体図
extern int g_tutorialMap ;
//ゲーム目的
extern int g_tutorialMapStream;
//味方ターンカーソル
extern int g_tutorialAllyTurnCursor;
//下画面情報
extern int g_tutorialAllyTurnInfoSpeed ;
//味方ターン移動先選択
extern int g_tutorialAllyTurnSelect;
//味方ターン移動
extern int g_tutorialAllyTurnMove ;
//味方ターン攻撃予測
extern int g_tutorialPredictionBattle;
//敵ターン切り替え
extern int g_tutorialEnemyTurn;
//敵ターン動き
extern int g_tutorialMapEnemyTurnMove ;
//回復スポットの説明
extern int g_tutorialMapHeal;

//長立ち絵
extern int g_bossNormal;
extern int g_bossSmile;

//チュートリアル画像描画
void tutorialDraw();

//チュートリアル会話メッセージ
void tutorialMessage();