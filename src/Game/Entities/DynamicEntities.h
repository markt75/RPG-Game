#pragma once

#include "Entity.h"
#include "Animation.h"

enum Direction {left, right, up, down};  

class DynamicEntities : public Entity {
    protected:
        int health;     
        int baseDamage;
        // Fighting coordinates and dimensions
        int fx, fy, fw, fh; 
        ofImage fightingSprite; 

        int speed = 8; 
        bool walking = false;       
        Animation *walkUp;      
        Animation *walkDown;   
        Animation *walkLeft;    
        Animation *walkRight;   
        Animation *fighting; 
    
    public:
        DynamicEntities(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health , int baseDamage, string fightingPath, string overworldPath);
        virtual void tickFighting() = 0;
        virtual void renderFighting();
        virtual void tickOverworld() = 0;
        int getHealth() { return health; };
        void setHealth(int health) { this->health = health; };     
        int getDmg() { return baseDamage; };    
        void setDmg(int baseDamage) { this->baseDamage = baseDamage; };
        int getSpeed() { return speed; };
        void setSpeed(int speed) { this->speed = speed; }
        int const maxHealth = this->health;
};