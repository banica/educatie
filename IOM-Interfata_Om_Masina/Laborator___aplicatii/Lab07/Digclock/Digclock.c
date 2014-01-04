#include <windows.h>

#include <time.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate       (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMTimer        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMNcHitTest    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint        (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMWinIniChange (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy      (HWND hwnd, WPARAM wParam, LPARAM lParam);

#define ID_TIMER 1

void InitClass (WNDCLASS* wndclass, HINSTANCE hInstance, char* szAppName)
{
  wndclass->style         = CS_HREDRAW | CS_VREDRAW;
  wndclass->lpfnWndProc   = WndProc;
  wndclass->cbClsExtra    = 0;
  wndclass->cbWndExtra    = 0;
  wndclass->hInstance     = hInstance;
  wndclass->hIcon         = NULL;
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

  hwnd = CreateWindowEx (0X00000008L,
                         szAppName,
                         "Digital Clock",
                         WS_POPUP | WS_DLGFRAME,
                         0,
                         0,
                         0,
                         0,
                         NULL,
                         NULL,
                         hInstance,
                         NULL);
  if (hwnd == NULL)
	 return FALSE;

  while (!SetTimer (hwnd, ID_TIMER, 1000, NULL))
    if (IDCANCEL == MessageBox (hwnd, "Too many clocks or timers!", szAppName,
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL))
      return FALSE;

  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);

  return TRUE;
}

BOOL AppInit (HINSTANCE hInstance,
				  HINSTANCE hPrevInstance,
				  int nCmdShow)
{
  static char szAppName [] = "DigClock";

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

	case WM_CREATE:       return WMCreate       (hwnd, wParam, lParam);
	case WM_TIMER:        return WMTimer        (hwnd, wParam, lParam);
   case WM_NCHITTEST:    return WMNcHitTest    (hwnd, wParam, lParam);
	case WM_PAINT:        return WMPaint        (hwnd, wParam, lParam);
	case WM_WININICHANGE: return WMWinIniChange (hwnd, wParam, lParam);
	case WM_DESTROY:      return WMDestroy      (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


char sDate [2], sTime [2], sAMPM [2][5];
int  iDate, iTime;


void SetInternational (void)
{
  char cName [] = "intl";

  iDate = GetProfileInt (cName, "iDate", 0);
  iTime = GetProfileInt (cName, "iTime", 0);

  GetProfileString (cName, "sDate",  "/", sDate,     2);
  GetProfileString (cName, "sTime",  ":", sTime,     2);
  GetProfileString (cName, "s1159", "AM", sAMPM [0], 5);
  GetProfileString (cName, "s2359", "PM", sAMPM [1], 5);
}


long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC        hdc;
  TEXTMETRIC tm;
  int xClient, yClient, cxClient, cyClient;

  hdc = CreateIC ("DISPLAY", NULL, NULL, NULL);
  GetTextMetrics (hdc, &tm);
  DeleteDC (hdc);

  cxClient = 2*GetSystemMetrics (SM_CXDLGFRAME) + 16*tm.tmAveCharWidth;
  xClient  =   GetSystemMetrics (SM_CXSCREEN) - cxClient;
  cyClient = 2*GetSystemMetrics (SM_CYDLGFRAME) +  2*tm.tmHeight;
  yClient  =   GetSystemMetrics (SM_CYSCREEN) - cyClient;

  MoveWindow (hwnd, xClient, yClient, cxClient, cyClient, TRUE);

  SetInternational ();

  return 0;
}


long WMTimer (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  InvalidateRect (hwnd, NULL, FALSE);

  return 0;
}


long WMNcHitTest (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  return HTCAPTION;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{

#define YEAR  (datetime->tm_year % 100)
#define MONTH (datetime->tm_mon + 1)
#define MDAY  (datetime->tm_mday)
#define WDAY  (datetime->tm_wday)
#define HOUR  (datetime->tm_hour)
#define MIN   (datetime->tm_min)
#define SEC   (datetime->tm_sec)

  char        szWday [] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
  char        cBuffer [40];
  RECT        rcClient;
  HDC         hdc;
  PAINTSTRUCT ps;
  int         nLength;
  long        lTime;
  struct tm*  datetime;

  hdc = BeginPaint (hwnd, &ps);

  time (&lTime);
  datetime = localtime (&lTime);

  nLength = wsprintf (cBuffer, " %s %d%s%02d%s%02d \r\n",
                      (LPSTR) szWday + 4*WDAY,
                      iDate == 1 ? MDAY  : (iDate == 2 ? YEAR  : MONTH), (LPSTR) sDate,
                      iDate == 1 ? MONTH : (iDate == 2 ? MONTH : MDAY ), (LPSTR) sDate,
                      iDate == 1 ? YEAR  : (iDate == 2 ? MDAY  : YEAR ));
  if (iTime == 1)
    nLength += wsprintf (cBuffer + nLength, "  %02d%s%02d%s%02d  ",
                         HOUR, (LPSTR) sTime, MIN, (LPSTR) sTime, SEC);
  else
    nLength += wsprintf (cBuffer + nLength, "  %d%s%02d%s%02d %s  ",
                         (HOUR % 12) ? (HOUR % 12) : 12,
                         (LPSTR) sTime, MIN, (LPSTR) sTime, SEC,
                         (LPSTR) sAMPM [HOUR / 12]);

  GetClientRect (hwnd, &rcClient);
  DrawText (hdc, cBuffer, -1, &rcClient, DT_CENTER | DT_NOCLIP);

  EndPaint (hwnd, &ps);

  return 0;
}


long WMWinIniChange (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  SetInternational ();
  InvalidateRect (hwnd, NULL, TRUE);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  KillTimer (hwnd, ID_TIMER);
  PostQuitMessage (0);

  return 0;
}


