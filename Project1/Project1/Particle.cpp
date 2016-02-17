
#include "Particle.h"


/*Paricle class that handles all of the modifications and up dates to particle.
Takes in an option so that it can see if a button on the keyboard is pressed to activate rotation, random colors and such.
*/

// Constructor starts the particle
Particle::Particle(Options *op){
	option = op;
	size = 5;
	type = CUBE;
	randomize();

};

// the initial draw particle this is the initial state of the particle.
void Particle::drawParticle(){


	glColor3f(0.3, 0.5, 0.9);
	if (option->color)glColor3f(randFloat(1), randFloat(1), randFloat(1));
	
	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glTranslatef(p[0], p[1], 0);

	if (type == CUBE){
		glutSolidCube(size);
	}

	glPopMatrix();
}

//updates particle values each frame
void Particle::updatePart(){

	if (p[1] < 0){
		direction[1] *= -1;
		speed = speed /1.009;
	}


	direction[1] -= GRAVITY;

	p[0] += speed * direction[0];
	p[1] += speed * direction[1];

	glPushMatrix();
	if (option->rotate){
		spin[0] += spinRate[0];
		spin[1] += spinRate[1];
		spin[2] += spinRate[2];

		if (spin[0] >= 360) spin[0] -= 360;
		if (spin[1] >= 360) spin[1] -= 360;
		if (spin[2] >= 360) spin[2] -= 360;

		glRotatef(spin[0], 1.0, 0.0, 0.0);
		glRotatef(spin[0], 0.0, 1.0, 0.0);
		glRotatef(spin[0], 0.0, 0.0, 1.0);
	}

	glPopMatrix();
	
}


// This assigns random values to the initial particle.
void Particle::randomize(){
	p[0] = 0.0f;
	p[1] = 18.0f;
	direction[0] = randFloat(1) + 0.5f;
	direction[1] = randFloat(3) + 1;
	
	if (option->randSpeed){
		speed = (randFloat(2) + 3) / 100;
	}
	else{
		speed = 0.05f;
	}
	rotation = rand() % 359;
	if (option->spray){
		direction[1] *= 2;
		speed *= 0.8;
	}

	spin[0] = 0;
	spin[1] = 0;
	spin[2] = 0;

	spinRate[0] = randFloat(50);
	spinRate[1] = spinRate[0] - randFloat(25);
	if (spinRate[1] < 0.0)
		spinRate[1] = 0.0;
	spinRate[2] = spinRate[0] - spinRate[1];
}

// Generates a random float between 0.0 and 1.0
float Particle::randFloat(int n){
	float whole = rand() % n;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return r * n;
}