#include "DirectX12Game.h"



bool DirectX12Game::Initialize(){
	if (!DirectX::XMVerifyCPUSupport()) {
		MessageBoxA(NULL, "Failed to verify DirectX Math library support.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	Window* window = new Window();
	windows.Push(window);
	View* view = new View();
	views.Push(view);
	window->AddChild(view);

	graphics = new DirectX3DGraphics();
	view->SetGraphics(graphics);
	return true;
}

DirectX12Game::DirectX12Game(){
}


DirectX12Game::~DirectX12Game(){
}
