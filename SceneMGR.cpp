#include "DxLib.h"
#include "config.h"
#include "calcs.h"
#include "menu.h"
#include "prep.h"
#include "clres.h"
#include "startm.h"
#include "SceneMGR.h"
#include <string.h>

static eScene mScene = eScene_Startm;    //シーン管理変数

static eScene mNextScene = eScene_None;    //次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);//指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);//指定モジュールの終了処理を行う

//初期化
void SceneMgr_Initialize(){
    SceneMgr_InitializeModule(mScene);
}

//終了処理
void SceneMgr_Finalize(){
    SceneMgr_FinalizeModule(mScene);
}


//更新
void SceneMgr_Update(){
	  if(mNextScene != eScene_None){    //次のシーンがセットされていたら
        SceneMgr_FinalizeModule(mScene);//現在のシーンの終了処理を実行
        mScene = mNextScene;    //次のシーンを現在のシーンセット
        mNextScene = eScene_None;    //次のシーン情報をクリア
        SceneMgr_InitializeModule(mScene);    //現在のシーンを初期化
    }
    switch(mScene){       //シーンによって処理を分岐
    case eScene_Menu:    //現在の画面がメニューなら
        Menu_Update();   //メニュー画面の更新処理をする
        break;//以下略
    case eScene_Game:
        Game_Update();
        break;
    case eScene_Config:
        Config_Update();
		break;
	case eScene_Prep:
        Prep_Update();
        break;
    case eScene_Clres:
        Clres_Update();
        break;
    case eScene_Startm:
        Startm_Update();
        break;
    }
}

//描画
void SceneMgr_Draw(){
    switch(mScene){      //シーンによって処理を分岐
    case eScene_Menu:   //現在の画面がメニュー画面なら
        Menu_Draw();    //メニュー画面の描画処理をする
        break;//以下略
    case eScene_Game:
        Game_Draw();
        break;
    case eScene_Config:
        Config_Draw();
        break;
    case eScene_Prep:
        Prep_Draw();
        break;
    case eScene_Clres:
        Clres_Draw();
        break;
    case eScene_Startm:
        Startm_Draw();
        break;
    }
}

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene){
   mNextScene = NextScene;
}
// 引数sceneモジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene){
    switch(scene){          //シーンによって処理を分岐
    case eScene_Menu:       //指定画面がメニュー画面なら
        Menu_Initialize();  //メニュー画面の初期化処理をする
        break;//以下略
    case eScene_Game:
        Game_Initialize();
        break;
    case eScene_Config:
        Config_Initialize();
        break;
    case eScene_Prep:
        Prep_Initialize();
        break;
    case eScene_Clres:
        Clres_Initialize();
        break;
    case eScene_Startm:
        Startm_Initialize();
        break;
    }
}

// 引数sceneモジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene){
    switch(scene){         //シーンによって処理を分岐
    case eScene_Menu:      //指定画面がメニュー画面なら
        Menu_Finalize();   //メニュー画面の終了処理処理をする
        break;//以下略
    case eScene_Game:
        Game_Finalize();
        break;
    case eScene_Config:
        Config_Finalize();
        break;
    case eScene_Prep:
        Prep_Finalize();
        break;
    case eScene_Clres:
        Clres_Finalize();
        break;
    case eScene_Startm:
        Startm_Finalize();
        break;
    }
}

int Key[256];

int gpUpdatekey(){
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for(int i=0; i<256; i++){
		if(tmpKey[i] != 0){
			Key[i]++;
		}else{
			Key[i]=0;
		}
	}
		
	return 0;
}

int KeepValueKey(int *ad){
	memmove(ad, Key, sizeof(int) * 256);
	return 0;
}

int BGMvolume=7,SEvolume=7;

int VolumeSetNum(int Bv,int Sv){
	BGMvolume = Bv;
	SEvolume = Sv;
	return 0;
}

int Selected_Stage;

int Stage_Seld(int Af){
	Selected_Stage = Af;
	return 0;
}

int Stage_Selv(int *Ad){
	*Ad = Selected_Stage;
	return 0;
}

int VolumeSetRug(int *Mu,int *Se){
	*Mu = BGMvolume;
	*Se = SEvolume;
	return 0;
}

double ClearTime;
int ClearFlame;
int Score_S;

int ClearNum(double time,int flame,int score){
	ClearTime = time;
	ClearFlame = flame;
	Score_S = score;
	return 0;
}


int ClearVel(double *time_v,int *flame_v,int *score_v){
	*time_v = ClearTime;
	*flame_v = ClearFlame;
	*score_v = Score_S;
	return 0;
}
