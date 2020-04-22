#include <math.h>
#include "DxLib.h"
#include "SceneMGR.h"

#define INIT_SCREEN_W (640)
#define INIT_SCREEN_H (480)

//■■■■■■■■■■■■FPS計測■■■■■■■■■■■■
static int mStartTime;
static int mCount;
static float mFps;
static const int N = 60;
static const int FPS = 60;

bool Flame_Count(){
	if(mCount == 0){
		mStartTime = GetNowCount();
	}
	if(mCount == N){
		int t = GetNowCount();
		mFps = 1000.f/((t-mStartTime)/(float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Wait(){
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount*1000/FPS - tookTime;
	if(waitTime > 0){
		Sleep(waitTime);
	}
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{

	int DesktopW,DesktopH;
	double WindowExW,WindowExH;

	SetMainWindowText("test"); //ウィンドウのタイトルを設定する
	SetWindowSizeChangeEnableFlag(TRUE,TRUE);//サイズ変更を可能にする
	ChangeWindowMode(TRUE);  //ウィンドウモードを有効にする
	SetWindowStyleMode(0);//最大化ボタンが存在し、さらに枠が細くなるウィンドウモードに変更

	//画面サイズをデスクトップのサイズと同じにする
	GetDefaultState(&DesktopW,&DesktopH,NULL);
	//SetGraphMode(DesktopW,DesktopH,32);

	//SetUseASyncChangeWindowModeFunction(TRUE,NULL,NULL);
	//SetWindowSize(INIT_SCREEN_W,INIT_SCREEN_H);//ウィンドウサイズは画面と一致させる
	SetWindowPosition((DesktopW - INIT_SCREEN_W)/2,(DesktopH - INIT_SCREEN_H)/2);//ウィンドウの位置を画面の中心にする

	if( DxLib_Init() == -1 )// ＤＸライブラリ初期化処理
	{return -1 ;}// エラーが起きたら直ちに終了
	//GetWindowSize(&WindowW,&WindowH);
	//WindowExW = WindowW / 640;
	WindowExH = ((double)DesktopH-100.0) / 480.0;
	SetWindowMaxSize(DesktopW,DesktopH);
	SetWindowMinSize(DesktopW/3,DesktopH/3);
	SetWindowSizeExtendRate(WindowExH);
	SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウの裏画面設定


	SceneMgr_Initialize();

//■■■■■■■■■■■■■■■■■■■■■■メインループ■■■■■■■■■■■■■■■■■■■■■■

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdatekey()==0){
		
		   Flame_Count();
		   SceneMgr_Update();  //更新
		   SceneMgr_Draw();    //描画
		   Wait();


	}

	SceneMgr_Finalize();
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

DxLib_End() ;				// ＤＸライブラリ使用の終了処理
return 0 ;				// ソフトの終了 

}
