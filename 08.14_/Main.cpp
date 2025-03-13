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


const int WIDTH = 50;       // 게임 화면의 가로 크기
const int HEIGHT = 50;      // 게임 화면의 세로 크기
const int UI_WIDTH = 75;    // UI 영역을 포함한 전체 화면의 가로 크기

///////////////////////////////////////////////////
///// 보스스테이지
const int width = 150;  
const int height = 55; 
const int UI_width = 175;
const int centerX = width / 2;
const int centerY = height / 2;
///////////////////////////////////////////////////

int shootTimer = 0;        // 총알 발사 타이머
int enemySpawnTimer = 0;   // 적 생성 타이머
int playerShootTimer = 0;  // 플레이어 총알 발사 타이머 

int h = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들
void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void setConsoleSize(int width, int height);
void clearScreen();
void clearScreenbossStage(); // 보스 스테이지용

void Scoring();

EnemyPool<EnemyA> enemyPoolA(5);     // 적 최대 5마리
EnemyPool<EnemyB> enemyPoolB(5);     // 적 최대 5마리
EnemyPool<EnemyC> enemyPoolC(5);     // 적 최대 5마리
EnemyPool<Boss>   enemyPoolBoss(1);  // 보스 1 마리


// ProjectilePool Set
ProjectilePool projectilePool(100);  
BossStagePlayerProjectilePool BossStagePlayerProjectpool(200);
BossStagePlayerSkillPool BSPlayerSkillPool(100); 
AsteroidPool AsteroidPool1(100);

// Normal Stage  Input
void processInput();
// Boss Stage Input
void processInput_BOSS_STAGE();
// Normal Stage 게임 상황 업데이트 
void update();
// Normal Stage Draw
void draw();

int BackGround();

// Main
int main() 
{
    
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1; 
    c.bVisible = 0; //커서 숨기기
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);

    setConsoleSize(UI_WIDTH, HEIGHT + 5);
    srand(time(NULL));
    setcursor(0, 0);
    StartBgm();
    while (true)
    {
        Title();
        int i = 0;
        cin >> i;
        system("cls");
        switch (i)
        {
        case 1:
            StopBgm();
            normalStage(); // BGM
            while (true)
            {
                sw.start();
                processInput();
                update();
                draw();
                if (player.score > 5000)
                {
                    break;
                }
            }
            clearScreenbossStage();
            gotoxy(75, 30);
            std::cout << " 적 폭격기 출현!!!" << endl;
            StopBgm();
            BossStageBgm();  // 보스스테이지 BGM
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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

void clearScreenbossStage()
{

    gotoxy(0, 0);
    cout << string(UI_width + 100, ' ') << endl;
    for (int i = 1; i < height; i++)
    {
        gotoxy(0, i);
        cout << string(UI_width + 100, ' ') << endl;
    }
}

// Player Input
// Normal Stage
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
        Projectile* p = projectilePool.get();
        if (p)
        {
            p->x = player.x + 5;
            p->y = player.y;
            p->damage = player.GetDamage();
            p->isEnemy = false;
            playerShootTimer = 0;
        }
    }
}

// Player Input
// Boss Stage 
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
        if (player.x < 38)
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
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && playerShootTimer >= player.Shooting)
    {
        BossStagePlayerProjectile* get_playerpool = BossStagePlayerProjectpool.get_player_projectile();
        if (get_playerpool)
        {
            // Left Blaster
            get_playerpool->x1 = player.x;
            get_playerpool->y1 = player.y;
            // Right Blaster
            get_playerpool->x2 = player.x;
            get_playerpool->y2 = player.y;

            get_playerpool->damage = player.GetDamage();

            // p1->isEnemy = false;
            playerShootTimer = 0;
        }
    } 
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000)) // VK_CONTROL -> Special Attack
    {
        BossStagePlayerSkill* player_skill = BSPlayerSkillPool.get();
        if (player_skill && player.health > 1)
        {

            // Lazer Attack
            player_skill->xs = player.x;
            player_skill->ys = player.y;
            player_skill->damage = 10;
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
    if (player.score <= 5000)
    {
        enemySpawnTimer++;
        if (enemySpawnTimer >= 25)
        {
            int randomSpawn = rand() % 6;
            if (randomSpawn == 0 || randomSpawn == 3 || randomSpawn == 5)
            {
                EnemyA* EnemyA = enemyPoolA.get();
                if (EnemyA)
                {
                    EnemyA->x = rand() % (WIDTH - 2);
                    EnemyA->y = 2;
                }
            }
            if (randomSpawn == 1)
            {
                EnemyB* EnemyB = enemyPoolB.get();
                if (EnemyB)
                {
                    EnemyB->x = rand() % (WIDTH - 2);
                    EnemyB->y = 2;
                }
            }

            if (randomSpawn == 2 || randomSpawn == 4)
            {
                EnemyC* EnemyC = enemyPoolC.get();
                if (EnemyC)
                {
                    EnemyC->x = rand() % (WIDTH - 2);
                    EnemyC->y = 2;
                }
            }
            enemySpawnTimer = 0;
        }
    }

    // pool Update
    enemyPoolA.update();
    enemyPoolB.update();
    enemyPoolC.update();

    projectilePool.update();


    // Player Hit
    for (Projectile& p : projectilePool.getAll())
    {
        if (p.active && p.isEnemy && p.x >= player.x && p.x <= player.x + 7 && p.y == player.y)
        {
            player.TakeDamage(p.damage);
            p.active = false;
        }
    }


    // Enemy Attack
    for (Projectile& projectile : projectilePool.getAll())
    {
        if (projectile.active && !projectile.isEnemy)
        {
            for (EnemyA& e : enemyPoolA.getAll())
            {
                if (e.active && projectile.x >= e.x - 2 && projectile.x <= e.x + 2 && projectile.y < e.y + 3)
                {
                    e.takeDamage(projectile.damage);
                    projectile.active = false;
                    player.score += 100;
                    player.Upgrade();
                }
            }
            for (EnemyB& e : enemyPoolB.getAll())
            {
                if (e.active && projectile.x >= e.x - 2 && projectile.x <= e.x + 2 && projectile.y < e.y + 3)
                {
                    e.takeDamage(projectile.damage);
                    projectile.active = false;
                    player.score += 200;
                    player.Upgrade();
                }
            }
            for (EnemyC& e : enemyPoolC.getAll())
            {
                if (e.active && projectile.x >= e.x && projectile.x <= e.x + 2 && projectile.y == e.y)
                {
                    e.takeDamage(projectile.damage);
                    projectile.active = false;
                    player.score += 150;
                    player.Upgrade();
                }
            }
        }
    }

    // Enemy Attack
    for (EnemyA& e : enemyPoolA.getAll())
    {
        if (e.shouldShoot())
        {
            Projectile* EnemyA_Projectile = projectilePool.get();
            if (EnemyA_Projectile)
            {
                EnemyA_Projectile->x = e.x + 1;
                EnemyA_Projectile->y = e.y + 1;
                EnemyA_Projectile->damage = e.damage;
                EnemyA_Projectile->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (EnemyB& e : enemyPoolB.getAll())
    {
        if (e.shouldShoot())
        {
            Projectile* EnemyB_Projectile = projectilePool.get();
            if (EnemyB_Projectile)
            {
                EnemyB_Projectile->x = e.x + 1;
                EnemyB_Projectile->y = e.y + 1;
                EnemyB_Projectile->damage = e.damage;
                EnemyB_Projectile->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (EnemyC& e : enemyPoolC.getAll())
    {
        if (e.shouldShoot())
        {
            Projectile* EnemyC_Projectile = projectilePool.get();
            if (EnemyC_Projectile)
            {
                EnemyC_Projectile->x = e.x + 1;
                EnemyC_Projectile->y = e.y + 1;
                EnemyC_Projectile->damage = e.damage;
                EnemyC_Projectile->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }
}

void draw()
{
    clearScreen();
    setcursor(0, 0);

    // Normal Stage
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


    gotoxy(WIDTH + 2, 5);
    std::cout << "Energy : " << player.health;
    gotoxy(WIDTH + 2, 6);

    for (int i = 0; i < player.health; i++)
    {
        TextColor(10, 0);
        cout << "";
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
    projectilePool.draw();
    
    Sleep(32);
}

// BossStage
int BackGround()
{
    const int numStars = 40;

    float starsX[numStars];
    float starsY[numStars];

    float prevStarsX[numStars];
    float prevStarsY[numStars];
    float speeds[numStars];

    // BackGround Star Set
    for (int i = 0; i < numStars; ++i)
    {
        starsX[i] = centerX;
        starsY[i] = centerY;
        prevStarsX[i] = centerX;
        prevStarsY[i] = centerY;
        speeds[i] = (float)(rand() % 5 + 1) / 2.0f;
    }
    while (true)
    {
        clearScreenbossStage();

        // BossStage OutLine
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
        
        // Star Draw
        for (int i = 0; i < numStars; ++i)
        {
            prevStarsX[i] = starsX[i];
            prevStarsY[i] = starsY[i];
            starsX[i] += cos(i) * speeds[i];
            starsY[i] += sin(i) * speeds[i];
            if (prevStarsX[i] >= 0 && prevStarsX[i] < width && prevStarsY[i] >= 0 && prevStarsY[i] < height)
            {
                gotoxy((int)prevStarsX[i], (int)prevStarsY[i]);
                std::cout << ".";
            }
            if (starsX[i] >= 0 && starsX[i] < width && starsY[i] >= 0 && starsY[i] < height)
            {
                gotoxy((int)starsX[i], (int)starsY[i]);
                std::cout << "*";
            }
            else
            {
                starsX[i] = centerX;
                starsY[i] = centerY;
            }
        }

        // player Attack -> Boss Hit
        for (BossStagePlayerProjectile& PlayerProjectile : BossStagePlayerProjectpool.getAll())
        {
            for (Boss& boss : enemyPoolBoss.getAll())
            {
                if (boss.active && PlayerProjectile.active1)
                {
                    if (PlayerProjectile.x1 * 3 + 1 >= boss.x * 3 && PlayerProjectile.x1 * 3 + 1 <= boss.x * 3 + 20 && PlayerProjectile.y1 < boss.y + 5)
                    {
                        boss.takeDamage(PlayerProjectile.damage);
                        PlayerProjectile.active1 = false;
                        player.score += 100;
                    }
                    if (PlayerProjectile.x2 * 3 + 35 >= boss.x * 3 && PlayerProjectile.x2 * 3 + 35 <= boss.x * 3 + 20 && PlayerProjectile.y1 < boss.y + 10)
                    {
                        boss.takeDamage(PlayerProjectile.damage);
                        PlayerProjectile.active1 = false;
                        player.score += 100;
                    }
                }
            }
        }
        for (BossStagePlayerSkill& p : BSPlayerSkillPool.getAll())
        {
            for (Boss& boss : enemyPoolBoss.getAll())
            {
                if (boss.active && p.active_s && player.health > 1)
                {
                    if (p.xs * 3 + 17 >= boss.x * 3 && p.xs * 3 + 17 <= boss.x * 3 + 35 && p.ys < boss.y + 5)
                    {
                        boss.takeDamage(p.damage);
                        p.active_s = false;
                        player.score += 2000;
                    }
                }
            }
        }
        
        for (Boss& boss : enemyPoolBoss.getAll())
        {
            if (boss.shouldShoot())
            {
                Asteroid* BossProjectile = AsteroidPool1.get();
                if (BossProjectile)
                {
                    BossProjectile->b_x = boss.x * 3 + 13 + rand() % 10;
                    BossProjectile->b_y = boss.y + 14;
                    BossProjectile->damage = 1;
                    BossProjectile->trackPlayer(player.x, player.y); // trackPlayer
                }
                boss.resetShootTimer();
            }
        }


        // Boss Attack Update
        AsteroidPool1.draw();
        AsteroidPool1.update();


        // BossProjectile -> Player Hit
        for (Asteroid& asteroid : AsteroidPool1.getAll())
        {
            if (asteroid.active && asteroid.b_x >= player.x * 3.f + 5.f && asteroid.b_x <= player.x * 3.f + 30.f && asteroid.b_y > player.y - 1 && asteroid.b_y < player.y + 3)
            {
                player.TakeDamage(asteroid.damage);
                asteroid.active = false;
            }
        }
        
        // UI
        gotoxy(width + 2, 5);
        std::cout << "Energy : " << player.health;
        for (int i = 0; i < player.health; i++)
        {
            gotoxy(width + 2+(i*2), 6);
            TextColor(10, 10);
            std::cout << "@";
            TextColor(15, 0);
        }

        gotoxy(width + 2, 10);
        std::cout << "Score : " << player.score;

        gotoxy(width + 2, 15);
        std::cout << "Damage : " << "5";

        gotoxy(width + 2, 20);
        std::cout << "Time : ";
        gotoxy(width + 2, 21);
        sw.print_elapsed();

        gotoxy(width + 2, 22);
        for (Boss& boss : enemyPoolBoss.getAll())
        {
            std::cout << "Boss : " << boss.health;
            if (boss.health <= 0)
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
        // Boss HP
        gotoxy(width + 2, 23);
        for (Boss& boss : enemyPoolBoss.getAll())
        {
            for (int i = 0; i < boss.health / 300; i++)
            {
                TextColor(4, 4);
                std::cout << "@";
                TextColor(15, 0);
            }
            TextColor(15, 0);
        }

        // Player Draw
        player.BossStagePlayerDraw();
        // Boss Draw
        enemyPoolBoss.draw();
        if (true)
        {
            Boss* boss = enemyPoolBoss.get();
            if (boss)
            {
                boss->x = 25;
                boss->y = 2;
            }
        }
        // Input Change
        processInput_BOSS_STAGE();
        
        if (player.health > 1)
        {
            BSPlayerSkillPool.draw();
            BSPlayerSkillPool.update();
        }

        // Boss Move
        enemyPoolBoss.update();
        // Boss Stage Player Projectile
        BossStagePlayerProjectpool.update();
        BossStagePlayerProjectpool.draw();

        Sleep(16);
    }
}

void Scoring() 
{
    std::string name;
    int Score = player.score;
    StopBgm();
    
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

    
    // Create Directory
    std::filesystem::create_directory("Save");

    // ofstream Set
    std::ofstream ofs("Save/ranking.rnk", std::ios::app);
    if (!ofs) 
    {
        ofs.open("Save/ranking.rnk", std::ios::out);
    }
    ofs << name << " " << Score << std::endl;
    ofs.close();
    gotoxy(190, 45);
    std::cout << "Save Completed!" << std::endl;
    TextColor(15, 0);
}