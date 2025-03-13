#pragma once
#include <vector>
#include "Projectile.h"

// Normal Stage Projectile pool
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
        for (Projectile& projectile : pool) 
        {
            if (!projectile.active) 
            {
                projectile.active = true;
                return &projectile;
            }
        }
        return nullptr;
    }

    void update() {
        for (Projectile& projectile : pool) 
        {
           projectile.update();
        }
    }

    void draw() {
        for (Projectile& projectile : pool) 
        {
           projectile.draw();
        }
    }

    std::vector<Projectile>& getAll() 
    {
        return pool;
    }
};

// Boss Attack
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
        for (Asteroid& asteroid : pool) 
        {
            if (!asteroid.active) 
            {
                asteroid.active = true;
                return &asteroid;
            }
        }
        return nullptr;
    }

    void update() 
    {
        for (Asteroid& asteroid : pool) 
        {
            asteroid.update();
        }
    }

    void draw() {
        for (Asteroid& asteroid : pool) 
        {
            asteroid.draw();
        }
    }

    std::vector<Asteroid>& getAll() 
    {
        return pool;
    }
};


// BossStagePlayerProjectilePool
class BossStagePlayerProjectilePool
{
    std::vector<BossStagePlayerProjectile> BossStagePlayerpool;

public:
    
    BossStagePlayerProjectilePool(int size)
    {
        BossStagePlayerpool.resize(size);
    }

    BossStagePlayerProjectile* get_player_projectile() 
    {
        for (BossStagePlayerProjectile& player_projectile : BossStagePlayerpool) 
        {
            if (!player_projectile.active1) 
            {
                player_projectile.active1 = true;
                return &player_projectile;
            }
        }
        return nullptr;
    }

    void update() 
    {
        for (BossStagePlayerProjectile& player_projectile : BossStagePlayerpool) 
        {
           player_projectile.update();
        }
    }

    void draw() 
    {
        for (BossStagePlayerProjectile& player_projectile : BossStagePlayerpool) 
        {
            player_projectile.draw();
        }
    }

    std::vector<BossStagePlayerProjectile>& getAll() 
    {
        return BossStagePlayerpool;
    }
};

// Boss Stage Player Skill
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
        for (BossStagePlayerSkill& player_skill : PlayerSkillPool)
        {
            if (!player_skill.active_s)
            {
                player_skill.active_s = true;
                return &player_skill;
            }
        }
        return nullptr;
    }

    void update() {
        for (BossStagePlayerSkill& player_skill : PlayerSkillPool)
        {
            player_skill.update();
        }
    }

    void draw() {
        for (BossStagePlayerSkill& player_skill : PlayerSkillPool)
        {
            player_skill.draw();
        }
    }

    std::vector<BossStagePlayerSkill>& getAll()
    {
        return PlayerSkillPool;
    }
};