#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>      // sin(), cos()
#include <thread>
#include <fstream>
#include <filesystem>

#include "Player.h"
#include "Enemy.h"
#include "EnemyPool.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "Stopwatch.h"
#include "Interface.h"
#include "RankingShow.h"
#include "Bgm.h"


const int WIDTH = 50;       // ���� ȭ���� ���� ũ��
const int HEIGHT = 50;      // ���� ȭ���� ���� ũ��
const int UI_WIDTH = 75;    // UI ������ ������ ��ü ȭ���� ���� ũ��

///////////////////////////////////////////////////
// ������������
const int width = 150;  // �ܼ� ���� ũ��
const int height = 55; // �ܼ� ���� ũ��
const int UI_width = 175;
const int centerX = width / 2;
const int centerY = height / 2;
///////////////////////////////////////////////////

int shootTimer = 0;         // �Ѿ� �߻� Ÿ�̸�
int enemySpawnTimer = 0;    // �� ���� Ÿ�̸�
int playerShootTimer = 0;   // �÷��̾� �Ѿ� �߻� Ÿ�̸�

int h = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ�

void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void setConsoleSize(int width, int height);
void clearScreen();
void clearScreen1(); // ���� ����������

void Scoring(); // ���� ���

// Player player(WIDTH / 2 - 3, HEIGHT - 5, 5); // �÷��̾� �ʱ�ȭ (ü�� 5)

EnemyPool<EnemyA> enemyPoolA(5);     // �� �ִ� 5����
EnemyPool<EnemyB> enemyPoolB(5);     // �� �ִ� 5����
EnemyPool<EnemyC> enemyPoolC(5);     // �� �ִ� 5����
EnemyPool<Boss>   enemyPoolBoss(1);  // ���� 1 ���� 


//�Ϲݽ������� �Ѿ� ��ü 100��
ProjectilePool projectilePool(100);  // �Ѿ� 100��
BossStagePlayerProjectilePool BossStagePlayerProjectpool(200); // ������ �÷��̾� �Ѿ� 200��
BossStagePlayerSkillPool BSPlayerSkillPool(100); // �÷��̾� ��ų 
AsteroidPool AsteroidPool1(100); // �����Ѿ�

// Ű���� ����Ű ���� �Է�, �÷��̾� ���� �ֱ� 
// �Ϲݽ�������
void processInput();

// ��������������
void processInput_BOSS_STAGE();


// �Ϲ� �������� ���� ��Ȳ ������Ʈ 
void update();

// �Ϲ� ���������� �ʿ��� ��� �׸���
void draw();

/// ///////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////
// ������������ �ʿ��� �͵�
int BackGround(); // ������������

// ���� �Լ�
int main() 
{
    
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1; //�β� : 1
    c.bVisible = 0; //Ŀ�� �����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);

    setConsoleSize(UI_WIDTH, HEIGHT + 5);
    srand(time(NULL));
    setcursor(0, 0);
    StartBgm(); // �����װ� ����
    while (true)
    {
        Title();
        int i = 0;
        cin >> i;
        system("cls");
        switch (i)
        {
        case 1:
            StopBgm(); // �����װ� ����
            normalStage(); // �Ϲݽ������� ����
            while (true)
            {
                

                sw.start(); // �����ġ

                processInput();
                update();
                draw();
                if (player.score > 5000)// ������������ ����
                {
                    break;
                }
            }
            clearScreen1();
            gotoxy(75, 30);
            std::cout << " �� ���ݱ� ����!!!" << endl;
            StopBgm(); // �뷡 ����
            BossStageBgm(); // ������������
            // 3�ʴ��
            std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // �Ǵ� std::chrono::seconds(3)
            while (true)
            {
                processInput_BOSS_STAGE();
                BackGround();
            }

            break;
        case 3:
            return 0;
        case 2:
            RankingShow();
            // cout << " �������� ���ư��� : 1 �Է� " << endl;
            if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
            {
                system("cls");
                break;
            }
            else return 0;
            
        default:
            break;
        }
    }
    return 0;
}

void gotoxy(int x, int y)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(console, coord);
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 50;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setConsoleSize(int width, int height)
{
    SMALL_RECT windowSize = { 0, 0, (SHORT)(width), (SHORT)(height) };
    SetConsoleWindowInfo(console, TRUE, &windowSize);
}

void clearScreen()
{
    gotoxy(0, 0);
    std::cout << std::string(WIDTH + 2, ' ') << std::endl;
    for (int i = 1; i < HEIGHT + 1; ++i)
    {
        gotoxy(0, i);
        std::cout << std::string(UI_width + 100, ' ') << std::endl;
    }
}

void clearScreen1() // ���� ����������
{

    gotoxy(0, 0);
    cout << string(UI_width + 100, ' ') << endl;
    for (int i = 1; i < height; i++)
    {
        gotoxy(0, i);
        cout << string(UI_width + 100, ' ') << endl;
    }
}

// Ű���� ����Ű ���� �Է�, �÷��̾� ���� �ֱ� 
// �Ϲݽ�������
void processInput()
{
    playerShootTimer++;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if (player.x > 1)
            player.x -= 2;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (player.x < WIDTH - 8)
            player.x += 2;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (player.y > 1)
            player.y -= 1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (player.y < HEIGHT - 3)
            player.y += 1;
    }
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && playerShootTimer >= player.Shooting) // ���� ���� 
    {
        auto p = projectilePool.get();
        if (p)
        {
            p->x = player.x + 5;
            p->y = player.y;
            // �÷��̾� ������ ���� �κ�
            p->damage = player.GetDamage();

            p->isEnemy = false;
            playerShootTimer = 0;
        }
    }
}

// ��������������
void processInput_BOSS_STAGE()
{
    playerShootTimer++;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if (player.x > 1)
            player.x -= 2;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (player.x < 38)// ����
            player.x += 2;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (player.y > 1)
            player.y -= 1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (player.y < height - 6)
            player.y += 1;
    }
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && playerShootTimer >= player.Shooting) // ���� ���� 
    {
        auto p1 = BossStagePlayerProjectpool.get1();
        if (p1)
        {
            // �÷��̾� �ʱ�ȭ �ٽ� �ʿ�?
            // ���� �Ѿ�
            p1->x1 = player.x;
            p1->y1 = player.y;
            // ������ �Ѿ�
            p1->x2 = player.x;
            p1->y2 = player.y;


            // �÷��̾� ������ ���� �κ�
            p1->damage = player.GetDamage();

            // p1->isEnemy = false;
            playerShootTimer = 0;
        }
    }
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) /*&& playerShootTimer >= player.Shooting*/)  // ctrl Ű ����
    {
        auto ps = BSPlayerSkillPool.get();
        if (ps && player.health > 1)
        {

            // ��ü �߾� ������
            ps->xs = player.x;
            ps->ys = player.y;

            // �÷��̾� ������ ���� �κ�
            ps->damage = 10;

            // p1->isEnemy = false;
            playerShootTimer = 0;
            h += 1;
            if (h % 10 == 0)
            {
                player.health -= 1;
            }
        }
    }
}

void update()
{
    // �Ϲ� ��������
    //////////////////////////////////////////////////////
    // �� ���� Ÿ�̸ӷ� �� ����
    // Ǯ�� ���� �������ɽÿ��� ������ ����
    if (player.score <= 5000)
    {

        enemySpawnTimer++;
        if (enemySpawnTimer >= 25)
        {
            int randomSpawn = rand() % 6;
            // �� ������ ���� Ȯ�� �ٸ���
            if (randomSpawn == 0 || randomSpawn == 3 || randomSpawn == 5)
            {
                auto e = enemyPoolA.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            if (randomSpawn == 1)
            {
                auto e = enemyPoolB.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            if (randomSpawn == 2 || randomSpawn == 4)
            {
                auto e = enemyPoolC.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            enemySpawnTimer = 0;
        }
    }

    // Ǯ ������Ʈ ������ �ݿ�
    enemyPoolA.update();
    enemyPoolB.update();
    enemyPoolC.update();
    // enemyPoolBoss.update();

    // �Ѿ� ������Ʈ
    projectilePool.update();


    // �� �Ѿ˰� �÷��̾� �浹 ó��
    for (auto& p : projectilePool.getAll())
    {
        if (p.active && p.isEnemy && p.x >= player.x && p.x <= player.x + 7 && p.y == player.y)
        {
            player.takeDamage(p.damage);
            p.active = false;
        }
    }


    // �÷��̾� �Ѿ˰� �� �浹 ó��
    for (auto& p : projectilePool.getAll())
    {
        // �� ������ �ǰ� ó�� �߰� ������ �ٸ�
        if (p.active && !p.isEnemy)
        {
            for (auto& e : enemyPoolA.getAll())
            {
                if (e.active && p.x >= e.x - 2 && p.x <= e.x + 2 && p.y < e.y + 3)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 100;
                    player.upgrade();
                }
            }
            for (auto& e : enemyPoolB.getAll())
            {
                if (e.active && p.x >= e.x - 2 && p.x <= e.x + 2 && p.y < e.y + 3)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 200;
                    player.upgrade();
                }
            }
            for (auto& e : enemyPoolC.getAll())
            {
                if (e.active && p.x >= e.x && p.x <= e.x + 2 && p.y == e.y)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 150;
                    player.upgrade();
                }
            }
        }
    }

    // �� �Ѿ� �߻�
    for (auto& e : enemyPoolA.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (auto& e : enemyPoolB.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (auto& e : enemyPoolC.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }
}

void draw()
{
    clearScreen();
    setcursor(0, 0);

    /////////////////////////////////////////////////////////////////////////////////////////////
    // �Ϲݽ�������
    gotoxy(0, 0);
    std::cout << "*";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "*";
    for (int i = WIDTH + 1; i < UI_WIDTH; i++) std::cout << "-";
    std::cout << "*";

    for (int i = 1; i <= HEIGHT; i++)
    {
        gotoxy(0, i);
        std::cout << "|";
        gotoxy(WIDTH + 1, i);
        std::cout << "|";
        gotoxy(UI_WIDTH, i);
        std::cout << "|";
    }

    gotoxy(0, HEIGHT + 1);
    std::cout << "*";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "*";
    for (int i = WIDTH + 1; i < UI_WIDTH; i++) std::cout << "-";
    std::cout << "*";


    ////////////////////////////////////////////////////////////////////////////////////////////
    gotoxy(WIDTH + 2, 5);
    std::cout << "Energy : " << player.health;
    gotoxy(WIDTH + 2, 6);
    for (int i = 0; i < player.health; i++)
    {
        TextColor(10, 0);
        std::cout << "��";
        TextColor(15, 0);
    }

    gotoxy(WIDTH + 2, 10);
    std::cout << "Score : " << player.score;

    gotoxy(WIDTH + 2, 15);
    std::cout << "Damage : " << player.damage;

    gotoxy(WIDTH + 2, 20);
    std::cout << "Time : ";
    gotoxy(WIDTH + 2, 21);
    sw.print_elapsed();


    player.draw();
    enemyPoolA.draw();
    enemyPoolB.draw();
    enemyPoolC.draw();
    // enemyPoolBoss.draw();
    projectilePool.draw();

    Sleep(32);
}

// ������������ �ʿ��� �͵�
int BackGround() // ������������
{
    const int numStars = 40;  // ���� ����

    float starsX[numStars];
    float starsY[numStars];

    float prevStarsX[numStars];
    float prevStarsY[numStars];
    float speeds[numStars];

    // ���� �ʱ� ��ġ�� �ӵ� ����
    for (int i = 0; i < numStars; ++i)
    {
        // ���� ���� ȣ���� ����? �Ϻ��ϰ� ������ ���� ����� ���
        // float angle = (float)(rand() % 360) * 3.14159f / 180.0f;
        starsX[i] = centerX;
        starsY[i] = centerY;

        prevStarsX[i] = centerX;
        prevStarsY[i] = centerY;
        // �ӵ� ����
        speeds[i] = (float)(rand() % 5 + 1) / 2.0f; // �ӵ� ����
    }

    // ���� �̵��� ����ؼ� �ݺ�
    while (true)
    {


        clearScreen1();

        /////////////////////////////////////////////////////////////////////////////////////////////
        // ������������ ��� �׸���
        gotoxy(0, 0);
        std::cout << "*";
        for (int i = 0; i < width; i++) std::cout << "-";
        std::cout << "*";
        for (int i = width + 1; i < UI_width; i++) std::cout << "-";
        std::cout << "*";

        for (int i = 1; i <= height; i++)
        {
            gotoxy(0, i);
            std::cout << "|";
            gotoxy(width + 1, i);
            std::cout << "|";
            gotoxy(UI_width + 1, i);
            std::cout << "|";
        }

        gotoxy(0, height + 1);
        std::cout << "*";
        for (int i = 0; i < width; i++) std::cout << "-";
        std::cout << "*";
        for (int i = width + 1; i < UI_width; i++) std::cout << "-";
        std::cout << "*";


        ////////////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < numStars; ++i)
        {
            // ���� ��ġ ����
            prevStarsX[i] = starsX[i];
            prevStarsY[i] = starsY[i];

            // �� ���� ��ġ�� ������Ʈ (���� ����)
            // cos(), sin()�ȿ� ������ �����̴�. 
            starsX[i] += cos(i) * speeds[i];
            starsY[i] += sin(i) * speeds[i];

            // �ܻ��� ���� ���� ��ġ�� ���� ��´�
            if (prevStarsX[i] >= 0 && prevStarsX[i] < width && prevStarsY[i] >= 0 && prevStarsY[i] < height)
            {
                gotoxy((int)prevStarsX[i], (int)prevStarsY[i]);
                std::cout << ".";
            }

            // ���� ���� ��ġ�� ���� �׸���
            if (starsX[i] >= 0 && starsX[i] < width && starsY[i] >= 0 && starsY[i] < height)
            {
                gotoxy((int)starsX[i], (int)starsY[i]);
                std::cout << "*";
            }

            else
            {
                // ���� ȭ�� ������ ������ �ٽ� �߾ӿ��� ����
                starsX[i] = centerX;
                starsY[i] = centerY;
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // �÷��̾� �⺻���� ���� �ǰ�
        for (auto& p : BossStagePlayerProjectpool.getAll())
        {
            for (auto& e : enemyPoolBoss.getAll())
            {
                if (e.active && p.active1)
                {
                    // ���� �ǰ�
                    // ���� ���Ʈ
                    if (p.x1 * 3 + 1 >= e.x * 3 && p.x1 * 3 + 1 <= e.x * 3 + 20 && p.y1 < e.y + 5) // ���״� ���� ++�ذ�!
                    {
                        // cout << "!@#!@#@!#!@#!" << endl;
                        e.takeDamage(p.damage);
                        p.active1 = false;
                        player.score += 100;

                        //player.upgrade();
                    }
                    // ������ ���Ʈ
                    if (p.x2 * 3 + 35 >= e.x * 3 && p.x2 * 3 + 35 <= e.x * 3 + 20 && p.y1 < e.y + 10)
                    {
                        e.takeDamage(p.damage);
                        p.active1 = false;
                        player.score += 100;
                        //player.upgrade();
                    }
                }
            }
        }

        // �÷��̾� ��ų ���� �ǰ� 
        // �÷��̾� ��ų �÷��̾� �������Ҹ�

        for (auto& p : BSPlayerSkillPool.getAll())
        {
            for (auto& e : enemyPoolBoss.getAll())
            {
                if (e.active && p.active_s && player.health > 1)
                {
                    if (p.xs * 3 + 17 >= e.x * 3 && p.xs * 3 + 17 <= e.x * 3 + 35 && p.ys < e.y + 5)
                    {
                        e.takeDamage(p.damage);
                        p.active_s = false;
                        player.score += 2000;
                    }

                }
            }
        }

        // ���� �Ѿ� �߻�
        for (auto& e : enemyPoolBoss.getAll())
        {
            if (e.shouldShoot())
            {
                auto ep = AsteroidPool1.get();
                if (ep)
                {
                    ep->b_x = e.x * 3 + 13 + rand() % 10;
                    ep->b_y = e.y + 14;
                    ep->damage = 1;
                    // ep->isEnemy = true;
                    ep->trackPlayer(player.x, player.y); // �÷��̾ �����ϵ��� ����
                }
                e.resetShootTimer();
            }
        }


        // ���� �Ѿ� �߻� ������Ʈ
        AsteroidPool1.draw();
        AsteroidPool1.update();


        // ���� �Ѿ˰� �÷��̾� �浹 ó��
        for (auto& p : AsteroidPool1.getAll())
        {
            if (p.active && p.b_x >= player.x * 3.f + 5.f && p.b_x <= player.x * 3.f + 30.f && p.b_y > player.y - 1 && p.b_y < player.y + 3)
            {
                player.takeDamage(p.damage);
                p.active = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // UI
        gotoxy(width + 2, 5);
        std::cout << "Energy : " << player.health;
        for (int i = 0; i < player.health; i++)
        {
            gotoxy(width + 2+(i*2), 6);
            TextColor(10, 10);
            std::cout << "  ";
            TextColor(15, 0);
        }

        gotoxy(width + 2, 10);
        std::cout << "Score : " << player.score;

        gotoxy(width + 2, 15);
        std::cout << "Damage : " << "5";

        /*gotoxy(width + 2, 17);
        std::cout << "player x,y : " << player.x << player.y;*/
        /*gotoxy(width + 2, 18);
        for (auto& e : enemyPoolBoss.getAll())
        {
            std::cout << "���� x,y : " << h;
        }*/

        gotoxy(width + 2, 20);
        std::cout << "Time : ";
        gotoxy(width + 2, 21);
        sw.print_elapsed();

        gotoxy(width + 2, 22);
        for (auto& e : enemyPoolBoss.getAll())
        {
            std::cout << "Boss : " << e.health;
            if (e.health <= 0)
            {
                sw.stop();
                system("cls");
                gotoxy(0, 15);
                Conpleted();
                Scoring();
                
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                exit(0);
            }
        }
        // ����ü�� �׷���
        gotoxy(width + 2, 23);
        for (auto& e : enemyPoolBoss.getAll())
        {

            for (int i = 0; i < e.health / 300; i++)
            {
                TextColor(4, 4);
                std::cout << "��";
                TextColor(15, 0);
            }
            TextColor(15, 0);
        }

        // �÷��̾�
        player.BossStagePlayerDraw();
        // ����
        enemyPoolBoss.draw();

        if (true)
        {
            auto e = enemyPoolBoss.get();
            if (e)
            {
                e->x = 25;
                e->y = 2;
            }
        }

        // �Ѿ� ��������
        // projectilePool.draw(); 

        /////////////////////////////////////////////
        // ������������ �÷��̾� ����
        processInput_BOSS_STAGE();

        // �÷��̾� ��ų�߰�
        if (player.health > 1)
        {
            BSPlayerSkillPool.draw();
            BSPlayerSkillPool.update();
        }

        // ���� ������
        enemyPoolBoss.update();
        // �÷��̾� �Ѿ� �߰�
        BossStagePlayerProjectpool.update();
        BossStagePlayerProjectpool.draw();

        Sleep(16);  // �ִϸ��̼� �ӵ� ����
    }
}

// ������� �Լ�
void Scoring() 
{
    std::string name;
    int Score = player.score;
    StopBgm(); // �뷡 ����

    // �ֿܼ� �̸� �Է� ��û
    gotoxy(0, 32);
    TextColor(2, 0);
    cout << "                                                                                                                                  ____________________________________________________________________________ " << endl;
    cout << "                                                                                                                                  %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x% " << endl;
    cout << "                                                                                                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                                                                T - 65B  Mission Completed     " << endl;
    cout << "                                                                                                                                                                             --------------------------------- " << endl;
    cout << "                                                                                                                                                                                        (Rebel Alliance)       " << endl;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                     Name : ";
    cin >> name;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                     Time :     ";
    sw.print_elapsed();
    cout << endl;
    cout << "                                                                                                                                     Score :    " << player.score << endl;
    cout << "                                                                                                                                                                                                               " << endl;
     
    gotoxy(0, 46);
    cout << "                                                                                                                                  ____________________________________________________________________________ " << endl;
    cout << "                                                                                                                                  %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x% " << endl;
    cout << "                                                                                                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

    
    // ���丮 ���� (�̹� �����ص� ���� �߻����� ����)
    std::filesystem::create_directory("Save");

    // ���� ���� �Ǵ� ����
    std::ofstream ofs("Save/ranking.rnk", std::ios::app);
    if (!ofs) 
    {
        ofs.open("Save/ranking.rnk", std::ios::out);
    }

    // ���Ͽ� �̸��� �ð��� ���
    ofs << name << " " << Score << std::endl;

    // ���� �ݱ�
    ofs.close();

    // ���� �Ϸ� �޽���
    gotoxy(190, 45);
    std::cout << "Save Completed!" << std::endl;
    TextColor(15, 0);
}