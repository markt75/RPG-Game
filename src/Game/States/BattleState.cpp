#include "BattleState.h"

BattleState::BattleState(Player *player, Area *area)
{
    stage = area->getStage();
    music.load("audio/battle.wav");
    music.setLoop(true);
    music.setVolume(0.25);
    buttonChange.load("audio/ui/beep.mp3");
    buttonChange.setVolume(0.5);
    buttonSelect.load("audio/ui/boop.mp3");
    buttonSelect.setVolume(0.5);
    this->player = player;
    currentButton = 1;
    resultTimer = 0;
    canInteract = true;
    maxPlayerHealth = player->getHealth();
    button1.load("images/ui/buttons/rock.png");
    button2.load("images/ui/buttons/paper.png");
    button3.load("images/ui/buttons/scissors.png");
    result1.load("images/ui/buttons/rock1.png");
    result2.load("images/ui/buttons/paper1.png");
    result3.load("images/ui/buttons/scissors1.png");
}

void BattleState::startBattle(Enemy *enemy)
{
    bossFight = false;
    this->enemy = enemy;
    maxEnemyHealth = enemy->getHealth();
}

void BattleState::startBossBattle(Boss *boss)
{
    bossFight = true;
    this->boss = boss;
    maxBossHealth = boss->getHealth();
}

void BattleState::tick()
{
    if (getPausedState() > 0)
    {
        if (canInteract)
        {
            if (player->getHealth() <= 0)
            {
                setNextState("End");
                setFinished(true);
                return;
            }

            if (bossFight == false)
            {
                if (enemy->getHealth() <= 0)
                {
                    setNextState("Win");
                    setFinished(true);
                    return;
                }
            }

            if (bossFight == true)
            {
                if (boss->getHealth() <= 0 && bossFirstPhase == true)  
                {
                    bossFirstPhase = false;
                    setNextState("Win");
                    setFinished(true);
                    return;   
                } 
            }
        }

        player->tickFighting();

        if (!bossFight) { enemy->tickFighting(); }

        if (bossFight) { boss->tickFighting(); }
    

        if (choice != Move::none && canInteract)
        {
            enemyChoice = rand() % 3 + 1;
            if (!bossFight)
            {
                if ((choice == Move::rock && enemyChoice == 2 ) || (choice == Move::paper && enemyChoice == 3 ) || (choice == Move::scissors && enemyChoice == 1 ))
                {
                    player->setHealth(player->getHealth() - enemy->getDmg()*2.0);
                    enemy->setHealth(enemy->getHealth() - player->getDmg()/2.0);

                    outcome = Outcome::lose;
                }
                else if ((choice == Move::rock && enemyChoice == 3 ) || (choice == Move::paper && enemyChoice == 1 ) || (choice == Move::scissors && enemyChoice == 2 ))
                {
                    player->setHealth(player->getHealth() - enemy->getDmg()/2.0);
                    enemy->setHealth(enemy->getHealth() - player->getDmg()*2.0);

                    outcome = Outcome::win;
                }
                else
                {
                    player->setHealth(player->getHealth() - enemy->getDmg());
                    enemy->setHealth(enemy->getHealth() - player->getDmg());

                    outcome = Outcome::draw;
                }
            }
            
            bossChoice = rand() % 3 + 1;
            if (bossFight)
            {
                if ((choice == Move::rock && bossChoice == 2) || (choice == Move::paper && bossChoice == 3) || (choice == Move::scissors && bossChoice == 1))
                {
                    player->setHealth(player->getHealth() - boss->getDmg()*2.0); 
                    boss->setHealth(boss->getHealth() - player->getDmg()/2.0); 

                    outcome = Outcome::lose;
                }
                else if ((choice == Move::rock && bossChoice == 3) || (choice == Move::paper && bossChoice == 1) || (choice == Move::scissors && bossChoice == 2))
                {
                    player->setHealth(player->getHealth() - boss->getDmg()/2.0);  
                    boss->setHealth(boss->getHealth() - player->getDmg()*2.0);

                    outcome = Outcome::win;
                }
                else
                {
                    player->setHealth(player->getHealth() - boss->getDmg());
                    boss->setHealth(boss->getHealth() - player->getDmg());

                    outcome = Outcome::draw;
                }
            }

            resultTimer = 30;
            canInteract = false;
        }

        if (bossFight)
        {
            if (boss->getHealth() <= 1 && bossFirstPhase == false){        
                boss->setHealth(maxBossHealth);
                boss->setDmg(boss->getDmg() + 2);
                bossFirstPhase = true;
            }
        }
    }
}

void BattleState::render()
{
    // render stage
    stage.draw(0, 0, ofGetWidth(), ofGetHeight());

    // render combatant sprites
    player->renderFighting();

    if (!bossFight) { enemy->renderFighting(); }

    if (bossFight) { boss->renderFighting(); }

    // render move buttons
    ofSetColor(180, 180, 180);
    if (currentButton == 1)
        ofSetColor(255, 255, 255);
    button1.draw(10 * 4, 84 * 4, 192, 192);
    ofSetColor(180, 180, 180);
    if (currentButton == 2)
        ofSetColor(255, 255, 255);
    button2.draw(56 * 4, 84 * 4, 192, 192);
    ofSetColor(180, 180, 180);
    if (currentButton == 3)
        ofSetColor(255, 255, 255);
    button3.draw(102 * 4, 84 * 4, 192, 192);
    ofSetColor(255, 255, 255);

    renderOutcome();

    renderHealthBar();

    renderPauseScreen();

    ofSetColor(255, 255, 255);
}

void BattleState::renderHealthBar()
{
    ofImage healthbar;
    healthbar.load("images/ui/healthbar.png");
    healthbar.draw(64, 64, 192, 192);
    healthbar.draw(384, 64, 192, 192);

    for (int i = 0; i < 3; i++)
    {
        double playerHealthRatio = (double)player->getHealth() / (double)maxPlayerHealth;
        double enemyHealthRatio = (double)enemy->getHealth() / (double)maxEnemyHealth;
        
        if (bossFight == true){
            double bossHealthRatio = (double)boss->getHealth() / (double)maxBossHealth;    

            if (bossHealthRatio < 0)
            { 
                bossHealthRatio = 0; 
            }
            else if (bossHealthRatio < 0.33)    
            {
                ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
            }
            else if (bossHealthRatio < 0.66 )     
            {
                ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
            }
            else
            {
                ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);
            }
            
            ofDrawRectangle(428, 152 + i * 4, (int)(36 * bossHealthRatio) * 4, 4);  
        }


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
        ofDrawRectangle(108, 152 + i * 4, (int)(36 * playerHealthRatio) * 4, 4);


        if (enemyHealthRatio < 0)
        {
            enemyHealthRatio = 0;
        }
        else if (enemyHealthRatio < 0.33)    
        {
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        }
        else if (enemyHealthRatio < 0.66 )     
        {
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        }
        else
        {
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);
        }
        ofDrawRectangle(428, 152 + i * 4, (int)(36 * enemyHealthRatio) * 4, 4);  

    }
    ofFill();
}

void BattleState::renderOutcome()
{
    if (resultTimer > 1)
    {
        resultTimer--;
        float posY = 60 * 4;
        float pposX = 64 * 4;
        float eposX = 80 * 4;
        float dim = 64;

        switch (outcome)
        {
        case Outcome::win:
            ofSetColor(100, 255, 100);
            if (choice == Move::rock)
                result1.draw(pposX, posY, dim, dim);
            if (choice == Move::paper)
                result2.draw(pposX, posY, dim, dim);
            if (choice == Move::scissors)
                result3.draw(pposX, posY, dim, dim);
            
            if (bossFight == false){
            ofSetColor(255, 100, 100);
            if (enemyChoice == 1)                       
                result1.draw(eposX, posY, dim, dim);
            if (enemyChoice == 2)    
                result2.draw(eposX, posY, dim, dim);
            if (enemyChoice == 3)    
                result3.draw(eposX, posY, dim, dim);
            }

            if (bossFight == true){ 
                ofSetColor(255, 100, 100);      
                if (bossChoice == 1)   
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)   
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)    
                    result3.draw(eposX, posY, dim, dim);
            }
            break;
        case Outcome::lose:
            ofSetColor(255, 100, 100);
            if (choice == Move::rock)
                result1.draw(pposX, posY, dim, dim);
            if (choice == Move::paper)
                result2.draw(pposX, posY, dim, dim);
            if (choice == Move::scissors)
                result3.draw(pposX, posY, dim, dim);
            
            if (bossFight == false){
            ofSetColor(100, 255, 100);
            if (enemyChoice == 1)    
                result1.draw(eposX, posY, dim, dim);
            if (enemyChoice == 2)    
                result2.draw(eposX, posY, dim, dim);
            if (enemyChoice == 3)    
                result3.draw(eposX, posY, dim, dim);
            }

            if (bossFight == true){
                ofSetColor(100, 255, 100);
                if (bossChoice == 1)   
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)   
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)    
                    result3.draw(eposX, posY, dim, dim);
            }
            break;
        case Outcome::draw:
            ofSetColor(200, 200, 100);
            if (choice == Move::rock)
                result1.draw(pposX, posY, dim, dim);
            if (choice == Move::paper)
                result2.draw(pposX, posY, dim, dim);
            if (choice == Move::scissors)
                result3.draw(pposX, posY, dim, dim);
            
            if (bossFight == false){
            if (enemyChoice == 1) 
                result1.draw(eposX, posY, dim, dim);
            if (enemyChoice == 2)    
                result2.draw(eposX, posY, dim, dim);    
            if (enemyChoice == 3)    
                result3.draw(eposX, posY, dim, dim);
            }

            if (bossFight == true){
                if (bossChoice == 1)   
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)   
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)    
                    result3.draw(eposX, posY, dim, dim);
            }
            break;
        }
        ofSetColor(255, 255, 255);
    }
    if (resultTimer == 1)
    {
        canInteract = true;
        choice = Move::none;
        resultTimer--;
    }
}
//Displays screen indicating that game is paused
void BattleState::renderPauseScreen(){
    if(getPausedState() < 0){

        ofImage screen;
        screen.load("images/ui/pauseScreen.png");
        screen.draw(100, 100, ofGetWidth()-200, ofGetHeight()-200);

    }
}

void BattleState::keyPressed(int key)
{
    if (canInteract)
    {
        if (key == OF_KEY_LEFT || key == 'a')
        {
            buttonChange.play();
            if (currentButton == 1)
            {
                currentButton = 3;
            }
            else
            {
                currentButton--;
            }
        }
        if (key == OF_KEY_RIGHT || key == 'd')
        {
            buttonChange.play();
            if (currentButton == 3)
            {
                currentButton = 1;
            }
            else
            {
                currentButton++;
            }
        }
        if (key == OF_KEY_RETURN)
        {
            buttonSelect.play();
            switch (currentButton)
            {
            case 2:
                choice = Move::paper;
                break;
            case 3:
                choice = Move::scissors;
                break;
            default:
                choice = Move::rock;
                break;
            }
        }
        if (key == 'h')
        {
            player->setHealth(maxPlayerHealth);
        }

    }
    //Pressing 'p' key will cause the game to pause during the battle state
    if (key == 'p')
        {

            setPausedState(-1 * getPausedState());
            
            if(getPausedState() > 0){
                canInteract = true;
            } else{
                canInteract = false;
            }
        }
}

void BattleState::keyReleased(int key)
{
}

void BattleState::mousePressed(int x, int y, int button)
{
}

void BattleState::reset()
{
    setFinished(false);
    setNextState("");
}

void BattleState::resetPlayer()
{
    maxPlayerHealth = player->getHealth();
}