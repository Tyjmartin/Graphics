
/* rotate_light.c:
* This rotates a green cube.
*
* Brian J. Ross
* November 2000.
*/


#include <stdio.h>
#include <freeglut.h>

#define X 0
#define Y 1
#define Z 2

struct glob {
	float angle[3];
	int axis;
	int local;
};

struct glob global = { { 0.0, 0.0, 0.0 }, Y, GL_FALSE };

void myLightInit() {
	GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);   /* turns on lighting */
	glEnable(GL_LIGHT0);     /* turns on light 0  */
	glEnable(GL_NORMALIZE);
}

void userintro() {
	printf("Left mouse = rotate left faster\n");
	printf("Right mouse = rotate right faster\n");
	printf("Middle mouse = reset\n");
	printf("x, y, z = rotate about x, y, or z axis\n");
	printf("l = toggle local viewing for lighting\n");
	printf("q = quit\n");
}

void drawcube() {
	int pt[][3] = { { 10, 10, 10 }, { 10, -10, 10 }, { -10, -10, 10 }, { -10, 10, 10 },
	{ 10, 10, -10 }, { 10, -10, -10 }, { -10, -10, -10 }, { -10, 10, -10 } };

	int face[][4] = { { 0, 3, 2, 1 }, { 3, 7, 6, 2 }, { 7, 4, 5, 6 }, { 4, 0, 1, 5 }, { 0, 4, 7, 3 }, { 1, 2, 6, 5 } };
	float norm[][3] = { { 0, 0, 1.0 }, { -1.0, 0, 0 }, { 0, 0, -1.0 }, { 1.0, 0, 0 }, { 0, 1.0, 0 }, { 0, -1.0, 0 } };
	int i;
	GLfloat mat_ambient[] = { 0.0215, 0.1745, 0.0215, 1.0 };
	GLfloat mat_diffuse[] = { 0.0757, 0.6142, 0.1757, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 77.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(global.angle[X], 1.0, 0.0, 0.0);
	glRotatef(global.angle[Y], 0.0, 1.0, 0.0);
	glRotatef(global.angle[Z], 0.0, 0.0, 1.0);

	for (i = 0; i < 6; ++i) {
		glNormal3fv(norm[i]);
		glBegin(GL_POLYGON);
		glVertex3iv(pt[face[i][0]]);
		glVertex3iv(pt[face[i][1]]);
		glVertex3iv(pt[face[i][2]]);
		glVertex3iv(pt[face[i][3]]);
		glEnd();
	}
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {

	switch (key){
	case 'x':
	case 'X':
		global.axis = X;
		break;

	case 'y':
	case 'Y':
		global.axis = Y;
		break;

	case 'z':
	case 'Z':
		global.axis = Z;
		break;

	case 'l':
	case 'L':
		global.local = !global.local; // toggle local viewer
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, global.local);
		break;

	case 0x1B:
	case 'q':
	case 'Q':
		exit(0);
		break;
	}
}

void mouse(int btn, int state, int x, int y) {

	/*
	printf("%3d, %3d, %f %f %f\n", btn, state,
	global.angle[X],global.angle[Y],global.angle[Z]); */

	if (state == GLUT_DOWN) {
		if (btn == GLUT_LEFT_BUTTON) {
			global.angle[global.axis] = global.angle[global.axis] + 0.2;
		}
		else if (btn == GLUT_RIGHT_BUTTON) {
			global.angle[global.axis] = global.angle[global.axis] - 0.2;
		}
		else {
			global.angle[X] = 0.0;
			global.angle[Y] = 0.0;
			global.angle[Z] = 0.0;
			glPopMatrix();
			glPushMatrix();
		}
	}
}

int main(int argc, char **argv) {

	userintro();
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Glut rotate 2");
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawcube);
	glutIdleFunc(drawcube);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	myLightInit();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glutMainLoop();
}
