#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate  (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Hatch Brushes Demonstration",
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
  static char szAppName [] = "Brushes";

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
	case WM_PAINT:   return WMPaint   (hwnd, wParam, lParam);
	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


int cxChar, cyChar;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  TEXTMETRIC tm;
  HDC        hdc;

  hdc = GetDC (hwnd);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight + tm.tmExternalLeading;

  ReleaseDC (hwnd, hdc);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  #define NUMBRUSH (sizeof (lbrBrushes) / sizeof (LOGBRUSH))
  static LOGBRUSH lbrBrushes [] = {{BS_HATCHED, RGB (0, 0, 0), HS_HORIZONTAL},
                                   {BS_HATCHED, RGB (0, 0, 0), HS_VERTICAL},
                                   {BS_HATCHED, RGB (0, 0, 0), HS_FDIAGONAL},
                                   {BS_HATCHED, RGB (0, 0, 0), HS_BDIAGONAL},
                                   {BS_HATCHED, RGB (0, 0, 0), HS_CROSS},
                                   {BS_HATCHED, RGB (0, 0, 0), HS_DIAGCROSS}};

  static char* lpszBrushDescr [] = {"HS_HORIZONTAL",
                                    "HS_VERTICAL",
                                    "HS_FDIAGONAL",
                                    "HS_BDIAGONAL",
                                    "HS_CROSS",
                                    "HS_DIAGCROSS"};

  PAINTSTRUCT ps;
  HDC         hdc;
  HBRUSH      hBrush;
  int         i;

  hdc = BeginPaint (hwnd, &ps);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  SetMapMode     (hdc, MM_ANISOTROPIC);
  SetWindowExtEx   (hdc,1,1,NULL);
  SetViewportExtEx (hdc,cxChar,cyChar/2,NULL);

  SetBkMode (hdc, TRANSPARENT);
  SelectObject (hdc, GetStockObject (NULL_PEN));

  for (i = 0; i < NUMBRUSH; i++) {

    TextOut (hdc, 1, 6*i + 2, lpszBrushDescr [i], lstrlen (lpszBrushDescr [i]));

    hBrush = CreateBrushIndirect (&lbrBrushes [i]);
    hBrush = SelectObject (hdc, hBrush);

    Rectangle (hdc, 16, 6*i + 1, 36, 6*i + 6);

    hBrush = SelectObject (hdc, hBrush);
    DeleteObject (hBrush);
  }

  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam){
  PostQuitMessage (0);

  return 0;
}


