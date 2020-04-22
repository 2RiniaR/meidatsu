#ifndef DEF_SCENEMGR_H

#define DEF_SCENEMGR_H

#pragma once

typedef enum {
    eScene_Menu,    //���j���[���
    eScene_Game,    //�Q�[�����
    eScene_Config,  //�ݒ���
	eScene_Prep,
	eScene_Clres,
	eScene_Startm,
	
    eScene_None,    //����

} eScene ;

struct MenuElement_t{
	int x;
	int y;
	char name[30];
};


void SceneMgr_Initialize();//������
void SceneMgr_Finalize();//�I������
//�X�V
void SceneMgr_Update();

//�`��
void SceneMgr_Draw();

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene nextScene);
int gpUpdatekey();
int KeepValueKey(int *ad);
int VolumeSetNum(int Bv,int Sv);
int Stage_Seld(int Af);
int Stage_Selv(int *Ad);
int VolumeSetRug(int *Mu,int *Se);

int ClearNum(double time,int flame,int score);
int ClearVel(double *time_v,int *flame_v,int *score_v);

#endif