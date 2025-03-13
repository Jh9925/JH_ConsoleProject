#pragma once
#include <windows.h>  // windows.h는 기본 헤더로 mmsystem.h에 포함되어 있어 명시적으로 포함하지 않아도 됩니다.
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

void StopBgm();
void BossStageBgm();
void StartBgm();
void normalStage();


void StopBgm()
{
    PlaySound(NULL, 0, 0);
}


void BossStageBgm()
{
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
