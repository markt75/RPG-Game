#pragma once

#include "Entity.h"

class StaticEntities : public Entity {
    private:
        ofImage sprite;
        string overworldPath;
        int renderX = 1000;
        int renderY = 1000;

    
    public:
        StaticEntities(int ox, int oy, string overworldPath);
        void renderOverworld();
        void setRenderX(int x){ renderX = x; };
        void setRenderY(int y){ renderY = y; };
        int getOX() { return ox; };
        int getOY() { return oy; };


};