#pragma once
#include <iostream>
#include <windows.h>
#include "Player.h"

void TextColor(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}


extern const int HEIGHT;

Player player(WIDTH / 2 - 3, HEIGHT - 5, 10); // �÷��̾� �ʱ�ȭ (ü�� 10)

class Projectile 
{
public:
    int x, y;          // �Ѿ��� ��ǥ
    int damage;        // �Ѿ��� ���ط�
    bool isEnemy;      // ���� �Ѿ����� ����
    bool active;       // �Ѿ��� Ȱ��ȭ ����

    void update() 
    {
        if (active) 
        {
            y += (isEnemy ? 1 : -1);  // ���� �Ѿ��� �Ʒ���, �÷��̾��� �Ѿ��� ���� �̵�
            if (y < 0 || y >= HEIGHT) 
            {
                active = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
        }
    }

    void draw() 
    {
        if (active)
        {
            gotoxy(x, y);
            if (isEnemy)
            {
                TextColor(3, 0);
                std::cout << "*";
                TextColor(15, 0);
            }
            else
            {
                TextColor(4, 0);
                std::cout << player.GetBulShape();
                TextColor(15, 0);
            }
           
        }
    }


};

class BossStagePlayerProjectile
{
public:
    int x1, y1;          // ���� �Ѿ��� ��ǥ
    int x2, y2;          // ������ �Ѿ��� ��ǥ
    int damage;        // �Ѿ��� ���ط�
    // bool isEnemy;      // ���� �Ѿ����� ����
    bool active1 = true;       // �Ѿ��� Ȱ��ȭ ����



    void update()
    {
        if (active1)
        {
            damage = 5;
            y1 -= 4;  // �÷��̾��� �Ѿ��� ���� �̵�, y�� 3���������� ȭ�� �߽ɱ��� ������ +1 ���G�� -1
            y2 -= 4;
             // �Ѿ��� �ִ°�
            int c = 0;
            c++;
            if (c % 5 == 1)
            {
                if (x1*3 < 55) x1+=2;
                if (x2 * 3 < 55) x2++;
                if (x1 * 3 > 55) x1-=1;
                if (x2 * 3 > 55) x2 -= 2;
            }
            
            
            if (y1 < 1)
            {
                active1 = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
            if (y2 < 1)
            {
                active1 = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
        }
    }

    void draw()
    {
        if (active1)
        {
            gotoxy(x1*3+1, y1);
            TextColor(4, 0);
            std::cout << "";  // �Ѿ��� �ð��� ǥ��
            gotoxy(x1 * 3 + 1, y1+1);
            std::cout << "||";
            TextColor(15, 0);

            gotoxy(x2*3+35, y2);
            TextColor(4, 0);
            std::cout << "";
            gotoxy(x2 * 3 + 35, y2+1);
            std::cout << "||";
            TextColor(15, 0);
        }  
    }


};


class BossStagePlayerSkill
{
public:
    int xs, ys;          // ���� �Ѿ��� ��ǥ
   
    int damage;        // �Ѿ��� ���ط�
    // bool isEnemy;      // ���� �Ѿ����� ����
    bool active_s = true;       // �Ѿ��� Ȱ��ȭ ����



    void update()
    {
        if (active_s)
        {
            damage = 50;
            ys -= 4;  // �÷��̾��� �Ѿ��� ���� �̵�
        }

        if (ys < 0)
        {
            active_s = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
        }
    }

    void draw()
    {
        if (active_s)
        {
            int beamLength = 40;  // ���� ���� ����
            TextColor(0, 10);

            for (int i = 0; i < beamLength; ++i)
            {
                int beamY = ys - i;  // ���� ���� ���ϰ�
                if (beamY >= 0)  // ȭ���� ����� �ʵ���
                {
                    gotoxy(xs * 3 + 17, beamY);
                    std::cout << "  ";
                }
            }

            TextColor(15, 0);  // ���� �������� ����
        }
    }
};

//  �����Ѿ˷� ����
class Asteroid
{
public:
    float b_x, b_y;          // �Ѿ��� ��ǥ
    int damage;        // �Ѿ��� ���ط�
    float dx, dy;    // �̵��� ���� ����
    bool active;       // �Ѿ��� Ȱ��ȭ ����


    void trackPlayer(int playerX, int playerY)
    {
        // �÷��̾���� �Ÿ� ���
        float deltaX = (playerX*3+18)  - b_x;
        float deltaY = playerY - b_y;
        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

        // ���� ���� ��� �� ����ȭ
        dx = deltaX / distance;
        dy = deltaY / distance;
    }


    void update()
    {
        if (active)
        {
            b_x += dx;
            b_y += dy;

            // b_y += 1;  // ���� �Ѿ��� �Ʒ���, �÷��̾��� �Ѿ��� ���� �̵�
            if (b_y < 10 || b_y >= HEIGHT || b_x < 1 || b_x >= 170)
            {
                active = false;  // ȭ�� ������ ������ ��Ȱ��ȭ
            }
        }
    }

    void draw()
    {
        if (active)
        {
            if (b_y < 25)
            {
                gotoxy(b_x, b_y);
                cout << "" << endl;
               
            }

            if (b_y >= 25 && b_y < 50)
            {
               TextColor(13, 0);
               gotoxy(b_x, b_y);
               cout << "��"<< endl;
               
               gotoxy(b_x, b_y+1);
               cout << "����" << endl;
               gotoxy(b_x, b_y+2);
               cout << "��" << endl;
               TextColor(15, 0);
              
            }

        }
    }

};