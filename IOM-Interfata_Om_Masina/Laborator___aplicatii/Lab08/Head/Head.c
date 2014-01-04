#include <windows.h>
#include <io.h>
#include <string.h>
#include <direct.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMCommand  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy  (HWND hwnd, WPARAM wParam, LPARAM lParam);

long ListWMKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam);

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = LoadIcon (NULL, IDI_APPLICATION);
  wndclass->hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass->hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
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
							  "File Head",
							  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
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
  static char szAppName [] = "Head";

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

	case WM_CREATE:   return WMCreate   (hwnd, wParam, lParam);
	case WM_SIZE:     return WMSize     (hwnd, wParam, lParam);
	case WM_SETFOCUS: return WMSetFocus (hwnd, wParam, lParam);
	case WM_COMMAND:  return WMCommand  (hwnd, wParam, lParam);
	case WM_PAINT:    return WMPaint    (hwnd, wParam, lParam);
	case WM_DESTROY:  return WMDestroy  (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


#define MAXPATH 80

BOOL     bValidFile;
char     szFile [16];
HWND     hwndList, hwndText;
OFSTRUCT ofs;
RECT     rcPaint;
WNDPROC  lpfnOldList;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char       szBuffer [MAXPATH + 1];
  HINSTANCE     hInstance;
  HDC        hdc;
  TEXTMETRIC tm;

  hdc = GetDC (hwnd);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
  GetTextMetrics (hdc, &tm);
  ReleaseDC (hwnd, hdc);

  rcPaint.left = 20*tm.tmAveCharWidth;
  rcPaint.top  =  3*tm.tmHeight;

  hInstance = (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE);
  hwndList = CreateWindow ("listbox",
                           NULL,
                           WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD,
                           tm.tmAveCharWidth,
                           tm.tmHeight*3,
                           tm.tmAveCharWidth*13 + GetSystemMetrics (SM_CXVSCROLL),
                           tm.tmHeight*10,
                           hwnd,
                           (HMENU)1,
                           hInstance,
                           NULL);

  lpfnOldList = (WNDPROC) GetWindowLong (hwndList, GWL_WNDPROC);
  SetWindowLong (hwndList, GWL_WNDPROC, (LONG)ListProc);
  SendMessage (hwndList, LB_DIR, 0x37, (LONG) (LPSTR) "*.*");

  hwndText = CreateWindow ("static",
                           getcwd (szBuffer, MAXPATH),
                           WS_CHILDWINDOW | WS_VISIBLE | SS_LEFT,
                           tm.tmAveCharWidth,
                           tm.tmHeight,
                           tm.tmAveCharWidth*MAXPATH,
                           tm.tmHeight,
                           hwnd,
                           (HMENU)2,
                           hInstance,
                           NULL);

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  rcPaint.right  = LOWORD (lParam);
  rcPaint.bottom = HIWORD (lParam);

  return 0;
}


long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetFocus (hwndList);

  return 0;
}


long WMCommand (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char     szBuffer [MAXPATH + 1];
  short    i;

	if (LOWORD(wParam) == 1 && HIWORD (wParam) == LBN_DBLCLK) {
    i = (WORD) SendMessage (hwndList, LB_GETCURSEL, 0, 0);
    if (i == LB_ERR)
      return 0;

    SendMessage (hwndList, LB_GETTEXT, i, (LONG) (char far*) szBuffer);
    if (OpenFile (szBuffer, &ofs, OF_EXIST | OF_READ) != -1) {

      bValidFile = TRUE;
      strcpy (szFile, szBuffer);
      getcwd (szBuffer, MAXPATH);
      if (szBuffer [strlen (szBuffer) - 1] != '\\')
        strcat (szBuffer, "\\");
      SetWindowText (hwndText, strcat (szBuffer, szFile));

    } else {

      bValidFile = FALSE;
      szBuffer [strlen (szBuffer) - 1] = '\0';
      chdir (szBuffer + 1);
      getcwd (szBuffer, MAXPATH);
      SendMessage (hwndList, LB_RESETCONTENT, 0, 0);
      SendMessage (hwndList, LB_DIR, 0x37, (LONG) (LPSTR) "*.*");
    }

    InvalidateRect (hwnd, NULL, TRUE);
  }
  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  #define MAXREAD 2048

  char        sReadBuffer [MAXREAD];
  HDC         hdc;
  PAINTSTRUCT ps;
  int         iCount;  
	HANDLE			iHINSTANCE;

  hdc = BeginPaint (hwnd, &ps);
  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
  SetTextColor (hdc, GetSysColor (COLOR_WINDOWTEXT));
  SetBkColor   (hdc, GetSysColor (COLOR_BTNFACE));

	if (bValidFile) {
    iHINSTANCE = CreateFile (szFile, GENERIC_READ, FILE_SHARE_READ, 
 														 NULL, OPEN_EXISTING, 0, NULL);
    if (iHINSTANCE == (HANDLE) -1)
		{bValidFile = FALSE;
		}
    else {
			ReadFile (iHINSTANCE, sReadBuffer, MAXREAD, &iCount, NULL) ;
      CloseHandle (iHINSTANCE) ;
			DrawText (hdc, sReadBuffer, iCount, &rcPaint, 
					DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX) ;
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


LRESULT CALLBACK ListProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {

    case WM_KEYDOWN: ListWMKeyDown (hwnd, wParam, lParam); break;

  }

  return CallWindowProc (lpfnOldList, hwnd, message, wParam, lParam);
}

long ListWMKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  if (wParam == VK_RETURN)
    SendMessage (GetParent (hwnd), WM_COMMAND, MAKELONG (1, LBN_DBLCLK), (LPARAM)hwnd);

  return 0;
}





