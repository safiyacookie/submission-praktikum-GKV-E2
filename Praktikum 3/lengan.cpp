#include <GL/glut.h>
#include <cmath>

float angle = -45.0f;

void drawJointedArm() {
    glPushMatrix();

    // Balok pertama
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(-0.3f, 0.0f, 0.0f);
    glScalef(0.6f, 0.15f, 0.2f);
    glutSolidCube(1.0);

    glPopMatrix();
    glPushMatrix();

    // Rotasi untuk balok kedua agar bisa bergerak
    glTranslatef(0.0f, -0.1f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.3f, 0.0f, 0.0f);
    glScalef(0.6f, 0.15f, 0.2f);
    glutSolidCube(1.0);

    // Menambahkan dua jari sebagai balok kecil di ujungnya
    glColor3f(0.0f, 0.0f, 1.0f); // Warna merah untuk jari

    glPushMatrix();
    glTranslatef(0.35f, 0.1f, 0.1f); // Memberi jarak lebih jauh
    glScalef(0.3f, 0.075f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.35f, -0.1f, 0.1f); // Memberi jarak lebih jauh
    glScalef(0.3f, 0.075f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Menambahkan dua balok tambahan di ujung balok kedua
    glColor3f(0.0f, 0.0f, 1.0f); // Warna hijau untuk balok tambahan

    glPushMatrix();
    glTranslatef(0.5f, 0.15f, 0.0f); // Memberi jarak lebih jauh
    glScalef(0.3f, 0.075f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.15f, 0.0f); // Memberi jarak lebih jauh
    glScalef(0.3f, 0.075f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.5f);

    drawJointedArm();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {
        angle += 5.0f; // Putar ke kiri
    }
    else if (key == 'd') {
        angle -= 5.0f; // Putar ke kanan
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lengan Berbentuk Sudut");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
