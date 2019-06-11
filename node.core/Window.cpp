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


	//char szFileName[MAX_PATH];


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
		//GetModuleFileName(window->hinst, szFileName, MAX_PATH);
		//MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
		break;

	//case WM_NCCREATE:
	//	break;

	case WM_PAINT://window (or part of) needs to be repainted
	{
		unsigned int i = window->views.Count();
		while (i-- > 0) {
			window->views[i]->Draw();
			DBOUT("draw\n");
		}
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
		window->renderSettings.Width = LOWORD(lParam);
		window->renderSettings.Height = HIWORD(lParam);

		switch (wParam) {
		case SIZE_MINIMIZED:
			window->renderSettings.Minimized = true;
			window->renderSettings.Maximized = false;
			break;
		case SIZE_RESTORED:
			window->renderSettings.Minimized = false;
			window->renderSettings.Maximized = false;
			break;
		case SIZE_MAXIMIZED:
			window->renderSettings.Minimized = false;
			window->renderSettings.Maximized = true;
			break;
		}

		//send message to views that the size has changed
		window->SendMessageToAllViews(MESSAGE_PARENT_SETTINGS_CHANGED, PARENT_SETTINGS_CHANGED_SIZE,NULL,true);

		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


Node* Window::AddChild(Node* newNode) {
	if (dynamic_cast<View*>(newNode)) {
		AddView((View*)newNode);
		//Node::CreateAndSendMessage(newNode, MESSAGE_SET_RENDER_SETTINGS, (void*)&renderSettings);

		DBOUT("\t- window:window handle :" << (renderSettings.Window ? "true" : "false") << "\n");
		Node::CreateAndSendMessageImmediate(newNode, MESSAGE_SET_RENDER_SETTINGS, (void*)&renderSettings);
		//Message m;
		//m.sender = this;
		//m.receiver = newNode;
		//m.code = MESSAGE_SET_RENDER_SETTINGS;
		//m.data = (void*)&renderSettings;
		//newNode->HandleMessage(m);
	}
	return Node::AddChild(newNode);
}

bool Window::AddView(View* newView) {
	if (views.Exists(newView)) return false;
	views.Push(newView);
	return true;
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

	renderSettings.Window = CreateWindowEx(
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

	validWindow = !(renderSettings.Window == NULL);
	DBOUT(GetLastError() << std::endl);

	//set the initial render settings
	//renderSettings.Height = 0;
	//renderSettings.Width = 0;
	renderSettings.Minimized = false;

	Window::SendMessageToAllViews(MESSAGE_RENDER_SETTINGS_CHANGED, NULL,NULL,true );

	//UpdateWindow(hwnd);//i don't know what this does or where to call it, so I commented it out
	ShowWindow(renderSettings.Window, nCmdShow);
}

void Window::Draw() {
	DBOUT("DRAW WINDOW\n");
}

unsigned int Window::Height() {
	return renderSettings.Height;
}

bool Window::IsOpen() {
	return validWindow && IsWindow(renderSettings.Window);
}

bool Window::IsMaximized() {
	return renderSettings.Maximized;
}

bool Window::IsMinimized() {
	return renderSettings.Minimized;
}

bool Window::IsValidWindow() {
	return validWindow;
}


void Window::SendMessageToAllViews(const unsigned int code,const unsigned int subCode, void* data,bool immediate) {
	unsigned int i = views.Count();

	Message viewMessage;
	viewMessage.code = code;
	viewMessage.subCode = subCode;
	viewMessage.data = data;
	viewMessage.sender = this;	
	while (i-- > 0) {
		viewMessage.receiver = views[i];
		if (immediate) {
			views[i]->HandleMessage(viewMessage);
		}
		else {
			(void)Node::SendAMessage(viewMessage);
		}
	}



}

void Window::Update() {
	msg = { };
	//it gets caught in the loop because there is always a message
	//int mCount = 0;
	//while (GetMessage(&msg, NULL, 0, 0) && mCount++ < 10)
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
	bool isMsg = GetMessage(&msg, NULL, 0, 0);
	if (isMsg) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Node::Update();
}

unsigned int Window::Width() {
	return renderSettings.Width;
}

Window::Window() {
	Create(10);
}

Window::~Window() {

}
