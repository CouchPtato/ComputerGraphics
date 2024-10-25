#include <iostream.h>
#include <conio.h>
#include <graphics.h>

void LineBres()
{
  int x0, y0, x1, y1;
  cout << "\n \t Bresenham's Line \n";
  cout << "Enter co-ordinates of Starting Point: ";
  cin >> x0 >> y0;

  cout << "Enter co-ordinates of Ending Point: ";
  cin >> x1 >> y1;

  int dx, dy, p, x, y;
  
  dx = x1 - x0;
  dy = y1 - y0;
  x = x0;
  y = y0;
  p = 2*dy - dx;
  
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

  while(x < x1)
  {
    if(p >= 0)
    {
      putpixel(x,y,7);
      y = y + 1;
      p = p + 2*dy - 2*dx;
    }
    else
    {
      putpixel(x,y,7);
      p = p + 2*dy;
    }
    x = x + 1;
  }
  getch();
  closegraph();
}

int main()
{
  LineBres();
  return 0;
}