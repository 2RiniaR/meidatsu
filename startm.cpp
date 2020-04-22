#include "startm.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�
static int iImage;
	
	int SelectNum = 0;
	static int Key[256];
	static int SEfH,SEgH,BGMaH;
	static int Mvol,Svol; //����
	static int bright=255; // �t�F�[�h�A�E�g�A�C��
	static int menuBw=0; //�I�����ꂽ�t���O

//������
void Startm_Initialize(){

	menuBw=3;
	bright=0;
    mImageHandle = LoadGraph("pic/main.PNG");//�摜�̃��[�h
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

//�I������
void Startm_Finalize(){

	StopSoundMem(BGMaH);

    DeleteGraph(mImageHandle);//�摜�̉��
	DeleteGraph(iImage);
	DeleteSoundMem(SEfH);
	DeleteSoundMem(SEgH);
	DeleteSoundMem(BGMaH);
}

//�X�V
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
				case 2: exit(0);//�I��
					break;
			}
		}
	}else if(menuBw == 1 || menuBw == 2){ //�t�F�[�h�A�E�g����
		bright=bright-10;
		if(bright < 0){bright=0;}
		SetDrawBright(bright,bright,bright);
		if(bright <= 0 && menuBw == 1){
			 SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
		}else if(bright <= 0 && menuBw == 2){
			 SceneMgr_ChangeScene(eScene_Config);//�V�[�����R���t�B�O�ɕύX
		}
	}else{
		bright=bright+10;
		if(bright > 255){bright=255;}
		SetDrawBright(bright,bright,bright);
		if(bright >= 255){menuBw=0;}
	}

}

//�`��
void Startm_Draw(){
	static int i=0;
	DrawGraph(0,0,mImageHandle,TRUE);
	DrawGraph(135,265+(SelectNum*60),iImage,TRUE);
	
}