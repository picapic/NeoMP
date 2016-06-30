//For the future:
//1 show center of mass

#include<stdlib.h>
#include<gl/glu.h>
#include<gl/gl.h>
#include<math.h>
#include<time.h>

#ifdef WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif

#ifdef WIN32
#define random(X) (rand()%X)
#endif

#define MIN(X,Y) (X>Y?Y:X)
#define MAX(X,Y) (X>Y?X:Y)

#define VMAX 14
#define BRAKE 0.005f
#define ITERATES 20000000
#define LENGTH 25
#define VISIBLE_NUM 10
#define INVISIB_NUM 35
#define INVIS_THREE 0

struct Parameters
{
	HWND hWnd;
	int X;
	int Y;
};

class dot {
  int X;
  int Y;
  int XSize;
  int YSize;
  int length;
  float x0;
  float y0;
  float x1;
  float y1;
  float *x;
  float *y;
  float mass;
  float Fx;
  float Fy;
  float Vx;
  float Vy;
  int color;
  static dot *first;
  dot *next;

public:
  dot();
  dot(float in_mass, int in_color);
  dot(float in_mass, int in_color, int in_length);
  dot(float in_mass, int in_color, int in_length, int in_XSize, int in_YSize);
  dot(float in_x0, float in_y0, float in_mass, int in_color);
  dot(float in_x0, float in_y0, float in_Vx, float in_Vy, float in_mass, int in_color);
  ~dot();

  void draw(void);
  void update(void);
};

dot *dot::first = NULL;

dot::dot()
{
  int i;
  XSize = 640;
  YSize = 480;
  x0 = 0.0;
  y0 = 0.0;
  x1 = x0;
  y1 = y0;
  length = 1;
  x = new float[length];
  y = new float[length];
  for(i = 0; i < length; ++i)
  {
    x[i] = x0;
    y[i] = y0;
  }
  X = (int)x0;
  Y = (int)y0;
  mass = 1;
  Fx = 0;
  Fy = 0;
  Vx = 0;
  Vy = 0;
  color = 1;
  first = this;
  next = NULL;
}

dot::dot(float in_mass, int in_color)
{
  time_t t;
  int i;
  class dot *list;

  if(first == NULL)
  {
    first = this;
    next = NULL;
  }
  else
  {
    list = first;
    while(list->next != NULL)
      list = list->next;
    list->next = this;
    next = NULL;
  }

  XSize = 640;
  YSize = 480;

  mass = in_mass;
  Fx = 0;
  Fy = 0;
  color = in_color;
  time(&t);
  for(i = 0; i < t%10; ++i)
    random(t); //start moment random
  x0 = x1 = (t+random(XSize/2)+XSize/4+5)+random(10000)/10000.0f;
  time(&t);
  t = t%160;
  y0 = y1 = (t+random(YSize/2)+YSize/4+5)+random(10000)/10000.0f;
  X = (int)x0;
  Y = (int)y0;
  Vx = Vy = 0;
  //time(&t);
  //t = t%160;
  //Vx = (t%50*(random(2)-1))*0.1;
  //time(&t);
  //t = t%160;
  //Vy = (t%50*(random(2)-1))*0.1;
  length = 1;
  x = new float[length];
  y = new float[length];
  for(i = 0; i < length; ++i)
  {
    x[i] = x0;
    y[i] = y0;
  }
}

dot::dot(float in_mass, int in_color, int in_length)
{
  time_t t;
  int i;
  class dot *list;

  if(first == NULL)
  {
    first = this;
    next = NULL;
  }
  else
  {
    list = first;
    while(list->next != NULL)
      list = list->next;
    list->next = this;
    next = NULL;
  }

  XSize = 640;
  YSize = 480;

  mass = in_mass;
  Fx = 0;
  Fy = 0;
  color = in_color;
  time(&t);
  t = t%160;
  for(i = 0; i < t; ++i)
    random(t); //start moment random
  x0 = x1 = (t+random(XSize/2)+XSize/4+5)+random(10000)/10000.0f;
  time(&t);
  t = t%160;
  y0 = y1 = (t+random(YSize/2)+YSize/4+5)+random(10000)/10000.0f;
  X = (int)x0;
  Y = (int)y0;
  Vx = Vy = 0;
  //time(&t);
  //t = t%160;
  //Vx = (t%50*(random(2)-1))*0.1;
  //time(&t);
  //t = t&160;
  //Vy = (t%50*(random(2)-1))*0.1;
  length = in_length;
  x = new float[length];
  y = new float[length];
  for(i = 0; i < length; ++i)
  {
    x[i] = x0;
    y[i] = y0;
  }
}

dot::dot(float in_mass, int in_color, int in_length, int in_XSize, int in_YSize)
{
  time_t t;
  int i;
  class dot *list;

  if(first == NULL)
  {
    first = this;
    next = NULL;
  }
  else
  {
    list = first;
    while(list->next != NULL)
      list = list->next;
    list->next = this;
    next = NULL;
  }

  XSize = in_XSize;
  YSize = in_YSize;

  mass = in_mass;
  Fx = 0;
  Fy = 0;
  color = in_color;
  time(&t);
  t = t%160;
  for(i = 0; i < t; ++i)
    random(t); //start moment random
  x0 = x1 = (t+random(XSize/2)+XSize/4+5)+random(10000)/10000.0f;
  time(&t);
  t = t%160;
  y0 = y1 = (t+random(YSize/2)+YSize/4+5)+random(10000)/10000.0f;
  X = (int)x0;
  Y = (int)y0;
  Vx = Vy = 0;
  //time(&t);
  //t = t%160;
  //Vx = (t%50*(random(2)-1))*0.1;
  //time(&t);
  //t = t&160;
  //Vy = (t%50*(random(2)-1))*0.1;
  length = in_length;
  x = new float[length];
  y = new float[length];
  for(i = 0; i < length; ++i)
  {
    x[i] = x0;
    y[i] = y0;
  }
}

dot::dot(float in_x0, float in_y0, float in_mass, int in_color)
{
  int i;

  x0 = x1 = in_x0;
  y0 = y1 = in_y0;
  color = in_color;
  X = (int)x0;
  Y = (int)y0;
  mass = in_mass;
  Fx = 0;
  Fy = 0;
  Vx = Vy = 0;
  length = 1;
  x = new float[length];
  y = new float[length];
  for(i = 0; i < length; ++i)
  {
    x[i] = x0;
    y[i] = y0;
  }
  XSize = 640;
  YSize = 480;
}

dot::~dot()
{
  delete [] x;
  delete [] y;
  if(first == this)
	  first = NULL;
}

void dot::draw()
{
  int i;
  float coordinate;

  if(length <= 0)
    return;

  glLineWidth(2.0f);
  glColor3f(0.0, 0.0, 0.0);

  if(length > 1)
  {
//	  glBegin(GL_LINE_STRIP);
	  glBegin(GL_LINES);
	  glVertex2f(x[0], y[0]);
	  glVertex2f(x[1], y[1]);
	  glEnd();  
  }
  else
  {
//	  glBegin(GL_LINE_STRIP);
	  glBegin(GL_LINES);
	  glVertex2f(x0, y0);
	  glVertex2f(x1, y1);
	  glEnd();  
  }

  x0 = x1;
  y0 = y1;
  for(i = 0; i < length-1; ++i)
  {
    x[i] = x[i+1];
    y[i] = y[i+1];
  }
  x[length-1] = x0;
  y[length-1] = y0;
//  glColor3f(fabs((float)Vy)+0.5, fabs((float)Vx/(float)Vy)+0.5, fabs(Vx+Vy));
  if(length > 1)
  {
//	  glBegin(GL_LINE_STRIP);
	  glBegin(GL_LINES);
	  for(i = 1; i < length-1; ++i)
	  {
	    coordinate = (1.0f-(float)i/((float)length - 1.0f))/2.0f;
	    if(i > (length-1)/2.0f)
		  glColor3f(0.0, coordinate, 0.0);
		else
		  glColor3f(0.0, 0.5f-coordinate, 0.0);
	    glVertex2f(x[i-1], y[i-1]);
  	    glVertex2f(x[i], y[i]);
	  }
	  glEnd();  
  }
  else
  {
	  glBegin(GL_LINE_STRIP);
	  glVertex2f(x0, y0);
	  glVertex2f(x1, y1);
	  glEnd(); 
  }
  glFinish();
}

void dot::update()
{
  dot *list;
  float r;
  float M;
  float F0, F0x, F0y;
  float resx, resy;
  float ax, ay;

  list = first;
  while(list != NULL)
  {
    if(list == this)
    {
      list = list->next;
      continue;
    }

    resx = list->x0-x0;
    resy = list->y0-y0;

    r = sqrt( resx*resx + resy*resy );
//For radius
    if(r < 5)
    {
	  if(abs(resx) < 5)
		  if(resx > 0)
		resx = 5;
		  else
		resx = -5;

	  if(abs(resy) < 5)
		  if(resy > 0)
		resy = 5;
		  else
		resy = -5;
    }

    r = sqrt( resx*resx + resy*resy );
    M = list->mass*mass;
    F0 = M/pow(r,3);
    F0x = F0*resx;
    F0y = F0*resy;
    Fx = Fx + F0x;
    Fy = Fy + F0y;


    list = list->next;
  }

//  fprintf(stderr, "%f, %f\n", Fx, Fy);
  ax = Fx/mass;
  ay = Fy/mass;
  Vx = Vx + ax;
  Vy = Vy + ay;

//For slow
  if(Vx > VMAX)
    Vx = VMAX;
  if(Vy > VMAX)
    Vy = VMAX;
  if(Vx < -VMAX)
    Vx = -VMAX;
  if(Vy < -VMAX)
    Vy = -VMAX;

  x1 = x0 + Vx;
  y1 = y0 + Vy;

  Fx = 0;
  Fy = 0;

//Brakes -(and attraction)
  //if(Vx > 0)
    Vx = Vx - BRAKE*(Vx/VMAX);
//  if(Vy < 0)
    Vy = Vy - BRAKE*(Vy/VMAX);
//  if(Vx < 0)
    //Vx = Vx + BRAKE*(Vx/VMAX);
//  if(Vy > 0)
//    Vy = Vy + BRAKE*(Vy/VMAX);

//For mirror
  if(x1 > (XSize-15) || x1 < 15)
  {
    Vx = -Vx;
    x1=(x1>(XSize-15))?x1-1:x1+1;
  }
  if(y1 < 15 || y1 > (YSize-15))
  {
    Vy = -Vy;
    y1=(y1>(YSize-15))?y1-1:y1+1;
  }
}

DWORD WINAPI ShowScreen(void *lpParams)
{
  int i, iter;
  int key;
  dot *a[VISIBLE_NUM+INVISIB_NUM+3];
  int dotts;
  int vis_num, inv_num, inv_thr;
  HDC dc;
  HGLRC rc;
  int X, Y;

  dc = GetDC((*((Parameters *)lpParams)).hWnd);
  rc = wglCreateContext(dc);
  wglMakeCurrent(dc, rc);

  X = (*((Parameters *)lpParams)).X;
  Y = (*((Parameters *)lpParams)).Y;
  gluOrtho2D(0, X, 0, Y);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  vis_num = VISIBLE_NUM+1;
  inv_num = INVISIB_NUM+1;

  if( (VISIBLE_NUM+INVISIB_NUM) > 15)
    dotts = INVIS_THREE?3:0;
  else
    dotts = INVIS_THREE?2:0;
  dotts = dotts + VISIBLE_NUM + INVISIB_NUM;

  a[0] = new dot(800, random(5)+1, X, Y);
  delete a[0]; //for color random

  key = 1; //keyboard flag

  for(i = 0; i < vis_num; ++i)
  {
    a[i] = new dot(random(30)+10, random(10)+4, LENGTH, X, Y);
  }

  for(i = VISIBLE_NUM; i < vis_num+INVISIB_NUM; ++i)
  {
    a[i] = new dot(random(30)+10, /*random(10)+4*/0, 0, X, Y);
  }

  if(INVIS_THREE)
  {
    a[VISIBLE_NUM+INVISIB_NUM] = new dot(900, /*random(2)+1*/0, 0, X, Y);
    a[VISIBLE_NUM+INVISIB_NUM+1] = new dot(700, /*random(2)+3*/0, 0, X, Y);
    if((VISIBLE_NUM + INVISIB_NUM) > 15)
      a[VISIBLE_NUM+INVISIB_NUM+2] = new dot(500, /*random(5)+1*/0, 0, X, Y);
  }

  for(iter = 0; iter < ITERATES; ++iter)
  {
    for(i = 0; i < dotts; ++i)
    {
      a[i]->draw();
      a[i]->update();
    }

#ifdef _WIN32
//    Sleep(1);
#else
	usleep(15);
#endif
  }

  for(i = 0; i < dotts; ++i)
    delete a[i];

  wglMakeCurrent(dc, NULL);

  return 0;
}
