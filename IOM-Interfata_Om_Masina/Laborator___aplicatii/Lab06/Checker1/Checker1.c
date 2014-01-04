#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMSize        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Checker1 Mouse Hit-Test Demo",
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
  static char szAppName [] = "Checker1";

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

	case WM_SIZE:        return WMSize        (hwnd, wParam, lParam);
	case WM_LBUTTONDOWN: return WMLButtonDown (hwnd, wParam, lParam);
	case WM_PAINT:       return WMPaint       (hwnd, wParam, lParam);
	case WM_DESTROY:     return WMDestroy     (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

#define DIVISIONS 5

BOOL  fState [DIVISIONS][DIVISIONS];
short cxBlock, cyBlock;

long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  cxBlock = LOWORD (lParam) / DIVISIONS;
  cyBlock = HIWORD (lParam) / DIVISIONS;

  return 0;
}


long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  RECT  rect;
  short x, y;

  x = LOWORD (lParam) / cxBlock;
  y = HIWORD (lParam) / cyBlock;

  if (x < DIVISIONS && y < DIVISIONS) {
    fState [x][y] ^= 1;
    rect.left   =  x     *cxBlock;
    rect.top    =  y     *cyBlock;
    rect.right  = (x + 1)*cxBlock;
    rect.bottom = (y + 1)*cyBlock;

    InvalidateRect (hwnd, &rect, FALSE);
  }
  else
    MessageBeep (0);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC         hdc;
  PAINTSTRUCT ps;
  short       x, y;

  hdc = BeginPaint (hwnd, &ps);

  for (x = 0; x < DIVISIONS; x++)
    for (y = 0; y < DIVISIONS; y++) {
      Rectangle (hdc, x*cxBlock, y*cyBlock, (x + 1)*cxBlock, (y + 1)*cyBlock);
      if (fState [x][y]) {
        MoveToEx (hdc, x*cxBlock, y*cyBlock, NULL);
        LineTo (hdc, (x + 1)*cxBlock, (y + 1)*cyBlock);
        MoveToEx (hdc, (x + 1)*cxBlock, y*cyBlock, NULL);
        LineTo (hdc, x*cxBlock, (y + 1)*cyBlock);
      }
    }
  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


