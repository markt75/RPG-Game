#pragma once

#include "DynamicEntities.h"
#include "Entity.h" 
#include "Animation.h"

class Enemy : public DynamicEntities {
    private:
        Direction direction = Direction::down;      
        int renderX = 1000;
        int renderY = 1000;
        string id;
        int moveTimer;
        bool dead = false;
        string entityName;
        ofImage sprite; 

    
    public:
        Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy);
        ~Enemy();
        int getOX() { return ox; };
        int getOY() { return oy; };
        bool isDead() { return dead;};
        void kill() { this->dead = true;};
        void revive() { this->dead = false;};
        void setRenderX(int x){ renderX = x; };
        void setRenderY(int y){ renderY = y; };
        void tickOverworld();
        void tickFighting();    
        void renderOverworld();     
        void keyPressed(int key);
        void keyReleased(int key);
        void reset();
        string getId(){ return id; };
        ofImage getSprite() { return overworldSprite;};
};