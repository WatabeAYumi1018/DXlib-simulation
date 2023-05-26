#pragma once

//エフェクトサイズ
const int EFFECT_SIZE = 120;	

//アニメーションのMAXフレーム
const int MAX_EFFECT_FRAM = 10;

const int SPEED_DIFFERENCE = 5;

const int HP_ALLAY_X = 800;
const int HP_ENEMY_X = 400;
const int HP_Y = 500;

//戦闘中の画面ハンドル
extern int g_battleGround ;
extern int g_battleParaBack ;

//戦闘中のパラ表示
extern int g_battle_hp[1][35];
extern int g_battle_attack[1][42];
extern int g_battle_hit[1][25];

//キャラアニメーション関連
extern int g_charaAlly_vector ;		//味方キャラの向き
extern int g_charaEnemy_vector;		//敵キャラの向き
extern int g_vectorAlly_count ;		//味方カウント変数
extern float g_vectorEnemy_count ;	//敵カウント変数
extern float g_animAlly_timeCount;	//仲間描画速さの制御
extern float g_animEnemy_timeCount;	//敵描画速さの制御

//戦闘中の攻撃エフェクト
extern int g_battle_effect_sword[1][14];
extern int g_battle_effect_snip[1][14];
extern int g_battle_effect_magic[1][14];
extern int g_battle_effect_leader[1][14];

//攻撃エフェクトのアニメーションハンドル
extern float g_effectTimeCount ;
extern int g_effectFrame ;

//戦闘アニメーションの生存フラグ
extern bool g_flagBattleAnime ;

//HP減算フラグ
extern bool g_flagBattleHp ;

//HPタイムカウント
extern float g_HpTimeCount ;

//攻撃可能かどうか判定
bool checkCanBattle(int attack, int defence);

//戦闘下画面のグラフィック描画
void battleGraph();

//戦闘中の情報描画(攻撃/防御)
void battleInfo(int attack, int defence);

//開始時のHP描画
void battleHp(int attack, int defence);

//戦闘画面のキャラアニメ
void battleCharaGraphic(float delta_time, int attack, int defence);

//戦闘エフェクトアニメ
void battleEffectGraphic(float delta_time, int chara);

//ロスト処理
void battleLost(int chara);

//三すくみの関係
bool ThreeRelation(int attack, int defence);

//戦闘計算処理
int battleCalculate(int attack, int defence);

//戦闘によるダメージ変化の流れ
void battleHpMove(float delta_time, int attack, int defence);

//戦闘処理終了
void battleExit();

//スピード比較
//bool battleSpeed(float delta_time, int attack, int defence);