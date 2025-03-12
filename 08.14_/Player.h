#pragma once
#include <iostream>
#include <windows.h> 
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//#include "Projectile.h""

using namespace std;
extern HANDLE console;

void TextColor1(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}

void GameOverBgm();
void StopBgm1();
void GameOver();
void GameOver1();
void gotoxy(int x, int y);

bool isStopBgm1 = false;
bool isGameOverBgm = false;

int FIN = 0;
class Player 
{
public:
    int x, y;          // 플레이어의 좌표
    int health;        // 플레이어의 체력
    int score;         // 플레이어의 점수
    int damage = 1;
    std::string BulShape = "^";
    int Shooting = 3;

    Player(int startX, int startY, int hp) : x(startX), y(startY), health(hp), score(0) {}
    // 일반스테이지 기체
    void draw() 
    {
        // 플레이어를 화면에 그리기
        gotoxy(x, y);
        cout << "    !!   ";
        gotoxy(x, y+1);
        cout << " |  ||  |";
        gotoxy(x, y+2);
        cout << "├ =[()]=┤";
        gotoxy(x, y+3);
        cout << "    ^^";

    }
    // 보스스테이지 기체
    void BossStagePlayerDraw()
    {
        gotoxy(x*3, y);
        cout << " oo__          _      _          __oo" << endl;
        gotoxy(x*3, y+1);
        cout << "     '''--,,,_(_)_--_(_)_,,,--'''" << endl;
        gotoxy(x*3, y+2);
        cout << "             _>_[____]_<_" << endl;
        gotoxy(x*3, y+3);
        cout << "     ___--''' (_)(__)(_) '''--___" << endl;
        gotoxy(x*3, y+4);
        cout << " oo''                            ''oo" << endl;


    }
    // 데미지 받는 함수
    void takeDamage(int dmg) 
    {
        health -= dmg;
        // 게임 오버
        if (health <= 0) 
        {
            system("cls");
            // std::cout << "Game Over!" << std::endl;  // 체력이 0 이하로 떨어지면 게임 종료
            if (!isStopBgm1)
            {
                StopBgm1();
                isStopBgm1 = true;
            }
            if (!isGameOverBgm)
            {
                GameOverBgm();
                isGameOverBgm = true;
            }
            gotoxy(0, 10);
            GameOver1();

            gotoxy(0,40);
            GameOver();
           
            cin >> FIN;
            if (FIN == 1) exit(0);
            
        }
    }
    // 업그레이드
    void upgrade()
    {
        if (score > 1500)
        {
            BulShape = "^^";
            damage = 2;
            Shooting = 5;
        }
        if (score > 3000)
        {
           
            BulShape = "A";
            damage = 5;
            Shooting = 2;
        }
    }
    // Get
    string GetBulShape() 
    {
        return BulShape;
    }

    int GetDamage()
    {
        return damage;
    }

};

void GameOverBgm()
{
    PlaySound(TEXT("audio/01 The Imperial March (Darth Vader_'s Theme)_[cut_29sec].wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
}

void StopBgm1()
{
    // 현재 재생 중인 소리를 멈춥니다.
    PlaySound(NULL, 0, 0);
}

// 게임오버 이미지
void GameOver()
{
cout << "                                                                        _                                                                _                                                "<<endl;
cout << "                                                                      /' `\\                                                            /' `\\                                           /'"<<endl;
cout << "                                                                    /'     )                                                         /'     )                                        /'  "<<endl;
cout << "                                                                  /'             ____      ,__________      ____                   /'      /' .     ,     ____       ____          /'    "<<endl;
cout << "                                                                /'   _         /'    )    /'    )     )   /'    )                /'      /'   |    /    /'    )    )'    )--     /'      "<<endl;
cout << "                                                              /'    ' )      /'    /'   /'    /'    /'  /(___,/'               /'      /'     |  /'   /(___,/'   /'            /'        "<<endl;
cout << "                                                             (_____,/'      (___,/(__ /'    /'    /(__ (________              (_____,/'      _|/(__  (________ /'            O           "<<endl;
cout << endl << endl << endl << endl << endl << endl;

}

void GameOver1()
{
            cout <<"                                                                             ' ' '''''''''=#= ' ''''-==*#######***===++* -'==+==**###**--+==============-'  " << endl;
            cout <<"                                                                            '''-''''''''''-*#'''''''--+*#######*******==*-''-*=*########+--===============+ " << endl;
            cout <<"                                                                            '''''''''' ''''#* ' '''''-'*####*====+=+======---**==********=-+=============== " << endl;
            cout <<"                                                                            '-'''''''-''''=#=  '' '''-*#*= -=-'---'-''''-=--+ -' ''''''  -++=============== " << endl;
            cout <<"                                                                            ++=+++=++++--'=#= ''''''+*=  '-' '''  ' '''-*='+=-''  '    '    '========**=*== " << endl;
            cout <<"                                                                            ============+-*# -+='''=+   -  '''-=''' ''''##=-*  ''''      '    =*===*******= " << endl;
            cout <<"                                                                            =============+##=-'-'-+    '   ''=##=''' ''-*#=-='  '=*+    '      =*===****=*= " << endl;
            cout <<"                                                                            ==============#==#**--     ' ''-+=*=-''''''+*='-+=--'-=#'       ' ' =*==******* " << endl;
            cout <<"                                                                            ==============-*###-+       '-=**##**======*=-'-++==++==*=          '=***=***** " << endl;
            cout <<"                                                                            ==============*###++       '--++==+==+===****-=-----==*=+    '       '********* " << endl;
            cout <<"                                                                            ==============###==         '-+==     ''=###*=''==-=+*##==+'-+      ' =******** " << endl;
            cout <<"                                                                            =============*##*+'    '    ''--+-   '''=****+   -'  +=*=+-'''         =******* " << endl;
            cout <<"                                                                            ============*###--      '    ''--+'  '+=****'         '-++-'-   '  ''   ******* " << endl;
            cout <<"                                                                            *===========###=+ '         '  '-++  =***#=             -  -'     '  '  =****** " << endl;
            cout <<"                                                                            *===*======####-               ''-++*****-               '---       '''' =***** " << endl;
            cout <<"                                                                            **=****===*###='     '   -+++--''--+-***'-               ' ++-      ''''  ***** " << endl;
            cout <<"                                                                            ***=***==*###*' ' '     ''''-++++++--===   ''''-''''-''''''+**+     '-'--'=**** " << endl;
            cout <<"                                                                            **=*****=##*=         '' '+=====+--'''  '     '  '  '''-''         '-+==-'=**** " << endl;
            cout <<"                                                                            **=*******='''   ' '  ' ''-+++-''''''    ''        '-+--         '  ''-+-=***** " << endl;
            cout <<"                                                                            **=*****=*=+-''''''   '----+++--''''''    ''    ---' '-='         ''-===******* " << endl;
            cout <<"                                                                            ******=-=*==+''-'' '''-++++====+--'''  '  '    -  '+-+*#=   ' -'+====********** " << endl;
            cout <<"                                                                            **=***=====-''''--'''-+==========+---''''''''   ' '-+=*##= ' ''-+=====***====== " << endl;
            cout <<"                                                                            #* -U *****==-''-'''''-===*****======+++++----''''+=***===  ''' ' '++==*==++-++ " << endl;
            cout <<"                                                                            #*******==++---'-'''''' '-==*###**===========+----=*##*='  ' ' '  ''''+======== " << endl;


}
