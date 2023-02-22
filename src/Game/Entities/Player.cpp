#include "Player.h"

Player::Player(int health, int baseDamage) : DynamicEntities(INIT_X, INIT_Y, 64, 64, 64, 164, 192, 192, health, baseDamage, "images/entities/player/downframes/player-ow-front1.png", "images/entities/player/fightingframes/player-f1.png")
{

    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    vector<ofImage> fightingFrames = {};
    ofImage temp;

    for (int i = 1; i < 5; i++)
    {
        temp.load("images/entities/player/downframes/player-ow-front" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/player/upframes/player-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/player/leftframes/player-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/player/rightframes/player-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }

    temp.load("images/entities/player/fightingframes/player-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/player/fightingframes/player-f2.png");
    fightingFrames.push_back(temp);

    walkDown = new Animation(5, downFrames);
    walkUp = new Animation(5, upFrames);
    walkLeft = new Animation(5, leftFrames);
    walkRight = new Animation(5, rightFrames);
    fighting = new Animation(7, fightingFrames);
    pressedKeys = {};
}

void Player::tickOverworld()
{
    if (!pressedKeys.empty())
    {
        switch (pressedKeys[0])
        {
        case 'a':
            direction = Direction::left;
            if (this->ox - speed >= CENTER_X)
                this->ox -= speed;
            walkLeft->tick();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case 'd':
            direction = Direction::right;
            if (this->ox + speed <= OXDIMENSION - CENTER_X)
                this->ox += speed;

            walkRight->tick();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case 'w':
            direction = Direction::up;
            if (this->oy - speed >= CENTER_Y)
                this->oy -= speed;
            walkUp->tick();
            overworldSprite = walkUp->getCurrentFrame();

            break;
        case 's':
            direction = Direction::down;
            if (this->oy + speed <= OYDIMENSION - CENTER_Y)
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
            overworldSprite.load("images/entities/player/leftframes/player-ow-left1.png");
            break;
        case Direction::right:
            overworldSprite.load("images/entities/player/rightframes/player-ow-right1.png");
            break;
        case Direction::up:
            overworldSprite.load("images/entities/player/upframes/player-ow-up1.png");
            break;
        case Direction::down:
            overworldSprite.load("images/entities/player/downframes/player-ow-front1.png");
            break;
        }
    }
}

void Player::tickFighting()
{
    fightingSprite = fighting->getCurrentFrame();
    fighting->tick();
}

void Player::renderOverworld()
{
    // uncomment this to see the coordinates of your player
    // ofDrawBitmapString("ow:" + to_string(ox), 100, 60);
    // ofDrawBitmapString("oy:" + to_string(oy), 100, 80);
    overworldSprite.draw(CENTER_X, CENTER_Y, ow, oh);
}

void Player::keyPressed(int key)
{
    if (key == 'w' || key == 'a' || key == 's' || key == 'd')
    {
        if(find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end()){
            pressedKeys.push_back(key);
        }
    }
}

void Player::keyReleased(int key)
{
    if (key == 'w' || key == 'a' || key == 's' || key == 'd')
    {
        vector<char>::iterator pos = find(pressedKeys.begin(), pressedKeys.end(), key);
        if(pos != pressedKeys.end()){
            pressedKeys.erase(pos);
        }
    }
}

void Player::reset()
{
    ox = INIT_X;
    oy = INIT_Y;
    fx = INIT_X;
    fy = INIT_Y;
}

Player::~Player() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}