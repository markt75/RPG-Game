#pragma once

#include "ofMain.h"
#include "TitleState.h"
#include "OverworldState.h"
#include "BattleState.h"
#include "WinState.h"
#include "EndGameState.h"
#include "LoadingState.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void setupAreas();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	private:
		Area *area1;
		Area *area2;
		Area *currentArea;
		State *currentState;
		TitleState *titleState;
		OverworldState *overworldState;
		BattleState *battleState;
		WinState *winState;
		EndGameState *endGameState;
		LoadingState *loadingState1;
		LoadingState *loadingState2;
		Player *player;
};
