#include <windows.h>

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int		WINAPI WinMain(	HINSTANCE hInstance, 
						HINSTANCE hPrevInstance,
						LPSTR lpCmdLine,     
						int nCmdShow)

{
  static char szAppName [] = "HelloWin";
  HWND        hwnd;
  MSG         msg;
  WNDCLASS    wndclass;

  if (!hPrevInstance) {

	wndclass.style         = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;

	RegisterClass (&wndclass);
  }

  hwnd = CreateWindow (szAppName,
					   "The Hello Program",
					   WS_OVERLAPPEDWINDOW,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   NULL,
					   NULL,
					   hInstance,
					   NULL);

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  while (GetMessage (&msg, NULL, 0, 0)) {

	TranslateMessage (&msg);
	DispatchMessage (&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK	WndProc(HWND hwnd, 
							UINT message, 
							WPARAM wParam, 
							LPARAM lParam)


{
  HDC         hdc;
  PAINTSTRUCT ps;
  RECT        rect;

  switch (message) {

	case WM_PAINT:

	  hdc = BeginPaint (hwnd, &ps);

	  GetClientRect (hwnd, &rect);

	  DrawText (hdc, "Hello, Windows!", -1, &rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	  EndPaint (hwnd, &ps);
	  return 0;

	case WM_DESTROY:

	  PostQuitMessage (0);
	  return 0;
  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

