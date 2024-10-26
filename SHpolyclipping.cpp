#include <iostream.h>
#include <graphics.h>
#include <conio.h>

struct Point {
    int x, y;
};

int xmin, ymin, xmax, ymax;

int isInside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= xmin;
        case 1: return p.x <= xmax;
        case 2: return p.y >= ymin;
        case 3: return p.y <= ymax;
    }
    return 0;
}

Point getIntersection(Point p1, Point p2, int edge) {
    Point intersection;
    float m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    switch (edge) {
        case 0: intersection.x = xmin; intersection.y = p1.y + m * (xmin - p1.x); break;
        case 1: intersection.x = xmax; intersection.y = p1.y + m * (xmax - p1.x); break;
        case 2: intersection.y = ymin; intersection.x = p1.x + (ymin - p1.y) / m; break;
        case 3: intersection.y = ymax; intersection.x = p1.x + (ymax - p1.y) / m; break;
    }
    return intersection;
}

int clipPolygon(Point inPoints[], int inCount, Point outPoints[], int edge) {
    int outCount = 0;
    Point s = inPoints[inCount - 1];
    for (int i = 0; i < inCount; i++) {
        Point p = inPoints[i];
        if (isInside(p, edge)) {
            if (isInside(s, edge)) {
                outPoints[outCount++] = p;
            } else {
                outPoints[outCount++] = getIntersection(s, p, edge);
                outPoints[outCount++] = p;
            }
        } else if (isInside(s, edge)) {
            outPoints[outCount++] = getIntersection(s, p, edge);
        }
        s = p;
    }
    return outCount;
}

void drawPolygon(Point points[], int n) {
    for (int i = 0; i < n - 1; i++) {
        line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }
    line(points[n - 1].x, points[n - 1].y, points[0].x, points[0].y);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char*>("C:\\TURBOC3\\BGI"));
    
    cout << "Enter clipping window (xmin, ymin, xmax, ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
    
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    Point inPoints[20], outPoints[20];
    
    cout << "Enter vertices (x y):\n";
    for (int i = 0; i < n; i++) {
        cin >> inPoints[i].x >> inPoints[i].y;
    }
    
    setcolor(GREEN);
    drawPolygon(inPoints, n);
    getch();
    
    for (int edge = 0; edge < 4; edge++) {
        n = clipPolygon(inPoints, n, outPoints, edge);
        for (int i = 0; i < n; i++) {
            inPoints[i] = outPoints[i];
        }
    }
    
    cleardevice();
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
    setcolor(RED);
    drawPolygon(inPoints, n);

    getch();
    closegraph();
    return 0;
}
