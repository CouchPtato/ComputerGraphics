#include <graphics.h>
#include <math.h>
#include <iostream.h>
#include <conio.h>

const int MAX_VERTICES = 8;
const int MAX_EDGES = 12;

// Function to multiply a 4x4 transformation matrix with a 4x1 point matrix
void multiply(float a[4][4], float b[4][1], float res[4][1]) 
{
    for (int i = 0; i < 4; i++) 
    {
        res[i][0] = 0;
        for (int j = 0; j < 4; j++) 
        {
            res[i][0] += a[i][j] * b[j][0];
        }
    }
}

// Apply transformation matrix to all vertices
void applyTransformation(float mat[4][4], float vertices[][3], int n) 
{
    float input[4][1], res[4][1];
    for (int i = 0; i < n; i++) 
    {
        input[0][0] = vertices[i][0];
        input[1][0] = vertices[i][1];
        input[2][0] = vertices[i][2];
        input[3][0] = 1;
        multiply(mat, input, res);
        vertices[i][0] = res[0][0];
        vertices[i][1] = res[1][0];
        vertices[i][2] = res[2][0];
    }
}

// Draw 3D object by connecting vertices (for simplicity, drawing lines between consecutive vertices)
void drawObject(float vertices[][3], int edges[][2], int numEdges, int color) 
{
    setcolor(color);
    for (int i = 0; i < numEdges; i++) 
    {
        int start = edges[i][0];
        int end = edges[i][1];
        line(vertices[start][0], vertices[start][1], vertices[end][0], vertices[end][1]);
    }
}

// Apply parallel projection
void parallelProjection(float vertices[][3], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        vertices[i][2] = 0; // Drop the z-coordinate
    }
}

// Apply perspective projection
void perspectiveProjection(float vertices[][3], int n, float d) 
{
    for (int i = 0; i < n; i++) 
    {
        float z = vertices[i][2];
        vertices[i][0] = vertices[i][0] * d / (d + z);
        vertices[i][1] = vertices[i][1] * d / (d + z);
    }
}

int main() 
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Predefined cube vertices (8 vertices of a cube)
    float vertices[MAX_VERTICES][3] = {
        {100, 100, 100}, // 0
        {200, 100, 100}, // 1
        {200, 200, 100}, // 2
        {100, 200, 100}, // 3
        {100, 100, 200}, // 4
        {200, 100, 200}, // 5
        {200, 200, 200}, // 6
        {100, 200, 200}  // 7
    };

    // Predefined cube edges (12 edges of a cube)
    int edges[MAX_EDGES][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    int n = MAX_VERTICES;
    int numEdges = MAX_EDGES;

    cleardevice();
    drawObject(vertices, edges, numEdges, YELLOW); // Original object
    getch();
    cleardevice();

    float x1 = vertices[0][0];
    float y1 = vertices[0][1];
    float z1 = vertices[0][2];

    float translationToOrigin[4][4] = {
        {1, 0, 0, -x1},
        {0, 1, 0, -y1},
        {0, 0, 1, -z1},
        {0, 0, 0, 1}
    };
    float translationBack[4][4] = {
        {1, 0, 0, x1},
        {0, 1, 0, y1},
        {0, 0, 1, z1},
        {0, 0, 0, 1}
    };

    float angle;
    cout << "Enter rotation angle around X-axis (in degrees): ";
    cin >> angle;
    angle = angle * M_PI / 180; // Convert to radians
    float rotationX[4][4] = {
        {1, 0, 0, 0},
        {0, cos(angle), -sin(angle), 0},
        {0, sin(angle), cos(angle), 0},
        {0, 0, 0, 1}
    };
    drawObject(vertices, edges, numEdges, RED); // Before transformation
    applyTransformation(translationToOrigin, vertices, n);
    applyTransformation(rotationX, vertices, n);
    applyTransformation(translationBack, vertices, n);
    drawObject(vertices, edges, numEdges, GREEN);   // After transformation
    getch();
    cleardevice();

    cout << "Enter rotation angle around Y-axis (in degrees): ";
    cin >> angle;
    angle = angle * M_PI / 180; // Convert to radians
    float rotationY[4][4] = {
        { cos(angle), 0,  sin(angle), 0},
        {0, 1, 0, 0},
        {-sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}
    };
    drawObject(vertices, edges, numEdges, RED); // Before transformation
    applyTransformation(translationToOrigin, vertices, n);
    applyTransformation(rotationY, vertices, n);
    applyTransformation(translationBack, vertices, n);
    drawObject(vertices, edges, numEdges, GREEN);   // After transformation
    getch();
    cleardevice();

    cout << "Enter rotation angle around Z-axis (in degrees): ";
    cin >> angle;
    angle = angle * M_PI / 180; // Convert to radians

    float rotationZ[4][4] = {
        {cos(angle), -sin(angle), 0, 0},
        {sin(angle), cos(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    drawObject(vertices, edges, numEdges, RED); // Before transformation
    applyTransformation(translationToOrigin, vertices, n);
    applyTransformation(rotationZ, vertices, n);
    applyTransformation(translationBack, vertices, n);
    drawObject(vertices, edges, numEdges, GREEN);   // After transformation
    getch();
    cleardevice();

    float tx, ty, tz;
    cout << "Enter translation values (tx ty tz): ";
    cin >> tx >> ty >> tz;
    float translation[4][4] = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}
    };
    drawObject(vertices, edges, numEdges, RED); // Before transformation
    applyTransformation(translation, vertices, n);
    drawObject(vertices, edges, numEdges, GREEN);   // After transformation
    getch();
    cleardevice();

    float sx, sy, sz;
    cout << "Enter scaling values (sx sy sz): ";
    cin >> sx >> sy >> sz;

    float scaling[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };

    drawObject(vertices, edges, numEdges, RED); // Before transformation
    // Apply the transformations
    applyTransformation(translationToOrigin, vertices, n);
    applyTransformation(scaling, vertices, n);
    applyTransformation(translationBack, vertices, n);
    drawObject(vertices, edges, numEdges, GREEN);   // After transformation
    getch();
    cleardevice();

    cout << "Applying parallel projection...\n";
    drawObject(vertices, edges, numEdges, RED); // Before projection
    parallelProjection(vertices, n);
    drawObject(vertices, edges, numEdges, BLUE);  // After projection
    getch();
    cleardevice();

    float d;
    cout << "Enter the distance for perspective projection: ";
    cin >> d;
    drawObject(vertices, edges, numEdges, RED); // Before projection
    perspectiveProjection(vertices, n, d);
    drawObject(vertices, edges, numEdges, CYAN);  // After projection
    getch();

    closegraph();
    return 0;
}
