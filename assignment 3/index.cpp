#include "index.h"
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
 

index::index(){	
	//set values of the vector
	this->x = 0;
	this->y = 0;
	this->z = 0;
	
}

//implementation of the normailze function
void index::normalize(index normal[], int i, int j,int indexsize){	

		norm = sqrt(pow((normal[i*indexsize + j].x),2.0) + pow((normal[i*indexsize + j].y),2.0) + pow((normal[i*indexsize + j].z),2.0));
		
		normal[i*indexsize + j].x = normal[i*indexsize + j].x/norm;
		normal[i*indexsize + j].y = normal[i*indexsize + j].y/norm;
		normal[i*indexsize + j].z = normal[i*indexsize + j].z/norm;
	

}

