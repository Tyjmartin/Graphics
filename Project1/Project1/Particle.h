#ifndef PARTICLE
#define PARTICLE

#include <stdio.h>
#include <time.h>
#include "glut.h"
#include "Options.h"


// Particle interface
const int CUBE = 1;
const int SPHERE = 2;
const float GRAVITY = 0.003f;

class Particle {



public:
	Options *option;
	float p[2];
	float direction[2];
	float speed;

	int size;
	int type;
	float spin[3];
	int rotation;
	float color[3];
	float spinRate[3];
	int remove;

	//constructor
public:
	Particle(Options *op);
	void drawParticle();
	void updatePart();
	void randomize();
	float randFloat(int n);

};

#endif