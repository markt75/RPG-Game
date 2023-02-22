#include "EndGameState.h"

EndGameState::EndGameState() {
    loseScreen.load("images/ui/losescreen.png");
    winScreen.load("images/ui/winscreen.png");
    music.load("audio/ui/boop.wav");
    win = false;
}

void EndGameState::tick() {

}

void EndGameState::render(){
    if(win) winScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    else loseScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void EndGameState::keyPressed(int key) {
    setNextState("Title");
    setFinished(true);
}

void EndGameState::mousePressed(int x, int y, int button) {

}

void EndGameState::reset() {
    setFinished(false);
    setNextState("");
}