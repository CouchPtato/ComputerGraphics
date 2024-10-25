#include <iostream.h>
#include <graphics.h>
#include <conio.h>

void CircleMidPoint()
{
  float x,y,d,h,k,r;

  cout << "\n\t\tMidpoint method to draw a circle\n";
  cout << "Enter coordinates of centre of the circle: ";
  cin >> h >> k;
  cout << "\nEnter the radius of the circle: ";
  cin >> r;

  x = 0;
  y = r;
  d = 3 - 2*r;

  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

  while(x <= y)
  {
    putpixel((x + h), (y + h), WHITE);
    putpixel((-x + h), (y + h), WHITE);
    putpixel((-x + h), (-y + h), WHITE);
    putpixel((x + h), (-y + h), WHITE);
    putpixel((y + h), (x + h), WHITE);
    putpixel((-y + h), (x + h), WHITE);
    putpixel((-y + h), (-x + h), WHITE);
    putpixel((y + h), (-x + h), WHITE);

    if(d <= 0)
    {
      d = d + 2*x + 3;
      x = x + 1;
    }
    else
    {
      d = d + 2*(x - y) + 5;
      y = y - 1;
      x = x + 1;
    }
  }
  getch();
  closegraph();
}

int main()
{
  CircleMidPoint();
  return 0;
}