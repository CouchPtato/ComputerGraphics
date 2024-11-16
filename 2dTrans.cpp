#include <graphics.h>
#include <math.h>
#include <iostream.h>
#include <conio.h>

const int MAX_SIDES = 100;

void multiply(float a[3][3], float b[3][1], float res[3][1]) {
    for (int i = 0; i < 3; i++) {
        res[i][0] = 0;
        for (int j = 0; j < 3; j++) {
            res[i][0] += a[i][j] * b[j][0];
        }
    }
}

void applyTransformation(float mat[3][3], int points[][2], int n, int fixedX, int fixedY) {
    float res[3][1], input[3][1];
    for (int i = 0; i < n; i++) {
        // Translate point to origin relative to fixed point
        input[0][0] = points[i][0] - fixedX;
        input[1][0] = points[i][1] - fixedY;
        input[2][0] = 1;
        multiply(mat, input, res);
        // Translate back to original position
        points[i][0] = res[0][0] + fixedX;
        points[i][1] = res[1][0] + fixedY;
    }
}

void drawPolygon(int points[][2], int n, int color) {
    setcolor(color);
    for (int i = 0; i < n; i++) {
        line(points[i][0], points[i][1], points[(i + 1) % n][0], points[(i + 1) % n][1]);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int n;
    cout << "Enter the number of sides for the polygon (max " << MAX_SIDES << "): ";
    cin >> n;

    if (n > MAX_SIDES) {
        cout << "Number of sides exceeds the maximum allowed (" << MAX_SIDES << "). Exiting program.";
        closegraph();
        return 0;
    }

    int points[MAX_SIDES][2];
    cout << "Enter the coordinates of the vertices (x y):\n";
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i + 1 << ": ";
        cin >> points[i][0] >> points[i][1];
    }

    int fixedX = points[0][0], fixedY = points[0][1];

    cleardevice();
    drawPolygon(points, n, YELLOW); // Original polygon in yellow
    getch();
    cleardevice();

    float tx, ty;
    cout << "Enter translation values (tx ty): ";
    cin >> tx >> ty;
    float translation[3][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};
    drawPolygon(points, n, RED); // Before transformation
    applyTransformation(translation, points, n, fixedX, fixedY);
    drawPolygon(points, n, GREEN);   // After transformation
    getch();
    cleardevice();

    float sx, sy;
    cout << "Enter scaling values (sx sy): ";
    cin >> sx >> sy;
    float scaling[3][3] = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
    drawPolygon(points, n, RED); // Before transformation
    applyTransformation(scaling, points, n, fixedX, fixedY);
    drawPolygon(points, n, GREEN);   // After transformation
    getch();
    cleardevice();

    float angle;
    cout << "Enter rotation angle (in degrees): ";
    cin >> angle;
    angle = angle * M_PI / 180;
    float rotation[3][3] = {{cos(angle), -sin(angle), 0},
                            {sin(angle), cos(angle), 0},
                            {0, 0, 1}};
    drawPolygon(points, n, RED); // Before transformation
    applyTransformation(rotation, points, n, fixedX, fixedY);
    drawPolygon(points, n, GREEN);   // After transformation
    getch();
    closegraph();

    return 0;
}
