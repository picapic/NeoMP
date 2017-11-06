#define STRICT
//#define INSTANCE_MODE
#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>

#include"hello.h"

// Подключаем библиотеки opengl и glu
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

int PASCAL Privet(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpszCmdLine,
				   int nCmdShow);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ClientResize(HWND hWnd, int nWidth, int nHeight);
void InitMyOpenGL(HWND hWnd);
void ResizeMyOpenGL(HWND hWnd);
void CloseMyOpenGL(HWND hWnd);
void Fullscreen(void);
void DrawSomething(HWND hWnd);

#ifdef INSTANCE_MODE
int PASCAL WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpszCmdLine,
				   int nCmdShow)
#else
int PASCAL Privet(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpszCmdLine,
				   int nCmdShow)
#endif
{ HDC hdc;
  MSG msg;
  HWND hWnd;
  WNDCLASS wc;
  int X, Y;
  unsigned long thread;
  Parameters params;

  if(hPrevInstance)
  { MessageBox(NULL, "You can start just one copy of this application.", "Error!", MB_OK | MB_ICONINFORMATION);
    return FALSE;
  }

  wc.style = 0;
  wc.lpfnWndProc = (WNDPROC) WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hInstance = NULL;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);;
  wc.lpszMenuName = (LPSTR) NULL;
  wc.lpszClassName = "OpenGLClass";

  if(!RegisterClass(&wc))
	  return 0;

  hWnd = CreateWindowEx(
				WS_EX_APPWINDOW,
				"OpenGLClass",
				"OpenGL",
				DS_MODALFRAME | WS_VISIBLE | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				600,
				450,
				NULL,
				NULL,
				hInstance,
				NULL);

  if(!hWnd)
		return FALSE;

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  hdc = GetDC(hWnd);
  X = GetDeviceCaps(hdc, HORZRES);
  Y = GetDeviceCaps(hdc, VERTRES);
  ReleaseDC(hWnd, hdc);
  MoveWindow(hWnd, X/2-175, Y/2-125, 350, 250, true);
  SetFocus(hWnd);
  ShowCursor(false);

  params.hWnd = hWnd;
  params.X = X;
  params.Y = Y;
  CreateThread(NULL, 0, ShowScreen, &params, 0, &thread);

  while(GetMessage(&msg, 0, 0, 0))
  {
    TranslateMessage(&msg);
	DispatchMessage(&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK  
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int n;
  HDC hdc;

  switch(msg) {

  case WM_CREATE:
	  {
		  InitMyOpenGL(hWnd);
		  break;
	  }
  case WM_SIZE:
	  {
		  ResizeMyOpenGL(hWnd);
		  break;
	  }
  case WM_PAINT : {
		break;
	}
  case WM_LBUTTONDOWN:
  case WM_MBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_MOUSEWHEEL:
	  {
//		  PostQuitMessage(0);
                        DestroyWindow(hWnd);
		  break;
	  }

  case WM_CHAR: {
        switch (wParam) 
        { 
/*
            case 0x08:
                // Process a backspace.
				PostQuitMessage(0);
                break; 
            case 0x0A: 
                // Process a linefeed. 
				PostQuitMessage(0);
                break; 
            case 0x1B: 
                // Process an escape. 
				PostQuitMessage(0);
                break; 
            case 0x09: 
                // Process a tab.
				PostQuitMessage(0);
                break; 
            case 0x0D: 
                // Process a carriage return. 
				PostQuitMessage(0);
//				DrawSomething(hWnd);
//				ShowScreen();
				break; 
			case 0x20:
                // Process a carriage spacebar.
				PostQuitMessage(0);
				break;
			default: 
                // Process displayable characters. 
				PostQuitMessage(0);
*/                               
                break; 
        }
		break;
	}

  case WM_NCLBUTTONDBLCLK : 
  case WM_DESTROY : {
	    CloseMyOpenGL(hWnd);
		PostQuitMessage(0);
		return 0;
	}
  }

  n = DefWindowProc(hWnd, msg, wParam, lParam);
  return n;
}

//изменение размеров окна пользователем
void ClientResize(HWND hWnd, int nWidth, int nHeight)
{
  RECT rcClient;
  POINT ptDiff;
  GetClientRect(hWnd, &rcClient);
  ptDiff.x = rcClient.right;
  ptDiff.y = rcClient.bottom;
  MoveWindow(hWnd, 0, 0, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
}

void InitMyOpenGL(HWND hWnd)
{
	HDC hdc;
	HGLRC hglrc;
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormat;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	hdc = GetDC(hWnd);
	iPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iPixelFormat, &pfd);
	hglrc = wglCreateContext(hdc);
	if(hglrc)
		wglMakeCurrent(hdc, hglrc);
}

void ResizeMyOpenGL(HWND hWnd)
{
	RECT rc;

	GetClientRect(hWnd, &rc);
	glViewport(0,0,rc.right,rc.bottom);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void CloseMyOpenGL(HWND hWnd)
{
	HGLRC hglrc;
	HDC hdc;

	hglrc = wglGetCurrentContext();
	if(hglrc)
	{
		hdc = wglGetCurrentDC();
		wglMakeCurrent(NULL, NULL);
		ReleaseDC(hWnd, hdc);
		wglDeleteContext(hglrc);
	}

	ChangeDisplaySettings(NULL, 0);
}

void DrawSomething(HWND hWnd)
{
	GLubyte fillpattern[128];
	gluOrtho2D(-100, 700, -100, 500);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

/*
	glColor3f(0, 0, 0);
	glLineWidth(2.0f);
	glLineStipple(3, 0x08ff);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(-400, 0);
	glVertex2f(400, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, -300);
	glVertex2f(0, 300);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 10; ++i)
	{
		glVertex2f(-350.0f+70.0f*i, 60.0f);
		glVertex2f(-315.0f+70.0f*i, -60.0f);
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-300, 100);
	glVertex2f(-200, 290);
	glVertex2f(-100, 100);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0, 150);
	glVertex2f(200, 200);
	glVertex2f(400, 150);
	glVertex2f(200, 100);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(100, 100);
	glVertex2f(-100, 50);
	glEnd();

	memset(fillpattern, 0, sizeof(fillpattern));
	for(int j = 0; j < 16; ++j)
	{
		for(int i = 0; i < 2; ++i)
		{
			fillpattern[j*4+i] = 0xff;
			fillpattern[64+j*4+i+2] = 0xff;
		}
	}
	glColor3f(0, 0, 1.0);
	glPointSize(1);
	glLineWidth(1.0f);
	glPolygonStipple(fillpattern);
	glEnable(GL_POLYGON_STIPPLE);
	glBegin(GL_POLYGON);
	glVertex2f(-300, -150);
	glVertex2f(-200, -80);
	glVertex2f(0, -100);
	glVertex2f(200, -200);
	glVertex2f(-100, -250);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);
*/
	glFinish();
}
