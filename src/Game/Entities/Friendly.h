#pragma once

#include "DynamicEntities.h"
#include "Entity.h" 
#include "Animation.h"

class Friendly : public Entity {
    private:
        Direction direction = Direction::down;      
        int renderX = 1000;
        int renderY = 1000;
        string id;
        int moveTimer;
        string entityName;
        ofImage sprite;
        ofImage dialogue;

        int speed = 8; 
        bool walking = false;       
        Animation *walkUp;      
        Animation *walkDown;   
        Animation *walkLeft;    
        Animation *walkRight;   
    
    public:
        Friendly(string id, string entityName, int ox, int oy);
        ~Friendly();
        int getOX() { return ox; };
        int getOY() { return oy; };
        void setRenderX(int x){ renderX = x; };
        void setRenderY(int y){ renderY = y; };
        void tickOverworld();
        void friendInteract();    
        void renderOverworld();     
        void keyPressed(int key);
        void keyReleased(int key);
        void reset();
        string getId(){ return id; };
        int counter = 0;
};