#include "Game.h"



Game::Game(){
}


Game::~Game(){
}


bool Game::Initialize() {
	return false;
}


void Game::Run() {

	unsigned int i;
	while (windows.Count() > 0) {
		i = windows.Count();
		while (i-- > 0) {
			windows[i]->Update();
		}
	}
}

bool Game::SetGraphics(Graphics * graphics)
{
	if (this->graphics) {
		delete this->graphics;
	}
	this->graphics = graphics;
	unsigned int i = views.Count();
	while (i-- > 0) {
		views[i]->SetGraphics(graphics);
	}
	return true;
}
