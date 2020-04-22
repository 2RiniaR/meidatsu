#include "calcs.h"
#include "SceneMGR.h"
#include "DxLib.h"
#include <stdlib.h>
#include <stdio.h>

static int MX=320,MY=6640; //�ʒu
static int MDX,MDY; //�ړ�����
//static double MDHX,MDHY; //�����ړ�����
static double MVU,MVD,MVR,MVL; //�����x
static int Key[256]; //�L�[���擾�z��ϐ�
int x,y;
static int MMSX,MMSY;
static int GrX=0,GrY=0; //�E�B���h�E����ʒu
static int GrSX,GrSY,GrQX,GrQY;
static int DrawPlX,DrawPlY;

static double L_time = 60.0; //�c�莞��
static double D_time = 0.0; //�o�ߎ���
static int Flametime=0;
static double Flag_Mad=3.0; //�D�ɓ����Ă����1.5�ɂȂ�A�X�ɓ����Ă����6�ɂȂ�B�@����₷���B
static int Flag_Move=0; //�f�t�H���g�̓������x�B�@�ʏ펞��4�A�X����1�ɂȂ�B
static int Flag_Ice=0; //�X�ɓ������u�Ԃ̂�1�ɂȂ�B
static int Flag_IceV=0; //�X�ɓ����Ă����1�ɂȂ�B
static int Player_muki=0; //�v���C���[�L�����̌���
static int Player_damage=0; //�_���[�W��H����Ă����1
static int naname_idou=0; //�i�i���Ɉړ����Ă����1
static int muteki=0; //���G����
static int Player_Life=3; //�v���C���[�̃��C�t
static int Flag_Dash=0; //�������̌���
static int Player_live=0; //����ł����1
static int Doroyoke=0; //�D�����C�̌��ʎ���
static int Gomukutu=0; //�S���C�̌��ʎ���
static int Togemukou=0; //�g�Q�����̌��ʎ���

static int Atari_wallL,Atari_wallR,Atari_wallU,Atari_wallD,Atari_8,Atari_9,Atari_A,Atari_B,Atari_C,Atari_D,Atari_E,Atari_L,Atari_R,Atari_G,Atari_U; //�����蔻��̃t���b�O

static int S_Score=0;

static int Flag_fade=2; //�t�F�[�h�C������2�A�t�F�[�h�A�E�g����1�A���ɂȂ����0�A�J�E���g�_�E������3�A�c��^�C���ł��4�A�^�C���I�[�o�[��5�A�N���A��6�A���g���C�������Ƃ���7
static int bright=0; //�t�F�[�h�̖��邳
static int clear_count=239; //�N���A���̕\������
static int retry_yesno=1;
static int miss_flag=0; //�~�X�̌��߂��1�ɂȂ�A���g���C�����2�ɂȂ�
static int speed_tile_lev=0,speed_tile_flag=0;
static int wall_lev=0,wall_flag=0;
static int late_music_flag=0; //�}��BGM�ɂȂ�����1

static int count_fonthandle; //�J�E���g�_�E���\���̃t�H���g�n���h��
static int bar_fonthandle; //���̃o�[�̃t�H���g�n���h��
static int retry_fonthandle;
static int font_haba; //�t�H���g�̕�
static int Mvol,Svol;

static double countdown=239; //�J�E���g�_�E���i�t���[�����j
static int Selected_StageA;

const double Time_Limit[3]={100.0,160.0,140.0};
const int syoki_X[3]={320,80,304},syoki_Y[3]={6640,208,4624};
const int yokohabaV[3]={20,200,20},tatehabaV[3]={210,14,147};
static int yokohaba,tatehaba;

//char map[30][40];
//char map_Item[30][40];

char map[300][300];
char map_Item[300][300];


static int Player_image;
	

FILE *filepoint;

FILE *filepoint_I;

int i;

static int Selected_Stage; //�I�΂ꂽ�X�e�[�W

static int img_block,img_item;

//���y�n���h��
static int BGM_main,BGM_late;
static int SE_speed,SE_damage,SE_countA,SE_countB,SE_countC,SE_goal,SE_goal2,SE_miss,SE_miss2,SE_choose,SE_choose2,SE_item,SE_item2,SE_item3;

//������
void Game_Initialize(){


	//����������
	Flag_fade = 2;
	bright = 0;
	countdown=239;
	clear_count=239;
	miss_flag=0;
	L_time = 240.0;
	Flametime=0;
	retry_yesno=1;
	miss_flag=0;
	Flag_Mad=3.0;
	Player_muki=0;
	Player_damage=0;
	naname_idou=0;
	Flag_Move=4;
	Player_Life=3;
	late_music_flag=0;
	MX=320,MY=6640,MDX=0,MDY=0,MMSX=0,MMSY=0,GrX=0,GrY=0,MVL=0,MVR=0,MVU=0,MVD=0;
	Player_live=0;
	late_music_flag=0;
	wall_lev=0;
	wall_flag=0;
	Flag_Dash=0;
	muteki=0;
	speed_tile_lev=0;
	speed_tile_flag=0;
	Doroyoke=0;
	Togemukou=0;
	Gomukutu=0;
	S_Score=0;
	Atari_wallL=0,Atari_wallR=0,Atari_wallU=0,Atari_wallD=0,Atari_8=0,Atari_9=0,Atari_A=0,Atari_B=0,Atari_C=0,Atari_D=0,Atari_E=0,Atari_L=0,Atari_R=0,Atari_G=0,Atari_U=0;


	Player_image = LoadGraph("pic/player.PNG");
	img_item=LoadGraph("pic/items.PNG");
	img_block=LoadGraph("pic/blocks.PNG");

	count_fonthandle = CreateFontToHandle(NULL,256,5,DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	retry_fonthandle = CreateFontToHandle(NULL,48,4,DX_FONTTYPE_ANTIALIASING);
	bar_fonthandle = CreateFontToHandle(NULL,24,4,DX_FONTTYPE_ANTIALIASING);

	Stage_Selv(&Selected_Stage);
	yokohaba = yokohabaV[Selected_Stage];
	tatehaba = tatehabaV[Selected_Stage];
	MX=syoki_X[Selected_Stage];
	MY=syoki_Y[Selected_Stage];
	L_time=Time_Limit[Selected_Stage];


	if(Selected_Stage == 0){
		filepoint = fopen("Gdata/MAP/Stage1_map.txt","r");
	}else if(Selected_Stage == 1){
		filepoint = fopen("Gdata/MAP/Stage2_map.txt","r");
	}else{
		filepoint = fopen("Gdata/MAP/Stage3_map.txt","r");
	}

	

	for(i=0;i<tatehaba;i++){
		
			fread(&map[i],1,yokohaba+1,filepoint);
		
	}

	if(Selected_Stage == 0){
		filepoint_I = fopen("Gdata/ITEMS/Stage1_items.txt","r");
	}else if(Selected_Stage == 1){
		filepoint_I = fopen("Gdata/ITEMS/Stage2_items.txt","r");
	}else{
		filepoint_I = fopen("Gdata/ITEMS/Stage3_items.txt","r");
	}

	
	for(i=0;i<tatehaba;i++){
		
			fread(&map_Item[i],1,yokohaba+1,filepoint_I);
		
	}
	

	if(Selected_Stage%4 == 1){
		BGM_main=LoadSoundMem("sounds/game_maoudamashii_6_dangeon03.ogg");
	}else if(Selected_Stage%4 == 2){
		BGM_main=LoadSoundMem("sounds/game_maoudamashii_6_dangeon18.ogg");
	}else if(Selected_Stage%4 == 3){
		BGM_main=LoadSoundMem("sounds/game_maoudamashii_6_dangeon21.ogg");
	}else{
		BGM_main=LoadSoundMem("sounds/game_maoudamashii_6_dangeon15.ogg");
	}
	BGM_late=LoadSoundMem("sounds/game_maoudamashii_1_battle04.ogg");
	SE_speed=LoadSoundMem("sounds/se_maoudamashii_system36.wav");
	SE_damage=LoadSoundMem("sounds/se_maoudamashii_se_ignition01.wav");
	SE_countA=LoadSoundMem("sounds/se_maoudamashii_system28.wav");
	SE_countB=LoadSoundMem("sounds/se_maoudamashii_system27.wav");
	SE_countC=LoadSoundMem("sounds/se_maoudamashii_system18.wav");
	SE_goal=LoadSoundMem("sounds/se_maoudamashii_system04.wav");
	SE_goal2=LoadSoundMem("sounds/se_maoudamashii_jingle05.wav");
	SE_miss=LoadSoundMem("sounds/se_maoudamashii_explosion03.wav");
	SE_miss2=LoadSoundMem("sounds/se_maoudamashii_jingle08.wav");
	SE_choose=LoadSoundMem("sounds/se_maoudamashii_system43.wav");
	SE_choose2=LoadSoundMem("sounds/se_maoudamashii_system45.wav");
	SE_item=LoadSoundMem("sounds/se_maoudamashii_system48.wav");
	SE_item2=LoadSoundMem("sounds/se_maoudamashii_system14.wav");
	SE_item3=LoadSoundMem("sounds/se_maoudamashii_system17.wav");

	VolumeSetRug(&Mvol,&Svol);

	ChangeVolumeSoundMem(Svol*25,SE_speed);
	ChangeVolumeSoundMem(Svol*25,SE_damage);
	ChangeVolumeSoundMem(Svol*25,SE_countA);
	ChangeVolumeSoundMem(Svol*25,SE_countB);
	ChangeVolumeSoundMem(Svol*25,SE_countC);
	ChangeVolumeSoundMem(Svol*25,SE_goal);
	ChangeVolumeSoundMem(Svol*25,SE_goal2);
	ChangeVolumeSoundMem(Svol*25,SE_miss);
	ChangeVolumeSoundMem(Svol*25,SE_miss2);
	ChangeVolumeSoundMem(Mvol*25,BGM_late);
	ChangeVolumeSoundMem(Mvol*25,BGM_main);
	ChangeVolumeSoundMem(Mvol*25,SE_item);
	ChangeVolumeSoundMem(Mvol*25,SE_item2);
	ChangeVolumeSoundMem(Mvol*25,SE_item3);

}

//�I������
void Game_Finalize(){
   
	InitSoundMem();

	DeleteGraph(Player_image);
	DeleteGraph(img_block);
	DeleteGraph(img_item);

	InitFontToHandle() ;

	fclose(filepoint);

}
//�X�V
void Game_Update(){

	KeepValueKey(Key);

	if(Flag_fade == 0 || Flag_fade == 4){ //�ʏ펞

		naname_idou = 0;
		Atari_wallL=0,Atari_wallR=0,Atari_wallU=0,Atari_wallD=0,Atari_8=0,Atari_9=0,Atari_A=0,Atari_B=0,Atari_C=0,Atari_D=0,Atari_E=0,Atari_L=0,Atari_R=0,Atari_G=0,Atari_U=0;
	  
		//�������������������ϐ��̏�����������������������
	
		MDX=0;
		MDY=0;
		//MDHX=0.0;
		//MDHY=0.0;


		//�������������������L�[���蕔��������������������

		if(Key[KEY_INPUT_RIGHT] > 0){
			MVR=MVR+0.1;
			if(Key[KEY_INPUT_UP] <= 0 && Key[KEY_INPUT_DOWN] <= 0){MDX=MDX+Flag_Move;}
			else{
				MDX=MDX+int(Flag_Move*0.8);
				naname_idou=1;
				if(Flag_Move*0.8 <= 0){
					MDX+=1;
				}
			}
		}else{MVR=MVR-0.1;}

		if(Key[KEY_INPUT_LEFT] > 0){
			MVL=MVL+0.1;
			if(Key[KEY_INPUT_UP] <= 0 && Key[KEY_INPUT_DOWN] <= 0){MDX=MDX-Flag_Move;}
			else{
				MDX=MDX-int(Flag_Move*0.8);
				naname_idou=1;
				if(Flag_Move*0.8 <= 0){
					MDX-=1;
				}//MDX=MDX-int(Flag_Move*0.8),naname_idou=1;}
			}
		}else{MVL=MVL-0.1;}

		if(Key[KEY_INPUT_DOWN] > 0){
			MVD=MVD+0.1;
			if(Key[KEY_INPUT_LEFT] <= 0 && Key[KEY_INPUT_RIGHT] <= 0){MDY=MDY+Flag_Move;}
			else{
				MDY=MDY+int(Flag_Move*0.8);
				naname_idou=1;
				if(Flag_Move*0.8 <= 0){
					MDY+=1;
				}//MDY=MDY+int(Flag_Move*0.8),naname_idou=1;}
			}
		}else{MVD=MVD-0.1;}

		if(Key[KEY_INPUT_UP] > 0){
			MVU=MVU+0.1;
			if(Key[KEY_INPUT_LEFT] <= 0 && Key[KEY_INPUT_RIGHT] <= 0){MDY=MDY-Flag_Move;}
			else{
				MDY=MDY-int(Flag_Move*0.8);
				naname_idou=1;
				if(Flag_Move*0.8 <= 0){
					MDY-=1;
				}//MDY=MDY-int(Flag_Move*0.8),naname_idou=1;}
			}
		}else{MVU=MVU-0.1;}


		//�v���C���[�L�����̌�������
		if(Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_LEFT] <= 0 && Key[KEY_INPUT_RIGHT] <= 0){
			Player_muki=0;
		}else if(Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_LEFT] > 0 && Key[KEY_INPUT_RIGHT] > 0){
			Player_muki=0;
		}else if(Key[KEY_INPUT_DOWN] > 0 && Key[KEY_INPUT_LEFT] <= 0 && Key[KEY_INPUT_RIGHT] <= 0){
			Player_muki=2;
		}else if(Key[KEY_INPUT_DOWN] > 0 && Key[KEY_INPUT_LEFT] > 0 && Key[KEY_INPUT_RIGHT] > 0){
			Player_muki=2;
		}else if(Key[KEY_INPUT_LEFT] > 0 && Key[KEY_INPUT_UP] <= 0 && Key[KEY_INPUT_DOWN] <= 0){
			Player_muki=3;
		}else if(Key[KEY_INPUT_LEFT] > 0 && Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_DOWN] > 0){
			Player_muki=3;
		}else if(Key[KEY_INPUT_RIGHT] > 0 && Key[KEY_INPUT_UP] <= 0 && Key[KEY_INPUT_DOWN] <= 0){
			Player_muki=1;
		}else if(Key[KEY_INPUT_RIGHT] > 0 && Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_DOWN] > 0){
			Player_muki=1;
		}else if(Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_RIGHT] > 0){
			Player_muki=5;
		}else if(Key[KEY_INPUT_UP] > 0 && Key[KEY_INPUT_LEFT] > 0){
			Player_muki=4;
		}else if(Key[KEY_INPUT_DOWN] > 0 && Key[KEY_INPUT_RIGHT] > 0){
			Player_muki=6;
		}else if(Key[KEY_INPUT_DOWN] > 0 && Key[KEY_INPUT_LEFT] > 0){
			Player_muki=7;
		}

		//�������������������ړ��K�p����������������������

		
		
		if(MVU < 0.0){MVU = 0.0;}
		if(MVD < 0.0){MVD = 0.0;}
		if(MVL < 0.0){MVL = 0.0;}
		if(MVR < 0.0){MVR = 0.0;}

		if(Flag_Ice == 1){
			if(MVU > MVD){MVU+=3.0;}
			if(MVD > MVU){MVD+=3.0;}
			if(MVL > MVR){MVL+=3.0;}
			if(MVR > MVL){MVR+=3.0;}
		}
		
		if(MVU > Flag_Mad){MVU = Flag_Mad;}
		if(MVD > Flag_Mad){MVD = Flag_Mad;}
		if(MVL > Flag_Mad){MVL = Flag_Mad;}
		if(MVR > Flag_Mad){MVR = Flag_Mad;}
		
		if(naname_idou == 0){
			MDX=MDX+int(MVR);
			MDX=MDX-int(MVL);
			MDY=MDY-int(MVU);
			MDY=MDY+int(MVD);
		}else{
			MDX=MDX+int(MVR*0.75);
			MDX=MDX-int(MVL*0.75);
			MDY=MDY-int(MVU*0.75);
			MDY=MDY+int(MVD*0.75);
		}

		if(Flag_Dash > 0){
			MDX*=2;
			MDY*=2;
			//MVU*=2;
			//MVD*=2;
			//MVL*=2;
			//MVR*=2;
		}

		if(Key[KEY_INPUT_LSHIFT] > 0){
			MDX/=2;
			MDY/=2;
		}

		//�����������������������蔻�聡������������������
		MMSX=int(MX+MDX)/32;
		MMSY=int(MY+MDY)/32;

		Flag_Mad = 2.0;
		Flag_Move = 3;
		Flag_IceV = 0;
		speed_tile_flag=0;
		wall_flag=0;


		//��Q��
		for(x=-1;x<2;x++){

			for(y=-1;y<2;y++){

				if(MMSX+x >= 0 && MMSX+x <= yokohaba-1 && MMSY+y >= 0 && MMSY+y <= tatehaba-1){

		//�������������������������A�C�e����������������������������������
					if(map_Item[MMSY+y][MMSX+x] == '1'){	//+10���v

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							L_time += 10.0;
							PlaySoundMem(SE_item2,DX_PLAYTYPE_BACK,TRUE);
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '2'){	//+5���v

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							L_time += 5.0;
							PlaySoundMem(SE_item2,DX_PLAYTYPE_BACK,TRUE);
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '3'){	//�D�����C

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							Doroyoke += 300;
							PlaySoundMem(SE_item,DX_PLAYTYPE_BACK,TRUE);
							if(Doroyoke > 300){Doroyoke=300;}
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '4'){	//�S���C

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							Gomukutu += 300;
							PlaySoundMem(SE_item,DX_PLAYTYPE_BACK,TRUE);
							if(Gomukutu > 300){Gomukutu=300;}
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '5'){	//��

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							Player_Life += 1;
							PlaySoundMem(SE_item,DX_PLAYTYPE_BACK,TRUE);
							if(Player_Life > 3){Player_Life=3;}
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '6'){	//�g�Q����

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							Togemukou += 300;
							PlaySoundMem(SE_item,DX_PLAYTYPE_BACK,TRUE);
							if(Togemukou > 300){Togemukou=300;}
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}else if(map_Item[MMSY+y][MMSX+x] == '7'){	//�R�C��

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							S_Score += 500;
							PlaySoundMem(SE_item3,DX_PLAYTYPE_BACK,TRUE);
							map_Item[MMSY+y][MMSX+x]=0;
							
						}
					}


		//��������������������������Q����������������������������������
					
					if(map[MMSY+y][MMSX+x] == 'C'){	//������

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_C == 0){

							Atari_C=1;

							speed_tile_flag = 1;
							speed_tile_lev += 1;
							Flag_Dash = 60;
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'U'){	//������R���x�A�[

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_U == 0){

							Atari_U=1;

							MDY-=2;
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'D'){	//�������R���x�A�[

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_D == 0){

							Atari_D=1;

							MDY+=2;
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'L'){	//�������R���x�A�[

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_L == 0){

							Atari_L=1;

							MDX-=2;
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'R'){	//�E�����R���x�A�[

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_R == 0){

							Atari_R=1;

							MDX+=2;
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'B'){	//�n�⏰

						if(MX+MDX+11 > (MMSX+x)*32 && MX+MDX-12 < (MMSX+x)*32+31 && MY+MDY+11 > (MMSY+y)*32 && MY+MDY-12 < (MMSY+y)*32+31 && Atari_B == 0){

							Atari_B=1;

							
							if(muteki == 0){
								PlaySoundMem(SE_damage,DX_PLAYTYPE_BACK,TRUE);
								Player_Life -= 1;
								S_Score -= 100;
								muteki = 180;
							}
							Flag_Mad = 1.5;

							if(MDX < 0){
								MDX=MDX/2;
								if(MDX >= 0){MDX=-1;}
							}else if(MDX > 0){
								MDX=MDX/2;
								if(MDX <= 0){MDX=1;}
							}
							if(MDY < 0){
								MDY=MDY/2;
								if(MDY >= 0){MDY=-1;}
							}else if(MDY > 0){
								MDY=MDY/2;
								if(MDY <= 0){MDY=1;}
							}
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'A'){	//�g�Q��

						if(MX+MDX+11 > (MMSX+x)*32 && MX+MDX-12 < (MMSX+x)*32+31 && MY+MDY+11 > (MMSY+y)*32 && MY+MDY-12 < (MMSY+y)*32+31 && Togemukou == 0 && Atari_A == 0){

							Atari_A=1;

							if(muteki == 0){
								PlaySoundMem(SE_damage,DX_PLAYTYPE_BACK,TRUE);
								S_Score -= 100;
								Player_Life -= 1;
								muteki = 180;
							}
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == '9'){	//�X��

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Gomukutu == 0 && Atari_9 == 0){

							Atari_9=1;

							Flag_Move = 1;
							Flag_Mad = 5.0;
							Flag_Ice=Flag_Ice+1;
							Flag_IceV = 1;
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == '8'){	//������

						if(MX+MDX+13 > (MMSX+x)*32 && MX+MDX-14 < (MMSX+x)*32+31 && MY+MDY+13 > (MMSY+y)*32 && MY+MDY-14 < (MMSY+y)*32+31 && Doroyoke == 0 && Atari_8 == 0){

							Atari_8=1;

							Flag_Mad = 1.5;

							if(MDX < 0){
								MDX=MDX/2;
								if(MDX >= 0){MDX=-1;}
							}else if(MDX > 0){
								MDX=MDX/2;
								if(MDX <= 0){MDX=1;}
							}
							if(MDY < 0){
								MDY=MDY/2;
								if(MDY >= 0){MDY=-1;}
							}else if(MDY > 0){
								MDY=MDY/2;
								if(MDY <= 0){MDY=1;}
							}
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == 'E'){	//�������D��

						if(MX+MDX+13 > (MMSX+x)*32 && MX+MDX-14 < (MMSX+x)*32+31 && MY+MDY+13 > (MMSY+y)*32 && MY+MDY-14 < (MMSY+y)*32+31 && Doroyoke == 0 && Atari_E == 0){

							Atari_E=1;

							
							Flag_Mad = 1.0;

							if(MDX < 0){
								MDX=MDX/4;
								if(MDX >= 0){MDX=-1;}
							}else if(MDX > 0){
								MDX=MDX/4;
								if(MDX <= 0){MDX=1;}
							}
							if(MDY < 0){
								MDY=MDY/4;
								if(MDY >= 0){MDY=-1;}
							}else if(MDY > 0){
								MDY=MDY/4;
								if(MDY <= 0){MDY=1;}
							}
							
							
						}
					}else if(map[MMSY+y][MMSX+x] == '0' || map[MMSY+y][MMSX+x] == '1'|| map[MMSY+y][MMSX+x] == '2'|| map[MMSY+y][MMSX+x] == '3'){ //���ʕ�

						

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							if(MY+15 <= (MMSY+y)*32 || MY-16 >= (MMSY+y)*32+31){

								if(abs(((MMSY+y)*32+31)-(MY-16)) > abs(((MMSY+y)*32)-(MY+15)) && Atari_wallU == 0){ //�ǂ̏�
									MDY=((MMSY+y)*32)-(MY+15)-1;
									MVD=0.0;
									Atari_wallU=1;
								}
								if(abs(((MMSY+y)*32+31)-(MY-16)) < abs(((MMSY+y)*32)-(MY+15)) && Atari_wallD == 0){ //�ǂ̉�

									MDY=((MMSY+y)*32+31)-(MY-16)+1;

									MVU=0.0;
									Atari_wallD=1;
								}
							
							}
						}
						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31){

							if(MX+15 <= (MMSX+x)*32 || MX-16 >= (MMSX+x)*32+31){
								
								if(abs(((MMSX+x)*32+31)-(MX-16)) > abs(((MMSX+x)*32)-(MX+15)) && Atari_wallL == 0){ //�ǂ̍�
									MDX=((MMSX+x)*32)-(MX+15)-1;
									MVR=0.0;
									Atari_wallL=1;
								}
								if(abs(((MMSX+x)*32+31)-(MX-16)) < abs(((MMSX+x)*32)-(MX+15)) && Atari_wallR == 0){ //�ǂ̉E
									MDX=((MMSX+x)*32+31)-(MX-16)+1;
									MVL=0.0;
									Atari_wallR=1;
								}
								

							}
						}
					}else if(map[MMSY+y][MMSX+x] == 'G'){ //�S�[��

						if(MX+MDX+15 > (MMSX+x)*32 && MX+MDX-16 < (MMSX+x)*32+31 && MY+MDY+15 > (MMSY+y)*32 && MY+MDY-16 < (MMSY+y)*32+31 && Atari_G == 0){

							Atari_G=1;

							StopSoundMem(BGM_main);
							StopSoundMem(BGM_late);
							PlaySoundMem(SE_goal,DX_PLAYTYPE_BACK,TRUE);
							PlaySoundMem(SE_goal2,DX_PLAYTYPE_BACK,TRUE);
							Flag_fade = 6;
							
							
						}
					}
				}
			}
		}


	/*
		if(���@�E�[ > ���̍��[ && ���@���[ < ���̉E�[ && ���@���[ > ���̏�[ && ���@��[ < ���̉��[){
			if(�ړ��O�̎��@�E�[ <= ���̍��[ || �ړ��O�̎��@���[ >= ���̉E�[){����������}
			if(�ړ��O�̎��@���[ <= ���̏�[ || �ړ��O�̎��@��[ >= ���̉��[){�c��������}
		}

		*/

		if(Flag_IceV == 0){
			Flag_Ice=0;
		}

		if(speed_tile_flag == 0){
			speed_tile_lev=0;
		}

		if(speed_tile_lev == 1){
			PlaySoundMem(SE_speed,DX_PLAYTYPE_BACK,TRUE);
		}

		//��ʒ[
		if(MX+MDX < 16){MDX=16-MX,MVL=0.0;}
		if(MX+MDX > yokohaba*32-16){MDX=yokohaba*32-1-(MX+15),MVR=0.0;}
		if(MY+MDY < 16){MDY=16-MY,MVU=0.0;}
		if(MY+MDY > tatehaba*32-16){MDY=tatehaba*32-1-(MY+15),MVD=0.0;}

		//�������������������ړ����聡��������������������

		MX=MX+MDX;
		MY=MY+MDY;

		//��ʂ𓮂���
		GrX=MX-320;
		if(GrX<0){GrX=0;}
		if(GrX > yokohaba*32-640){GrX=yokohaba*32-640;}
		GrY=MY-256;
		if(GrY<0){GrY=0;}
		if(GrY > tatehaba*32-448){GrY=tatehaba*32-448;}

		//���������������������Ԍv��������������������
		
		if(Flametime == 5){
			L_time = L_time - 0.1;
			D_time = D_time + 0.1;
			if(L_time < 10.0){
				Flag_fade=4;
			}
			if(L_time <= 0.0){
				Flag_fade=5;
				L_time=0.0;
				Player_live=1;
				StopSoundMem(BGM_main);
				StopSoundMem(BGM_late);
				PlaySoundMem(SE_miss,DX_PLAYTYPE_BACK,TRUE);
				PlaySoundMem(SE_miss2,DX_PLAYTYPE_BACK,TRUE);
			}
			Flametime=0;
		}else{
			Flametime++;
		}

		if(muteki > 0){
			muteki -= 1;
		}

		if(S_Score < 0){S_Score = 0;}

		if(Player_Life <= 0){
			Flag_fade=5;
			Player_live=1;
			StopSoundMem(BGM_main);
			StopSoundMem(BGM_late);
			PlaySoundMem(SE_miss,DX_PLAYTYPE_BACK,TRUE);
			PlaySoundMem(SE_miss2,DX_PLAYTYPE_BACK,TRUE);
		}

		if(Flag_Dash > 0){
			Flag_Dash -= 1;
		}

		if(L_time <= 10.0){
			late_music_flag += 1;
		}

		if(late_music_flag == 1){
			StopSoundMem(BGM_main);
			PlaySoundMem(BGM_late,DX_PLAYTYPE_LOOP,TRUE);
		}
		if(L_time <= 10.0 && int(L_time*10)%10==0 && L_time >= 0.5){
			PlaySoundMem(SE_countC,DX_PLAYTYPE_BACK,TRUE);
		}

		if(Doroyoke > 0){
			Doroyoke--;
		}
		if(Gomukutu > 0){
			Gomukutu--;
		}
		if(Togemukou > 0){
			Togemukou--;
		}
		//���������������������̑��̏ꍇ�̏���������������������
	}else if(Flag_fade == 2){  //�t�F�[�h�C��
		//��ʂ𓮂���
		GrX=MX-320;
		if(GrX<0){GrX=0;}
		if(GrX > yokohaba*32-640){GrX=yokohaba*32-640;}
		GrY=MY-256;
		if(GrY<0){GrY=0;}
		if(GrY > tatehaba*32-448){GrY=tatehaba*32-448;}

		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){Flag_fade=3;}
	}else if(Flag_fade == 3){  //�J�E���g�_�E��
		if(countdown==239 || countdown==179 || countdown==119){
			PlaySoundMem(SE_countA,DX_PLAYTYPE_BACK,TRUE);
		}else if(countdown==59){
			PlaySoundMem(SE_countB,DX_PLAYTYPE_BACK,TRUE);
		}
		countdown = countdown-1;
		if(countdown <= 0){
			PlaySoundMem(BGM_main,DX_PLAYTYPE_LOOP,TRUE);
			Flag_fade=0;
		}
	}else if(Flag_fade == 1){
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0){
			if(miss_flag == 1){
				SceneMgr_ChangeScene(eScene_Menu);
			}else if(miss_flag == 2){
				SceneMgr_ChangeScene(eScene_Game);
			}else{
				ClearNum(D_time,Flametime,S_Score);
				SceneMgr_ChangeScene(eScene_Prep);//�V�[�����N���A�ɕύX
			}
		}
	}else if(Flag_fade == 7){
		if(Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_LEFT] == 1){
			PlaySoundMem(SE_choose,DX_PLAYTYPE_BACK,TRUE);
			retry_yesno = retry_yesno + 1;
		}

		if(Key[KEY_INPUT_Z] == 1){
			if(retry_yesno%2 == 0){ //��߂�
				PlaySoundMem(SE_choose2,DX_PLAYTYPE_BACK,TRUE);
				miss_flag=1;
				Flag_fade=1;
			}else if(retry_yesno%2 == 1){ //���g���C
				PlaySoundMem(SE_choose2,DX_PLAYTYPE_BACK,TRUE);
				miss_flag=2;
				retry_yesno = 2;
				Key[KEY_INPUT_Z] = 2;
				Flag_fade=1;
			}
		}
	}else if(Flag_fade == 6){
		clear_count=clear_count-1;
		if(clear_count < 0){Flag_fade=1;}
	}
}

//�`��
void Game_Draw(){

	DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);

	//������������������map�`�恡��������������������

	GrSX=int(GrX/32);
	GrSY=int(GrY/32);
	GrQX=GrX%32; //�Y��(0�`31)
	GrQY=GrY%32;

	for(x=0;x<21;x++){
		for(y=0;y<15;y++){
			
			//��Q���`��
			if(map[GrSY+y][GrSX+x] == '0'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,0,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '1'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,32,0,32,32,img_block,TRUE,FALSE);
			
			}else if(map[GrSY+y][GrSX+x] == '2'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,64,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '3'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,96,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '4'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,128,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '5'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,160,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '6'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,192,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '7'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,224,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '8'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,256,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == '9'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,288,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'A'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,320,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'B'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,352,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'C'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,384,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'D'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,576,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'E'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,416,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'L'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,608,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'R'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,544,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'U'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,512,0,32,32,img_block,TRUE,FALSE);
				
			}else if(map[GrSY+y][GrSX+x] == 'G'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,480,0,32,32,img_block,TRUE,FALSE);
			}

			//�A�C�e���`��
			if(map_Item[GrSY+y][GrSX+x] == '1'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,0,0,32,32,img_item,TRUE,FALSE);
				
			}else if(map_Item[GrSY+y][GrSX+x] == '2'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,32,0,32,32,img_item,TRUE,FALSE);
			
			}else if(map_Item[GrSY+y][GrSX+x] == '3'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,64,0,32,32,img_item,TRUE,FALSE);
				
			}else if(map_Item[GrSY+y][GrSX+x] == '4'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,96,0,32,32,img_item,TRUE,FALSE);
				
			}else if(map_Item[GrSY+y][GrSX+x] == '5'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,128,0,32,32,img_item,TRUE,FALSE);
				
			}else if(map_Item[GrSY+y][GrSX+x] == '6'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,160,0,32,32,img_item,TRUE,FALSE);
				
			}else if(map_Item[GrSY+y][GrSX+x] == '7'){
				DrawRectGraph(x*32-GrQX,y*32-GrQY,192,0,32,32,img_item,TRUE,FALSE);
				
			}
		}
	}

	//DrawFormatString(0,0,GetColor(0,0,0),"%d,%d,%d,%d,%f",GrX,GrY,MX-16,MY-16,L_time);


	//������������������player�`�恡������������������

	
	if(GrX==0){DrawPlX=MX;}
	else if(GrX==yokohaba*32-640){DrawPlX=MX-(yokohaba*32-640);}
	else{DrawPlX=320;}

	if(GrY==0){DrawPlY=MY;}
	else if(GrY==tatehaba*32-448){DrawPlY=MY-(tatehaba*32-448);}
	else{DrawPlY=256;}

	//DrawBox(DrawPlX-16,DrawPlY-16,DrawPlX+16,DrawPlY+16,GetColor(0,255,0),TRUE);
	if(Player_live == 0){
		if(muteki == 0){
			DrawRectGraph(DrawPlX-16,DrawPlY-16,Player_muki*32,Player_damage*32,32,32,Player_image,TRUE,FALSE);
		}else if(int(muteki/9)%2 == 1){
			DrawRectGraph(DrawPlX-16,DrawPlY-16,Player_muki*32,32,32,32,Player_image,TRUE,FALSE);
		}
	}


	//���������������������̃o�[�`�恡����������������
	DrawBox(0,448,640,480,GetColor(0,0,0),TRUE);
	if(Flag_fade == 4){
		DrawFormatStringToHandle(8,452,GetColor(255,0,0),bar_fonthandle,"Time:%5.1f",L_time);
	}else{
		DrawFormatStringToHandle(8,452,GetColor(255,255,255),bar_fonthandle,"Time:%5.1f",L_time);
	}

	if(Player_Life <= 1){
		DrawFormatStringToHandle(170,452,GetColor(255,0,0),bar_fonthandle,"Life:%d",Player_Life);	
	}else{
		DrawFormatStringToHandle(170,452,GetColor(255,255,255),bar_fonthandle,"Life:%d",Player_Life);	
	}

	DrawFormatStringToHandle(270,452,GetColor(255,255,255),bar_fonthandle,"SCORE:%d",S_Score); //S_Score

	if(Doroyoke > 0){
		DrawFormatStringToHandle(430,452,GetColor(int(Doroyoke/2)+105,int(Doroyoke/2)+105,0),bar_fonthandle,"�D",Player_Life);
	}
	if(Gomukutu > 0){
		DrawFormatStringToHandle(480,452,GetColor(0,int(Gomukutu/2)+105,int(Gomukutu/2)+105),bar_fonthandle,"�X",Player_Life);
	}
	if(Togemukou > 0){
		DrawFormatStringToHandle(530,452,GetColor(int(Togemukou/2)+105,0,int(Togemukou/2)+105),bar_fonthandle,"�j",Player_Life);
	}
	if(Flag_Dash > 0){
		DrawFormatStringToHandle(580,452,GetColor(int(Flag_Dash*3)+75,int(Flag_Dash*3)+75,int(Flag_Dash*3)+75),bar_fonthandle,"����",Player_Life);
	}

	if(Flag_fade == 3){
		if(countdown > 60){
			font_haba = GetDrawFormatStringWidthToHandle(count_fonthandle,"%d",int(countdown/60));
			DrawFormatStringToHandle(320-int(font_haba/2),96,GetColor(255,127,12),count_fonthandle,"%d",int(countdown/60));
		}else{
			font_haba = GetDrawFormatStringWidthToHandle(count_fonthandle,"START");
			DrawFormatStringToHandle(320-int(font_haba/2),96,GetColor(255,127,12),count_fonthandle,"START");
		}
	}

	if(Flag_fade == 6){
		font_haba = GetDrawFormatStringWidthToHandle(count_fonthandle,"GOAL!");
		DrawFormatStringToHandle(320-int(font_haba/2),96,GetColor(255,127,12),count_fonthandle,"GOAL!");
	}

	if(Flag_fade == 5){

		//�����\��
		if(clear_count > 220){
			DrawCircle(DrawPlX,DrawPlY,(240-clear_count)*8,GetColor(255,0,0),TRUE);
		}else if(clear_count <= 220 && clear_count > 200){
			DrawCircle(DrawPlX,DrawPlY,(clear_count-200)*8,GetColor(255,0,0),TRUE);
		}else if(clear_count <= 200 && clear_count > 180){
			DrawCircle(DrawPlX,DrawPlY,(200-clear_count)*8,GetColor(255,0,0),TRUE);
		}else if(clear_count <= 180 && clear_count >160){
			DrawCircle(DrawPlX,DrawPlY,(clear_count-160)*8,GetColor(255,0,0),TRUE);
		}else if(clear_count <= 160 && clear_count > 140){
			DrawCircle(DrawPlX,DrawPlY,(160-clear_count)*8,GetColor(255,0,0),TRUE);
		}else if(clear_count <= 140 && clear_count >120){
			DrawCircle(DrawPlX,DrawPlY,(clear_count-120)*8,GetColor(255,0,0),TRUE);
		}
		font_haba = GetDrawFormatStringWidthToHandle(count_fonthandle,"MISS!");
		DrawFormatStringToHandle(320-int(font_haba/2),96,GetColor(255,0,0),count_fonthandle,"MISS!");
		clear_count=clear_count-1;
		if(clear_count < 0){Flag_fade=7;}
	}

	if(Flag_fade == 7){
		DrawBox(70,280,570,420,GetColor(0,130,190),TRUE);
		DrawBox(90,300,550,400,GetColor(240,240,240),TRUE);

		if(retry_yesno%2 == 1){
			DrawFormatStringToHandle(120,336,GetColor(255,0,0),retry_fonthandle,"���g���C");
			DrawFormatStringToHandle(370,336,GetColor(0,0,0),retry_fonthandle,"��߂�");
		}else{
			DrawFormatStringToHandle(120,336,GetColor(0,0,0),retry_fonthandle,"���g���C");
			DrawFormatStringToHandle(370,336,GetColor(255,0,0),retry_fonthandle,"��߂�");
		}
	}

		

}