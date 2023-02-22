#include "Enemy.h"

Enemy::Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy) : DynamicEntities(ox, oy, 64, 64, 400, 164, 192, 192, health, baseDamage, "images/entities/enemy1/fightingframes/enemy1-f1.png", "images/entities/enemy1/downframes/enemy1-ow-down1.png")
{
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    vector<ofImage> fightingFrames = {};
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

    temp.load("images/entities/" + entityName + "/fightingframes/" + entityName + "-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/" + entityName + "/fightingframes/" + entityName + "-f2.png");
    fightingFrames.push_back(temp);

    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
    fighting = new Animation(7, fightingFrames);
}

void Enemy::tickOverworld()
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

void Enemy::renderOverworld()
{
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Enemy::tickFighting()
{
    fightingSprite = fighting->getCurrentFrame();
    fighting->tick();
}

void Enemy::keyPressed(int key)
{
}

void Enemy::keyReleased(int key)
{
}

void Enemy::reset()
{
}

Enemy::~Enemy()
{
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete fighting;
}