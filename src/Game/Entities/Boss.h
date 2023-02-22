#pragma once

#include "Enemy.h"

class Boss : public Enemy {

    public:
        Boss(string id, int health, int baseDamage, string entityName, int ox, int oy) : Enemy(id, health, baseDamage, entityName, ox, oy){}
};