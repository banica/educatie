#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMMouseMove   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMLButtonUp   (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Capture Screen Mouse Demo",
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
  static char szAppName [] = "CapScr1";

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

	case WM_LBUTTONDOWN: return WMLButtonDown (hwnd, wParam, lParam);
	case WM_MOUSEMOVE:   return WMMouseMove   (hwnd, wParam, lParam);
	case WM_LBUTTONUP:   return WMLButtonUp   (hwnd, wParam, lParam);
	case WM_DESTROY:     return WMDestroy     (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


BOOL fCapturing = FALSE;
BOOL fBlocking  = FALSE;
POINT ptBeg, ptEnd;

long WMLButtonDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{

  if (!fCapturing) {
    fCapturing = TRUE;
    SetCapture (hwnd);
    SetCursor (LoadCursor (NULL, IDC_CROSS));
		} 
	else if (!fBlocking) {
    fBlocking = TRUE;
		ptBeg.x = LOWORD (lParam);
		ptBeg.y = HIWORD (lParam);
    ptEnd = ptBeg;
		}
  return 0;
}


void InvertBlock (HWND hwnd, POINT ptBeg, POINT ptEnd)
{
  HDC hdc;

  hdc = CreateDC ("DISPLAY", NULL, NULL, NULL);
  ClientToScreen (hwnd, &ptBeg);
  ClientToScreen (hwnd, &ptEnd);

  PatBlt (hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y, DSTINVERT);

  DeleteDC (hdc);
}

long WMMouseMove (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  if (fBlocking) {
    InvertBlock (hwnd, ptBeg, ptEnd);
		ptEnd.x = LOWORD (lParam);
		ptEnd.y = HIWORD (lParam);
    InvertBlock (hwnd, ptBeg, ptEnd);
  }

  return 0;
}


long WMLButtonUp (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC  hdc;
  RECT rect;

  if (fBlocking) {
    fCapturing = fBlocking = FALSE;
    InvertBlock (hwnd, ptBeg, ptEnd);
    ptEnd.x = LOWORD (lParam);
		ptEnd.y = HIWORD (lParam);
    SetCursor (LoadCursor (NULL, IDC_WAIT));

    hdc = GetDC (hwnd);

    GetClientRect (hwnd, &rect);
    StretchBlt (hdc, 0, 0, rect.right, rect.bottom,
                hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y, SRCCOPY);

    ReleaseDC (hwnd, hdc);

    SetCursor (LoadCursor (NULL, IDC_ARROW));
    ReleaseCapture ();
  }

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


