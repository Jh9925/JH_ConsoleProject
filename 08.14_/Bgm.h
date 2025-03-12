#pragma once
#include <windows.h>  // windows.h�� �⺻ ����� mmsystem.h�� ���ԵǾ� �־� ��������� �������� �ʾƵ� �˴ϴ�.
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

void StopBgm();
void BossStageBgm();
void StartBgm();
void normalStage();


void StopBgm()
{
    // ���� ��� ���� �Ҹ��� ����ϴ�.
    PlaySound(NULL, 0, 0);
}


void BossStageBgm()
{
    // ���� ��θ� ������ ���� ��ΰ� ��Ȯ���� Ȯ���ؾ� �մϴ�. ���� ��ΰ� �ùٸ��ٸ� �̴�� ��� �����մϴ�.
    PlaySound(TEXT("audio/03-Battle-Of-The-Heroes_[cut_204sec].wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
}

void StartBgm()
{
    PlaySound(TEXT("audio/01 Star Wars And The Revenge Of The Sith_[cut_49sec].wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
}

void normalStage()
{
    PlaySound(TEXT("audio/01 Star Wars And The Revenge Of The Sith_normal_stage.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
}
