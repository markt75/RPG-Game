#include "DynamicEntities.h"
#include "Entity.h"

DynamicEntities::DynamicEntities(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health , int baseDamage, string fightingPath, string overworldPath) : Entity(ox, oy, ow, oh, overworldPath) {
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->health = health;
    this->baseDamage = baseDamage;

    fightingSprite.load(fightingPath);
}

void DynamicEntities::renderFighting() {
    fightingSprite.draw(fx, fy, fw, fh);
}
