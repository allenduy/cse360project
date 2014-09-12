#include <Windows.h>
#include <d2d1_1.h> 
#include "Graphics.h"

//READ THIS BEFORE YOU RUN THIS EXAMPLE:

/* Direct2D libraries are in d2d1_1.h. The _1 is used for Windows 8 
development, so if you get an error, change the header to <d2d1.h>.  
Also, you may need to add d2d1.lib to your project dependencies */


Graphics* graphics; //graphics object that we made in Graphics.h

//An application-defined function that processes messages sent to a window. 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_DESTROY){PostQuitMessage(0); return 0;}
	
	if(uMsg == WM_PAINT)
	{
		graphics->BeginDraw();
		/**************  Begin Drawing Here ***************/

		graphics->ClearScreen(0.0f,0.0f,0.5f);

		//EXAMPLE: Draws 10 random circles to the screen.  These are redrawn whenever the uMsg is passed in as WM_PAINT.
		//		   Try resizing your window
		for(int i=0; i<10; i++)
			graphics->DrawCircle(rand()%800,rand()%600,rand()%100,1.0f,0.0f,0.0f,1.0f);
		
		/***************  End Drawing Here ****************/
		graphics->EndDraw();
	}

	return DefWindowProc( hwnd,  uMsg,  wParam,  lParam); 
}

//wWinMain is similar to main method.  This is where the program begins executing.
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	//creates windowclass and sets some properties
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW; //default background color
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; //allows the user to adjust the window

	RegisterClassEx(&windowclass); //Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function.

	//makes window with these dimms
	RECT rect = {0,0,800,600};
	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//defines the window handler to be a new window with the title being "Group Project" and with the initial position on the screen at (100,100)
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"MainWindow","Group Project",WS_OVERLAPPEDWINDOW,100,100,rect.right-rect.left,rect.bottom-rect.top,NULL,NULL,hInstance,0);

	if(!windowhandle) return -1; //error handling

	graphics = new Graphics(); //initializes graphics object made in Graphics.h

	if(!graphics->Init(windowhandle)) //error handling
	{
		delete graphics;
		return -1;
	}

	ShowWindow(windowhandle, nCmdShow); //displays window to screen

	MSG message;
		/*The system passes input to a window procedure in the form of a message. Messages are generated by both the system and applications. 
		The system generates a message at each input event�for example, when the user types, moves the mouse, or clicks a control such as a scroll bar. 
		The system also generates messages in response to changes in the system brought about by an application, such as when an application changes the 
		pool of system font resources or resizes one of its windows. An application can generate messages to direct its own windows to perform 	tasks or 
		to communicate with windows in other applications.*/

	//handles the message requests
	while(GetMessage(&message, NULL,0,0))
	{
		DispatchMessage(&message);
	}

	delete graphics; //gets rid of our graphics object for memory handling
	return 0;
}