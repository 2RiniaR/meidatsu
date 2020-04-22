#include "config.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int mImageHandle_C;    //画像ハンドル格納用変数

	MenuElement_t MenuElement_C[3]={
		{100,150,"BGM音量"},
		{100,200,"SE音量"},
		{100,250,"戻る"},
	};
	int SelectNum_C = 0;
	int ConfigSet[2]={7,7};  //選んだ番号
	static int Key[256];
	int update=0;
	static int Flag_S;
	static int bright;
	static int Svol,Mvol;
	static int SEiH,SEgH,BGMcH;

//初期化
void Config_Initialize(){
	Flag_S=2;
	bright=0;
	SEiH = LoadSoundMem("sounds/se_maoudamashii_se_switch01.wav");
	SEgH = LoadSoundMem("sounds/se_maoudamashii_system45.wav");
	BGMcH = LoadSoundMem("sounds/game_maoudamashii_5_town25b.ogg");
	VolumeSetRug(&Mvol,&Svol);
	ChangeVolumeSoundMem(Svol*25,SEiH);
	ChangeVolumeSoundMem(Svol*25,SEgH);
	ChangeVolumeSoundMem(Mvol*25,BGMcH);
	SetFontSize(32);
	PlaySoundMem(BGMcH,DX_PLAYTYPE_LOOP,TRUE);
}

//終了処理
void Config_Finalize(){
	DeleteSoundMem(SEiH);
	DeleteSoundMem(SEgH);
	DeleteSoundMem(BGMcH);
}

//更新
void Config_Update(){

	VolumeSetRug(&Mvol,&Svol);
	ChangeVolumeSoundMem(Svol*25,SEiH);
	ChangeVolumeSoundMem(Svol*25,SEgH);
	ChangeVolumeSoundMem(Mvol*25,BGMcH);

	if(Flag_S == 0){
		KeepValueKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){  //下を押したときの処理
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			SelectNum_C = (SelectNum_C + 1) % 3;
		}
		if(Key[KEY_INPUT_UP] == 1) {  //上を押したときの処理
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			SelectNum_C = (SelectNum_C + 2) % 3;
		}
	
		if(Key[KEY_INPUT_LEFT] == 1 && SelectNum_C != 2) {  //左を押したときの処理
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			ConfigSet[SelectNum_C] = ConfigSet[SelectNum_C] - 1;
			update = 1;
			if(ConfigSet[SelectNum_C] < 0){
				ConfigSet[SelectNum_C] = 0;
			}
		}

		if(Key[KEY_INPUT_RIGHT] == 1 && SelectNum_C != 2) {  //右を押したときの処理
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			ConfigSet[SelectNum_C] = ConfigSet[SelectNum_C] + 1;
			update = 1;
			if(ConfigSet[SelectNum_C] > 10){
				ConfigSet[SelectNum_C] = 10;
			}
		}

		if(update == 1){
			VolumeSetNum(ConfigSet[0],ConfigSet[1]);
		}

		if(Key[KEY_INPUT_Z] == 1 && SelectNum_C == 2){  //「戻る」でZを押すとメニューに戻る処理
			PlaySoundMem(SEgH,DX_PLAYTYPE_BACK,TRUE);
			Flag_S=1;	
		}
	}else if(Flag_S == 1){
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0){
			SceneMgr_ChangeScene(eScene_Startm);
		}
	}else{
		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){Flag_S=0;}
	}
}

//描画
void Config_Draw(){
	DrawBox(0,0,640,480,GetColor(200,200,255),TRUE);
	static int i=0;
	for(i=0;i<3;i++){
		DrawFormatString(MenuElement_C[i].x,MenuElement_C[i].y,GetColor(0,255,0),"%s",MenuElement_C[i].name);
		if(i < 2){
			DrawFormatString(350,MenuElement_C[i].y,GetColor(0,0,180),"＜  %d  ＞",ConfigSet[i]);
		}
	}
	DrawFormatString(70,MenuElement_C[SelectNum_C].y,GetColor(150,150,0),"⇒");
}