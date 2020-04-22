#include "clres.h"
#include "SceneMGR.h"
#include "DxLib.h"

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�

//������
void Clres_Initialize(){
    mImageHandle = LoadGraph("images/Scene_Config.png");//�摜�̃��[�h
}

//�I������
void Clres_Finalize(){
    DeleteGraph(mImageHandle);//�摜�̉��
}

//�X�V
void Clres_Update(){
    if(CheckHitKey(KEY_INPUT_ESCAPE)!=0){//Esc�L�[��������Ă�����
        SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
    }
}

//�`��
void Clres_Draw(){
	DrawGraph(0,0,mImageHandle,FALSE);
    DrawString(0, 0,"�ݒ��ʂł��B",GetColor(255,255,255));
    DrawString(0,20,"Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B",GetColor(255,255,255));
}