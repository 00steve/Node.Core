#pragma once


#include <Windows.h>

struct RenderSettings {
	unsigned int Height;
	bool Minimized;
	bool Maximized;
	unsigned int Width;
	HWND Window;
};

#include "Drawable.h"
#include "Node.h"







class Graphics : public Drawable, public Node{
private:
	RenderSettings* parentRenderSettings;
	Drawable* target;

public:

	virtual void Draw() = 0;

	Graphics();
	~Graphics();

	virtual void HandleMessage(Message message);

	virtual bool Initialize() = 0;


	virtual bool SetTarget(Drawable* newTarget);

	virtual void Update() = 0;
};

