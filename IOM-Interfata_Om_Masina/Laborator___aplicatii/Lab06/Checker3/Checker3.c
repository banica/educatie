#include <windows.h>

LRESULT CALLBACK WndProc      (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate      (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy     (HWND hwnd, WPARAM wParam, LPARAM lParam);

long ChildWMCreate      (HWND hwnd, WPARAM wParam, LPARAM lParam);
long ChildWMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam);
long ChildWMPaint       (HWND hwnd, WPARAM wParam, LPARAM lParam);

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

void InitChildClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szChildName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = ChildWndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = sizeof (LONG);
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = NULL;
  wndclass->hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass->hbrBackground = GetStockObject (WHITE_BRUSH);
  wndclass->lpszMenuName  = NULL;
  wndclass->lpszClassName = szChildName;
}

BOOL InitApplication (HINSTANCE hInstance, char* szAppName, char*szChildName)
{
  WNDCLASS wndclass, childwndclass;

  InitClass (&wndclass, hInstance, szAppName);
  InitChildClass (&childwndclass, hInstance, szChildName);

  return (RegisterClass (&wndclass) && RegisterClass (&childwndclass));
}

BOOL InitInstance (HINSTANCE hInstance,
                   char* szAppName,
                   int nCmdShow)
{
  HWND		  hwnd;

  hwnd = CreateWindow (szAppName,
							  "Checker3 Mouse Hit-Test Demo",
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

char szAppName   [] = "Checker3";
char szChildName [] = "Checker3_Child";

BOOL AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  if (!hPrevInstance) {
	 if (!InitApplication (hInstance, szAppName, szChildName))
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

  case WM_CREATE:      return WMCreate      (hwnd, wParam, lParam);
	case WM_SIZE:        return WMSize        (hwnd, wParam, lParam);
	case WM_LBUTTONDOWN: return WMLButtonDown (hwnd, wParam, lParam);
	case WM_DESTROY:     return WMDestroy     (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


#define DIVISIONS 5

HWND  hwndChild [DIVISIONS][DIVISIONS];
short cxBlock, cyBlock;


long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  short x, y;

  for (x = 0; x < DIVISIONS; x++)
    for (y = 0; y < DIVISIONS; y++)
      hwndChild [x][y] = CreateWindow (szChildName, NULL,
                                       WS_CHILDWINDOW | WS_VISIBLE,
                                       0, 0, 0, 0,
                                       hwnd, 
																			 (HMENU) (y*DIVISIONS + x),
                                       (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  short x,y;

  cxBlock = LOWORD (lParam) / DIVISIONS;
  cyBlock = HIWORD (lParam) / DIVISIONS;

  for (x = 0; x < DIVISIONS; x++)
    for (y = 0; y < DIVISIONS; y++)
      MoveWindow (hwndChild [x][y], x*cxBlock, y*cyBlock, cxBlock, cyBlock, TRUE);

  return 0;
}


long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  MessageBeep (0);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


 LRESULT CALLBACK ChildWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {

	case WM_CREATE:      return ChildWMCreate      (hwnd, wParam, lParam);
	case WM_LBUTTONDOWN: return ChildWMLButtonDown (hwnd, wParam, lParam);
	case WM_PAINT:       return ChildWMPaint       (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

long ChildWMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetWindowLong (hwnd, 0, 0);

  return 0;
}


long ChildWMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetWindowLong (hwnd, 0, 1^GetWindowLong (hwnd, 0));
	InvalidateRect (hwnd, NULL, FALSE);

  return 0;
}


long ChildWMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC         hdc;
  PAINTSTRUCT ps;
  RECT        rect;
	

  hdc = BeginPaint (hwnd, &ps);

  GetClientRect (hwnd, &rect);
  Rectangle (hdc, 0, 0, rect.right, rect.bottom);

  if (GetWindowLong (hwnd, 0)) {
    MoveToEx (hdc, 0, 0, NULL);
    LineTo (hdc, rect.right, rect.bottom);
		MoveToEx (hdc, 0, rect.bottom, NULL);
    LineTo (hdc, rect.right, 0);
  }

  EndPaint (hwnd, &ps);

  return 0;
}




