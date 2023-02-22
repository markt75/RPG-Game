#include "Friendly.h"

Friendly::Friendly(string id, string entityName, int ox, int oy) : Entity(ox, oy, 64, 64, "images/entities/enemy1/downframes/friendly-ow-down1.png")
{
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    ofImage temp;

    for (int i = 1; i < 5; i++)
    {
        temp.load("images/entities/" + entityName + "/downframes/" + entityName + "-ow-down" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/upframes/" + entityName + "-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/leftframes/" + entityName + "-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/rightframes/" + entityName + "-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }

    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
}

void Friendly::tickOverworld()
{
    if (moveTimer == 60)
    {
        walking = true;
        switch (direction)
        {
        case Direction::left:
            direction = Direction::up;
            break;
        case Direction::right:
            direction = Direction::left;
            break;
        case Direction::up:
            direction = Direction::down;
            break;
        case Direction::down:
            direction = Direction::right;
            break;
        }
    }
    if (moveTimer == 45)
    {
        walking = false;
    }
    moveTimer--;
    if (moveTimer == 0) moveTimer = 60;

    if (walking)
    {
        switch (direction)
        {
        case Direction::left:
            this->ox -= speed;
            walkLeft->tick();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += speed;
            walkRight->tick();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->tick();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->tick();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        }
    }
    else
    {
        switch (direction)
        {
        case Direction::left:
            overworldSprite.load("images/entities/" + entityName + "/leftframes/" + entityName + "-ow-left1.png");
            break;
        case Direction::right:
            overworldSprite.load("images/entities/" + entityName + "/rightframes/" + entityName + "-ow-right1.png");
            break;
        case Direction::up:
            overworldSprite.load("images/entities/" + entityName + "/upframes/" + entityName + "-ow-up1.png");
            break;
        case Direction::down:
            overworldSprite.load("images/entities/" + entityName + "/downframes/" + entityName + "-ow-down1.png");
            break;
        }
    }
}

void Friendly::renderOverworld()
{
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Friendly::friendInteract(){
    dialogue.load("images/ui/dialogue.png");
    dialogue.draw(100, 170, ofGetWidth()-200, ofGetHeight()-200);
}

void Friendly::keyPressed(int key)
{   
}

void Friendly::keyReleased(int key)
{
}

void Friendly::reset()
{
}

Friendly::~Friendly()
{
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}
