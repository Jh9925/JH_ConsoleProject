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
    int x, y;          
    int health;        
    int score;         
    int damage = 1;
    std::string BulShape = "^";
    int Shooting = 3;

    Player(int startX, int startY, int hp) : x(startX), y(startY), health(hp), score(0) {}
    // Normal Stage X-Wing
    void draw() 
    {
        gotoxy(x, y);
        cout << "    !!   ";
        gotoxy(x, y+1);
        cout << " |  ||  |";
        gotoxy(x, y+2);
        cout << "-=[()]=-";
        gotoxy(x, y+3);
        cout << "    ^^";

    }
    // Boss Stage X-Wing
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
    void TakeDamage(int dmg) 
    {
        health -= dmg;
        if (health <= 0) 
        {
            system("cls");
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
    // Upgrade
    void Upgrade()
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
    PlaySound(NULL, 0, 0);
}

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
