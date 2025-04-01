#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

GLuint texture;
float angle = 0.0f;

GLuint LoadTexture(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return 0;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    int imageSize = width * height * 3;
    unsigned char* data = new unsigned char[imageSize];
    fread(data, sizeof(unsigned char), imageSize, file);
    fclose(file);

    for (int i = 0; i < imageSize; i += 3) {
        std::swap(data[i], data[i + 2]); // Convert BGR to RGB
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;
    return textureID;
}

void drawCube() {
    if (texture == 0) return;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    drawCube();
    glutSwapBuffers();
}

void update(int value) {
    angle += 2.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    texture = LoadTexture("flower1.bmp"); // ✅ Load texture ONCE here

    if (texture == 0) {
        std::cerr << "Failed to load texture!" << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rotating Cube with Texture");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
