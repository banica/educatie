#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMCommand (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam);

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
							  "Button Look",
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
  static char szAppName [] = "BtnLook";

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

	case WM_CREATE:  return WMCreate  (hwnd, wParam, lParam);
	case WM_SIZE:    return WMSize    (hwnd, wParam, lParam);
	case WM_PAINT:   return WMPaint   (hwnd, wParam, lParam);
	case WM_COMMAND: return WMCommand (hwnd, wParam, lParam);
	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


typedef struct {
  long style;
  char* text;
} buttonstruct;

buttonstruct button [] =
  {{BS_PUSHBUTTON,       "PUSHBUTTON"     },
   {BS_DEFPUSHBUTTON,    "DEFPUSHBUTTON"  },
   {BS_CHECKBOX,         "CHECKBOX"       },
   {BS_AUTOCHECKBOX,     "AUTOCHECKBOX"   },
   {BS_3STATE,           "3STATE"         },
   {BS_AUTO3STATE,       "AUTO3STATE"     },
   {BS_RADIOBUTTON,      "RADIOBUTTON"    },
   {BS_AUTORADIOBUTTON,  "AUTORADIOBUTTON"},
   {BS_GROUPBOX,         "GROUPBOX"       },
   {BS_USERBUTTON,       "USERBUTTON"     }};

#define NUMBUTTONS (sizeof (button) / sizeof (buttonstruct))

long cxChar, cyChar;
HWND  hwndButton [NUMBUTTONS];
RECT  rcPaint;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC        hdc;
  TEXTMETRIC tm;
  short      i;

  hdc = GetDC (hwnd);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight + tm.tmExternalLeading;

  ReleaseDC (hwnd, hdc);

  for (i = 0; i < NUMBUTTONS; i++)
    hwndButton [i] = CreateWindow ("button",
                                   button [i].text,
                                   WS_CHILD | WS_VISIBLE | button [i].style,
                                   cxChar,
                                   cyChar*(2*i + 1),
                                   20*cxChar,
                                   7*cyChar / 4,
                                   hwnd,
                                   (HMENU)i,
                                   ((LPCREATESTRUCT) lParam) -> hInstance,
                                   NULL);

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  rcPaint.left   = 24*cxChar;
  rcPaint.top    =  3*cyChar;
  rcPaint.right  = LOWORD (lParam);
  rcPaint.bottom = HIWORD (lParam);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  static char szPrm [] = "LOWORD(wParam) HIWORD(lParam)  HIWORD(lParam)";
  static char szTop [] = "Control ID     Notification    Window HINSTANCE   ";
  static char szUnd [] = "__________     ____________    ________________";

  HDC         hdc;
  PAINTSTRUCT ps;

  InvalidateRect (hwnd, &rcPaint, TRUE);

  hdc = BeginPaint (hwnd, &ps);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
  SetBkMode (hdc, TRANSPARENT);

  TextOut (hdc, rcPaint.left, 1*cyChar, szPrm, sizeof (szPrm) - 1);
  TextOut (hdc, rcPaint.left, 2*cyChar, szTop, sizeof (szTop) - 1);
  TextOut (hdc, rcPaint.left, 2*cyChar, szUnd, sizeof (szUnd) - 1);

  EndPaint (hwnd, &ps);

  return 0;
}


long WMCommand (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  static char szFormat [] = " %4X              %04X          %04X-%04X";
  static char szBuffer [50];

  HDC         hdc;
  
  ScrollWindow (hwnd, 0, -cyChar, &rcPaint, &rcPaint);

  hdc = GetDC (hwnd);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  TextOut (hdc, rcPaint.left, cyChar*(rcPaint.bottom / cyChar - 1), szBuffer,
           sprintf (szBuffer, szFormat, LOWORD(wParam), HIWORD (wParam), LOWORD(lParam), HIWORD(lParam)));

  ReleaseDC (hwnd, hdc);
  ValidateRect (hwnd, NULL);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}



