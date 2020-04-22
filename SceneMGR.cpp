#include "DxLib.h"
#include "config.h"
#include "calcs.h"
#include "menu.h"
#include "prep.h"
#include "clres.h"
#include "startm.h"
#include "SceneMGR.h"
#include <string.h>

static eScene mScene = eScene_Startm;    //�V�[���Ǘ��ϐ�

static eScene mNextScene = eScene_None;    //���̃V�[���Ǘ��ϐ�

static void SceneMgr_InitializeModule(eScene scene);//�w�胂�W���[��������������
static void SceneMgr_FinalizeModule(eScene scene);//�w�胂�W���[���̏I���������s��

//������
void SceneMgr_Initialize(){
    SceneMgr_InitializeModule(mScene);
}

//�I������
void SceneMgr_Finalize(){
    SceneMgr_FinalizeModule(mScene);
}


//�X�V
void SceneMgr_Update(){
	  if(mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
        SceneMgr_FinalizeModule(mScene);//���݂̃V�[���̏I�����������s
        mScene = mNextScene;    //���̃V�[�������݂̃V�[���Z�b�g
        mNextScene = eScene_None;    //���̃V�[�������N���A
        SceneMgr_InitializeModule(mScene);    //���݂̃V�[����������
    }
    switch(mScene){       //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:    //���݂̉�ʂ����j���[�Ȃ�
        Menu_Update();   //���j���[��ʂ̍X�V����������
        break;//�ȉ���
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

//�`��
void SceneMgr_Draw(){
    switch(mScene){      //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:   //���݂̉�ʂ����j���[��ʂȂ�
        Menu_Draw();    //���j���[��ʂ̕`�揈��������
        break;//�ȉ���
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

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene NextScene){
   mNextScene = NextScene;
}
// ����scene���W���[��������������
static void SceneMgr_InitializeModule(eScene scene){
    switch(scene){          //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:       //�w���ʂ����j���[��ʂȂ�
        Menu_Initialize();  //���j���[��ʂ̏���������������
        break;//�ȉ���
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

// ����scene���W���[���̏I���������s��
static void SceneMgr_FinalizeModule(eScene scene){
    switch(scene){         //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:      //�w���ʂ����j���[��ʂȂ�
        Menu_Finalize();   //���j���[��ʂ̏I����������������
        break;//�ȉ���
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
