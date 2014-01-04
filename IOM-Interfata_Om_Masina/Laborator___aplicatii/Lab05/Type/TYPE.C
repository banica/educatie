#include <windows.h>


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

long WMCreate    (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSize      (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMSetFocus  (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMKillFocus (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMKeyDown   (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMChar      (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMPaint     (HWND hwnd, WPARAM wParam, LPARAM lParam);
long WMDestroy   (HWND hwnd, WPARAM wParam, LPARAM lParam);

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
							  "Typing Program",
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
  static char szAppName [] = "Type";

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

   case WM_CREATE:    return WMCreate    (hwnd, wParam, lParam);
   case WM_SIZE:      return WMSize      (hwnd, wParam, lParam);
   case WM_SETFOCUS:  return WMSetFocus  (hwnd, wParam, lParam);
   case WM_KILLFOCUS: return WMKillFocus (hwnd, wParam, lParam);
   case WM_KEYDOWN:   return WMKeyDown   (hwnd, wParam, lParam);
   case WM_CHAR:      return WMChar      (hwnd, wParam, lParam);
   case WM_PAINT:     return WMPaint     (hwnd, wParam, lParam);
	case WM_DESTROY:   return WMDestroy   (hwnd, wParam, lParam);

  }

  return DefWindowProc (hwnd, message, wParam, lParam);
}


char* pBuffer;
int   cxBuffer, cyBuffer;

#define BUFFER(x, y) (*(pBuffer + y*cxBuffer + x))

long cxChar, cyChar;
int   cxClient, cyClient, xCaret, yCaret;


long WMCreate (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC        hdc;
  TEXTMETRIC tm;

  hdc = GetDC (hwnd);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
  GetTextMetrics (hdc, &tm);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight; 

  ReleaseDC (hwnd, hdc);

  return 0;
}


long WMSize (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  int x,y;

  cxClient = LOWORD (lParam);
  cyClient = HIWORD (lParam);

  cxBuffer = cxClient / cxChar;
  if (cxBuffer == 0)
    cxBuffer = 1;
  cyBuffer = cyClient / cyChar;
  if (cyBuffer == 0)
    cyBuffer = 1;

  if (pBuffer != NULL)
    free (pBuffer);

  pBuffer = NULL;
  if ((LONG) cxBuffer * cyBuffer <= 65535L)
    pBuffer = (char *) malloc (cxBuffer * cyBuffer);

  if (pBuffer == NULL)
    MessageBox (hwnd,
                "Window too large. Cannot allocate enough memory",
                "Type",
                MB_ICONEXCLAMATION | MB_OK);
  else
    for (y = 0; y < cyBuffer; y++)
      for (x = 0; x < cxBuffer; x++)
        BUFFER (x,y) = ' ';

  xCaret = 0;
  yCaret = 0;

  if (hwnd == GetFocus ())
    SetCaretPos (xCaret*cxChar, yCaret*cyChar);

  return 0;
}


long WMSetFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  CreateCaret (hwnd, NULL, cxChar,cyChar);
  SetCaretPos (xCaret*cxChar, yCaret*cyChar);
  ShowCaret (hwnd);

  return 0;
}


long WMKillFocus (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HideCaret (hwnd);
  DestroyCaret ();

  return 0;
}


long WMKeyDown (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  int x;

  switch (wParam) {

    case VK_HOME:
      xCaret = 0;
      break;

    case VK_END:
      xCaret = cxBuffer - 1;
      break;

    case VK_PRIOR:
      yCaret = 0;
      break;

    case VK_NEXT:
      yCaret = cyBuffer - 1;
      break;

    case VK_LEFT:
      if (xCaret > 0)
        xCaret--;
      break;

    case VK_RIGHT:
      if (xCaret < cxBuffer - 1)
        xCaret++;
      break;

    case VK_UP:
      if (yCaret > 0)
        yCaret--;
      break;

    case VK_DOWN:
      if (yCaret < cyBuffer - 1)
        yCaret++;
      break;

    case VK_DELETE:

      for (x = xCaret; x < cxBuffer - 1; x++)
        BUFFER (x, yCaret) = BUFFER (x + 1, yCaret);
      BUFFER (cxBuffer - 1, yCaret) = ' ';

      HideCaret (hwnd);
      hdc = GetDC (hwnd);

      SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
      TextOut (hdc, xCaret*cxChar, yCaret*cyChar,
               &BUFFER (xCaret, yCaret), cxBuffer - xCaret);

      ReleaseDC (hwnd, hdc);
      ShowCaret (hwnd);

      break;

  }

  SetCaretPos (xCaret*cxChar, yCaret*cyChar);

  return 0;
}


long WMChar (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  int i, x, y;

  for (i = 0; i < LOWORD (lParam); i++)
    switch (wParam) {

      case '\b': /* backspace */
        if (xCaret > 0) {
           xCaret--;
           SendMessage (hwnd, WM_KEYDOWN, VK_DELETE, 1L);
        }
        break;

      case '\t': /* tab */
        do {
          SendMessage (hwnd, WM_CHAR, ' ', 1L);
        } while (xCaret % 8 != 0);
        break;

      case '\n': /* linefeed */
        if (++yCaret == cyBuffer)
          yCaret = 0;
        break;

      case '\r': /* carriage return */
        xCaret = 0;

        if (++yCaret == cyBuffer)
          yCaret = 0;
        break;

      case '\x1B': /* escape */
        for (y = 0; y < cyBuffer; y++)
          for (x = 0; x < cxBuffer; x++)
            BUFFER (x, y) = ' ';

        xCaret = 0;
        yCaret = 0;
        InvalidateRect (hwnd, NULL, FALSE);
        break;

    default:
      BUFFER (xCaret, yCaret) = (char) wParam;

      HideCaret (hwnd);
      hdc = GetDC (hwnd);

      SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
      TextOut (hdc, xCaret*cxChar, yCaret*cyChar, &BUFFER (xCaret, yCaret), 1);

      ReleaseDC (hwnd, hdc);
      ShowCaret (hwnd);

      if (++xCaret == cxBuffer) {
        xCaret = 0;

        if (++yCaret == cyBuffer)
          yCaret = 0;
      }

      break;

  }

  SetCaretPos (xCaret*cxChar, yCaret*cyChar);

  return 0;
}


long WMPaint (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HDC         hdc;
  PAINTSTRUCT ps;
  int y;

  hdc = BeginPaint (hwnd, &ps);

  SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

  for (y = 0; y < cyBuffer; y++)
    TextOut (hdc, 0, y*cyChar, & BUFFER (0, y), cxBuffer);

  EndPaint (hwnd, &ps);

  return 0;
}


long WMDestroy (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  PostQuitMessage (0);

  return 0;
}


