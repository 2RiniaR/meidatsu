#include "clres.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int mImageHandle;    //画像ハンドル格納用変数

//初期化
void Clres_Initialize(){
    mImageHandle = LoadGraph("images/Scene_Config.png");//画像のロード
}

//終了処理
void Clres_Finalize(){
    DeleteGraph(mImageHandle);//画像の解放
}

//更新
void Clres_Update(){
    if(CheckHitKey(KEY_INPUT_ESCAPE)!=0){//Escキーが押されていたら
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
    }
}

//描画
void Clres_Draw(){
	DrawGraph(0,0,mImageHandle,FALSE);
    DrawString(0, 0,"設定画面です。",GetColor(255,255,255));
    DrawString(0,20,"Escキーを押すとメニュー画面に戻ります。",GetColor(255,255,255));
}