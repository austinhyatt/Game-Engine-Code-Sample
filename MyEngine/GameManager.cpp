#include "GameManager.h"
#include "Clock.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

df::GameManager::GameManager() {

	setType("GameManager");

	game_over = false;

	frame_time = df::FRAME_TIME_DEFAULT;
}

df::GameManager& df::GameManager::getInstance() {
	int startUp();
	static GameManager game_manager = GameManager();
	return game_manager;
}

void df::GameManager::run() {
	Clock clock;
	int game_loop_count = 0;
	LM.writeLog("GM.run() Started!");
	while (!game_over) {
		clock.delta();

		EventStep s(game_loop_count);
		onEvent(&s);
		game_loop_count++;
		IM.getInput();

		WM.update();		// update game world state
		WM.draw();			// draw current scene to back buffer
		DM.swapBuffers();	// swap back buffer to current buffer
		long int loop_time = clock.split() / 1000;
		long int sleep_time = frame_time - loop_time;
		if (loop_time > frame_time) {
			LM.writeLog("GameManager::run(): Can't keep up! Target Frame Time: %d ms, split %d ms", frame_time, loop_time);
			// LM.writeLog("sleep_time: %d", sleep_time/1000);
			sleep_time = 0;
		}
		Sleep(sleep_time);
	}
	LM.writeLog("Game loop ended!");
}

// starts up all managers in the correct order
// Get's an instance and calls their startUp command
int df::GameManager::startUp() {
	LM.startUp(); // starts up log manager 

	WM.startUp(); // starts up world manager and sets camera and world boundary
	WM.setBoundary(df::Box(df::Vector(), DM.getHorizontal(), DM.getVertical()));
	WM.setView(df::Box(df::Vector(), DM.getHorizontal(), DM.getVertical()));

	DM.startUp(); // starts up display manager
	IM.startUp(); // starts up input manager
	RM.startUp(); // starts up resource manager
	LM.writeLog("GameManager started!");
	timeBeginPeriod(1);
	return 1;
}

void df::GameManager::shutDown() {
	timeEndPeriod(1);
	LM.writeLog("GameManager Shutting down!");
	IM.shutDown();
	WM.shutDown();
	DM.shutDown();
	RM.shutDown();
	LM.shutDown();
	setGameOver();
}

void df::GameManager::setGameOver(bool new_game_over) {
	game_over = new_game_over;

}

bool df::GameManager::getGameOver() const {
	return game_over;
}

int df::GameManager::getFrameTime() const {
	return frame_time;
}