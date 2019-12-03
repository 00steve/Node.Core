#include <stdio.h>
#include <iostream>
#include <sstream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bitset>
#include <shellapi.h> // For CommandLineToArgvW

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

// In order to define a function called CreateWindow, the Windows macro needs to
// be undefined.
#if defined(CreateWindow)
#undef CreateWindow
#endif

// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>
using namespace Microsoft::WRL;



//#include "Node.h"
//#include "Window.h"
//#include "DirectX3DGraphics.h"
//#include "Component.h"

#include "DirectX12Game.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {


	//Map<Node*> t = Map<Node*>();
	//
	//Node* n = new Node();
	//t.Add("things", n);
	//Node* n3 = new Node();
	//if (n3->Register("things")) {
	//	DBOUT("Added newthing\n");
	//}
	//else {
	//	DBOUT("Couldn't add newthing\n");
	//}



	//create game to contain all of the components
	DirectX12Game game = DirectX12Game();
	if (game.Initialize()) {
		game.Run();
	}

	return 0;
}