#include <stdio.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <bitset>

#include "Node.h"
#include "Window.h"
#include "DirectX3DGraphics.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {


	Map<Node*> t = Map<Node*>();
	
	Node* n = new Node();
	t.Add("things", n);
	Node* n3 = new Node();
	if (n3->Register("things")) {
		DBOUT("Added newthing\n");
	}
	else {
		DBOUT("Couldn't add newthing\n");
	}



	Window* window = new Window();

	View* v1 = new View();
	window->AddChild(v1);

	DirectX3DGraphics* dx3 = new DirectX3DGraphics();
	v1->AddChild(dx3);
	//v1->SetGraphics(dx3);
	//window->AddView(v1);


	window->Create(nCmdShow);
	while (window->IsOpen()) {
		window->Update();
	}
	

	return 0;
}