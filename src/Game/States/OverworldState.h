#pragma once

#include "State.h"
#include "Area.h"
#include "Player.h"
#include "Enemy.h"
#include "Friendly.h"
#include "OverworldCamera.h"
#include "Boss.h"

class OverworldState : public State
{
    private:
        ofImage overworldImage;
        Player *player;
        Friendly *friendly;
        OverworldCamera *camera;
        Area *area;
        std::vector<Enemy*> enemies;
        Enemy *enemy;
        Boss *boss; 
        bool bossFight = false; 
        int pausedState = 1;
        bool interact = false, collision = false;
        int timer, on_off = 0;
        
    public:
        OverworldState(Player *player, Area *area);
        Player* getPlayer() { return player;};
        Friendly* getFriendly() {return friendly;};
        void setFriendly(Friendly *friendly) {this->friendly = friendly;};
        void setEnemy(Enemy *enemy) { this->enemy = enemy;};
        Enemy* getEnemy() { return enemy;};
        void loadArea(Area *Area);
        Area* getArea() { return area;};
        Boss* getBoss() { return boss; }   
        void setBoss(Boss *boss) { this->boss = boss; } 
        void tick();
        void render();
        void renderHUD();
        void keyPressed(int key);
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);
        void reset();
        bool getBossFight() { return bossFight; }   
        void setBossFight(bool bossFight) { this->bossFight = bossFight; }
        int getPausedState() {return pausedState;};
        void setPausedState(int pausedState){ this->pausedState = pausedState;};
        
};