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

Player player(WIDTH / 2 - 3, HEIGHT - 5, 10); // player Init

class Projectile 
{
public:
    int x, y;          
    int damage;        
    bool isEnemy;      
    bool active;       

    void update() 
    {
        if (active) 
        {
            y += (isEnemy ? 1 : -1);  // projectile Direction Set
            if (y < 0 || y >= HEIGHT) 
            {
                active = false; 
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

// Boss Stage Player Projectile
class BossStagePlayerProjectile
{
public:
    int x1, y1;          
    int x2, y2;          
    int damage;       
    bool active1 = true;       
    void update()
    {
        if (active1)
        {
            damage = 5;
            y1 -= 4; 
            y2 -= 4;
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
                active1 = false; 
            }
            if (y2 < 1)
            {
                active1 = false;
            }
        }
    }
    void draw()
    {
        if (active1)
        {
            gotoxy(x1*3+1, y1);
            TextColor(4, 0);
            std::cout << "";
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
    int xs, ys;         
    int damage;      
    bool active_s = true;       
    void update()
    {
        if (active_s)
        {
            damage = 50;
            ys -= 4; 
        }
        if (ys < 0)
        {
            active_s = false; 
        }
    }
    void draw()
    {
        if (active_s)
        {
            int beamLength = 40; 
            TextColor(0, 10);
            for (int i = 0; i < beamLength; ++i)
            {
                int beamY = ys - i;  
                if (beamY >= 0) 
                {
                    gotoxy(xs * 3 + 17, beamY);
                    std::cout << "  ";
                }
            }
            TextColor(15, 0); 
        }
    }
};

//  BossProjectile
class Asteroid
{
public:
    float b_x, b_y;    // x, y
    int damage;       
    float dx, dy;      // Direction Vector
    bool active;      


    void trackPlayer(int playerX, int playerY)
    {
        // Get Distance
        float deltaX = (playerX*3+18)  - b_x;
        float deltaY = playerY - b_y;
        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        dx = deltaX / distance;
        dy = deltaY / distance;
    }


    void update()
    {
        if (active)
        {
            b_x += dx;
            b_y += dy;
            if (b_y < 10 || b_y >= HEIGHT || b_x < 1 || b_x >= 170)
            {
                active = false;
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
                cout << "|" << endl;
               
            }

            if (b_y >= 25 && b_y < 50)
            {
               TextColor(13, 0);
               gotoxy(b_x, b_y);
               cout << "|"<< endl;
               
               gotoxy(b_x, b_y+1);
               cout << "││" << endl;
               gotoxy(b_x, b_y+2);
               cout << "∀" << endl;
               TextColor(15, 0);
              
            }

        }
    }

};