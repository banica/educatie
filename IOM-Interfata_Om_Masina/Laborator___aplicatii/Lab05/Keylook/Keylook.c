#include <windows.h>

#include <stdio.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate      (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint       (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMKeyDown     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMKeyUp       (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMChar        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDeadChar    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSysKeyDown  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSysKeyUp    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSysChar     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSysDeadChar (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Keyboard Message Looker",
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
  static char szAppName [] = "KeyLook";

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

   case WM_CREATE:      return WMCreate      (hwnd, wParam, lParam);
   case WM_SIZE:        return WMSize        (hwnd, wParam, lParam);
   case WM_PAINT:       return WMPaint       (hwnd, wParam, lParam);
   case WM_KEYDOWN:     return WMKeyDown     (hwnd, wParam, lParam);
   case WM_KEYUP:       return WMKeyUp       (hwnd, wParam, lParam);
   case WM_CHAR:        return WMChar        (hwnd, wParam, lParam);
   case WM_DEADCHAR:    return WMDeadChar    (hwnd, wParam, lParam);
   case WM_SYSKEYDOWN:  WMSysKeyDown  (hwnd, wParam, lParam); break;
   case WM_SYSKEYUP:    WMSysKeyUp    (hwnd, wParam, lParam); break;
   case WM_SYSCHAR:     WMSysChar     (hwnd, wParam, lParam); break;
   case WM_SYSDEADCHAR: WMSysDeadChar (hwnd, wParam, lParam); break;
 	 case WM_DESTROY:     return WMDestroy     (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

long cxChar, cyChar;
RECT rcPaint;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC        hdc;
  TEXTMETRIC tm;

  hdc = GetDC (hwnd);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight;

  ReleaseDC (hwnd, hdc);

  rcPaint.left = 0;
  rcPaint.top = 3*cyChar/2;

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  rcPaint.right = LOWORD (lParam);
  rcPaint.bottom = HIWORD (lParam);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC         hdc;
  PAINTSTRUCT ps;
  static char szTop [] = "Message        Key Char Repeat Scan Ext ALT Prev Tran";
  static char szUnd [] = "_______        ___ ____ ______ ____ ___ ___ ____ ____";

  InvalidateRect (hwnd, NULL, TRUE);
  hdc = BeginPaint (hwnd, &ps);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  SetBkMode (hdc, TRANSPARENT);
  TextOut (hdc, cxChar, cyChar / 2, szTop, sizeof (szTop) - 1);
  TextOut (hdc, cxChar, cyChar / 2, szUnd, sizeof (szUnd) - 1);

  EndPaint (hwnd, &ps);

  return 0;
}


void ShowKey (HWND hwnd, int iType, char* szMessage, WPARAM wParam, LPARAM lParam)
{
  static char* szFormat [2] =
    {"%-14s %3d    %c %6u %4d %3s %3s %4s %4s",
     "%-14s    %3d %c %6u %4d %3s %3s %4s %4s"};

  char szBuffer [80];
  HDC  hdc;

  ScrollWindow (hwnd, 0, -cyChar, &rcPaint, &rcPaint);

  hdc = GetDC (hwnd);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  TextOut (hdc, cxChar, rcPaint.bottom - cyChar, szBuffer,
           wsprintf (szBuffer, szFormat [iType],
                     (LPSTR) szMessage, wParam,
                     (BYTE) (iType ? wParam : ' '),
                     LOWORD (lParam),
                     HIWORD (lParam) & 0xFF,
                     (LPSTR) (0x01000000L & lParam ? "Yes"  : "No"),
                     (LPSTR) (0x20000000L & lParam ? "Yes"  : "No"),
                     (LPSTR) (0x40000000L & lParam ? "Down" : "Up"),
                     (LPSTR) (0x80000000L & lParam ? "Up"   : "Down")));

	
  ReleaseDC (hwnd, hdc);

  ValidateRect (hwnd, NULL);
}


long WMKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 0, "WM_KEYDOWN", wParam, lParam);

  return 0;
}


long WMKeyUp (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 0, "WM_KEYUP", wParam, lParam);

  return 0;
}


long WMChar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 1, "WM_CHAR", wParam, lParam);

  return 0;
}


long WMDeadChar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 1, "WM_DEADCHAR", wParam, lParam);

  return 0;
}


long WMSysKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 0, "WM_SYSKEYDOWN", wParam, lParam);

  return 0;
}


long WMSysKeyUp (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 0, "WM_SYSKEYUP", wParam, lParam);

  return 0;
}


long WMSysChar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 1, "WM_SYSCHAR", wParam, lParam);

  return 0;
}


long WMSysDeadChar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  ShowKey (hwnd, 1, "WM_SYSDEADCHAR", wParam, lParam);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


