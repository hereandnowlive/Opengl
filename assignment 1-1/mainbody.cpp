#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


#include "point.h"



//instances of class

point comp; //instance of the point class in header

vec2D foo; //instance of the vec2D class in header

color paint; //instance of the color class in header for storage of color values

polygon shape;


// vectors

std::vector<point> array;  //first click point

std::vector<point> vecarray; // stores the vector normals

std::vector<point> array2;//stores second click for line mode

std::vector<color> colorarray; //stores point color values

std::vector<int> counter;

//incrementing variables
int j=0; //counter to tell if the mouse is making a vertex or making a direction

int v; //used for randomization and minimum number for the random object generator

int a = 0; // for mode 2, makes the display lines work

int b = 0; //cuts off the points that are already in the polygon

int g = 0; //tells the number of sides in a specific polygon

float width = 599;

float height = 599;

//color variables
float colora;
float colorb;
float colorc;


//<initialization storage variables>

//normalization variable
float norm = 0.0f;


//speed variable
int speed = 1;


//pause variable
int pause = 0;


//mode varaible: tells what mode your in, default zero mode which is nothing
int mode = 0;

//point size
int pointsize = 3;

//line width
float linewidth = 2;

/* display function - GLUT display callback function
 *		clears the screen, draws a square, and displays it
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
		
	
		
		
				//POINT MODE----------------------------------
				if(mode == 1){
					for(int i = 0; i < array.size(); i++){	
						glColor3f(colorarray[i].cola, colorarray[i].colb, colorarray[i].colc);
						glBegin(GL_POINTS);
						glVertex2f(array[i].x, (height-array[i].y));
						glEnd();
					}
				}
				//LINE MODE-----------------------------------
				else if(mode == 2){
				
					
						for(int i = 0 + a; i < array.size(); i++){	
							glColor3f(colorarray[i].cola, colorarray[i].colb, colorarray[i].colc);
							glBegin(GL_POINTS);
							glVertex2f(array[i].x, (height-array[i].y));
							glEnd();
						}
					
						
					
						for(int i = 0; i < array.size(); i++){	
							
							glColor3f(colorarray[i].cola, colorarray[i].colb, colorarray[i].colc);
							glBegin(GL_LINES);
							if(i % 2 != 0 && i != 0){
								glVertex2f(array[i-1].x, (height-array[i-1].y));
								glVertex2f(array[i].x, (height-array[i].y));
							}
							glEnd();
							
						}						
						
						

				}
				//POLYGON MODE--------------------------------
				else if(mode == 3){
					
					
					for(int i = 0 + b; i < array.size(); i++){
						glColor3f(colorarray[i].cola, colorarray[i].colb, colorarray[i].colc);
						glBegin(GL_POINTS);
						glVertex2f(array[i].x, (height-array[i].y));
						glEnd();
					}
					
					


						for(int s = 0; s < counter.size(); s++){
							
							for(int k = 0; k < counter[s]; k++){
								glColor3f(colorarray[k].cola, colorarray[k].colb, colorarray[k].colc);
								glBegin(GL_POLYGON);
								glVertex2f(array[k].x, (height-array[k].y));
							}

							
						}

						glEnd();
								
					
					
					
				}
				
			
			
				
	
	glutSwapBuffers();
}
		
	
void randomcolors(){ //simplifies alot of randamization of colours at the beginning of modes
	colora = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	colorb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	colorc = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}



void mouse(int btn, int state, int x, int y)
{
	
	
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && j==0)
	{	

		
		
		 if(array.size() % 2 != 0){  //mode 2 remove dots counter
			a = a + 2;
		 }
		 
		 paint.cola = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // each randomizes a section of the colour statement for vertices
		 paint.colb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		 paint.colc = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		 colorarray.push_back(paint);
		 
		 
		comp.x = x;
		comp.y = y;
		
		if(mode == 3){
			g = g + 1;
			
			
			
			array.push_back(comp);
			foo.tempvec1 = comp;
		
		
		}
		
		if(mode == 1 | mode == 2){

			array.push_back(comp);
			foo.tempvec1 = comp;
		}
		
		
		
		j = 1;	
	}

	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && j==1){
		
		
		

		
		j = 0;
		comp.x = x;
		comp.y = y;
		if(mode == 1 | mode == 2){
			
			foo.tempvec2 = comp;
			foo.vec.x = foo.tempvec2.x - foo.tempvec1.x;
			foo.vec.y =(foo.tempvec2.y - foo.tempvec1.y);
			norm = sqrt(pow(foo.vec.x,2.0) + pow(foo.vec.y,2.0)); // sets a norm variable to do the normilization of the vector
			
			foo.vec.x = foo.vec.x/norm;
			foo.vec.y = foo.vec.y/norm;
			
			
			vecarray.push_back(foo.vec);
		}
		
		if(mode == 3){
		
			foo.tempvec2 = comp;
			foo.vec.x = foo.tempvec2.x - foo.tempvec1.x;
			foo.vec.y =(foo.tempvec2.y - foo.tempvec1.y);
			norm = sqrt(pow(foo.vec.x,2.0) + pow(foo.vec.y,2.0)); //embed this in a function away in another class
			
			foo.vec.x = foo.vec.x/norm;
			foo.vec.y = foo.vec.y/norm;
			
			
			vecarray.push_back(foo.vec);
		
		
		
		}
		
		
		
		
	}
	
	

	
}



void clear(){
		while(!array.empty()){
			array.pop_back();
		}
		while(!vecarray.empty()){
			vecarray.pop_back();
		}
		while(!colorarray.empty()){
			colorarray.pop_back();
		}
		while(!counter.empty()){
			counter.pop_back();
		}
		j=0;
		pointsize = 3;
		linewidth = 2;
		a = 0;
		b = 0;
		g = 0;
}

void kbd(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q': 
			exit(0);
			break;

			
		case 'w': 
		
			
			b = b + g;
			counter.push_back(g);
			g = 0;
			
				
			break;	
		
		
		case 'P':
			if(pause == 0){
				pause = 1;
			}
			else if(pause == 1){
				pause = 0;
			}
			break;
			
		case '+':
			if(speed < 10){	//limits speed to prevent breaking the program
			speed = speed + 1;
			}
			break;
			
		case '-':
			if(speed > 1){	//limits speed to prevent breaking the program
			speed = speed - 1;
			}
			break;
		
		case 'R': //clears all vectors in program by human input 
			clear();
			randomcolors();
			break;
			
		case '1': 
			clear();
			randomcolors();
			mode = 1;
			break;
			
		case '2': 
			clear();
			randomcolors();
			mode = 2;
			break;
			
		case '3': 
			clear();
			randomcolors();
			mode = 3;
			break;
		
		case 'A': 
				clear();
				if(mode == 1 | mode == 2){
					v = 50 + (rand() % (int)(100 - 50 + 1));
						//printf("%d \n",v);
						
						
						for(int i = 0; i < v;i++){
							//simulated click 1
							 paint.cola = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
							 paint.colb = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
							 paint.colc = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
							 colorarray.push_back(paint);
							comp.x =  (rand() % (int)(width - 0 + 1));
							comp.y =  (rand() % (int)(height - 0 + 1));
							array.push_back(comp);	
							foo.tempvec1 = comp;
							
							//simulated click 2
							comp.x =  (rand() % (int)(width - 0 + 1));
							comp.y =  (rand() % (int)(height - 0 + 1));
							foo.tempvec2 = comp;
							foo.vec.x = foo.tempvec2.x - foo.tempvec1.x;
							foo.vec.y =(foo.tempvec2.y - foo.tempvec1.y);
							norm = sqrt(pow(foo.vec.x,2.0) + pow(foo.vec.y,2.0)); //embed this in a function away in another class
							
							foo.vec.x = foo.vec.x/norm;
							foo.vec.y = foo.vec.y/norm;
							
							vecarray.push_back(foo.vec);
							
							if(array.size() % 2 != 0){
							a = array.size();
							}
							
						}
				}
			break;
		
		case 'z': 
			if(pointsize < 100 | linewidth < 100){
				pointsize = pointsize + 1;
				linewidth = linewidth + 1.0f;
			}
			break;
		case 'x': 
			if(pointsize > 1 | linewidth > 1){
				pointsize = pointsize - 1;
				linewidth = linewidth - 1.0f;
			}
			break;			

	}
}


void init(void)
{
	gluOrtho2D(0, width, 0, height);
	glPointSize(pointsize);
	glLineWidth(linewidth);
	

}



void timer(int value)
{
	if(pause == 0){
	
	
		if(mode == 1 | mode == 2){
		
			for(int k = 0; k < vecarray.size(); k++){
					if(array[k].x > (width + 0.1)|array[k].x < -0.1){
						vecarray[k].x = -vecarray[k].x;
					}
					else if(array[k].y > (height + 0.1)|array[k].y < -0.1){
						vecarray[k].y = -vecarray[k].y;
					}
					array[k].x = array[k].x + (vecarray[k].x * speed);
					array[k].y = array[k].y + (vecarray[k].y * speed);
				
			}
			
		}
		
		if(mode == 3){
		
			for(int k = 0; k < vecarray.size(); k++){
					if(array[k].x > (width + 0.1)|array[k].x < -0.1){
						vecarray[k].x = -vecarray[k].x;
					}
					else if(array[k].y > (height + 0.1)|array[k].y < -0.1){
						vecarray[k].y = -vecarray[k].y;
					}
					array[k].x = array[k].x + (vecarray[k].x * speed);
					array[k].y = array[k].y + (vecarray[k].y * speed);
				
			}
		}
	

	}
		
		
		
	
	glPointSize(pointsize);
	glLineWidth(linewidth);
	glutPostRedisplay();
	glutTimerFunc(17, timer, 0);
	


}


/* main function - program entry point */
int main(int argc, char** argv)
{


	glutInit(&argc, argv);		//starts up GLUT
	
	width = glutGet(GLUT_SCREEN_WIDTH);
	printf("%f", width);
	
	height = glutGet(GLUT_SCREEN_HEIGHT);
	printf("%f", height);
	
	srand (static_cast <unsigned> (time(0)));
	
	glutInitWindowSize(width, height);
	
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("assignment1");	//creates the window
	
	
	glClear(GL_COLOR_BUFFER_BIT);

	
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutMouseFunc(mouse);
	glutTimerFunc(17, timer, 0);

	init();
	
	printf("Commands: \n q: exit program \n z: make dots and lines bigger \n x: make dots and lines smaller \n A: random output \n R: clear screen \n w: create polygon\n +: move dots faster\n-: move dots slower\nP: pause\n1: mode 1\n2: mode 2 \n3: mode 3\n");
	
	glutFullScreen();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}

//references:
// don't know if this was nessacary for this code since it is one of the only ways to implement a rand() properally but here it is
//http://stackoverflow.com/questions/686353/c-random-float-number-generation

