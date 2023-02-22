#pragma once

#include "Player.h"
#include "Friendly.h"
#include "Enemy.h"
#include "OverworldCamera.h"
#include "StaticEntities.h"
#include "Boss.h"

class Area 
{
    private:
        ofImage areaImage;
        ofSoundPlayer areaMusic;
        ofImage areaStage;
        ofPoint entrancePosition;
        std::vector<Enemy*> enemies;
        Area *nextArea;
        StaticEntities *object;
        vector<StaticEntities*> objects; 
        Boss *boss; 
        Friendly *friendly;
        string areaName;

    public:
        Area(Area *nextArea, string areaName, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy*> enemies, vector<StaticEntities*> trees, Boss* boss, Friendly* friendly);
        void resetEnemies();
        ofImage getImage() { return areaImage;};
        ofSoundPlayer getMusic() { return areaMusic;};
        ofImage getStage() { return areaStage;};
        ofPoint getEntrancePos() { return entrancePosition;};
        void setEnemies(std::vector<Enemy*> enemies) { this->enemies = enemies;};
        vector<Enemy*> getEnemies() { return enemies;};
        int getRemainingEnemies();
        Area* getNextArea() { return nextArea;};
        vector<StaticEntities*> getObjects() { return objects; };
        StaticEntities* getObject() { return object; };
        Boss* getBoss() { return boss; };
        Friendly* getFriendly() { return friendly; };
        void setAreaName(string areaName) {this->areaName = areaName;};
        string getAreaName() {return areaName;};        

};