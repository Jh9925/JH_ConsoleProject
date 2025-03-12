#pragma once
#include <vector>
#include "Enemy.h"

template <typename T>
class EnemyPool 
{
    std::vector<T> pool;
public:
    EnemyPool(int size) 
    {
        pool.resize(size);
    }

    T* get() 
    {
        for (auto& e : pool) 
        {
            if (!e.active) 
            {
                e.active = true;
                return &e;
            }
        }
        return nullptr;
    }

    void update() 
    {
        for (auto& e : pool) 
        {
            e.update();
        }
    }

    void draw() 
    {
        for (auto& e : pool) 
        {
            e.draw();
        }
    }

    std::vector<T>& getAll() 
    {
        return pool;
    }
};