#pragma once

//ストーリー背景
extern int g_storyBack;

//ストーリーウィンドウ
extern int g_storyWindow;

//メッセージ流し
extern int g_messageRun;

//少女普通立ち絵
extern int g_girlNormal;
//少女笑顔立ち絵
extern int g_girlSmile ;
//少女困り顔立ち絵
extern int g_girlTroubled;

//ストーリーシーンでの背景描画
void storyDraw();

//ストーリー画面エンターアイコン
void leafBottonDrawStory(float delta_time);

//会話メッセージ
void storyMessage();