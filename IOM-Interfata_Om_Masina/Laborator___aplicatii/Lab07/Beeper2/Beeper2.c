#include <windows.h>

LRESULT CALLBACK WndProc   (HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK TimerProc (HWND, UINT, UINT, DWORD);

long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam);

#define ID_TIMER 1

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
							  "Beeper2 Time Demo",
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

  while (!SetTimer (hwnd, ID_TIMER, 1000, TimerProc))
    if (IDCANCEL == MessageBox (hwnd, "Too many clocks or timers!", szAppName,
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL))
      return FALSE;

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  return TRUE;
}

BOOL AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "Beeper2";

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

LRESULT CALLBACK WndProc (HWND hwnd,
						       UINT message,
						       WPARAM wParam,
						       LPARAM lParam)

{
  switch (message) {

	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, ID_TIMER);
  PostQuitMessage (0);

  return 0;
}


VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
  static BOOL fFlipFlop = FALSE;
  HBRUSH      hBrush;
  HDC         hdc;
  RECT        rc;

  MessageBeep (-1);

  fFlipFlop = !fFlipFlop;
  InvalidateRect (hwnd, NULL, FALSE);

  GetClientRect (hwnd, &rc);

  hdc = GetDC (hwnd);

  hBrush = CreateSolidBrush (fFlipFlop ? RGB (255, 0, 0) : RGB (0, 0, 255));

  FillRect (hdc, &rc, hBrush);
  DeleteObject (hBrush);

  ReleaseDC (hwnd, hdc);
}



