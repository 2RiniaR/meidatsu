#include "menu.h"
#include "SceneMGR.h"
#include "DxLib.h"


static int mImage_A;    //画像ハンドル格納用変数
static int mImage_B;
static int mImage_C;
static int mImage_D;
static int mNumber_E;
	int Select_Stage=0;
	int a,BoxX,BoxY;
	static int Flag_V;
	static int yesno=2;
	static int bright=255; // フェードアウト、イン
	static int Mvol,Svol;
	static int BGMbH,SEiH,SEgH,SEjH;

	static int HighScore[3][3];
	static double FastTime[3][3];
	FILE *fp;
	FILE *fpt;

	int ai,bi;
	static int fontA,fontB;

	//FontHandle=CreateFontHandle(NULL,40,-1,DX_FONTTYPE_ANTIALIASING_EDGE_8X8)

	static int Key[255];
	//FILE *fp;
	//char* name[];
	//int ic;

//初期化
void Menu_Initialize(){

	fp = fopen("Gdata/DATA/highscore.txt","r");

	for(ai=0;ai<3;ai++){

		for(bi=0;bi<3;bi++){

			fscanf(fp,"%d",&HighScore[ai][bi]);

		}

	}

	fpt = fopen("Gdata/DATA/besttime.txt","r");

	for(ai=0;ai<3;ai++){

		for(bi=0;bi<3;bi++){

			fscanf(fpt,"%f",&FastTime[ai][bi]);

		}

	}
	Flag_V=3;
	bright=0;

	mImage_A = LoadGraph("pic/manuback3.PNG");
	mImage_B = LoadGraph("pic/manuback4.PNG");
	mImage_C = LoadGraph("pic/manuback1.PNG");
	mImage_D = LoadGraph("pic/manuback2.PNG");
	mNumber_E = LoadGraph("pic/number.PNG");

	SEiH = LoadSoundMem("sounds/se_maoudamashii_se_switch01.wav");
	SEgH = LoadSoundMem("sounds/se_maoudamashii_system45.wav");
	SEjH = LoadSoundMem("sounds/se_maoudamashii_system26.wav");
	BGMbH = LoadSoundMem("sounds/game_maoudamashii_5_town17.ogg");

	VolumeSetRug(&Mvol,&Svol);

	fontA = CreateFontToHandle(NULL,48,5,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontB = CreateFontToHandle(NULL,24,5,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	ChangeVolumeSoundMem(Svol*25,SEiH);
	ChangeVolumeSoundMem(Svol*25,SEgH);
	ChangeVolumeSoundMem(Svol*25,SEjH);
	ChangeVolumeSoundMem(Mvol*25,BGMbH);
	
	SetFontSize(48);

	PlaySoundMem(BGMbH,DX_PLAYTYPE_LOOP,TRUE);
	//fp = fopen("Gdata/stagename.txt","r");

	//for(ic=0;ic<20;ic++){
	//	fgets(name[ic],40,fp);
	//}
	

}

//終了処理
void Menu_Finalize(){
 
	DeleteSoundMem(SEiH);
	DeleteSoundMem(SEgH);
	DeleteSoundMem(SEjH);
	DeleteSoundMem(BGMbH);
	InitFontToHandle() ;
	InitGraph();
	//fclose(fp);

}
//更新
void Menu_Update(){

	//キー判定
	KeepValueKey(Key);

	if(Flag_V == 0){

		/*if(Key[KEY_INPUT_UP] == 1){
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			if(Select_Stage >= 4){
				Select_Stage = Select_Stage-4;
			}else{
				Select_Stage = Select_Stage+16;
			}
		}

		if(Key[KEY_INPUT_DOWN] == 1){
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			if(Select_Stage <= 15){
				Select_Stage = Select_Stage+4;
			}else{
				Select_Stage = Select_Stage-16;
			}
		}*/

		if(Key[KEY_INPUT_LEFT] == 1){
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			if(Select_Stage == 0){
				Select_Stage = 3;
			}else{
				Select_Stage = Select_Stage-1;
			}
		}

		if(Key[KEY_INPUT_RIGHT] == 1){
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			if(Select_Stage == 3){
				Select_Stage = 0;
			}else{
				Select_Stage = Select_Stage+1;
			}
		}

		if(Key[KEY_INPUT_Z] == 1){
			PlaySoundMem(SEgH,DX_PLAYTYPE_BACK,TRUE);
			Flag_V = 1;
			Key[KEY_INPUT_Z] = 2;
		}

	}else if(Flag_V == 1){

		if(Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_LEFT] == 1){
			PlaySoundMem(SEiH,DX_PLAYTYPE_BACK,TRUE);
			yesno = yesno + 1;
		}

		if(Key[KEY_INPUT_Z] == 1){
			if(yesno%2 == 0){
				PlaySoundMem(SEgH,DX_PLAYTYPE_BACK,TRUE);
				Stage_Seld(Select_Stage);
				Flag_V = 2;
			}else if(yesno%2 == 1){
				PlaySoundMem(SEjH,DX_PLAYTYPE_BACK,TRUE);
				Flag_V = 0;
				yesno = 2;
				Key[KEY_INPUT_Z] = 2;
			}
		}
	}else if(Flag_V == 2){
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0){
			if(Select_Stage == 3){
				SceneMgr_ChangeScene(eScene_Startm);
			}else{
			 SceneMgr_ChangeScene(eScene_Game);//シーンをメニューに変更
			}
		}
	}else{
		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){Flag_V=0;}
	}
}

//描画
void Menu_Draw(){

	if(Select_Stage%4 == 1){
		DrawGraph(0,0,mImage_A,FALSE);
	}else if(Select_Stage%4 == 2){
		DrawGraph(0,0,mImage_B,FALSE);
	}else if(Select_Stage%4 == 3){
		DrawGraph(0,0,mImage_C,FALSE);
	}else{
		DrawGraph(0,0,mImage_D,FALSE);
	}

	

	for(a=0;a<4;a++){
		BoxY = int(a / 4);
		BoxX = a % 4;
		if(a == Select_Stage){
			//DrawRectGraph(BoxX*80+32,BoxY*88+40,a*48,48,48,48,mNumber_E,TRUE,FALSE);
			DrawRectGraph(BoxX*80+32,BoxY*88+216,a*48,48,48,48,mNumber_E,TRUE,FALSE);
		}else{
			//DrawRectGraph(BoxX*80+32,BoxY*88+40,a*48,0,48,48,mNumber_E,TRUE,FALSE);
			DrawRectGraph(BoxX*80+32,BoxY*88+216,a*48,0,48,48,mNumber_E,TRUE,FALSE);
		}
	}

	DrawBox(352,40,604,440,GetColor(130,130,130),TRUE);
	DrawBox(372,60,584,420,GetColor(240,240,240),TRUE);
	//DrawFormatString(500,150,GetColor(0,0,0),"%s",name[Select_Stage]);

	if(Select_Stage == 0 ||Select_Stage == 1||Select_Stage == 2){

	DrawFormatStringToHandle(380,80,GetColor(0,0,0),fontA,"STAGE %d",Select_Stage+1);

	}

	//DrawFormatStringToHandle(390,150,GetColor(0,0,255),fontB,"Best Time");
	//DrawFormatStringToHandle(390,180,GetColor(255,0,255),fontB,"1st:%6.2f",FastTime[Select_Stage][0]);
	//DrawFormatStringToHandle(390,210,GetColor(0,0,0),fontB,"2nd:%6.2f",FastTime[Select_Stage][1]);
	//DrawFormatStringToHandle(390,240,GetColor(0,0,0),fontB,"3rd:%6.2f",FastTime[Select_Stage][2]);

	//DrawFormatStringToHandle(390,290,GetColor(255,0,0),fontB,"High Score");
//	DrawFormatStringToHandle(390,320,GetColor(255,0,255),fontB,"1st:%d",HighScore[Select_Stage][0]);
	//DrawFormatStringToHandle(390,350,GetColor(0,0,0),fontB,"2nd:%d",HighScore[Select_Stage][1]);
	//DrawFormatStringToHandle(390,380,GetColor(0,0,0),fontB,"3rd:%d",HighScore[Select_Stage][2]);
//	}


	if(Flag_V == 1){
		DrawBox(160,120,480,360,GetColor(0,130,190),TRUE);
		DrawBox(180,140,460,340,GetColor(240,240,240),TRUE);
		if(Select_Stage == 3){
			DrawFormatString(200,160,GetColor(0,0,0),"戻る");
		}else{
			DrawFormatString(200,160,GetColor(0,0,0),"STAGE %d",Select_Stage+1);
		}

		if(yesno%2 == 0){
			DrawFormatString(210,280,GetColor(255,0,0),"OK");
			DrawFormatString(310,280,GetColor(0,0,0),"戻る");
		}else{
			DrawFormatString(210,280,GetColor(0,0,0),"OK");
			DrawFormatString(310,280,GetColor(255,0,0),"戻る");
		}

	}
}
		

