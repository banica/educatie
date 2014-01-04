#include <windows.h>

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam);


void InitClass (WNDCLASS* wndclass, HANDLE hInstance, char* szAppName)
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

BOOL InitApplication (HANDLE hInstance, char* szAppName)
{
  WNDCLASS wndclass;

  InitClass (&wndclass, hInstance, szAppName);
  return RegisterClass (&wndclass);
}

BOOL InitInstance (HANDLE hInstance, char* szAppName, int nCmdShow)
{
  HWND		  hwnd;

  hwnd = CreateWindow (szAppName,
							  "Aplicatie Windows",
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

BOOL AppInit (HANDLE hInstance,
				  HANDLE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "schelet";

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

LRESULT CALLBACK	WndProc(HWND hwnd, 
							UINT message, 
							WPARAM wParam, 
							LPARAM lParam)


{

	HDC         hdc;
  PAINTSTRUCT ps;
  RECT        rect;
	

  switch (message) {
		
	case WM_PAINT:

	  hdc = BeginPaint (hwnd, &ps);

	  GetClientRect (hwnd, &rect);

	  DrawText (hdc, "Hello, Windows!", -1, &rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	  EndPaint (hwnd, &ps);
	  return 0;


	case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


