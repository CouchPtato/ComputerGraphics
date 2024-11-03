#include <stdio.h>
#include <conio.h>
#include <graphics.h>

int main()
{
  int n;
  int a[20][2], xi[20];

  printf("\n\n\tEnter the number of edges of the polygon: ");
  scanf("%d", &n);
  printf("\n\n\tEnter the coordinates of the polygon:\n\n");

  for(int i = 0; i < n; i++)
  {
    printf("\tX%d Y%d: ", i, i);
    scanf("%d %d", &a[i][0], &a[i][1]);
  }

  // Closing the polygon by setting last point as the first
  a[n][0] = a[0][0];
  a[n][1] = a[0][1];

  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

  // Draw the polygon outline by connecting each vertex
  setcolor(WHITE);
  for (int i = 0; i < n; i++)
  {
    line(a[i][0], a[i][1], a[i+1][0], a[i+1][1]);
  }

  int dx, dy;
  float slope[20];
  for (int i = 0; i < n; i++)
  {
    dy = a[i+1][1] - a[i][1];
    dx = a[i+1][0] - a[i][0];

    if(dy == 0)
      slope[i] = 1.0;
    else if(dx == 0)
      slope[i] = 0.0;
    else
      slope[i] = (float) dx / dy;
  }

  // Scan line fill
  for(int y = 0; y < 480; y++)
  {
    int k = 0;
    for(int i = 0; i < n; i++)
    {
      // Check if the scan line intersects the edge
      if(((a[i][1] <= y) && (a[i+1][1] > y)) || ((a[i][1] > y) && (a[i+1][1] <= y)))
      {
        xi[k] = (int)(a[i][0] + slope[i] * (y - a[i][1]));
        k++;
      }
    }

    for(int j = 0; j < k-1; j++)
    {
      for(int i = 0; i < k-1; i++)
      {
        if(xi[i] > xi[i+1])
        {
          int temp = xi[i];
          xi[i] = xi[i+1];
          xi[i+1] = temp;
        }
      }
    }

    setcolor(LIGHTMAGENTA);
    for(int i = 0; i < k; i += 2)
    {
      line(xi[i], y, xi[i+1], y);
      getch();
    }
  }
  closegraph();
  return 0;
}
