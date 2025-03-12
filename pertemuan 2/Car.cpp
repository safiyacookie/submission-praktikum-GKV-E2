#include <GL/glut.h>
#include <cmath>

float carX = 0.0f;  // Car's horizontal position
float speed = 0.02f;  // Movement speed

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * M_PI / 180.0f;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawTree(float x, float y) {
    // Tree Trunk
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.05f, y - 0.2f);
    glVertex2f(x + 0.05f, y - 0.2f);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x - 0.05f, y);
    glEnd();

    // Tree Leaves (Green Circle)
    glColor3f(0.0f, 0.7f, 0.0f);
    drawCircle(x, y + 0.1f, 0.15f);
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, -0.3f, 0.0f);  // Move car based on user input

    // Car Body
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.45f, -0.05f);
    glVertex2f(-0.45f, -0.05f);
    glEnd();

    // Car Roof
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(-0.3f, 0.1f);
    glEnd();

    // Windows
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.18f);
    glVertex2f(0.15f, 0.18f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(-0.2f, 0.1f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.25f, -0.05f, 0.05f);
    drawCircle(0.25f, -0.05f, 0.05f);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Road
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glEnd();

    // Draw Tree (Behind Car)
    drawTree(-0.7f, 0.0f);

    // Draw Car
    drawCar();

    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) carX -= speed;  // Move left
    if (key == GLUT_KEY_RIGHT) carX += speed; // Move right

    // Keep the car inside the screen bounds
    if (carX > 0.8f) carX = 0.8f;
    if (carX < -0.8f) carX = -0.8f;

    glutPostRedisplay();
}

void init() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Car with Tree");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);  // Register keyboard controls
    glutMainLoop();
    return 0;
}
