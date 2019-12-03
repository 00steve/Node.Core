#pragma once

#include "Window.h"
#include "View.h"
#include "Graphics.h"

class Game{

protected:

	Graphics*		graphics;
	List<View*>		views;
	List<Window*>	windows;

public:


	Game();

	~Game();

	virtual bool Initialize();

	virtual void Run();

	bool SetGraphics(Graphics* graphics);
};

