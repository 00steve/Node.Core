#pragma once

#include <windows.h>
#include "Node.h"
#include "Drawable.h"



class Window : public Node, public Drawable {
private:
	int height;
	HINSTANCE hinst;
	HWND hwnd;
	bool maximized;
	bool minimized;
	MSG msg;
	bool validWindow;
	int width;
	WNDCLASSEX wnd;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:

	virtual void Create(int nCmdShow);

	virtual void Draw();

	bool IsOpen();

	virtual void Update();

	bool ValidWindow();


	Window();
	~Window();
};
