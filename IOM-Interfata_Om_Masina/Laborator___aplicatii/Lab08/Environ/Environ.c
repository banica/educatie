#include <windows.h>
#include <stdlib.h>
#include <string.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMCommand  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy  (HWND hwnd, WPARAM wParam, LPARAM lParam);

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  wndclass->hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
							  "Environment List Box",
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

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  return TRUE;
}

BOOL AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "Environ";

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

	case WM_CREATE:   return WMCreate   (hwnd, wParam, lParam);
	case WM_SETFOCUS: return WMSetFocus (hwnd, wParam, lParam);
	case WM_COMMAND:  return WMCommand  (hwnd, wParam, lParam);
	case WM_DESTROY:  return WMDestroy  (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}



#define MAXENV 4096

HWND hwndList, hwndText;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char       szBuffer [MAXENV + 1];
  HDC        hdc;
  TEXTMETRIC tm;
  short      n;

  hdc = GetDC (hwnd);
  GetTextMetrics (hdc, &tm);
  ReleaseDC (hwnd, hdc);

  hwndList = CreateWindow ("listbox",
                           NULL,
                           WS_CHILD | WS_VISIBLE | LBS_STANDARD,
                           tm.tmAveCharWidth,
                           tm.tmHeight*3,
                           tm.tmAveCharWidth*16 + GetSystemMetrics (SM_CXVSCROLL),
                           tm.tmHeight*5,
                           hwnd,
                           (HMENU) 1,
                           (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),
                           NULL);

  hwndText = CreateWindow ("static",
                           NULL,
                           WS_CHILD | WS_VISIBLE | SS_LEFT,
                           tm.tmAveCharWidth,
                           tm.tmHeight,
                           tm.tmAveCharWidth*MAXENV,
                           tm.tmHeight,
                           hwnd,
                           (HMENU)2,
                           (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),
                           NULL);

  for (n = 0; environ [n] != NULL; n++) {
    if (strlen (environ [n]) > MAXENV)
      continue;
    *strchr (strcpy (szBuffer, environ [n]), '=') = '\0';
    SendMessage (hwndList, LB_ADDSTRING, 0, (LONG) (LPSTR) szBuffer);
  }

  return 0;
}


long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetFocus (hwndList);

  return 0;
}


long WMCommand (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char  szBuffer [MAXENV + 1];
  int n;
	
	if ( LOWORD(wParam) == 1 && HIWORD (wParam) == LBN_SELCHANGE) 
	{
    n = SendMessage (hwndList, LB_GETCURSEL, 0, 0);
    n = SendMessage (hwndList, LB_GETTEXT, n, (LONG) (LPSTR) szBuffer);
		
		strcpy (szBuffer + n + 1, getenv (szBuffer));
    szBuffer [n] = '=';

    SetWindowText (hwndText, szBuffer);
  }

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}



