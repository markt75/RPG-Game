#pragma once

#include "State.h"
#include "Animation.h"

class TitleState : public State
{
    private:
        ofImage titleImage;
        Animation *titlescreen;
    public:
        TitleState();
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();
};