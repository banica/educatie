#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMCommand  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy  (HWND hwnd, WPARAM wParam, LPARAM lParam);

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
							  "Popup Editor",
							  WS_OVERLAPPEDWINDOW,
							  CW_USEDEFAULT,
							  CW_USEDEFAULT,
							  GetSystemMetrics (SM_CXSCREEN) / 2,
							  GetSystemMetrics (SM_CYSCREEN) / 2,
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
  static char szAppName [] = "PopPad1";

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

	case WM_CREATE:   return WMCreate   (hwnd, wParam, lParam);
	case WM_SETFOCUS: return WMSetFocus (hwnd, wParam, lParam);
	case WM_SIZE:     return WMSize     (hwnd, wParam, lParam);
	case WM_COMMAND:  return WMCommand  (hwnd, wParam, lParam);
	case WM_DESTROY:  return WMDestroy  (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


HWND hwndEdit;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  hwndEdit = CreateWindow ("edit",
                           NULL,
                           WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                           WS_BORDER | ES_LEFT | ES_MULTILINE |
                           ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                           0, 0, 0, 0,
                           hwnd,
                           (HMENU) 1,
                           ((LPCREATESTRUCT) lParam)->hInstance,
                           NULL);

  return 0;
}


long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam){
  SetFocus (hwndEdit);

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam){
  MoveWindow (hwndEdit, 0, 0, LOWORD (lParam), HIWORD (lParam), TRUE);

  return 0;
}


long WMCommand (HWND hwnd, WPARAM wParam, LPARAM lParam){
  if (LOWORD(wParam) == 1 && HIWORD (wParam) == EN_ERRSPACE)
    MessageBox (hwnd, "Edit control out of space.", "Popup Editor", MB_OK | MB_ICONSTOP);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam){
  PostQuitMessage (0);

  return 0;
}


