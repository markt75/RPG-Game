#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30);
	ofSetWindowTitle("PA2");
	setupAreas();
	// Declaration and Initialization of States
	player = new Player(100, 6);
	titleState = new TitleState();
	loadingState1 = new LoadingState("Overworld");
	loadingState2 = new LoadingState("Battle");
	overworldState = new OverworldState(player, currentArea);
	battleState = new BattleState(player, currentArea);
	winState = new WinState();
	endGameState = new EndGameState();

	// Initial State
	currentState = titleState;

}

//--------------------------------------------------------------
void ofApp::setupAreas()
{
	//each area is 672 pixels wide and 640 pixels high, with 10 and 8 pixels of space between the player and the edge of the map respectively
	//each in-game pixel is 4 * 1 screen pixel

/*-----------------------------------Area_2-------------------------------------------------------*/
	// Enemies2
	vector<Enemy *> enemies2;
	ofPoint entrancePosition2(4 * 110, 4 * 116);
	Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
	Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
	Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
	Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
	Enemy *area2Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
	Enemy *area2Enemy6 = new Enemy("26", 30, 6, "enemy2", 4 * 194, 4 * 532);
	enemies2.push_back(area2Enemy1);
	enemies2.push_back(area2Enemy2);
	enemies2.push_back(area2Enemy3);
	enemies2.push_back(area2Enemy4);
	enemies2.push_back(area2Enemy5);
	enemies2.push_back(area2Enemy6);

	Boss *boss2 = new Boss("2", 60, 10, "boss2", 4 * 515, 4 * 98);	// Boss2
	Friendly *friendly2 = new Friendly("3", "friendly", 4 * 190, 4 * 170);	//Friend

/* ---------------------------------- Static objects 2 -----------------------------------------------------*/
	vector<StaticEntities*> objects2;
	string rockPath2 = "images/objects/rocks/rock2.png";
	string tree2Path1 = "images/objects/trees/tree2-1.png";
	string tree2Path2 = "images/objects/trees/tree2-2.png";
	//Trees2
	StaticEntities *area2tree1 = new StaticEntities(4 * 425, 4 * 475, tree2Path1);
	StaticEntities *area2tree2 = new StaticEntities(4 * 316, 4 * 100, tree2Path1);
	StaticEntities *area2tree3 = new StaticEntities(4 * 350, 4 * 550, tree2Path1);
	StaticEntities *area2tree4 = new StaticEntities(4 * 500, 4 * 200, tree2Path1);
	StaticEntities *area2tree5 = new StaticEntities(4 * 108, 4 * 404, tree2Path2);
	StaticEntities *area2tree6 = new StaticEntities(4 * 280, 4 * 398, tree2Path2);
	StaticEntities *area2tree7 = new StaticEntities(4 * 376, 4 * 325, tree2Path2);
	StaticEntities *area2tree8 = new StaticEntities(4 * 298, 4 * 236, tree2Path2);
	//Rocks2
	StaticEntities *rock2_1 = new StaticEntities(4 * 215, 4 * 375, rockPath2);
	StaticEntities *rock2_2 = new StaticEntities(4 * 425, 4 * 245, rockPath2);
	StaticEntities *rock2_3 = new StaticEntities(4 * 270, 4 * 86, rockPath2);
	objects2.push_back(area2tree1);
	objects2.push_back(area2tree2);
	objects2.push_back(area2tree3);
	objects2.push_back(area2tree4);
	objects2.push_back(area2tree5);
	objects2.push_back(area2tree6);
	objects2.push_back(area2tree7);
	objects2.push_back(area2tree8);
	objects2.push_back(rock2_1);
	objects2.push_back(rock2_2);
	objects2.push_back(rock2_3);
/* ------------------------------------------------------------------------------------------------------ */

	area2 = new Area(NULL, "Ice Realm" ,"images/areas/area2.png", "audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2, objects2, boss2, friendly2); 

/*-----------------------------------Area_1-------------------------------------------------------*/

	// Enemies1
	vector<Enemy *> enemies1;
	ofPoint entrancePosition1(4 * 414, 4 * 566);
	Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
	Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
	Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178);
	enemies1.push_back(area1Enemy1);
	enemies1.push_back(area1Enemy2);
	enemies1.push_back(area1Enemy3);

	Boss *boss1 = new Boss("1", 50, 6, "boss1", 4 * 208, 4 * 162);	//Boss1
	Friendly *friendly1 = new Friendly("3", "friendly", 4 * 220, 4 * 320);	//Friend

/* ---------------------------- Static Objects 1 --------------------------------------------------------------*/
	vector<StaticEntities*> objects1;
	string rockPath1 = "images/objects/rocks/rock1.png";
	string tree1Path1 = "images/objects/trees/tree1-1.png";
	string tree1Path2 = "images/objects/trees/tree1-2.png";
	//Trees1
	StaticEntities *area1tree1 = new StaticEntities(4 * 425, 4 * 475, tree1Path1);
	StaticEntities *area1tree2 = new StaticEntities(4 * 316, 4 * 100, tree1Path1);
	StaticEntities *area1tree3 = new StaticEntities(4 * 350, 4 * 550, tree1Path1);
	StaticEntities *area1tree4 = new StaticEntities(4 * 500, 4 * 200, tree1Path1);
	StaticEntities *area1tree5 = new StaticEntities(4 * 108, 4 * 404, tree1Path2);
	StaticEntities *area1tree6 = new StaticEntities(4 * 280, 4 * 398, tree1Path2);
	StaticEntities *area1tree7 = new StaticEntities(4 * 376, 4 * 325, tree1Path2);
	StaticEntities *area1tree8 = new StaticEntities(4 * 298, 4 * 236, tree1Path2);
	//Rocks1
	StaticEntities *rock1_1 = new StaticEntities(4 * 215, 4 * 375, rockPath1);
	StaticEntities *rock1_2 = new StaticEntities(4 * 425, 4 * 245, rockPath1);
	StaticEntities *rock1_3 = new StaticEntities(4 * 270, 4 * 86, rockPath1);
	objects1.push_back(area1tree1);
	objects1.push_back(area1tree2);
	objects1.push_back(area1tree3);
	objects1.push_back(area1tree4);
	objects1.push_back(area1tree5);
	objects1.push_back(area1tree6);
	objects1.push_back(area1tree7);
	objects1.push_back(area1tree8);
	objects1.push_back(rock1_1);
	objects1.push_back(rock1_2);
	objects1.push_back(rock1_3);
/* ------------------------------------------------------------------------------------------------- */

	area1 = new Area(area2, "Forest Realm", "images/areas/area1.png", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, objects1, boss1, friendly1);
	currentArea = area1;
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (currentState != nullptr)
	{
		currentState->tick();
		if (currentState->hasFinished())
		{
			currentState->toggleMusic();
			if (currentState->getNextState() == "Title")
			{
				endGameState->setWin(false);
				area1->resetEnemies();
				area2->resetEnemies();
				currentArea = area1;
				battleState->resetPlayer();
				battleState->setStage(currentArea->getStage());
				overworldState->loadArea(currentArea);
				currentState = titleState;

			}
			else if(currentState->getNextState() == "Loading1")
			{
				currentState = loadingState1;
			}
			else if(currentState->getNextState() == "Loading2"){
				currentState = loadingState2;
			}
			else if (currentState->getNextState() == "Overworld")
			{
				currentState = overworldState;
			}
			else if (currentState->getNextState() == "Battle")  
			{
				if (!overworldState->getBossFight()){	
				battleState->startBattle(overworldState->getEnemy());
				currentState = battleState;
				}

				if (overworldState->getBossFight()){	
				battleState->startBossBattle(overworldState->getBoss());	
				currentState = battleState;
				}
			}
			else if (currentState->getNextState() == "Win")
			{
				if (!overworldState->getBossFight()){	
				overworldState->getEnemy()->kill();
				}

				if (overworldState->getBossFight()){	
				overworldState->getBoss()->kill();			
				overworldState->setBossFight(false);
				}		

				if (currentArea->getRemainingEnemies() == 0 && currentArea->getBoss()->isDead()) 
				{
					if (currentArea->getNextArea() == NULL)
					{
						endGameState->setWin(true);
						currentState = endGameState;
					}
					else
					{
						currentArea = currentArea->getNextArea();
						overworldState->loadArea(currentArea);
						battleState->setStage(currentArea->getStage());
						currentState = winState;
					}
				}
				else
				{
					currentState = winState;
				}
			}
			else if (currentState->getNextState() == "End")
				currentState = endGameState;
			currentState->toggleMusic();
			currentState->reset();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (currentState != nullptr)
	{
		currentState->render();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (currentState != nullptr)
		currentState->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (currentState != nullptr)
		currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	if (currentState != nullptr)
		currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}