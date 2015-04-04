#ifndef __INDEX_H__	//guard against cyclic dependancy
#define __INDEX_H__



class index{ 
public:
	
	index();
	//variables for storing vectors
	float x;
	float y;
	float z;
	
	//intialization of normalize function
	void normalize(index normal[], int i, int j,int indexsize);
	float norm;
};

#endif