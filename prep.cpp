#include "prep.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int Flag_M=2;
static int bright=255; // �t�F�[�h�A�E�g�A�C��
static int Selected_Stage;
static int hyouji=0; //�\���ߒ�
static int Flametime=0;
static int time_s=0;
static int mImage_A,mImage_B,mImage_C,mImage_D;
static int Font_A,Font_B,Font_C;
static int font_haba;
static int ClearFlame,Score;
static double ClearTime;
static int Key[255];
static int Svol,Mvol;
static double ClearFlameA;
static const int Rank_S[3]={0,0,0};
static const int Rank_A[3]={0,0,0};
static const int Rank_B[3]={0,0,0};
static int TotalScore; //���v�̃X�R�A
static const double Deftime[3]={100.00,0.0,0.0}; 

static int BGM_F,SE_A,SE_B;

FILE *fpr;
static int ia;

//������
void Prep_Initialize(){
	/*

	fpr = fopen("Gdata/DATA/rank.txt","r");
	for(ia=0;ia<3;ia++){
		fscanf(fpr,"%d",&Rank_S[ia]);
	}
	for(ia=0;ia<3;ia++){
		fscanf(fpr,"%d",&Rank_A[ia]);
	}
	for(ia=0;ia<3;ia++){
		fscanf(fpr,"%d",&Rank_B[ia]);
	}
*/

	Flag_M=2;
	bright=0;
	Stage_Selv(&Selected_Stage);
	hyouji=0;
	Flametime=0;
	time_s=0;

	ClearVel(&ClearTime,&ClearFlame,&Score);
	VolumeSetRug(&Mvol,&Svol);

	mImage_A = LoadGraph("pic/manuback3.PNG");
	mImage_B = LoadGraph("pic/manuback4.PNG");
	mImage_C = LoadGraph("pic/manuback1.PNG");
	mImage_D = LoadGraph("pic/manuback2.PNG");

	Font_A = CreateFontToHandle(NULL,60,5,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	Font_B = CreateFontToHandle(NULL,48,4,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	Font_C = CreateFontToHandle(NULL,32,3,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	BGM_F=LoadSoundMem("sounds/game_maoudamashii_7_event43.ogg");
	SE_A=LoadSoundMem("sounds/se_maoudamashii_system44.wav");
	SE_B=LoadSoundMem("sounds/se_maoudamashii_system45.wav");

	ChangeVolumeSoundMem(Mvol*25,BGM_F);
	ChangeVolumeSoundMem(Svol*25,SE_A);
	ChangeVolumeSoundMem(Svol*25,SE_B);

	if(ClearFlame == 0){ClearFlameA = 0.00;}
	else if(ClearFlame == 1){ClearFlameA = 0.02;}
	else if(ClearFlame == 2){ClearFlameA = 0.03;}
	else if(ClearFlame == 3){ClearFlameA = 0.05;}
	else if(ClearFlame == 4){ClearFlameA = 0.07;}
	else {ClearFlameA = 0.08;}

	//�X�R�A�����߂�
	TotalScore=int((Deftime[Selected_Stage]-(ClearTime+ClearFlameA))*100)+Score;

	PlaySoundMem(BGM_F,DX_PLAYTYPE_LOOP,TRUE);
}

//�I������
void Prep_Finalize(){
	InitGraph();
	InitSoundMem();
   
}

//�X�V
void Prep_Update(){

	KeepValueKey(Key);

	if(Flag_M == 2){
		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){Flag_M=0;}
	}else if(Flag_M == 0){

		if(Flametime == 5){
			Flametime=0;
			time_s=time_s+1;
		}else{
			Flametime++;
		}

		hyouji = int(time_s/10);

		if(time_s == 10 || time_s == 20 || time_s == 30 || time_s == 40){
			if(Flametime == 0){
				PlaySoundMem(SE_A,DX_PLAYTYPE_BACK,TRUE);
			}
		}

		if(Key[KEY_INPUT_Z] == 1){
			if(time_s < 40){
				time_s = 40;
				PlaySoundMem(SE_A,DX_PLAYTYPE_BACK,TRUE);
				Key[KEY_INPUT_Z] = 2;
			}else{
				PlaySoundMem(SE_B,DX_PLAYTYPE_BACK,TRUE);
				Flag_M=1;
			}
		}
	}else if(Flag_M == 1){
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0){
			 SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
		}
	}
   
	
}

//�`��
void Prep_Draw(){

	if(Selected_Stage%4 == 1){
		DrawGraph(0,0,mImage_A,FALSE);
	}else if(Selected_Stage%4 == 2){
		DrawGraph(0,0,mImage_B,FALSE);
	}else if(Selected_Stage%4 == 3){
		DrawGraph(0,0,mImage_C,FALSE);
	}else{
		DrawGraph(0,0,mImage_D,FALSE);
	}

	DrawBox(40,30,600,450,GetColor(255,127,12),TRUE);
	DrawBox(60,45,580,435,GetColor(255,255,255),TRUE);

	//10��20���ؗj���͂����̕ҏW����n�߂Ă�

	if(hyouji >= 0){  //�X�e�[�W���\��
		font_haba = GetDrawFormatStringWidthToHandle(Font_A,"STAGE %d",Selected_Stage+1);
		DrawFormatStringToHandle(320-int(font_haba/2),74,GetColor(0,0,255),Font_A,"STAGE %d",Selected_Stage+1);
	}
	if(hyouji >= 1){  //�N���A�^�C���\��
		font_haba = GetDrawFormatStringWidthToHandle(Font_B,"�^�C��: %6.2f",ClearTime);
		DrawFormatStringToHandle(320-int(font_haba/2),150,GetColor(60,100,100),Font_B,"�^�C��: %6.2f",ClearTime+ClearFlameA);
	}
	if(hyouji >= 2){  //�X�R�A�\��
		font_haba = GetDrawFormatStringWidthToHandle(Font_B,"�X�R�A�F %d",Score);
		DrawFormatStringToHandle(320-int(font_haba/2),216,GetColor(90,0,50),Font_B,"�X�R�A�F %d",TotalScore);
	}
	/*if(hyouji >= 3){  //�����N�\��
		font_haba = GetDrawFormatStringWidthToHandle(Font_B,"�����N�FS");
		if(TotalScore >= Rank_S[Selected_Stage]){
			DrawFormatStringToHandle(320-int(font_haba/2),282,GetColor(255,127,13),Font_B,"�����N�FS");
		}else if(TotalScore >= Rank_S[Selected_Stage]){
			DrawFormatStringToHandle(320-int(font_haba/2),282,GetColor(140,140,140),Font_B,"�����N�FA");
		}else if(TotalScore >= Rank_S[Selected_Stage]){
			DrawFormatStringToHandle(320-int(font_haba/2),282,GetColor(150,80,6),Font_B,"�����N�FB");
		}else{
			DrawFormatStringToHandle(320-int(font_haba/2),282,GetColor(40,130,40),Font_B,"�����N�FC");
		}*/
	//}
	if(hyouji >= 4){  //�ǋL�\��
		font_haba = GetDrawFormatStringWidthToHandle(Font_C,"������ɂ� Z �������Ă�������");
		DrawFormatStringToHandle(320-int(font_haba/2),400,GetColor(0,0,0),Font_C,"������ɂ� Z �������Ă�������");
	}

	
}
