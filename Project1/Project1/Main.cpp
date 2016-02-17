

/*Tyler Martin
4836318
December 5 2014

*/
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <malloc.h>
#include <new>
#include <freeglut.h>
#include "Particle.h"

using namespace std;
Options *options;

const int MAX_PARTS = 200;

Particle *particle;

typedef struct {
	float friction;
	vector<Particle*> particles;
} global;

global glob;


// Initialize the options
void init(){
	options = new Options();
};




// Draws the fountain and the ground!
void drawGround(){
	glBegin(GL_QUADS);
		glColor3f(0.7, 0.1, 0.1);
		glNormal3i(0, 1, 0);
		glVertex3i(180, 0, 180);
		glVertex3i(180, 0, -180);
		glVertex3i(-180, 0, -180);
		glVertex3i(-180, 0, 180);
	glEnd();

	glColor3f(0.9, 0.3, 0.1);

	//draw fountain
	glPushMatrix();
	glTranslatef(0.0, 8.0, 0.0);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(15);
	glPopMatrix();
}


// This is the draw it takes care of the updating of the screen!
void draw(){
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	drawGround();
	
	if (glob.particles.size() < MAX_PARTS && options->running){
		Particle *p = new Particle(options);
		glob.particles.push_back(p);
	}

	for (int i = 0; i < glob.particles.size(); i++){
		glob.particles.at(i)->drawParticle();
		glob.particles.at(i)->updatePart();
	}
	
	
	glutSwapBuffers();
	glFlush();

	for (int i = 0; i < glob.particles.size(); i++){
		if (abs(glob.particles.at(i)->p[0]) > 180 || glob.particles.at(i)->speed <0.0000001f) {
			glob.particles.erase(glob.particles.begin() + i); //set iterator to index i and delete
		}
	}
}



void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1B:
	case'q':
	case 'Q':
		exit(0);
		break;
	case'p':
	case'P':
		options->running = !options->running;
		break;
	case's':
	case'S':
		options->randSpeed = !options->randSpeed;
		break;
	case'c':
	case'C':
		options->color = !options->color;
		break;
	case'r':
	case'R':
		options->rotate = !options->rotate;
		break;
	case'v':
	case'V':
		options->spray = !options->spray;
		break;
	case'f':
	case'F':
		Particle *p = new Particle(options);
		glob.particles.push_back(p);
		break;
	};

}//keyboard


int main(int argc, char** argv)
{
	srand(unsigned(time(NULL)));
	init();

	printf("Q:quit\nF:filter\nT:triangle\nS:save\n");
	glutInit(&argc, argv);
	glutInitWindowSize(options->width, options->height);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Particle Fountain");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	//glutMouseFunc(mouse);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)options->width / (float)options->height, 800, 1);
	gluLookAt(300, 200, 310, 0, 20, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	//wireframe mode glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//normal mode glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//initiLIZE LIGHTING
	glutMainLoop();

	return 0;
}