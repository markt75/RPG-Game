#pragma once

#include "DynamicEntities.h"
#include "Entity.h" 
#include "Animation.h"

#define INIT_X 100
#define INIT_Y 100
#define CENTER_X 288
#define CENTER_Y 208

#define OXDIMENSION 2688
#define OYDIMENSION 2560


class Player : public DynamicEntities {
    private:
        Direction direction = Direction::up;   
        vector<char> pressedKeys;
    
    public:
        Player(int health, int baseDamage);
        ~Player();
        void tickOverworld();
        void tickFighting();    
        void renderOverworld();     
        void keyPressed(int key);
        void keyReleased(int key);
        void reset();
        Direction getDirection() { return direction; }
};