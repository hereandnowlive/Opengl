#include "point.h"
#include <stdio.h> //needed for printf command
#include <ctime>
#include <cstdlib>
#include <vector>

point::point(){	
	x = 0;
	y = 0;
}

point::point(float xin, float yin){
		x = xin;
		y = yin;
}

//--------------------------------------

vec2D::vec2D(){	
}

vec2D::vec2D(point in1,point in2){

	tempvec1 = in1;
	tempvec2 = in2;

	
	vec.y = 600;

}



//--------------------------------------

color::color(){	
	cola = 0.5;
	colb = 0.5;
	colc = 0.5;
	}


color::color(float ain, float bin, float cin){

		//srand (static_cast <unsigned> (time(0)));
		cola = ain;
		colb = bin;
		colc = bin;
	
	}



//--------------------------------------


distancefunc::distancefunc(){	
	printf("hello5\n");
}


//--------------------------------------

fastdistancefunc::fastdistancefunc(){	
	printf("hello6\n");
}


//--------------------------------------

lengthfunc::lengthfunc(){	
	printf("hello7\n");
}



//--------------------------------------

normilizefunc::normilizefunc(){	
	printf("hello8\n");
}

//--------------------------------------


vecmult::vecmult(){	
	printf("hello9\n");
}


//--------------------------------------


createvec::createvec(){	
	printf("hello10\n");
}


//--------------------------------------


movepoint::movepoint(){	
	printf("hello10\n");
}

//--------------------------------------


polygon::polygon(){	
	
	std::vector<point> in;
	
}













