#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMTimer     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy   (HWND hwnd, WPARAM wParam, LPARAM lParam);

#define ID_TIMER 1

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = 0;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = LoadIcon(NULL,IDI_ASTERISK);
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
							  "Free Memory",
							  WS_SYSMENU,
								0,0,150,0,
							  NULL,
							  NULL,
							  hInstance,
							  NULL);
  if (hwnd == NULL)
	 return FALSE;

  while (!SetTimer (hwnd, ID_TIMER, 1000, NULL))
    if (IDCANCEL == MessageBox (hwnd, "Too many clocks or timers!", szAppName,
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL))
      return FALSE;

  ShowWindow (hwnd, SW_SHOWMINNOACTIVE);
  UpdateWindow (hwnd);

  return TRUE;
}

BOOL AppInit (HINSTANCE hInstance,
							HINSTANCE hPrevInstance,
							int nCmdShow)
{
  static char szAppName [] = "FreeMem";

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

	case WM_TIMER:     return WMTimer     (hwnd, wParam, lParam);
	case WM_DESTROY:   return WMDestroy   (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


DWORD dwFreeMem;

long WMTimer (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char cBuffer [25];
	MEMORYSTATUS memstats;

	GlobalMemoryStatus(&memstats);
  
  if (dwFreeMem != memstats.dwAvailPhys)
		{
			sprintf (cBuffer, " %.4f Mega ", dwFreeMem / 1048576.0);
			SetWindowText(hwnd, cBuffer);
		}

  dwFreeMem = memstats.dwAvailPhys;

  return 0;
}



long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, ID_TIMER);
  PostQuitMessage (0);

  return 0;
}


