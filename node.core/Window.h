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

	/*windows callback, handles all of the messages coming from windows*/
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:

	virtual void Create(int nCmdShow);

	virtual void Draw();

	unsigned int Height();

	bool IsMaximized();

	bool IsMinimized();

	bool IsOpen();

	bool IsValidWindow();

	virtual void Update();

	unsigned int Width();

	Window();

	~Window();
};
