#pragma once

#include "State.h"
#include "Area.h"
#include "Animation.h"

class LoadingState : public State{

    private:

        ofImage loadingImage;

        Animation *loadingScreen;

        string nState;

    public:

        LoadingState(string nState);
        void setNState(string nState) {this->nState = nState;}
        string getNState() {return nState;}
        int counter = 0;
        int multiplyer = 1;
        void tick();
        void render();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void reset();

};