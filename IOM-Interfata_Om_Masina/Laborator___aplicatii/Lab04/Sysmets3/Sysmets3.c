#include <windows.h>

#include "sysmets.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMVScroll (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMHScroll (HWND hwnd, WPARAM wParam, LPARAM lParam);
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
							  "Metrici sistem No. 3",
							  WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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
  static char szAppName [] = "SysMets3";

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
  MSG msg;

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
 	 case WM_SIZE:    return WMSize    (hwnd, wParam, lParam);
	 case WM_VSCROLL: return WMVScroll (hwnd, wParam, lParam);
	 case WM_HSCROLL: return WMHScroll (hwnd, wParam, lParam);
	 case WM_PAINT:   return WMPaint   (hwnd, wParam, lParam);
	 case WM_DESTROY: return WMDestroy (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}

long  cxChar, cyChar, cxCaps, nMaxWidth, cxClient, cyClient;
long nVScrollPos, nVScrollMax, nVScrollPage,
      nHScrollPos, nHScrollMax, nHScrollPage;

long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC          hdc;
  TEXTMETRIC   tm;

  hdc = GetDC (hwnd);

  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  if ((tm.tmPitchAndFamily & 0x0001) == 0)
    cxCaps = cxChar;
  else
    cxCaps = 3 * cxChar / 2;
  cyChar = tm.tmHeight + tm.tmExternalLeading;

  ReleaseDC (hwnd, hdc);

  nMaxWidth = 50*cxChar + 18*cxCaps;
  nVScrollPos = 0;
  nHScrollPos = 0;

  return 0;
}

long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  cxClient = LOWORD (lParam);
  cyClient = HIWORD (lParam);

  nVScrollPage = cyClient / cyChar;
  if (nVScrollPage == 0)
    nVScrollPage = 1;

  nVScrollMax = NUMLINES + 2 - nVScrollPage;
  if (nVScrollMax < 0)
    nVScrollMax = 0;
  if (nVScrollPos > nVScrollMax)
    nVScrollPos = nVScrollMax;

  SetScrollRange (hwnd, SB_VERT, 0, nVScrollMax, FALSE);
  SetScrollPos   (hwnd, SB_VERT, nVScrollPos, TRUE);

  nHScrollPage = 8;
  nHScrollMax = 2 + (nMaxWidth - cxClient) / cxChar;
  if (nHScrollMax < 0)
    nHScrollMax = 0;
  if (nHScrollPos > nHScrollMax)
    nHScrollPos = nHScrollMax;

  SetScrollRange (hwnd, SB_HORZ, 0, nHScrollMax, FALSE);
  SetScrollPos   (hwnd, SB_HORZ, nHScrollPos, TRUE);

  return 0;
}

long GetScrollInc (WPARAM wParam,
                    LPARAM lParam,
                    long nScrollPos,
                    long nScrollPage,
                    long nScrollMax)
{
  long nScrollInc;

  switch (LOWORD(wParam)) {

   case SB_TOP:
     nScrollInc = -nScrollPos;
     break;

   case SB_BOTTOM:
     nScrollInc = nScrollMax - nScrollPos;
     break;

   case SB_LINEUP:
     nScrollInc = -1;
     break;

   case SB_LINEDOWN:
     nScrollInc = 1;
     break;

   case SB_PAGEUP:
     nScrollInc = -nScrollPage;
     break;

   case SB_PAGEDOWN:
     nScrollInc = nScrollPage;
     break;

   case SB_THUMBTRACK:
     nScrollInc = HIWORD (wParam) - nScrollPos;
     break;

   default:
     nScrollInc = 0;
     break;
  }

  if (nScrollInc + nScrollPos < 0)
    nScrollInc = -nScrollPos;
  else if (nScrollInc + nScrollPos > nScrollMax)
    nScrollInc = nScrollMax - nScrollPos;

  return nScrollInc;
}

long WMVScroll (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  long nVScrollInc;

  nVScrollInc = GetScrollInc (wParam, lParam, nVScrollPos, nVScrollPage, nVScrollMax);

  if (nVScrollInc != 0) {
   nVScrollPos += nVScrollInc;
   SetScrollPos (hwnd, SB_VERT, nVScrollPos, TRUE);
   ScrollWindow (hwnd, 0, -cyChar * nVScrollInc, NULL, NULL);
   UpdateWindow (hwnd);
  }

  return 0;
}

long WMHScroll (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  long nHScrollInc;

  nHScrollInc = GetScrollInc (wParam, lParam, nHScrollPos, nHScrollPage, nHScrollMax);

  if (nHScrollInc != 0) {
   nHScrollPos += nHScrollInc;
   SetScrollPos (hwnd, SB_HORZ, nHScrollPos, TRUE);
   ScrollWindow (hwnd, -cxChar * nHScrollInc, 0, NULL, NULL);
  }

  return 0;
}

long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  char		  szBuffer [10];
  HDC       hdc;
	long			i, x, y, nPaintBeg, nPaintEnd;
  PAINTSTRUCT  ps;

  hdc = BeginPaint (hwnd, &ps);

  nPaintBeg = nVScrollPos + ps.rcPaint.top / cyChar - 1;
  if (nPaintBeg < 0)
   nPaintBeg = 0;

  nPaintEnd = nVScrollPos + ps.rcPaint.bottom / cyChar;
  if (nPaintEnd > NUMLINES)
   nPaintEnd = NUMLINES;

  for (i = nPaintBeg; i < nPaintEnd; i++) {

    x = cxChar*(1 - nHScrollPos);
    y = cyChar*(1 - nVScrollPos + i);

    TextOut (hdc, x, y,
           sysmetrics [i].szLabel,
           lstrlen (sysmetrics [i].szLabel));
    TextOut (hdc, x + 18*cxCaps, y,
           sysmetrics [i].szDesc,
           lstrlen (sysmetrics [i].szDesc));

    SetTextAlign (hdc, TA_RIGHT | TA_TOP);

    TextOut (hdc, x + 18*cxCaps + 50*cxChar, y,
           szBuffer,
           wsprintf (szBuffer, "%5d",
                   GetSystemMetrics (sysmetrics [i].nIndex)));

    SetTextAlign (hdc, TA_LEFT | TA_TOP);
  }

  EndPaint (hwnd, &ps);

  return 0;
}

long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}

