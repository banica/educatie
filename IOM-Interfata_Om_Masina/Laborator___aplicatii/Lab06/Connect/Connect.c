#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMMouseMove   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMLButtonUp   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint       (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy     (HWND hwnd, WPARAM wParam, LPARAM lParam);

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = LoadIcon (NULL, IDI_APPLICATION);
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

BOOL InitInstance (HINSTANCE hInstance, char* szAppName, int nCmdShow)
{
  HWND		  hwnd;

  hwnd = CreateWindow (szAppName,
							  "Connect-the-Dots Mouse Demo",
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
	 return FALSE;

  SetTimer (hwnd, 1, 1000, NULL);

	ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  return TRUE;
}

BOOL AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "Connect";

  if (!hPrevInstance) {
	 if (!InitApplication (hInstance, szAppName))
		return FALSE;
  }
  return InitInstance (hInstance, szAppName, nCmdShow);
}

int WINAPI WinMain (HINSTANCE hInstance,
					     HINSTANCE hPrevInstance,
					     LPSTR lpszCmdLine,
					     int nCmdShow)

{
  MSG		  msg;

  if (!AppInit (hInstance, hPrevInstance, nCmdShow))
	 return 0;

  while (GetMessage (&msg, NULL, 0, 0)) {
	 TranslateMessage (&msg);
	 DispatchMessage (&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {

	case WM_LBUTTONDOWN: return WMLButtonDown (hwnd, wParam, lParam);
	case WM_MOUSEMOVE:   return WMMouseMove   (hwnd, wParam, lParam);
	case WM_LBUTTONUP:   return WMLButtonUp   (hwnd, wParam, lParam);
	case WM_PAINT:       return WMPaint       (hwnd, wParam, lParam);
	case WM_DESTROY:     return WMDestroy     (hwnd, wParam, lParam);
  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


#define MAXPOINTS 1000

POINT points [MAXPOINTS];

short nCount;

long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  nCount = 0;
  InvalidateRect (hwnd, NULL, TRUE);

  return 0;
}


long WMMouseMove (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
	  if ((wParam & MK_LBUTTON) != 0 && nCount < MAXPOINTS) {
		
			points[nCount].x = LOWORD(lParam);
			points[nCount++].y = HIWORD(lParam);
      hdc = GetDC (hwnd);
      SetPixel (hdc, LOWORD (lParam), HIWORD (lParam), 0L);
      ReleaseDC (hwnd, hdc);
  }
	
  return 0;
}


long WMLButtonUp (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  InvalidateRect (hwnd, NULL, FALSE);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC         hdc;
  PAINTSTRUCT ps;
  short       i, j;

  hdc = BeginPaint (hwnd, &ps);

  for (i = 0; i < nCount - 1; i++)
    for (j = i; j < nCount; j++) {

      MoveToEx (hdc, points [i].x, points [i].y, NULL);
      LineTo (hdc, points [j].x, points [j].y);
    }

  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


