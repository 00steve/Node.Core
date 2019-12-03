#pragma once

#include <Windows.h>
#include "Node.h"
#include "Graphics.h"

class View : public Node {
private:
	Graphics* graphics;
	RenderSettings* parentRenderSettings;
	RenderSettings renderSettings;







public:

	virtual Node* AddChild(Node* newNode);

	virtual bool AdjustRenderSettings();

	virtual void Draw();

	virtual void HandleMessage(Message message);

	virtual bool SetGraphics(Graphics* newGraphics);

	virtual void Update();

	View();

	~View();

};

