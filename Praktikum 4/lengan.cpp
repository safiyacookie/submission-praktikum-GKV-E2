#include <GL/glut.h>
#include <iostream>

GLfloat xRotated = 0.0f, yRotated = 0.0f, zRotated = 0.0f;

static int shoulder = 0;
static int elbow = 0;
static int wrist = 0;
static int palmPitch = 0;  // Control for palm movement
static int thumbBase = 0, thumbMid = 0, thumbTip = 0;
static int indexBase = 0, indexMid = 0, indexTip = 0;
static int middleBase = 0, middleMid = 0, middleTip = 0;
static int ringBase = 0, ringMid = 0, ringTip = 0;
static int pinkyBase = 0, pinkyMid = 0, pinkyTip = 0;

void DrawWireCube(float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f) {
    glBegin(GL_LINES);
    // Front face lines
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);

    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);

    // Back face lines
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);

    // Connecting edges
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, -0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, -0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);

    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);
    glVertex3f(-0.5 * scaleX, 0.5 * scaleY, -0.5 * scaleZ);
    glEnd();
}

void DrawFingerSegment(float length, float width = 0.1f, float depth = 0.1f) {
    glPushMatrix();
    glScalef(length, width, depth);
    DrawWireCube();
    glPopMatrix();
}

void DrawHand() {
    // Draw palm
    glPushMatrix();
    glScalef(1.0, 0.2, 0.5);  // Scale to make a palm
    DrawWireCube();
    glPopMatrix();

    // Draw fingers
    float fingerOffset = 0.15; // Offset for finger placement
    float fingerLength = 0.5; // Length of finger segments

    // Thumb
    glPushMatrix();
    glTranslatef(0.5, 0.1, 0.2);
    glRotatef((GLfloat)thumbBase, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength);

    glTranslatef(fingerLength, 0.0, 0.0);
    glRotatef((GLfloat)thumbMid, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.75);

    glTranslatef(fingerLength * 0.75, 0.0, 0.0);
    glRotatef((GLfloat)thumbTip, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.5);
    glPopMatrix();

    // Index Finger
    glPushMatrix();
    glTranslatef(0.5, 0.1, 0.1);
    glRotatef((GLfloat)indexBase, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength);

    glTranslatef(fingerLength, 0.0, 0.0);
    glRotatef((GLfloat)indexMid, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.75);

    glTranslatef(fingerLength * 0.75, 0.0, 0.0);
    glRotatef((GLfloat)indexTip, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.5);
    glPopMatrix();

    // Middle Finger
    glPushMatrix();
    glTranslatef(0.5, 0.1, 0.0);
    glRotatef((GLfloat)middleBase, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength);

    glTranslatef(fingerLength, 0.0, 0.0);
    glRotatef((GLfloat)middleMid, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.75);

    glTranslatef(fingerLength * 0.75, 0.0, 0.0);
    glRotatef((GLfloat)middleTip, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.5);
    glPopMatrix();

    // Ring Finger
    glPushMatrix();
    glTranslatef(0.5, 0.1, -0.1);
    glRotatef((GLfloat)ringBase, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength);

    glTranslatef(fingerLength, 0.0, 0.0);
    glRotatef((GLfloat)ringMid, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.75);

    glTranslatef(fingerLength * 0.75, 0.0, 0.0);
    glRotatef((GLfloat)ringTip, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.5);
    glPopMatrix();

    // Pinky Finger
    glPushMatrix();
    glTranslatef(0.5, 0.1, -0.2);
    glRotatef((GLfloat)pinkyBase, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength);

    glTranslatef(fingerLength, 0.0, 0.0);
    glRotatef((GLfloat)pinkyMid, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.75);

    glTranslatef(fingerLength * 0.75, 0.0, 0.0);
    glRotatef((GLfloat)pinkyTip, 0.0, 0.0, 1.0);
    DrawFingerSegment(fingerLength * 0.5);
    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -7.0);

    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    DrawWireCube();
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    DrawWireCube();
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 1.0, 0.0, 0.0);

    // Draw the hand
    DrawHand();

    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(int width, int height) {
    if (height == 0 || width == 0) {
        return;
    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 's': shoulder = (shoulder + 5) % 360; break;
    case 'w': shoulder = (shoulder - 5) % 360; break;
    case 'e': elbow = (elbow + 5) % 180; break; // Limit elbow to 180 degrees
    case 'q': elbow = (elbow - 5) % 180; break; // Limit elbow to 180 degrees
    case 'd': wrist = std::min(wrist + 5, 90); break; // Limit wrist to 90 degrees
    case 'a': wrist = std::max(wrist - 5, -90); break; // Limit wrist to -90 degrees
    case 'r': palmPitch = std::min(palmPitch + 5, 90); break; // Limit palm pitch
    case 'f': palmPitch = std::max(palmPitch - 5, -90); break; // Limit palm pitch
    case 't': thumbBase = std::min(thumbBase + 5, 90); break;
    case 'g': thumbBase = std::max(thumbBase - 5, -45); break;
    case 'y': thumbMid = std::min(thumbMid + 5, 90); break;
    case 'h': thumbMid = std::max(thumbMid - 5, -45); break;
    case 'u': thumbTip = std::min(thumbTip + 5, 90); break;
    case 'j': thumbTip = std::max(thumbTip - 5, -45); break;
    case 'i': indexBase = std::min(indexBase + 5, 90); break;
    case 'k': indexBase = std::max(indexBase - 5, 0); break;
    case 'o': indexMid = std::min(indexMid + 5, 90); break;
    case 'l': indexMid = std::max(indexMid - 5, 0); break;
    case 'p': indexTip = std::min(indexTip + 5, 90); break;
    case ';': indexTip = std::max(indexTip - 5, 0); break;
    case 27: exit(0); break; // ESC key
    }
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    // You can add special key handling here if needed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Realistic Robotic Arm with Hand (GLUT)");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeys);

    glutMainLoop();
    return 0;
}
