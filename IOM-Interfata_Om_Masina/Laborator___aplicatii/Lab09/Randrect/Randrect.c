#include <windows.h>
#include <stdlib.h>

void Idle (HWND hwnd);

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMSize    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam);

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = NULL;
  wndclass->hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass->hbrBackground = GetStockObject (WHITE_BRUSH);
  wndclass->lpszMenuName  = NULL;
  wndclass->lpszClassName = szAppName;
}

BOOL InitApplication (HINSTANCE hInstance, char* szAppName)
{
  WNDCLASS wndclass;

  InitClass (&wndclass, hInstance, szAppName);
  return RegisterClass (&wndclass);
}


HWND InitInstance (HINSTANCE hInstance, char* szAppName, int nCmdShow)
{
  HWND hwnd;

  hwnd = CreateWindow (szAppName,
							  "Random Rectangles",
							  WS_OVERLAPPEDWINDOW,
							  CW_USEDEFAULT,
							  CW_USEDEFAULT,
							  CW_USEDEFAULT,
							  CW_USEDEFAULT,
							  NULL,
							  NULL,
							  hInstance,
							  NULL);
  if (hwnd == NULL)
	 return NULL;

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  return hwnd;
}

HWND AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "RandRect";

  if (!hPrevInstance) {
	 if (!InitApplication (hInstance, szAppName))
		return NULL;
  }
  return InitInstance (hInstance, szAppName, nCmdShow);
}

int WINAPI WinMain (HINSTANCE hInstance,
					     HINSTANCE hPrevInstance,
					     LPSTR lpszCmdLine,
					     int nCmdShow)

{
  HWND     hwnd;
  MSG		  msg;

  hwnd = AppInit (hInstance, hPrevInstance, nCmdShow);
  if (hwnd == NULL)
	 return 0;

  while (TRUE) {
    if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT)
        break;

  	   TranslateMessage (&msg);
	   DispatchMessage (&msg);
    }
    else
      Idle (hwnd);
  }

  return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd,
						       UINT message,
						       WPARAM wParam,
						       LPARAM lParam)

{
  switch (message) {

	case WM_SIZE:    return WMSize    (hwnd, wParam, lParam);
	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

int cxClient, cyClient;

long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  cxClient = LOWORD (lParam);
  cyClient = HIWORD (lParam);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


void Idle (HWND hwnd)
{
  HBRUSH hBrush;
  HDC    hdc;
  int    x1, x2, y1, y2, nRed, nGreen, nBlue;

  x1     = rand() % (cxClient + 1);
  x2     = rand() % (cxClient + 1);
  y1     = rand() % (cyClient + 1);
  y2     = rand() % (cyClient + 1);

  nRed   = rand() % (256);
  nGreen = rand() % (256);
  nBlue  = rand() % (256);

  hdc = GetDC (hwnd);
  hBrush = CreateSolidBrush (RGB (nRed, nGreen, nBlue));
  SelectObject (hdc, hBrush);

  Rectangle (hdc, min (x1, x2), min (y1, y2),
                  max (x1, x2), max (y1, y2));

  ReleaseDC (hwnd, hdc);
  DeleteObject (hBrush);

  return;
}

