/* CS 3GC3 - terrian assignment
 * by mitchell spector
 * Nov 27, 2014
 */
 #include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>  
#include <math.h>
#include <windows.h>
#include "index.h"


//the light postions
float light_pos0[] = {-100.0, 50.0, -100.0, 1.0};
float light_pos1[] = {200.0, 50.0, 200.0, 1.0};


//light factors, ambient, diffuse, specular 
float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {1, 0, 0, 1};
float spec0[4] = {1, 1, 1, 1}; 

float amb1[4] = {1, 1, 1, 1};
float diff1[4] = {0, 1, 0, 1};
float spec1[4] = {1, 1, 1, 1}; 


//material factors with same factors above and including shiny
float m_amb[] = {0.1, 0.1, 0.1, 1.0};
float m_diff[] = {0.7, 0.7, 0.7, 1.0};
float m_spec[] = {0.1, 0.1, 0.1, 1.0};
float shiny = 1.8;

//size range of the spikes
int spike = 30;
//controls the aglorithm rendered
int mode = 0;
//change between lights to move
int lightmove = 0;
//change between flat face and vertex shading
int gourd = 0;

//number of interations for the algorithm
int iteration = 400;

//the square size of the terrian eg: indexsize x indexsize
int indexsize = 50;

//on off for wireframe mode
int wireframe = 1;

//how much do you want the terrian to expand or contract by
int incrementor = 5;

// pointer for height map
float*heightmap;

//pointer for the vector storage systems
index*vectorstore;
index*avgvecstore;

//instantation of the index class to access specifically its functions
index func;

//camera position
float camPos[] = {0, 100, 0};



//This function contains the fault algorithm which produces the terrian seen
void generate(){

		heightmap = new float[indexsize*indexsize];
	//does the fault algorithm	
	if(mode == 0){		
		for(int k = 0; k<iteration; k++){
			float v = (rand()%360);
			float a = sin(v);
			float b = cos(v);
			float d = sqrt((indexsize*indexsize)+(indexsize*indexsize));
			float c = ((rand()%100)/100.0f) * d - (d/2.0);
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
					if(a*i + b*j - c > 0){
						heightmap [i*indexsize + j]+= 0.5;	
					}
					else{
						heightmap [i*indexsize + j]-= 0.5;	
					}
				}
			}
		}
	}
	//does the spike algorithm
	else{
		for(int k = 0; k<2; k++){
			float pd = 	(1 * 2)/ (3.14*pow(1,2));
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
					
					if(pd <= 1.0){
					
						heightmap [i*indexsize + j] += (rand()%spike +1)/2 + cos(pd*3.14)*(rand()%spike +1)/2;
					
					}
			

		
				
				}
			}
		}
		
	}
}

//This function creates vector normals for every face in the terrain
void quadvecs(){

	vectorstore = new index[indexsize*indexsize];
	
	
	for(int i = 0; i<(indexsize-2); i++){
		for(int j = 0; j < (indexsize-2);j++){
				
			float bx = 0;
			float by = heightmap [i*indexsize + (j+1)] - heightmap [i*indexsize + j];
			float bz = 1;
			
			float cx = 1;
			float cy = heightmap [(i+1)*indexsize + j] - heightmap [i*indexsize + j];
			float cz = 0;
		
			
			
			vectorstore[i*indexsize + j].x = by*cz - bz*cy;
			vectorstore[i*indexsize + j].y = bz*cx - bx*cz;
			vectorstore[i*indexsize + j].z = bx*cy - by*cx;
			
			
			//nomalizes the vector, more info in the index.cpp and index.h files
			func.normalize(vectorstore, i, j, indexsize);
			
			}
		}

	
	avgvecstore = new index[indexsize*indexsize];
	
	for(int i = 0; i<(indexsize-2); i++){
		for(int j = 0; j < (indexsize-2);j++){
		
			if(i == 0&& j!= 0){
				
				avgvecstore[i*indexsize + j].x = (vectorstore[i*indexsize + j].x)/(vectorstore[i*indexsize + (j+1)].x + vectorstore[i*indexsize + (j-1)].x);
				avgvecstore[i*indexsize + j].y = (vectorstore[i*indexsize + j].y)/(vectorstore[i*indexsize + (j+1)].y + vectorstore[i*indexsize + (j-1)].y);
				avgvecstore[i*indexsize + j].z = (vectorstore[i*indexsize + j].z)/(vectorstore[i*indexsize + (j+1)].z + vectorstore[i*indexsize + (j-1)].z);
				
			
			}
			else if(j == 0&& i!= 0){
			
				avgvecstore[i*indexsize + j].x = (vectorstore[i*indexsize + j].x)/(vectorstore[(i+1)*indexsize + j].x + vectorstore[(i-1)*indexsize + j].x);
				avgvecstore[i*indexsize + j].y = (vectorstore[i*indexsize + j].y)/(vectorstore[(i+1)*indexsize + j].y + vectorstore[(i-1)*indexsize + j].y);
				avgvecstore[i*indexsize + j].z = (vectorstore[i*indexsize + j].z)/(vectorstore[(i+1)*indexsize + j].z + vectorstore[(i-1)*indexsize + j].z);
				
			
			}
			else if((i == 0 && j == 0)||(i == indexsize-1 && j == indexsize-1) ){
				
				avgvecstore[i*indexsize + j].x = (vectorstore[i*indexsize + j].x);
				avgvecstore[i*indexsize + j].y = (vectorstore[i*indexsize + j].y);
				avgvecstore[i*indexsize + j].z = (vectorstore[i*indexsize + j].z);
			
			
			}
			
			else{
			
				avgvecstore[i*indexsize + j].x = (vectorstore[i*indexsize + j].x)/(vectorstore[(i-1)*indexsize + j].x + vectorstore[(i+1)*indexsize + j].x + vectorstore[i*indexsize + (j+1)].x + vectorstore[i*indexsize + (j-1)].x);
				avgvecstore[i*indexsize + j].y = (vectorstore[i*indexsize + j].y)/(vectorstore[(i-1)*indexsize + j].y + vectorstore[(i+1)*indexsize + j].y + vectorstore[i*indexsize + (j+1)].y + vectorstore[i*indexsize + (j-1)].y);
				avgvecstore[i*indexsize + j].z = (vectorstore[i*indexsize + j].z)/(vectorstore[(i-1)*indexsize + j].z + vectorstore[(i+1)*indexsize + j].z + vectorstore[i*indexsize + (j+1)].z + vectorstore[i*indexsize + (j-1)].z);
				
			
			}
		
		
		
		}
	}

}



void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	
	//enable lighting and both lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1); 
	glShadeModel(GL_SMOOTH);
	
	//set intial lighting factors for each light
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0); 

	glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec1); 
	
	//set material factors for the terrain
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//update the camera each display
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], indexsize/2.0,0,indexsize/2.0, 0,1,0);
	
	//display lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos1); 

	//does the wire frame view of the terrian
if(wireframe == 0){	

		for(int i = 0; i<(indexsize-2); i++){
			for(int j = 0; j < (indexsize-2);j++){
				
				glBegin(GL_LINES);
				glColor3f(1,1,1);
				glVertex3f(i,heightmap[i*indexsize + j],j);	
				glVertex3f(i,heightmap[i*indexsize + (j+1)],j+1);
			
				glEnd();
			}
		
		}
	
		for(int i = 0; i<(indexsize-2); i++){
			for(int j = 0; j < (indexsize-2);j++){
				
				glBegin(GL_LINES);
				glColor3f(1,1,1);
				glVertex3f(i,heightmap[i*indexsize + j],j);	
				glVertex3f(i+1,heightmap[(i+1)*indexsize + j],j);
			
				glEnd();
			}
		
		}	

}
// does the standard quad view of the terrian
else{

		for(int i = 0; i<(indexsize-2); i++){
			for(int j = 0; j < (indexsize-2);j++){
			
					if(gourd == 0){			
					glBegin(GL_QUAD_STRIP);
						glColor3f(1,1,1);
						glNormal3f(vectorstore[i*indexsize + j].x,vectorstore[i*indexsize + j].y ,vectorstore[i*indexsize + j].z);
						glVertex3f(i,heightmap[i*indexsize + j],j);	
						glVertex3f(i,heightmap[i*indexsize + (j+1)],j+1);
						glVertex3f(i+1,heightmap[(i+1)*indexsize + j],j);
						glVertex3f(i+1,heightmap[(i+1)*indexsize + (j+1)],j+1);
						
						
					glEnd();
					}
					
					else{
					glBegin(GL_QUAD_STRIP);
						glColor3f(1,1,1);
						glNormal3f(avgvecstore[i*indexsize + j].x,avgvecstore[i*indexsize + j].y ,avgvecstore[i*indexsize + j].z);
						glVertex3f(i,heightmap[i*indexsize + j],j);	
						glNormal3f(avgvecstore[i*indexsize + (j+1)].x,avgvecstore[i*indexsize + (j+1)].y ,avgvecstore[i*indexsize + (j+1)].z);
						glVertex3f(i,heightmap[i*indexsize + (j+1)],j+1);
						glNormal3f(avgvecstore[(i+1)*indexsize + j].x,avgvecstore[(i+1)*indexsize + j].y ,avgvecstore[(i+1)*indexsize + j].z);
						glVertex3f(i+1,heightmap[(i+1)*indexsize + j],j);
						glNormal3f(avgvecstore[(i+1)*indexsize + (j+1)].x,avgvecstore[(i+1)*indexsize + (j+1)].y ,avgvecstore[(i+1)*indexsize + (j+1)].z);
						glVertex3f(i+1,heightmap[(i+1)*indexsize + (j+1)],j+1);

					glEnd();
					
					}
			}
		
		}

	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(light_pos0[0],light_pos0[1],light_pos0[2]);
		glutSolidSphere(5, 16,16);	
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(light_pos1[0],light_pos1[1],light_pos1[2]);
		glutSolidSphere(5, 16,16);	
	glPopMatrix();


}



	
	glutSwapBuffers();
}

void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
	}
	
	//if 'w' is pressed the terrain will be shown in wire frame mode
	if(key == 'w' || key == 'W')
	{
		if(wireframe == 1){
		wireframe = 0;
		}
		else{
		wireframe = 1;
		}
		
	}
	
	//if the 'r' is pressed the terrian will be re-rendered
	if(key == 'r' || key == 'R')
	{
		for(int i = 0; i<(indexsize-1); i++){
			for(int j = 0; j < (indexsize-1);j++){
			
			heightmap [i*indexsize + j]= 0;
			
			}
		}
		delete[] heightmap;
		generate();
		delete[] vectorstore;
		quadvecs();	
		
	}
	
	//if the '+' is pressed it will increment the scale at which the terrian is increased
	if(key == '+'){
		
		if(incrementor < 10){
		
			incrementor += 1;
		}
		
	}
	
	//if the '-' is pressed it will decrement the scale at which the terrian is decreased
	if(key == '-'){
		
		if(incrementor > 1){
		
			incrementor -= 1;
		
		}
		
	}
	
	// both 3 and 4 increase and decrease the size of the terrain by the size of the incrementor
	if(key == '4'){
		
		if((indexsize+incrementor) < 300){
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			indexsize += incrementor;
			generate();
			delete[] vectorstore;
			quadvecs();	
		}
		else{
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			indexsize = 300;
			generate();	
			delete[] vectorstore;
			quadvecs();			
		
		}
	}
	
	if(key == '3'){
		
		if((indexsize-incrementor) > 50){
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			indexsize -= incrementor;
			generate();
			delete[] vectorstore;
			quadvecs();	
		}
		else{
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			indexsize = 50;
			generate();	
			delete[] vectorstore;
			quadvecs();	
		
		}
	}
	//do gourd shading
	if(key == 'e'|| key == 'E'){
		
		if(gourd == 0){
			gourd = 1;
		}
		else{
			gourd = 0;
		}
		
	}
	//switch the light you are moving
	if(key == '1'){
		
		if(lightmove == 0){
			lightmove = 1;
		}
		else{
			lightmove = 0;
		}
		
	}
	//t,f,g,h,b,n move the light selected
		if(key == 't'|| key == 'T'){
		
			if(lightmove == 0){
			light_pos0[2] += 1;
			
			}
			
			else{
			light_pos1[2] += 1;
			
			}
		
	}
	
		if(key == 'g'|| key == 'G'){
		
			if(lightmove == 0){
			light_pos0[2] -= 1;
			
			}
			
			else{
			light_pos1[2] -= 1;
			
			}

		
	}
	
	
		if(key == 'f'|| key == 'F'){
		
			if(lightmove == 0){
			light_pos0[0] += 1;
			
			}
			
			else{
			light_pos1[0] += 1;
			
			}
		
	}
	
		if(key == 'h'|| key == 'H'){
		
			if(lightmove == 0){
			light_pos0[0] -= 1;
			
			}
			
			else{
			light_pos1[0] -= 1;
			
			}
		
	}
	
	if(key == 'b'|| key == 'B'){
		
			if(lightmove == 0){
			light_pos0[1] -= 1;
			
			}
			
			else{
			light_pos1[1] -= 1;
			
			}
		
	}
		if(key == 'N'|| key == 'n'){
		
			if(lightmove == 0){
			light_pos0[1] += 1;
			
			}
			
			else{
			light_pos1[1] += 1;
			
			}
		
	}
	//switch algorithms	
	if(key == 'y'|| key == 'Y'){
		
			if(mode == 0){
			mode = 1;
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			
			delete[] heightmap;
			generate();
			delete[] vectorstore;
			quadvecs();	
			
			}
			
			else{
			mode = 0;
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			generate();
			delete[] vectorstore;
			quadvecs();	
			
			}
		
	}
	//expand spike agorithm
	if(key == 'i'|| key == 'I'){
		
			if(spike > 1){
			spike -= 1;
			
			}
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			generate();
			delete[] vectorstore;
			quadvecs();	
		
	}
	//decrease spike algorithm
	if(key == 'o'|| key == 'O'){
		
			if(spike < 50){
			spike += 1;
			
			}
			for(int i = 0; i<(indexsize-1); i++){
				for(int j = 0; j < (indexsize-1);j++){
				
				heightmap [i*indexsize + j]= 0;
				
				}
			}
			delete[] heightmap;
			generate();
			delete[] vectorstore;
			quadvecs();	
		
	}
	
}


void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			camPos[0]-=1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 1;
			break;
		
		case GLUT_KEY_HOME:
		
			camPos[1] += 1;
			break;

		case GLUT_KEY_END:
		if(camPos[1] > 50){
			camPos[1] -= 1;
		}
			break;

	}
	glutPostRedisplay();
}

void timer(int value){





glutTimerFunc(30, timer, 0);
glutPostRedisplay();

}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("terrian map");	//creates the window
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(kbd);
	glutSpecialFunc(special);
	
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_BACK);
	//start random seed
	time_t randtimer;
	srand (static_cast <unsigned> (time(&randtimer)));
	init();
	
	//generate terrian and create normals for the first terrian
	generate();
	generate();
	quadvecs();
	printf("\n q: quit program\n w: wireframe mode\n r: re-render terrian\n +or-: increment and decrement the terrian size counter\n 3 or 4: expand or contract the terrian\n e: switch to groud shading\n 1: switch between lights to move\n t,f,g,h,b,n: move the selected light around\n y: switch algorithms\n i or o: expand or decrease spikes\n home, end, up key, down key, left key, right key: move camera\n");
	glutTimerFunc(8, timer, 0);
	
	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}