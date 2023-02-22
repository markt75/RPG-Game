#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Area.h"
#include "Boss.h"

enum Move {rock, paper, scissors, none};
enum Outcome {win, lose, draw};
class BattleState : public State {
    private: 
        ofImage stage;
        Player *player;
        Enemy *enemy;
        Boss *boss; 
        Move choice = Move::none;
        Outcome outcome = Outcome::draw;
        int enemyChoice = 0;
        int bossChoice = 0; 
        ofSoundPlayer buttonChange;
        ofSoundPlayer buttonSelect;
        ofImage button1;
        ofImage button2;
        ofImage button3;
        ofImage result1;
        ofImage result2;
        ofImage result3;
        int currentButton;
        int maxPlayerHealth;
        int maxEnemyHealth;
        int maxBossHealth;
        int resultTimer;
        bool canInteract;
        bool bossFirstPhase = false;    
        bool bossFight;
        //Added state property to represent when game is unpaused (pausedState = 1 by default) or paused (pausedState = -1)
        int pausedState = 1;

    public:
        BattleState(Player *player, Area *area);
        void tick();
        void render();
        void startBattle(Enemy *enemy);
        void renderHealthBar();
        void renderOutcome();
        void renderPauseScreen();
        void setEnemy(Enemy *enemy) {this-> enemy = enemy;};
        Enemy* getEnemy() {return enemy;};
        Boss* getBoss() { return boss; }    
        void setBoss(Boss *boss) { this-> boss = boss; }    
        void startBossBattle(Boss *boss);
        void setStage(ofImage stage) {this-> stage = stage;};
        void keyPressed(int key);
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);
        void reset();
        void resetPlayer();
        int getPausedState() {return pausedState;};
        void setPausedState(int pausedState) {this->pausedState = pausedState;};
        int getCurrentPlayerHealth() {return maxPlayerHealth;};

};