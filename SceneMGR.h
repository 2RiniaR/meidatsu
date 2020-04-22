#ifndef DEF_SCENEMGR_H

#define DEF_SCENEMGR_H

#pragma once

typedef enum {
    eScene_Menu,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Config,  //設定画面
	eScene_Prep,
	eScene_Clres,
	eScene_Startm,
	
    eScene_None,    //無し

} eScene ;

struct MenuElement_t{
	int x;
	int y;
	char name[30];
};


void SceneMgr_Initialize();//初期化
void SceneMgr_Finalize();//終了処理
//更新
void SceneMgr_Update();

//描画
void SceneMgr_Draw();

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene nextScene);
int gpUpdatekey();
int KeepValueKey(int *ad);
int VolumeSetNum(int Bv,int Sv);
int Stage_Seld(int Af);
int Stage_Selv(int *Ad);
int VolumeSetRug(int *Mu,int *Se);

int ClearNum(double time,int flame,int score);
int ClearVel(double *time_v,int *flame_v,int *score_v);

#endif