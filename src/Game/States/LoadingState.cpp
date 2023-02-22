#include "LoadingState.h"
#include "ofApp.h"

LoadingState::LoadingState(string nState){

    this->nState = nState;

    vector<ofImage> loadingFrames;
    ofImage loadStateFrames;
    loadStateFrames.load("images/ui/loading-screen1.png");
    loadingFrames.push_back(loadStateFrames);
    loadStateFrames.load("images/ui/loading-screen2.png");
    loadingFrames.push_back(loadStateFrames);
    loadStateFrames.load("images/ui/loading-screen3.png");
    loadingFrames.push_back(loadStateFrames);

    loadingScreen = new Animation(9, loadingFrames);

    setNextState(getNState());

    music.load("audio/load.wav");
    music.setLoop(true);
    music.setVolume(0);
    music.play();

}

void LoadingState::tick(){

    loadingScreen->tick();
    loadingImage = loadingScreen->getCurrentFrame();

    counter++;

    if(counter == 30*multiplyer){

        setNextState(getNState());
        setFinished(true);
        multiplyer++;

    }
    
}

void LoadingState::render(){

    loadingImage.draw(0,0,ofGetWidth(),ofGetHeight());

}

void LoadingState::keyPressed(int key) {
    
}

void LoadingState::mousePressed(int x, int y, int button) {

}

void LoadingState::reset() {
    setFinished(false);
    setNextState("");
}