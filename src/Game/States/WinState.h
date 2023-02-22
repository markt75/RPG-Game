#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"

class WinState : public State
{
    private:
        Player *player;
        Enemy *enemy;
        ofImage screen;

    public:
        WinState();
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();
};