#pragma once

#include <windows.h>
#include "Drawable.h"
#include "List.h"
#include "Node.h"
#include "View.h"

class Window : public Node, public Drawable {
private:
	//int height;
	HINSTANCE hinst;
	//HWND hwnd;
	//bool maximized;
	//bool minimized;
	MSG msg;
	RenderSettings renderSettings;
	bool validWindow;
	List<View*> views;
	//int width;
	WNDCLASSEX wnd;

	/*windows callback, handles all of the messages coming from windows*/
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:

	void SendMessageToAllViews(unsigned int code, unsigned int subCode, void* data, bool immediate);


public:

	virtual Node* AddChild(Node* newNode);

	bool AddView(View* newView);

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
