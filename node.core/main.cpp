#include <stdio.h>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Node.h"
#include "Window.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	Node* n = new Node();


	Node* b = new Node();

	nCmdShow = 1;
	Window* window = new Window();
	window->Create(nCmdShow);


	DBOUT("valid window : " << (window->ValidWindow() ? "true" : "false"));
	n->AddChild(b);

	//window->Update();
	while (window->IsOpen()) {
		window->Update();
	}

	return 0;
}