#include "WinState.h"

WinState::WinState() {
    screen.load("images/ui/winscreen.png");
    music.load("audio/ui/beep.wav");
    setNextState("Loading1");

}

void WinState::tick() {

}

void WinState::render(){
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void WinState::keyPressed(int key) {
    setNextState("Loading1");
    setFinished(true);
}

void WinState::mousePressed(int x, int y, int button) {

}

void WinState::reset() {
    setFinished(false);
    setNextState("");
}