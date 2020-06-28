#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <cstdlib>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define ID_CATCH 500
#define ID_DROP 501
#define ID_UP 502
#define ID_DOWN 503
#define ID_LEFT 504
#define ID_RIGHT 505
#define ID_STOP 506
#define TIMER_X 1
#define TIMER_Y 2


HPEN	pen = CreatePen(PS_SOLID, 10, 0X000000);// skrzynka
HPEN	penW = CreatePen(PS_SOLID, 10, 0xFFFFFF);// skrzynka bialy
HPEN	pen1 = CreatePen(PS_SOLID, 5, 0X000080);//linka
HPEN	pen1W = CreatePen(PS_SOLID, 5, 0xFFFFFF);// linka bialy

POINT linia[3] = {700, 58,700,629};
POINT skrzynka[1] = {350, 450};//gorny lewy rog skrzynki

bool kierunek_y;
bool kierunek_x;
int przesuniecie_x = 0;
int przesuniecie_y = 0;
bool zlapany=0;

bool czy_zlapany() {
	if (linia[1].y >= skrzynka[0].y && linia[1].y <= skrzynka[0].y + 150) {
		if (linia[1].x >= skrzynka[0].x && linia[1].x <= skrzynka[0].x + 100) {
			return 1;
		}
	}
	return 0;
}

VOID Rysuj_skrzynke2(HWND hWnd, HDC hdc, POINT skrzynka[])
{
	SelectObject(hdc, pen);
	Rectangle(
		hdc,
		skrzynka[0].x,
		skrzynka[0].y,
		skrzynka[0].x + 100,
		skrzynka[0].y + 150
	);
	ReleaseDC(hWnd, hdc);
}

VOID Usun_skrzynke(HWND hWnd, HDC hdc, POINT skrzynka[]) {
	SelectObject(hdc, penW);
	Rectangle(
		hdc,
		skrzynka[0].x,
		skrzynka[0].y,
		skrzynka[0].x + 100,
		skrzynka[0].y + 150
	);
	ReleaseDC(hWnd, hdc);
}

VOID Rysuj_skrzynke(HWND hWnd, HDC hdc, POINT skrzynka[])
{
	SelectObject(hdc, pen);
	Rectangle(
		hdc,
		skrzynka[0].x,
		skrzynka[0].y,
		skrzynka[0].x + 100,
		skrzynka[0].y + 150
	);
	Sleep(100);
	Usun_skrzynke(hWnd, hdc, skrzynka);

}

VOID Usun(HWND hWnd, HDC hdc, POINT linia[]) {
	SelectObject(hdc, pen1W);
	Polyline(hdc, linia, 2);
	ReleaseDC(hWnd, hdc);
}

VOID Rysuj(HWND hWnd, HDC hdc, POINT linia[])
{
	SelectObject(hdc, pen1);
	Polyline(hdc, linia, 2);
	Sleep(50);
	Usun(hWnd, hdc, linia);
	
}

VOID Rysuj2(HWND hWnd, HDC hdc, POINT linia[])
{
	SelectObject(hdc, pen1);
	Polyline(hdc, linia, 2);
	ReleaseDC(hWnd, hdc);
}

void Background(HDC hdc) {
	Graphics graphics(hdc);
	Pen      pen(Color(255, 0, 0, 0), 10);
	graphics.DrawLine(&pen, 210, 50, 210, 630);
	graphics.DrawLine(&pen, 50, 50, 1200, 50);
	graphics.DrawLine(&pen, 150, 630, 250, 630);
	graphics.DrawRectangle(&pen, 350, 450, 100, 150);

}



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{

	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Pen      pen(Color(255, 0, 0, 0), 10);



	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Dźwig"),			  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters


	

	HWND hwndButton_catch = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"catch",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		400,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_CATCH,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.



	HWND hwndButton_drop = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"drop",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		110,         // x position 
		400,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_DROP,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND hwndButton_left = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"left",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		250,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_LEFT,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.
	

	HWND hwndButton_up = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"up",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		60,         // x position 
		200,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_UP,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND hwndButton_stop = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"stop",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		60,         // x position 
		250,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_STOP,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND hwndButton_down = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"down",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		60,         // x position 
		300,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_DOWN,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND hwndButton_right = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"right",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		110,         // x position 
		250,         // y position 
		50,        // Button width
		50,        // Button height
		hWnd,     // Parent window
		(HMENU)ID_RIGHT,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.


	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain



LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;
	switch (message)
	{
				
	case WM_COMMAND:
		switch (wParam) {
			case ID_UP: {
				hdc = GetDC(hWnd);
				Usun(hWnd, hdc, linia);
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Usun_skrzynke(hWnd, hdc, skrzynka);
				}
				kierunek_y = 1;
				SetTimer(hWnd, TIMER_Y, 25, NULL);	
				break;
			}
			case ID_DOWN:{
				hdc = GetDC(hWnd);
				Usun(hWnd, hdc, linia);
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Usun_skrzynke(hWnd, hdc, skrzynka);
				}
				kierunek_y = 0;
				SetTimer(hWnd, TIMER_Y, 25, NULL);
				break;
			}
			case ID_LEFT: {
				hdc = GetDC(hWnd);
				Usun(hWnd, hdc, linia);
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Usun_skrzynke(hWnd, hdc, skrzynka);
				}
				kierunek_x = 1;
				SetTimer(hWnd, TIMER_X, 25, NULL);
				break;
			}
			case ID_RIGHT: {
				hdc = GetDC(hWnd);
				Usun(hWnd, hdc, linia);
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Usun_skrzynke(hWnd, hdc, skrzynka);
				}
				kierunek_x = 0;
				SetTimer(hWnd, TIMER_X, 25, NULL);
				break;
			}
			case ID_STOP: {
				hdc = GetDC(hWnd);
				Rysuj2(hWnd, hdc, linia);
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Rysuj_skrzynke2(hWnd, hdc, skrzynka);
				}
				KillTimer(hWnd, TIMER_X);
				KillTimer(hWnd, TIMER_Y);
				break;
			}
			case ID_CATCH: {
				zlapany = czy_zlapany();
				break;
			}
			case ID_DROP: {
				if (zlapany == 1) {
					hdc = GetDC(hWnd);
					Rysuj_skrzynke2(hWnd, hdc, skrzynka);
					zlapany = 0;
				}
				break;
			}
			 
		}
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_X:
			if (kierunek_x==1) {// w lewo
				if (przesuniecie_x > -450) {
					hdc = GetDC(hWnd);
					linia[0].x = linia[0].x - 1;
					linia[1].x = linia[1].x - 1;
					Rysuj(hWnd, hdc, linia);
					przesuniecie_x--;
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							skrzynka[0].x = skrzynka[0].x - 1;
							Rysuj_skrzynke(hWnd, hdc, skrzynka);
						}
				}
				else {
					hdc = GetDC(hWnd);
					Rysuj2(hWnd, hdc, linia);
					KillTimer(hWnd, TIMER_X);
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							Rysuj_skrzynke2(hWnd, hdc, skrzynka);
						}
				}
			}
			else {// w prawo
				if (przesuniecie_x < 500) {
					hdc = GetDC(hWnd);
					linia[0].x = linia[0].x + 1;
					linia[1].x = linia[0].x + 1;
					Rysuj(hWnd, hdc, linia);
					przesuniecie_x++;
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							skrzynka[0].x = skrzynka[0].x + 1;
							Rysuj_skrzynke(hWnd, hdc, skrzynka);
						}
				}
				else {
					hdc = GetDC(hWnd);
					Rysuj2(hWnd, hdc, linia);
					KillTimer(hWnd, TIMER_X);
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							Rysuj_skrzynke2(hWnd, hdc, skrzynka);
						}
				}
			}		
			break;
		case TIMER_Y:
			if (kierunek_y == 1) {// w gore
				if (przesuniecie_y > -560) {
					hdc = GetDC(hWnd);
					linia[1].y = linia[1].y - 1;
					Rysuj(hWnd, hdc, linia);
					przesuniecie_y--;
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							skrzynka[0].y = skrzynka[0].y - 1;
							Rysuj_skrzynke(hWnd, hdc, skrzynka);
						}
				}
				else {
					hdc = GetDC(hWnd);
					Rysuj2(hWnd, hdc, linia);
					KillTimer(hWnd, TIMER_Y);
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							Rysuj_skrzynke2(hWnd, hdc, skrzynka);
						}
				}
			}
			else {//w dol
				if (przesuniecie_y < 0) {
					hdc = GetDC(hWnd);
					linia[1].y = linia[1].y + 1;
					Rysuj(hWnd, hdc, linia);
					przesuniecie_y++;
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							skrzynka[0].y = skrzynka[0].y + 1;
							Rysuj_skrzynke(hWnd, hdc, skrzynka);
						}
				}
				else {
					hdc = GetDC(hWnd);
					Rysuj2(hWnd, hdc, linia);
					KillTimer(hWnd, TIMER_Y);
						if (zlapany == 1) {
							hdc = GetDC(hWnd);
							Rysuj_skrzynke2(hWnd, hdc, skrzynka);
						}
				}
			}
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Background(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc

