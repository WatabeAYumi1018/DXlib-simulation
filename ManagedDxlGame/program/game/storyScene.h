#pragma once

//ストーリー背景
extern int g_storyBack;

//ストーリーウィンドウ
extern int g_storyWindow;

//メッセージ流し
extern int g_messageRun;

//少女立ち絵（仮）
extern int g_girl;

//ストーリーシーンでの背景描画
void storyDraw();

//ストーリー画面エンターアイコン
void leafBottonDrawStory(float delta_time);

//会話メッセージ
void storyMessage();