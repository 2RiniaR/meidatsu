#include <math.h>
#include "DxLib.h"
#include "SceneMGR.h"

#define INIT_SCREEN_W (640)
#define INIT_SCREEN_H (480)

//������������������������FPS�v��������������������������
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

	SetMainWindowText("test"); //�E�B���h�E�̃^�C�g����ݒ肷��
	SetWindowSizeChangeEnableFlag(TRUE,TRUE);//�T�C�Y�ύX���\�ɂ���
	ChangeWindowMode(TRUE);  //�E�B���h�E���[�h��L���ɂ���
	SetWindowStyleMode(0);//�ő剻�{�^�������݂��A����ɘg���ׂ��Ȃ�E�B���h�E���[�h�ɕύX

	//��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
	GetDefaultState(&DesktopW,&DesktopH,NULL);
	//SetGraphMode(DesktopW,DesktopH,32);

	//SetUseASyncChangeWindowModeFunction(TRUE,NULL,NULL);
	//SetWindowSize(INIT_SCREEN_W,INIT_SCREEN_H);//�E�B���h�E�T�C�Y�͉�ʂƈ�v������
	SetWindowPosition((DesktopW - INIT_SCREEN_W)/2,(DesktopH - INIT_SCREEN_H)/2);//�E�B���h�E�̈ʒu����ʂ̒��S�ɂ���

	if( DxLib_Init() == -1 )// �c�w���C�u��������������
	{return -1 ;}// �G���[���N�����璼���ɏI��
	//GetWindowSize(&WindowW,&WindowH);
	//WindowExW = WindowW / 640;
	WindowExH = ((double)DesktopH-100.0) / 480.0;
	SetWindowMaxSize(DesktopW,DesktopH);
	SetWindowMinSize(DesktopW/3,DesktopH/3);
	SetWindowSizeExtendRate(WindowExH);
	SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E�̗���ʐݒ�


	SceneMgr_Initialize();

//�����������������������������������������������C�����[�v��������������������������������������������

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdatekey()==0){
		
		   Flame_Count();
		   SceneMgr_Update();  //�X�V
		   SceneMgr_Draw();    //�`��
		   Wait();


	}

	SceneMgr_Finalize();
//����������������������������������������������������������������������������������������������������

DxLib_End() ;				// �c�w���C�u�����g�p�̏I������
return 0 ;				// �\�t�g�̏I�� 

}
