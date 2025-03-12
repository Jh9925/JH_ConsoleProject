#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>

using std::cout;
extern const int WIDTH;
extern const int HEIGHT;

void TextColor3(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}

class EnemyBase 
{
public:
    int x, y;          // ���� ��ǥ
    int health;        // ���� ü��
    int damage;        // ���� ���ط�
    int directionX, directionY;  // ���� �̵� ����
    bool active;       // ���� Ȱ��ȭ �������� ����
    int shootInterval; // ���� �Ѿ� �߻� ����
    int shootTimer;    // �Ѿ� �߻� Ÿ�̸�

    EnemyBase(int hp, int dmg, int dirX, int dirY, int shootInt)
        : health(hp), damage(dmg), directionX(dirX), directionY(dirY), active(false), shootInterval(shootInt), shootTimer(0) {}

    virtual void draw() = 0;  // ���� �Լ��� ���� ��ü���� ������ ���� Ŭ��������

    void update() 
    {
        if (active) 
        {
            x += directionX;
            y += directionY;
            if (y >= HEIGHT || x < 1 || x >= WIDTH-5) 
            {
                active = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
            shootTimer++;
        }
    }

    void takeDamage(int dmg) 
    {
        health -= dmg;
        if (health <= 0) 
        {
            active = false;  // ü���� 0 ���Ϸ� �������� ��Ȱ��ȭ
        }
    }

    bool shouldShoot() 
    {
        return active && shootTimer >= shootInterval;
    }

    void resetShootTimer() 
    {
        shootTimer = 0;
    }
};

class EnemyA : public EnemyBase 
{
public:
    EnemyA() : EnemyBase(3, 1, 1, 1, 20) {}

    void draw() override 
    {
        if (active) 
        {
            gotoxy(x, y);
            TextColor3(6, 0);
            std::cout << "|  _  |" << std::endl;
            gotoxy(x, y+1);
            std::cout << "|=(_)=|" << std::endl;
            gotoxy(x, y+2);
            std::cout << "|     |" << std::endl;  // EnemyA�� �ð��� ǥ��
            TextColor3(15, 0);

        }
    }
};

class EnemyB : public EnemyBase 
{
public:
    EnemyB() : EnemyBase(3, 1, -1, 1, 30) {}

    void draw() override 
    {
        if (active) {
            gotoxy(x, y);
            TextColor3(11, 0);
            std::cout << " |  _  |";
            gotoxy(x, y + 1);
            std::cout << " |=[O]=|";  // EnemyB�� �ð��� ǥ��
            gotoxy(x, y + 2);
            std::cout << "";
            TextColor3(15, 0);
        }
    }
};

class EnemyC : public EnemyBase 
{
public:
    EnemyC() : EnemyBase(1, 1, 0, 1, 15) {}

    void draw() override 
    {
        if (active) 
        {
            gotoxy(x, y + 3);
            TextColor3(7, 0);
            std::cout << "<o>";  // EnemyC�� �ð��� ǥ��
            TextColor3(15, 0);
        }
    }
    void update() 
    {
        if (active)
        {
            if (rand() % 10 == 1)
            {
                if (rand() % 2 == 1 && x < WIDTH - 5)
                {
                    x++;
                }
                else if (rand() % 2 == 0 && x > 0)
                {
                    x--;
                }
                if (rand() % 2 == 1)
                {
                    y++;
                }
                else if (rand() % 2 == 0)
                {
                    y--;
                }
            }
            if (y >= HEIGHT || x < 0 || x >= WIDTH) 
            {
                active = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
            shootTimer++;
        }
    }
};

class Boss : public EnemyBase
{
public:
    Boss() :EnemyBase(3000, 1, 0, 0, 10) {}

    void draw() override 
    {
        if (active) 
        {
            TextColor3(7, 0);
         gotoxy(x *3, y + 5);
         cout << "         ,,o                            __.o+. "<<endl;
         gotoxy(x * 3, y + 6);
         cout << "        od8^                         oo888888P^b  " << endl;
         gotoxy(x * 3, y + 7);
         cout << "      ,\".o'                          `b^'\"\"`b -`b  " << endl;
         gotoxy(x * 3, y + 8);
         cout << "    ,'.'o'                            t. = -`b -`t.    " << endl;
         gotoxy(x * 3, y + 9);
         cout << "   ; d o'          ___          _.--.. 8  -  `b  =`b" << endl;
         gotoxy(x * 3, y + 10);
         cout << "  dooo8<       .o:':__;o.     ,;;o88%%8bb - = `b  =`b. " << endl;
         gotoxy(x * 3, y + 11);
         cout << " |^88^88=. .,x88/::/ | \\`;;;;;;d%%%%%88%88888/%x88888 " << endl;
         gotoxy(x * 3, y + 12);
         cout << " :-88=88%%L8`%`|::|_>-<_||%;;%;8%%=;:::=%8;;\%%%%\8888 " << endl;
         gotoxy(x * 3, y + 13);
         cout << " |=88 88%%|HHHH|::| >-< |||;%;;8%%=;:::=%8;;;%%%%+|]88   " << endl;
         gotoxy(x * 3, y + 14);
         cout << " | 88-88%%LL.%.%b::Y_|_Y/%|;;;;`%8%%oo88%:o%.;;;;+|]88 " << endl;
         gotoxy(x * 3, y + 15);
         cout << " Yx88o88^^'\"`^^%8boooood..-\H_Hd%P%%88%P^%%^'\;;;/%%88 "<<endl;
         gotoxy(x * 3, y + 16);
         cout << "  `\"\^\           '''''       %P '''^' ;   = `+' - P' " << endl;
         gotoxy(x * 3, y + 17);
         cout << "   `.`.b                               :  -   d' - P  " << endl;
         gotoxy(x * 3, y + 18);
         cout << "     .`.b                             ,'-  = d' =.'   " << endl;
         gotoxy(x * 3, y + 19);
         cout << "      ``.b.                           :..-  :'  P     " << endl;
         gotoxy(x * 3, y + 20);
         cout << "       `q.>b                         `^^^:::::,'      " << endl;
         TextColor3(15, 0);
        }
    }

    void update() 
    {
        if (active)
        {
            if (rand() % 5 == 1)
            {
                if (rand() % 2 == 1 && x*3 <80)
                {
                    x+=rand() %3 +1;
                }
                else if (rand() % 2 == 0 && x*3 > 15)
                {
                    x-= rand() % 4 + 1;
                }
                if (rand() % 4 == 1 && y <7)
                {
                    y++;
                }
                else if (rand() % 2 == 0 && y >2)
                {
                    y--;
                }
            }
           
            shootTimer++;
        }
    }

};

