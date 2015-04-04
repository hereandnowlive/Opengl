#ifndef __PARTICLELIBRARY_H__	//guard against cyclic dependancy
#define __PARTICLELIBRARY_H__



class particle{ 
public:
	
	particle();

	//variables controlling the postion of the particle
	float px;
	float py;
	float pz;
	
	//variables controlling the dirction of the particle
	float dx;
	float dy;
	float dz;
	
	//speed modifier
	float speed;
	
	//variables controlling the direction of the particle
	float rx;
	float ry;
	float rz;
	
	//variables controlling the colour of the particle
	float r;
	float g;
	float b;
	
	//age of the particle
	float age;
	
	//wind modifier
	float wind;
	

	
};

#endif