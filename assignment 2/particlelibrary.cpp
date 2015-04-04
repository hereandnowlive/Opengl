#include "particlelibrary.h"
#include <stdlib.h> 
 

particle::particle(){	

	//variables controlling the postion of the particle
	this->px = -10;
	this->py = 10;
	this->pz = -10;
	
	
	//variables controlling the dirction of the particle
	this->dx = (((rand()%100)/100.0f)*0.25)+0.1;
	this->dy = (((rand()%100)/100.0f)*0.25)-0.4;
	this->dz = (((rand()%100)/100.0f)*0.25)+0.1;
	
	//speed modifier
	this->speed = 1;

	
	//variables controlling the direction of the particle
	this->rx = 0.0f;
	this->ry = 0.0f;
	this->rz = 0.0f;

	
	//variables controlling the colour of the particle
	this->r = ((rand()%100)/100.0);
	this->g = ((rand()%100)/100.0);
	this->b = ((rand()%100)/100.0);

	//age of the particle
	this->age = 10;
	
	//wind modifier
	this->wind = ((rand()%100)/100.0)*0.05;
}



