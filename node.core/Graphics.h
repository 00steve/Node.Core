#pragma once

struct RenderSettings {
	unsigned int Height;
	bool Minimized;
	bool Maximized;
	unsigned int Width;
};




#include "Drawable.h"
#include "Node.h"

class Graphics : public Drawable, public Node{
private:
	RenderSettings* renderSettings;
	Drawable* target;

public:

	virtual void Draw() = 0;

	Graphics();
	~Graphics();

	virtual bool Initialize() = 0;


	virtual bool SetTarget(Drawable* newTarget);

	virtual void Update() = 0;
};

