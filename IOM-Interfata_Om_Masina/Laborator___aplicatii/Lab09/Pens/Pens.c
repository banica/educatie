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
							  "Pen Style Demonstration Program",
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
  static char szAppName [] = "Pens";

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
  #define NUMPEN (sizeof (lpnPens) / sizeof (LOGPEN))
  static LOGPEN lpnPens [] = {{PS_SOLID,       {0, 0}, RGB (0, 0, 0)},
                              {PS_DASH,        {0, 0}, RGB (0, 0, 0)},
                              {PS_DOT,         {0, 0}, RGB (0, 0, 0)},
                              {PS_DASHDOT,     {0, 0}, RGB (0, 0, 0)},
                              {PS_DASHDOTDOT,  {0, 0}, RGB (0, 0, 0)},
                              {PS_NULL,        {0, 0}, RGB (0, 0, 0)},
                              {PS_INSIDEFRAME, {0, 0}, RGB (0, 0, 0)}};

  static char* lpszPenDescr [] = {"PS_SOLID",
                                  "PS_DASH",
                                  "PS_DOT",
                                  "PS_DASHDOT",
                                  "PS_DASHDOTDOT",
                                  "PS_NULL",
                                  "PS_INSIDEFRAME"};

  PAINTSTRUCT ps;
  HDC         hdc;
  HPEN        hPen;
  int         i;

  hdc = BeginPaint (hwnd, &ps);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  SetMapMode     (hdc, MM_ANISOTROPIC);
  SetWindowExtEx   (hdc,1,1,NULL);
  SetViewportExtEx (hdc,cxChar,cyChar/2,NULL);

  SetBkMode (hdc, TRANSPARENT);

  for (i = 0; i < NUMPEN; i++) {

    TextOut (hdc, 1, 2*i + 1, lpszPenDescr [i], lstrlen (lpszPenDescr [i]));

    hPen = CreatePenIndirect (&lpnPens [i]);
    hPen = SelectObject (hdc, hPen);

    MoveToEx (hdc, 16, 2*i + 2,NULL);
    LineTo (hdc, 36, 2*i + 2);

    hPen = SelectObject (hdc, hPen);
    DeleteObject (hPen);
  }

  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam){
  PostQuitMessage (0);

  return 0;
}


