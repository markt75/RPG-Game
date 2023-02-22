#include "OverworldState.h"
#include "BattleState.h"

OverworldState::OverworldState(Player *player, Area *area)
{
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
    music.setVolume(0.25);
    music.setLoop(true);
}

void OverworldState::loadArea(Area *area)
{
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}

void OverworldState::tick()
{
    setFriendly(area->getFriendly());
    if (getPausedState() > 0)
    {
        player->tickOverworld();
        friendly->tickOverworld();

        for (unsigned int i = 0; i < area->getEnemies().size(); i++)
        {
            if (!area->getEnemies().at(i)->isDead())
            { 
                area->getEnemies().at(i)->tickOverworld();
                if (player->collides(area->getEnemies().at(i)))
                {
                    setBossFight(false); 
                    setEnemy(area->getEnemies().at(i));
                    setNextState("Loading2");
                    setFinished(true);
                }
            }
        }
        camera->tick();

        // Decreases dialogue counter when activated
        if (player->collides(area->getFriendly()) && interact)
        {
            collision = true;
            timer--;
        }
        else
        {
            collision = false;
        }

        if (area->getRemainingEnemies() == 0)
        {
            if (!area->getBoss()->isDead())
            {
                area->getBoss()->tickOverworld();
                if (player->collides(area->getBoss()))
                {
                    setBossFight(true);     
                    setBoss(area->getBoss());
                    setNextState("Battle");
                    setFinished(true);
                }
                
            }
        }

        // Makes player not pass through static objects
        for (unsigned int i = 0; i < area->getObjects().size(); i++)
        {
            if (player->collides(area->getObjects().at(i)) && player->getDirection() == Direction::left){
                player->setOX(player->getOX() + player->getSpeed());
            }
            if (player->collides(area->getObjects().at(i)) && player->getDirection() == Direction::right){
                player->setOX(player->getOX() - player->getSpeed());
            }
            if (player->collides(area->getObjects().at(i)) && player->getDirection() == Direction::up){
                player->setOY(player->getOY() + player->getSpeed());
            }
            if (player->collides(area->getObjects().at(i)) && player->getDirection() == Direction::down){
                player->setOY(player->getOY() - player->getSpeed());
            }
        }
    }
}

void OverworldState::render()
{
    ofImage screen;
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->renderOverworld();

    renderHUD();

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())    // Enemies
        {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->renderOverworld();
        }
        
         if (area->getRemainingEnemies() == 0)      // Boss
         {
            int playerDistanceX = area->getBoss()->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getBoss()->getOY() - camera->getPlayerY();
            area->getBoss()->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getBoss()->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getBoss()->renderOverworld();
        }

    }
    // Fiend (npc)
    int playerDistanceX = area->getFriendly()->getOX() - camera->getPlayerX();
    int playerDistanceY = area->getFriendly()->getOY() - camera->getPlayerY();
    area->getFriendly()->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
    area->getFriendly()->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
    area->getFriendly()->renderOverworld();

    // Static Objects
    for (unsigned int i = 0; i < area->getObjects().size(); i++)
    {
        int playerdistanceX = area->getObjects().at(i)->getOX() - camera->getPlayerX();
        int playerdistanceY = area->getObjects().at(i)->getOY() - camera->getPlayerY();
        area->getObjects().at(i)->setRenderX(camera->getDimensionX() / 2 + playerdistanceX);
        area->getObjects().at(i)->setRenderY(camera->getDimensionY() / 2 + playerdistanceY);
        area->getObjects().at(i)->renderOverworld();
    }
    //Displays screen indicating that game is paused
    if(getPausedState() < 0){

        screen.load("images/ui/pauseScreen.png");
        screen.draw(100, 100, ofGetWidth()-200, ofGetHeight()-200);
    }
    //Displays npc dialogue
    if (interact && collision && timer >= 0){
        friendly->friendInteract();
    }

}

void OverworldState::renderHUD(){

    ofTrueTypeFont font1;
    ofImage healthbar;
    healthbar.load("images/ui/healthbar2.png");
    healthbar.draw(10, -25, 100, 100);

    for (int i = 0; i < 3; i++)
    {
        double playerHealthRatio = (double)player->getHealth() / 100.0;
        
        if (playerHealthRatio < 0)
        {
            playerHealthRatio = 0;
        }
        else if (playerHealthRatio < 0.33)
        {
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        }
        else if (playerHealthRatio < 0.66)
        {
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        }
        else
        {
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);
        } 
        ofDrawRectangle(33, 21 + i * 2, (int)(15 * playerHealthRatio) * 5, 2);

    }
    ofFill();

    ofSetColor(0,0,0);
    font1.load("font1.ttf", 10);
    font1.drawString("ENEMIES REMAINING:", 10, ofGetHeight()-10);
    font1.drawString(to_string(area->getRemainingEnemies()), 220, ofGetHeight()-10);
    font1.drawString("CURRENT AREA: ", 350, ofGetHeight()-10);
    font1.drawString(area->getAreaName(), 510, ofGetHeight()-10);

    ofSetColor(255,255,255);

}

void OverworldState::keyPressed(int key)
{
    player->keyPressed(key);

    if (key == 'r')
    {
        area->resetEnemies();
    }

    if (key == 'p')
    {
        setPausedState(-1 * getPausedState());
    }

    if (key == 'e'){
        on_off++;

        if (on_off == 1){
            interact = true;
            timer = 30;
        }
        
        if (on_off == 2){
            interact = false;
            timer = 0;
            on_off = 0;
        }
    }
}

void OverworldState::keyReleased(int key)
{
    player->keyReleased(key);
}

void OverworldState::mousePressed(int x, int y, int button)
{
}

void OverworldState::reset()
{
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}