#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"

class EndGameState : public State
{
    private:
        Player *player;
        Enemy *enemy;
        ofImage loseScreen;
        ofImage winScreen;
        bool win;

    public:
        EndGameState();
        bool getWin() { return win; };
        void setWin(bool winning) { this->win = winning; };
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();
};