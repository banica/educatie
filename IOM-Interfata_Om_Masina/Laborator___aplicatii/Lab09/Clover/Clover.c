#include <windows.h>
#include <math.h>

#define TWO_PI (2.0 * 3.14159)

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMSize    (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Draw a Clover",
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
  static char szAppName [] = "Clover";

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

	case WM_SIZE:    return WMSize    (hwnd, wParam, lParam);
	case WM_PAINT:   return WMPaint   (hwnd, wParam, lParam);
	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


int  cxClient, cyClient;
HRGN hRgnClip;

long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HRGN    hRgnTemp [6];
  HCURSOR hCursor;
  short   i;

  cxClient = LOWORD (lParam);
  cyClient = HIWORD (lParam);

  hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
  ShowCursor (TRUE);

  if (hRgnClip != NULL)
    DeleteObject (hRgnClip);

  hRgnTemp [0] = CreateEllipticRgn (0,                cyClient / 3,
                                      cxClient / 2, 2*cyClient / 3);
  hRgnTemp [1] = CreateEllipticRgn (  cxClient / 2,   cyClient / 3,
                                      cxClient,     2*cyClient / 3);
  hRgnTemp [2] = CreateEllipticRgn (  cxClient / 3, 0,
                                    2*cxClient / 3,   cyClient / 2);
  hRgnTemp [3] = CreateEllipticRgn (  cxClient / 3,   cyClient / 2,
                                    2*cxClient / 3,   cyClient);

  hRgnTemp [4] = CreateRectRgn (0, 0, 1, 1);
  hRgnTemp [5] = CreateRectRgn (0, 0, 1, 1);
  hRgnClip     = CreateRectRgn (0, 0, 1, 1);

  if (CombineRgn (hRgnTemp [4], hRgnTemp [0], hRgnTemp [1], RGN_OR)  == ERROR ||
      CombineRgn (hRgnTemp [5], hRgnTemp [2], hRgnTemp [3], RGN_OR)  == ERROR ||
      CombineRgn (hRgnClip,     hRgnTemp [4], hRgnTemp [5], RGN_XOR) == ERROR)

    MessageBox (hwnd, "Could not create region, window size too big!",
                "Clover", MB_ICONEXCLAMATION | MB_OK);

  for (i = 0; i < 6; i++)
    DeleteObject (hRgnTemp [i]);

  SetCursor (hCursor);
  ShowCursor (FALSE);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  double      fAngle, fRadius;
  HDC         hdc;
  PAINTSTRUCT ps;

  hdc = BeginPaint (hwnd, &ps);

  SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2,NULL);
  SelectClipRgn  (hdc, hRgnClip);

  fRadius = hypot (cxClient / 2.0, cyClient / 2.0);

  for (fAngle = 0.0; fAngle < TWO_PI; fAngle += TWO_PI / 360.0) {
    MoveToEx (hdc, 0, 0,NULL);
    LineTo (hdc, (int) ( fRadius*cos (fAngle) + 0.5),
                 (int) (-fRadius*sin (fAngle) + 0.5));
  }

  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam){
  if (hRgnClip != NULL)
    DeleteObject (hRgnClip);
  PostQuitMessage (0);

  return 0;
}


