#include "window.h"



LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	get or set a reference to the class depending on if the window is being created
	or if it is every time after the window has been created.
	*/
	Window* window;
	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT *cs = (CREATESTRUCT*)lParam;
		window = (Window*)cs->lpCreateParams;
		SetLastError(0);
		if (SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window) == 0) {
			if (GetLastError() != 0) {
				MessageBox(NULL, "There has been an error near here.", "Error", 0);
				return FALSE;
			}
		}
	}
	else {
		window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}


	char szFileName[MAX_PATH];


	switch (uMsg) {
	//when the window should close
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	//when the window is destroyed
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//when the left mouse button is pushed down on the window
	case WM_LBUTTONDOWN: 
		GetModuleFileName(window->hinst, szFileName, MAX_PATH);
		MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
		break;

	//case WM_NCCREATE:
	//	break;

	case WM_PAINT://window (or part of) needs to be repainted
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;


	//when the window gets keyboard focus
	case WM_SETFOCUS:
		break;

	//when the window size changes
	//https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-size
	case WM_SIZE:
		//get the new width and height
		window->width = LOWORD(lParam);
		window->height = HIWORD(lParam);

		switch (wParam) {
		case SIZE_MINIMIZED:
			window->minimized = true;
			window->maximized = false;
			break;
		case SIZE_RESTORED:
			window->minimized = false;
			window->maximized = false;
			break;
		case SIZE_MAXIMIZED:
			window->minimized = false;
			window->maximized = true;
			break;
		}
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}



void Window::Create(int nCmdShow) {

	hinst = GetModuleHandle(NULL);
	memset(&wnd, 0, sizeof(wnd));
	wnd.cbSize = sizeof(wnd);
	wnd.lpszClassName = "Window";
	wnd.lpfnWndProc = (WNDPROC)WindowProc;
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hInstance = hinst;

	int result = RegisterClassEx(&wnd);
	if (GetLastError() != 0) {
		DBOUT(GetLastError() << std::endl);
	}

	hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		wnd.lpszClassName,                     // Window class
		"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,       // Parent window    
		NULL,       // Menu
		hinst,  // Instance handle
		this     // Additional application data (pass in a reference to this object so it can be got later
	);

	validWindow = !(hwnd == NULL);
	DBOUT(GetLastError() << std::endl);

	minimized = false;

	//UpdateWindow(hwnd);//i don't know what this does or where to call it, so I commented it out
	ShowWindow(hwnd, nCmdShow);
}


void Window::Draw() {

}


bool Window::IsOpen() {
	return validWindow && IsWindow(hwnd);
}

void Window::Update() {

	msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}




	Node::Update();
}

bool Window::ValidWindow() {
	return validWindow;
}


Window::Window() {



}


Window::~Window() {

}
