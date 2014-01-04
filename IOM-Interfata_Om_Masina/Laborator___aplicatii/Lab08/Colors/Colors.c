#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate							(HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize								(HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSetFocus						(HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMVScroll						(HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMCtlColorScrollBar  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy						(HWND hwnd, WPARAM wParam, LPARAM lParam);

long ScrollWMKeyDown  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long ScrollWMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam);

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = NULL;
  wndclass->hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass->hbrBackground = CreateSolidBrush(0); //(RGB (0, 0, 0));
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
							  "Color Scroll",
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
  static char szAppName [] = "Colors1";

  if (!hPrevInstance) {
	 if (!InitApplication (hInstance, szAppName))
		return FALSE;
  } else
    return FALSE;

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

	case WM_CREATE:						return WMCreate							(hwnd, wParam, lParam);
	case WM_SIZE:							return WMSize								(hwnd, wParam, lParam);
	case WM_SETFOCUS:					return WMSetFocus						(hwnd, wParam, lParam);
	case WM_VSCROLL:					return WMVScroll						(hwnd, wParam, lParam);
	case WM_CTLCOLORSCROLLBAR:  
														return WMCtlColorScrollBar  (hwnd, wParam, lParam);
	case WM_DESTROY:					return WMDestroy						(hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


WNDPROC lpfnOldScroll; 
HBRUSH  hBrush [3];
HWND    hwndRect, hwndScroll [3], hwndLabel [3], hwndValue [3];
long   nFocus, color [3];

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  static char* szColorLabel [] = {"Red", "Green", "Blue"};
  HINSTANCE       hInstance;
  short        n;

  hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

  hwndRect = CreateWindow ("static",
                           NULL,
                           WS_CHILD | WS_VISIBLE | SS_WHITERECT,
                           0, 0, 0, 0,
                           hwnd,
                           (HMENU) 9,
                           hInstance,
                           NULL);


  for (n = 0; n < 3; n++) {
    hwndScroll [n] = CreateWindow ("scrollbar",
                                   NULL,
                                   WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT,
                                   0, 0, 0, 0,
                                   hwnd,
                                   (HMENU) n,
                                   hInstance,
                                   NULL);
    lpfnOldScroll = (WNDPROC) GetWindowLong (hwndScroll [n], GWL_WNDPROC);
    SetWindowLong  (hwndScroll [n], GWL_WNDPROC, (LONG) ScrollProc);
		SetScrollRange (hwndScroll [n], SB_CTL, 0, 255, FALSE);
    SetScrollPos   (hwndScroll [n], SB_CTL, 0, FALSE);

    hwndLabel [n]  = CreateWindow ("static",
                                   szColorLabel [n],
                                   WS_CHILD | WS_VISIBLE | SS_CENTER,
                                   0, 0, 0, 0,
                                   hwnd,
                                   (HMENU) (n + 3),
                                   hInstance,
                                   NULL);

    hwndValue [n]  = CreateWindow ("static",
                                   "0",
                                   WS_CHILD | WS_VISIBLE | SS_CENTER,
                                   0, 0, 0, 0,
                                   hwnd,
                                   (HMENU) (n + 6),
                                   hInstance,
                                   NULL);
  }

  hBrush [0] = CreateSolidBrush (RGB (255, 0, 0));
  hBrush [1] = CreateSolidBrush (RGB (0, 255, 0));
  hBrush [2] = CreateSolidBrush (RGB (0, 0, 255));

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  short      n, cxClient, cyClient; 
	long			 cyChar;
  HDC        hdc;
  TEXTMETRIC tm;

  cxClient = LOWORD (lParam);
  cyClient = HIWORD (lParam);

  hdc = GetDC (hwnd);
  GetTextMetrics (hdc, &tm);
  cyChar = tm.tmHeight;
  ReleaseDC (hwnd, hdc);

  SetFocus (NULL);

  MoveWindow (hwndRect, 0, 0, cxClient / 2, cyClient, TRUE);
  for (n = 0; n < 3; n++) {
    MoveWindow (hwndScroll [n], (2*n + 1)*cxClient / 14, 2*cyChar,
                cxClient / 14, cyClient - 4*cyChar, TRUE);
    MoveWindow (hwndLabel  [n], (4*n + 1)*cxClient / 28, cyChar / 2,
                cxClient / 7, cyChar, TRUE);
    MoveWindow (hwndValue  [n], (4*n + 1)*cxClient / 28, cyClient - 3*cyChar / 2,
                cxClient / 7, cyChar, TRUE);
  }

  SetFocus (hwndScroll [nFocus]);
	return 0;
}


long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetFocus (hwndScroll [nFocus]);
  return 0;
}


long WMVScroll (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  long  n;

  HBRUSH hbrBackground,hbrBackgroundOld;
  RECT   rcPaint;
  char   szBuffer [10];


	n = GetWindowLong ((HWND)lParam, GWL_ID);

  switch (LOWORD(wParam)) {
    case SB_PAGEDOWN:
      color [n] += 15;
    case SB_LINEDOWN:
      if (++color [n] > 255)
        color [n] = 255;
      break;

    case SB_PAGEUP:
      color [n] -= 15;
    case SB_LINEUP:
      if (--color [n] < 0)
        color [n] = 0;
      break;

    case SB_TOP:
      color [n] = 0;
      break;

    case SB_BOTTOM:
      color [n] = 255;
      break;

    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      color [n] = HIWORD (wParam);
      break;

  default:
    break;
  }

  SetScrollPos  (hwndScroll [n], SB_CTL, color [n], TRUE);
  SetWindowText (hwndValue  [n], itoa (color [n], szBuffer, 10));

  hbrBackgroundOld = (HBRUSH) GetClassLong (hwnd, GCL_HBRBACKGROUND);
  hbrBackground = CreateSolidBrush (RGB (color [0], color [1], color [2]));
  SetClassLong (hwnd, GCL_HBRBACKGROUND, (long) hbrBackground);
  DeleteObject (hbrBackgroundOld);

  GetClientRect (hwnd, &rcPaint);
  rcPaint.left = rcPaint.right / 2;
  InvalidateRect (hwnd, &rcPaint, TRUE);

  return 0;
}


long WMCtlColorScrollBar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HWND  hwndChild;
  HDC   hdc;
  POINT point;
  long n;

  hdc = (HDC) wParam;
  hwndChild = (HWND) (lParam);
  n = GetWindowLong (hwndChild, GWL_ID);

  SetBkColor   (hdc, GetSysColor (COLOR_CAPTIONTEXT));
  SetTextColor (hdc, GetSysColor (COLOR_WINDOWFRAME));
	
  point.x = point.y = 0;
  ClientToScreen (hwnd, &point);
  UnrealizeObject (hBrush [n]);
  SetBrushOrgEx (hdc, point.x, point.y,NULL);

  return ((long) hBrush [n]);
		
  
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HBRUSH hbrBackground;
  long  n;

  hbrBackground = (HBRUSH) GetClassLong (hwnd, GCL_HBRBACKGROUND);
  DeleteObject (hbrBackground);

  for (n = 0; n < 3; n++)
    DeleteObject (hBrush [n]);

  PostQuitMessage (0);

  return 0;
}


LRESULT CALLBACK ScrollProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_KEYDOWN:  ScrollWMKeyDown  (hwnd, wParam, lParam); break;
	case WM_SETFOCUS: ScrollWMSetFocus (hwnd, wParam, lParam); break;

  }

  return CallWindowProc (lpfnOldScroll, hwnd, message, wParam, lParam);
}



long ScrollWMKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  if (wParam == VK_TAB) {
    if (GetKeyState (VK_SHIFT) < 0)
      nFocus--;
    else
      nFocus++;

    if (nFocus > 2)
      nFocus = 0;
    else if (nFocus < 0)
      nFocus = 2;

    SetFocus (hwndScroll [nFocus]);
  }

  return 0;
}


long ScrollWMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  long n;

  n = GetWindowLong (hwnd, GWL_ID);
  nFocus = n;

  return n;
}



