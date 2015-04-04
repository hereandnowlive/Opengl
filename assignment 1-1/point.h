#ifndef __POINT_H__	//guard against cyclic dependancy
#define __POINT_H__

#include <vector>
//two dimension point>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
class point{ //stores all information relating to the first mode
public:
	
	point();
	point(float xin, float yin);

	
	float x;
	float y;
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//2D-vector>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class vec2D{ //stores all direction information
public:
	
	vec2D();
	vec2D(point in1,point in2);
	
	
	point vec;
	point tempvec1;
	point tempvec2;

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//color floats>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class color{
public:
	
	color();
	color(float ain, float bin, float cin);
	
	float cola;
	float colb;
	float colc;

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//distance function>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


class distancefunc{
public:
	
	distancefunc();

};
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//fast distance function>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
class fastdistancefunc{
public:
	
	fastdistancefunc();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//length function >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class lengthfunc{
public:
	
	lengthfunc();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//normilize function >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class normilizefunc{
public:
	
	normilizefunc();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//vector multiply function >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class vecmult{
public:
	
	vecmult();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//create vector function >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class createvec{
public:
	
	createvec();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//move point function >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class movepoint{
public:
	
	movepoint();

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

class polygon{
public:
	
	polygon();
	
	std::vector<point> in;

};



#endif