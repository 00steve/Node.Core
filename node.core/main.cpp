#include <stdio.h>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Node.h"
#include "Window.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	Map<Node> t = Map<Node>();
	
	Node* n = new Node();


	t.Add("things", n);
	Node* b = new Node();

	Window* window = new Window();
	window->Create(nCmdShow);

	n->AddChild(b);

	while (window->IsOpen()) {
		window->Update();
	}
	


	return 0;
}