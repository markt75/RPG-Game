#pragma once
#include "ofMain.h"                         // Refactor to only have OW coordinates, sprites attributes, ticking and rendering.
class Entity {
    protected:
        // Overworld Coordinates and dimensions
        int ox, oy, ow, oh;
        ofImage overworldSprite;

    public:
        Entity(int ox, int oy, int ow, int oh, string overworldPath);
        virtual void renderOverworld();
        int getOX() { return ox; };
        int getOY() { return oy; };
        int getOW() { return ow; };
        int getOH() { return oh; };
        ofRectangle getBounds();
        ofRectangle getBounds(int ox, int oy);
        void setOX(int ox) { this-> ox = ox; };
        void setOY(int oy) { this-> oy = oy; };
        bool collides(Entity* entity);
};