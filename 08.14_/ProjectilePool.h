#pragma once
#include <vector>
#include "Projectile.h"

// �Ϲݽ������� �÷��̾� �� �Ѿ� Ǯ
class ProjectilePool 
{
    std::vector<Projectile> pool;
public:
    ProjectilePool(int size) 
    {
        pool.resize(size);
    }

    Projectile* get() 
    {
        for (auto& p : pool) 
        {
            if (!p.active) 
            {
                p.active = true;
                return &p;
            }
        }
        return nullptr;
    }

    void update() {
        for (auto& p : pool) 
        {
            p.update();
        }
    }

    void draw() {
        for (auto& p : pool) 
        {
            p.draw();
        }
    }

    std::vector<Projectile>& getAll() 
    {
        return pool;
    }
};

/// <summary>
/// ///////////////////////////////////////////////////////////
/// </summary>
/// ���� �߻� �Ѿ�
class AsteroidPool
{
    std::vector<Asteroid> pool;
public:
    AsteroidPool(int size) 
    {
        pool.resize(size);
    }

    Asteroid* get() 
    {
        for (auto& p : pool) 
        {
            if (!p.active) 
            {
                p.active = true;
                return &p;
            }
        }
        return nullptr;
    }

    void update() 
    {
        for (auto& p : pool) 
        {
            p.update();
        }
    }

    void draw() {
        for (auto& p : pool) 
        {
            p.draw();
        }
    }

    std::vector<Asteroid>& getAll() 
    {
        return pool;
    }
};


// ������������ �÷��̾� �Ѿ� Ǯ
class BossStagePlayerProjectilePool
{
    std::vector<BossStagePlayerProjectile> BossStagePlayerpool;

public:
    
    BossStagePlayerProjectilePool(int size)
    {
        BossStagePlayerpool.resize(size);
    }

    BossStagePlayerProjectile* get1() 
    {
        for (auto& p : BossStagePlayerpool) 
        {
            if (!p.active1) 
            {
                p.active1 = true;
                return &p;
            }
        }
        return nullptr;
    }

    void update() 
    {
        for (auto& p : BossStagePlayerpool) 
        {
            p.update();
        }
    }

    void draw() 
    {
        for (auto& p : BossStagePlayerpool) 
        {
            p.draw();
        }
    }

    std::vector<BossStagePlayerProjectile>& getAll() 
    {
        return BossStagePlayerpool;
    }
};

// ������������ �÷��̾� ��ų
// �÷��̾��� �������� ������ �߻� ��� �߰� �ؾߵ�
class BossStagePlayerSkillPool
{
    std::vector<BossStagePlayerSkill> PlayerSkillPool;

public:

    BossStagePlayerSkillPool(int size)
    {
        PlayerSkillPool.resize(size);
    }

    BossStagePlayerSkill* get()
    {
        for (auto& p1 : PlayerSkillPool)
        {
            if (!p1.active_s)
            {
                p1.active_s = true;
                return &p1;
            }
        }
        return nullptr;
    }

    void update() {
        for (auto& p : PlayerSkillPool)
        {
            p.update();
        }
    }

    void draw() {
        for (auto& p : PlayerSkillPool)
        {
            p.draw();
        }
    }

    std::vector<BossStagePlayerSkill>& getAll()
    {
        return PlayerSkillPool;
    }
};