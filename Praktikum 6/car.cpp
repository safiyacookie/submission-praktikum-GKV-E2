#include <GL/glut.h>
#include <cmath>

// Lighting parameters
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Rotation angles
float angleX = 0.0f;
float angleY = 0.0f;

void init() {
    glClearColor(0.53, 0.81, 0.92, 1.0); // Sky blue background
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glShadeModel(GL_SMOOTH);
}

void drawCube(float r, float g, float b, float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f) {
    GLfloat mat_ambient[] = { r * 0.3, g * 0.3, b * 0.3, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawCar() {
    // Main body (chassis)
    drawCube(0.8, 0.2, 0.2, 2.0, 0.5, 1.0); // Red

    // Roof
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    drawCube(0.2, 0.2, 0.8, 1.5, 0.3, 0.9); // Blue
    glPopMatrix();

    // Front hood
    glPushMatrix();
    glTranslatef(1.0, 0.15, 0.0);
    drawCube(0.9, 0.9, 0.1, 0.5, 0.2, 0.9); // Yellow
    glPopMatrix();

    // Rear trunk
    glPushMatrix();
    glTranslatef(-1.0, 0.15, 0.0);
    drawCube(0.1, 0.8, 0.1, 0.5, 0.2, 0.9); // Green
    glPopMatrix();

    // Front bumper
    glPushMatrix();
    glTranslatef(1.3, -0.1, 0.0);
    drawCube(0.7, 0.7, 0.7, 0.2, 0.1, 1.0); // Silver
    glPopMatrix();

    // Rear bumper
    glPushMatrix();
    glTranslatef(-1.3, -0.1, 0.0);
    drawCube(0.7, 0.7, 0.7, 0.2, 0.1, 1.0); // Silver
    glPopMatrix();

    // Side doors
    glPushMatrix();
    glTranslatef(0.3, 0.0, 0.55);
    drawCube(0.8, 0.8, 0.8, 1.0, 0.4, 0.05); // Light gray
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0.0, -0.55);
    drawCube(0.8, 0.8, 0.8, 1.0, 0.4, 0.05); // Light gray
    glPopMatrix();

    // Windows
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    GLfloat window_mat[] = { 0.1, 0.1, 0.3, 0.7 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, window_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glScalef(1.4, 0.25, 0.85);
    glutSolidCube(1.0);
    glPopMatrix();

    // Wheels
    GLfloat tire_mat[] = { 0.1, 0.1, 0.1, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tire_mat);

    // Front left wheel
    glPushMatrix();
    glTranslatef(0.8, -0.4, 0.6);
    glutSolidTorus(0.1, 0.2, 16, 16);
    glPopMatrix();

    // Front right wheel
    glPushMatrix();
    glTranslatef(0.8, -0.4, -0.6);
    glutSolidTorus(0.1, 0.2, 16, 16);
    glPopMatrix();

    // Rear left wheel
    glPushMatrix();
    glTranslatef(-0.8, -0.4, 0.6);
    glutSolidTorus(0.1, 0.2, 16, 16);
    glPopMatrix();

    // Rear right wheel
    glPushMatrix();
    glTranslatef(-0.8, -0.4, -0.6);
    glutSolidTorus(0.1, 0.2, 16, 16);
    glPopMatrix();

    // Wheel hubs
    GLfloat hub_mat[] = { 0.8, 0.8, 0.8, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, hub_mat);

    // Front left hub
    glPushMatrix();
    glTranslatef(0.8, -0.4, 0.6);
    glutSolidSphere(0.08, 16, 16);
    glPopMatrix();

    // Front right hub
    glPushMatrix();
    glTranslatef(0.8, -0.4, -0.6);
    glutSolidSphere(0.08, 16, 16);
    glPopMatrix();

    // Rear left hub
    glPushMatrix();
    glTranslatef(-0.8, -0.4, 0.6);
    glutSolidSphere(0.08, 16, 16);
    glPopMatrix();

    // Rear right hub
    glPushMatrix();
    glTranslatef(-0.8, -0.4, -0.6);
    glutSolidSphere(0.08, 16, 16);
    glPopMatrix();

    // Headlights
    GLfloat light_mat[] = { 1.0, 1.0, 0.8, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 120.0);

    // Left headlight
    glPushMatrix();
    glTranslatef(1.3, 0.0, 0.3);
    glutSolidSphere(0.1, 16, 16);
    glPopMatrix();

    // Right headlight
    glPushMatrix();
    glTranslatef(1.3, 0.0, -0.3);
    glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position
    gluLookAt(0.0, 1.5, 5.0,  // eye position
        0.0, 0.0, 0.0,   // look at position
        0.0, 1.0, 0.0);  // up vector

    // Rotate the entire scene
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    // Draw the car
    drawCar();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'x':
        angleX += 5.0f;
        break;
    case 'X':
        angleX -= 5.0f;
        break;
    case 'y':
        angleY += 5.0f;
        break;
    case 'Y':
        angleY -= 5.0f;
        break;
    case 27: // ESC key
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Colorful 3D Car with Lighting");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
