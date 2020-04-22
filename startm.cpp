#include "startm.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int mImageHandle;    //画像ハンドル格納用変数
static int iImage;
	
	int SelectNum = 0;
	static int Key[256];
	static int SEfH,SEgH,BGMaH;
	static int Mvol,Svol; //音量
	static int bright=255; // フェードアウト、イン
	static int menuBw=0; //選択されたフラグ

//初期化
void Startm_Initialize(){

	menuBw=3;
	bright=0;
    mImageHandle = LoadGraph("pic/main.PNG");//画像のロード
	iImage = LoadGraph("pic/selecter.PNG");
	SEfH = LoadSoundMem("sounds/se_maoudamashii_system43.wav");
	SEgH = LoadSoundMem("sounds/se_maoudamashii_system45.wav");
	BGMaH = LoadSoundMem("sounds/game_maoudamashii_7_event44.ogg");
	VolumeSetRug(&Mvol,&Svol);
	ChangeVolumeSoundMem(Svol*25,SEfH);
	ChangeVolumeSoundMem(Svol*25,SEgH);
	ChangeVolumeSoundMem(Mvol*25,BGMaH);

	PlaySoundMem(BGMaH,DX_PLAYTYPE_LOOP,TRUE);
}

//終了処理
void Startm_Finalize(){

	StopSoundMem(BGMaH);

    DeleteGraph(mImageHandle);//画像の解放
	DeleteGraph(iImage);
	DeleteSoundMem(SEfH);
	DeleteSoundMem(SEgH);
	DeleteSoundMem(BGMaH);
}

//更新
void Startm_Update(){
	if (menuBw == 0){

		KeepValueKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){
			SelectNum = (SelectNum + 1) % 3;
			PlaySoundMem(SEfH,DX_PLAYTYPE_BACK,TRUE);
		}
		if(Key[KEY_INPUT_UP] == 1) {
			SelectNum = (SelectNum + 2) % 3;
			PlaySoundMem(SEfH,DX_PLAYTYPE_BACK,TRUE);
		}
	

		if(Key[KEY_INPUT_Z] == 1){
			PlaySoundMem(SEgH,DX_PLAYTYPE_BACK,TRUE);
			switch(SelectNum){
				case 0: menuBw=1;
					break;
				case 1: menuBw=2;
					break;
				case 2: exit(0);//終了
					break;
			}
		}
	}else if(menuBw == 1 || menuBw == 2){ //フェードアウト処理
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0 && menuBw == 1){
			 SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		}else if(bright <= 0 && menuBw == 2){
			 SceneMgr_ChangeScene(eScene_Config);//シーンをコンフィグに変更
		}
	}else{
		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){menuBw=0;}
	}

}

//描画
void Startm_Draw(){
	static int i=0;
	DrawGraph(0,0,mImageHandle,TRUE);
	DrawGraph(135,265+(SelectNum*60),iImage,TRUE);
	
}