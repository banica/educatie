#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMPaint   (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "ROP2 Demonstration Program",
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
  static char szAppName [] = "Rop2Look";

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

	case WM_PAINT:   return WMPaint   (hwnd, wParam, lParam);
	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  static LOGPEN lpBlack =     {PS_SOLID, {1, 0}, RGB (  0,   0,   0)},
                lpWhite =     {PS_SOLID, {1, 0}, RGB (255, 255, 255)},
                lpSeparator = {PS_SOLID, {0, 0}, RGB (  0,   0,   0)};

  static struct tagDrawingModes{
    short nMode;
    char  szDescr[20];
  } DrawingModes [] = {{R2_BLACK,        "R2_BLACK"},
                       {R2_NOTMERGEPEN,  "R2_NOTMERGEPEN"},
                       {R2_MASKNOTPEN,   "R2_MASKNOTPEN"},
                       {R2_NOTCOPYPEN,   "R2_NOTCOPYPEN"},
                       {R2_MASKPENNOT,   "R2_MASKPENNOT"},
                       {R2_NOT,          "R2_NOT"},
                       {R2_XORPEN,       "R2_XORPEN"},
                       {R2_NOTMASKPEN,   "R2_NOTMASKPEN"},
                       {R2_MASKPEN,      "R2_MASKPEN"},
                       {R2_NOTXORPEN,    "R2_NOTXORPEN"},
                       {R2_NOP,          "R2_NOP"},
                       {R2_MERGENOTPEN,  "R2_MERGENOTPEN"},
                       {R2_COPYPEN,      "R2_COPYPEN"},
                       {R2_MERGEPENNOT,  "R2_MERGEPENNOT"},
                       {R2_MERGEPEN,     "R2_MERGEPEN"},
                       {R2_WHITE,        "R2_WHITE"}};

  static int    nDrawingNumber = sizeof (DrawingModes) /
                                 sizeof (struct tagDrawingModes);

  HDC           hdc;
  HPEN          hPenBlack, hPenWhite, hPenSeparator;
  PAINTSTRUCT   ps;
  RECT          rect;
  TEXTMETRIC    tm;

  int           cxChar, cyChar;
  short         i;

  hPenBlack     = CreatePenIndirect (&lpBlack);
  hPenWhite     = CreatePenIndirect (&lpWhite);
  hPenSeparator = CreatePenIndirect (&lpSeparator);

  hdc = BeginPaint (hwnd, &ps);

  SetMapMode (hdc, MM_ANISOTROPIC);
  GetClientRect (hwnd, &rect);
  SetWindowExtEx (hdc, 120, 4*nDrawingNumber,NULL);
  SetViewportExtEx (hdc, rect.right, rect.bottom,NULL);
  SetBkMode (hdc, TRANSPARENT);

  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight;

  for (i = 0; i < 100; i += 20) {
    SetRect (&rect, i + 20, 0, i + 40, 4*nDrawingNumber);
    FillRect (hdc, &rect, GetStockObject (i / 20));
  }

  for (i = 0; i < nDrawingNumber; i++) {

    SetROP2 (hdc, R2_NOT);

    SelectObject (hdc, hPenSeparator);
    MoveToEx (hdc,   0, 4*i,NULL);
    LineTo (hdc, 120, 4*i);

    SetROP2 (hdc, DrawingModes [i].nMode);

    SelectObject (hdc, hPenWhite);
    MoveToEx (hdc, 30, 4*i + 1,NULL);
    LineTo (hdc,110, 4*i + 1);

    SelectObject (hdc, hPenBlack);
    MoveToEx (hdc, 30, 4*i + 3,NULL);
    LineTo (hdc,110, 4*i + 3);

    TextOut (hdc, cxChar, 4*i + 2 - cyChar / 2, DrawingModes [i].szDescr,
             lstrlen (DrawingModes [i].szDescr));
  }

  EndPaint (hwnd, &ps);

  DeleteObject (hPenBlack);
  DeleteObject (hPenWhite);
  DeleteObject (hPenSeparator);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


