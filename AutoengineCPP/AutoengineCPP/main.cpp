/*
	To create a window, use "Window wnd(800, 400, "Title");".
	- You can create multiple windows, but you will need to
	  change the window name (wnd) to a different name
	- To change window title, use "wnd.SetTitle("Title");"
*/

#include <Windows.h>
#include "messagemap.h"
#include "window.h"
#include <sstream>

//(all procedures must have this format)//
/*
	format:
	LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
*/

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	static WindowsMessageMap mm;
	OutputDebugString( mm( msg, lParam, wParam ).c_str() );

	switch( msg ) {
		case WM_CLOSE:
			PostQuitMessage( 0 ); //return code is changable
		break;
		/*case WM_CHAR:
		{
			static std::string title;
			title.push_back( (char)wParam );
			SetWindowText( hWnd, title.c_str() );
		}
		break;*/ //change window title based on what is typed
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

//main
int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow )
{
	const auto pClassName = "AutoEngineP";
	
	try {
		Window wnd(800, 400, "Autoengine C++"); //creates window with title "Autoengine C++"

		//message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			/*
				HOW TO CHECK IF KEY IS DOWN:
				if( wnd.kbd.KeyIsPressed( VK_CODE ) ) {
					
				}

				[REFRENCE VK CODES IN VK CODES.TXT]
			*/

			/*
			while (!wnd.mouse.IsEmpty()) {
				const auto e = wnd.mouse.Read();
				switch (e.GetType()) {
					case Mouse::Event::Type::Leave:
						wnd.SetTitle("gone!");
					break;

					case Mouse::Event::Type::Move:
					{
						std::ostringstream oss;
						oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
						wnd.SetTitle(oss.str());
					}
					break;
				}
			} //testing mouse position
			*/
		}

		if (gResult == -1) {
			return -1;
		}
		else {
			return msg.wParam;
		}
	}
	catch (const AutoengineException& e) {
		MessageBox( nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION );
	}
	catch (const std::exception e) {
		MessageBox( nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION );
	}
	catch ( ... ) {
		MessageBox( nullptr, "No details avaliable", "Unkown Exception", MB_OK | MB_ICONEXCLAMATION );
	}
	return -1;
}