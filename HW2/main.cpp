/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {

	int numTeapots = 10;
	float radius = 1.0;
	float vOffset = 0.3;

	for (int i = 0; i < numTeapots; i++)
	{
		float deg = (360.0/(((float)numTeapots/i)));
		glPushMatrix();

		// Rotate teapot from center of world
		glRotatef(deg, 0, 0, 1);
		
		// Translate right and up a little bit
		glTranslatef(radius, vOffset, 0.0);
		
		// Tilt teapot forward a little bit
		glRotatef(5.0, 0, 0, -1);

		glutSolidTeapot(0.1);
		glPopMatrix();
	}
}

void problem2() {
    float startHeight = 1.2;
	float stepWidth = 0.15;
	float heightInc = -0.05;
	float numSteps = 20;

	float currHeight = startHeight;

	float totalWidth = stepWidth * numSteps;

	// Put coordinate system at center of world on x-axis
	glPushMatrix();
	glTranslatef(-totalWidth/2, 0.0, 0.0);


	// Draw each step with an increasing/decreasing height
	for (int i = 0; i < numSteps; i++)
	{
		float height = startHeight + (heightInc*i);
		glPushMatrix();
		glTranslatef(i * stepWidth, height/2, 0.0);
		glScalef(stepWidth, height, 1);
		glutSolidCube(1);
		glPopMatrix();
	}

	glPopMatrix();
	
}

void problem3() {
    int numObjsV = 6;
	int numObjsH = 6;
	float objSize = 0.1;
	float horizSpacing = objSize + 0.20;
	float vertSpacing = objSize + 0.2;
	
	
	float width = (numObjsH * horizSpacing);
	float height = (numObjsV * vertSpacing);


	// Put coordinate system at center of world
	glPushMatrix();
	glTranslatef(-width/2, height/2 - vertSpacing, 0.0);

	// Draw each row of the triangle, reducing the number of teapots per row by one
	for (int row = 0; row < numObjsV; row++) {
		int currRowObjCnt = numObjsH - row;

		float rowWidth = (currRowObjCnt * horizSpacing);

		// Offset to the left of the row to center it in local space
		float rowOffset = (width - rowWidth + horizSpacing) / 2; 

		// Draw each teapot in the current row factoring in rowOffset to center horizontally
		for (int col = 0; col < currRowObjCnt; col++)
		{
			glPushMatrix();
			glTranslatef(rowOffset + col*horizSpacing, -row*vertSpacing, 0.0);
			glutSolidTeapot(objSize);
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void problem4() {
    // Draw a sunflower with petals

	float groundRadius = 15.0;
	float groundRoundness = 0.3;

	float stemHeight = 1.5;
	float stemRadius = 0.03;

	float flowerAngle = 45.0;
	float flowerBaseWidth = 0.3;
	float flowerBaseDepth = 0.05;

	float petalWidth = 0.08;
	float petalHeight = 0.5;
	int numPetals = 16;

	glPushMatrix();
		// Offset entire model down by half stem height
		glTranslatef(0.0, -stemHeight/2, 0.0);
		// Rotate model by 45 degrees
		glRotatef(45.0, 0.0, 1.0, 0.0);

		// Draw ground hill
		glPushMatrix();
			glScalef(1.0, groundRoundness, 1.0);
			glTranslatef(0.0, -groundRadius, 0.0);
			
			glutSolidSphere(groundRadius, 48, 48);
		glPopMatrix();

		// Draw stem
		glPushMatrix();
			glRotatef(90.0, -1.0, 0.0, 0.0);
			glutSolidCylinder(stemRadius, stemHeight, 16, 3);
		glPopMatrix();

		// Draw flower base
		glPushMatrix();
		
			glTranslatef(0.0, stemHeight, 0.0);
			glRotatef(flowerAngle, 0.0, 0.0, 1.0);

			glPushMatrix();
				glRotatef(90.0, -1.0, 0.0, 0.0);
				glutSolidCylinder(flowerBaseWidth, flowerBaseDepth, 16, 3);
			glPopMatrix();

			// Draw flower petals
			glPushMatrix();
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glTranslatef(flowerBaseDepth/2, 0.0, 0.0);
				// Draw each petal on flower base
				for (int i = 0; i < numPetals; i++)
				{
					glRotatef((360.0/numPetals), 1.0, 0.0, 0.0);
					glTranslatef(0.0, flowerBaseWidth, 0.0); // Offset petal onto flower base surface
					glBegin(GL_TRIANGLES);
					glColor3f(1.0, 1.0, 1.0);
					glVertex3f(0.0, 0.0, -petalWidth);
					glVertex3f(0.0, 0.0, petalWidth);
					glVertex3f(0.0, petalHeight, 0.0);
					glEnd();
					glTranslatef(0.0, -flowerBaseWidth, 0.0); // Undo offset petal onto flower base surface
				}
			glPopMatrix();
		
		glPopMatrix();

	glPopMatrix();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
