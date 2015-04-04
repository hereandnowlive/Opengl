#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include "particlelibrary.h"

using namespace std;



//stores pointers to instances of the particle class
vector<particle*> pararray;

//allows the creation of the cylinder
GLUquadric *quadric; 

//integer variables//

//controls the pause mode
int pause = 0;
//controls the speed multiplier
int speedadder = 0;
//the two angle controllers for the cannon
int ang1 = 60;
int ang2 = 30;

//controls the friction of the system on or off
int friction = 0;

//controls wind in the system on or off
int blow = 0;


float xaxis = 0;
float yaxis = 0;

float campos[] = {0,1,1};

particle s;
particle * inst;

//allows for the ablity to pop off the front of a vector
template<typename T>
void pop_front(vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}



/* drawAxis() -- draws an axis at the origin of the coordinate system
 *   red = +X axis, green = +Y axis, blue = +Z axis
 */
void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0,0,0);
	glVertex3f(50,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,50,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,50);
	glEnd();
	
}

/* display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
void display()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	//optionally draw the axis
	drawAxis();


	//draws a blue streched box
	glPushMatrix();
		
		glColor3f(0,0,1);
		
		glScalef(20,0.1,20);
		
		glutSolidCube(1.0f);
		//glRotatef(ang, 0,1,0);
		
	glPopMatrix();
	
	
	
		
	
	//creates cylinder with attached disk
		glPushMatrix();
		
		
			glColor3f(1,0,0);
			
			glTranslatef(-10,10,-10);
			
			glRotatef(ang1, 1, 0, 0);
			glRotatef(ang2, 0, 1, 0);
			quadric = gluNewQuadric();
			gluQuadricDrawStyle(quadric, GLU_FILL);
			gluQuadricOrientation(quadric, GLU_INSIDE);
			gluCylinder(quadric, 2.0f, 2.0f, 2.0f, 20, 20);
			
			
				glPushMatrix();
				glColor3f(0,1,0);
				gluDisk(quadric, 0.0f, 2.0f, 20, 1);
				gluDeleteQuadric(quadric);
				glPopMatrix();
				
		glPopMatrix();	
		
		
		
		//displays every particle currently on the vector and updates the position and rotation of said items of the vector		
			for (int i = 0; i < pararray.size(); i++){
			
				glPushMatrix();

					glColor3f(pararray.at(i)->r,pararray.at(i)->g,pararray.at(i)->b);
					
					glTranslatef(pararray.at(i)->px,pararray.at(i)->py,pararray.at(i)->pz);
					
					glRotatef(pararray.at(i)->rx,1,0,0);
					glRotatef(pararray.at(i)->ry,0,1,0);
					glRotatef(pararray.at(i)->rz,0,0,1);
					
					
					glutSolidCube(0.5f);
				
				glPopMatrix();
			
			
	}
	
	
	
	//swap buffers - rendering is done to the back buffer, bring it forward to display
	glutSwapBuffers();

	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}


void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			glRotatef(1, 0, 1, 0);
			break;

		case GLUT_KEY_RIGHT:
			glRotatef(-1, 0, 1, 0);
			break;

		case GLUT_KEY_UP:
			glRotatef(1, 1, 0, 0);
			break;

		case GLUT_KEY_DOWN:
			glRotatef(-1, 1, 0, 0);
			break;
		
	}
	glutPostRedisplay();
}

/* kbd -- the GLUT keyboard function 
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
	}
	
	//clears the vector and deletes all the information the pointers were pointing at
	if(key == 'r' || key == 'R')
	{
		for(int i = 0; i < pararray.size(); i=i+0){
			delete pararray.at(i);
			pararray.pop_back();
		}
	}
	
	//on off for friction
	if(key == 'f' || key == 'F')
	{
		if(friction == 0){
		friction = 1;
		}
		
		else{
		friction = 0;
		}
	}
	
	//on off for pause
	if(key ==32){
		if(pause == 0){
			pause = 1;
		}
		else{
		pause = 0;
		}
	}
	//w a s d are all controls for the cannon
	if(key == 'w' || key == 'W')
	{
		if(ang1 < 100){
			ang1 ++;
			yaxis -= 0.01;
		}
	}
	
	
		if(key == 's' || key == 'S')
	{
		if(ang1 > -100){
			ang1 --;
			yaxis += 0.01;
		}
	}
	
		if(key == 'a' || key == 'A')
	{
		if(ang2 < 100){
			ang2 ++;
			xaxis += 0.01;
		}	
	}
	
	
		if(key == 'd' || key == 'D')
	{
		if(ang2 > -100){
			ang2 --;
			xaxis -= 0.01;
		}	
	}
	//on off for the wind
	if(key == 'o' || key == 'O')
		{
			if (blow == 0){
				blow = 1;
			}
			else{
				blow = 0;
			}
		}
	
	//add speed
	if(key == '+')
		{
			if(speedadder < 4){
			speedadder++;
			}
			
		}
	//decrease speed
		if(key == '-')
		{
			if (speedadder > 0){
			
			speedadder--;
			}
		}
		
	
	
}

void timer(int value){


	//pause if enabled
	if(pause == 0){
		//create a new pointer to the particle class
		inst = new particle;
		//edit the speed, dy and dx to alter intial velocity and direction
		inst->speed += speedadder;
		inst->dx += xaxis;
		inst->dy += yaxis;
		
		//push the pointer on to the vector
		pararray.push_back(inst);
	
		for (int i = 0; i < pararray.size(); i++){
			
		//rotate each frame all axies by 1 and never rotate a axis past 360 degrees
			if(pararray.at(i)->rx < 360){
				pararray.at(i)->rx = pararray.at(i)->rx + 1;
			}
			if(pararray.at(i)->ry < 360){
				pararray.at(i)->ry = pararray.at(i)->ry + 1;
			}
			if(pararray.at(i)->rz < 360){
				pararray.at(i)->rz = pararray.at(i)->rz + 1;
			}
				
		//update position px and py of each particle by there related direction vector
				pararray.at(i)->px = pararray.at(i)->px + pararray.at(i)->dx*pararray.at(i)->speed;
				
				pararray.at(i)->pz = pararray.at(i)->pz + pararray.at(i)->dz*pararray.at(i)->speed;
		
			
		//update py by its direction vector but also update the direction vector of y to simulate gravity
				pararray.at(i)->py = pararray.at(i)->py + pararray.at(i)->dy;
				
				pararray.at(i)->dy = pararray.at(i)->dy - 0.1;
		
		//if wind is enabled add a update to the z axis direction vector 
				if(blow == 1){
					pararray.at(i)->dz = pararray.at(i)->dz - pararray.at(i)->wind;
				}
				
		//sets the boundaries for the hieght the particles should bounce at and where they should bounce 
					if(pararray.at(i)->py < 0.25 && pararray.at(i)->px < 10 && pararray.at(i)->pz < 10 && pararray.at(i)->pz > -10 && pararray.at(i)->px > -10){
						pararray.at(i)->dy = -pararray.at(i)->dy;
						if(friction == 1){
						pararray.at(i)->dy = pararray.at(i)->dy*0.9;
						}
					}

				
				
			//updates the age of the particle and if the particle is too old pop off the front since the oldest particle will always be the first instatiated on
			// the vector
				pararray.at(i)->age = pararray.at(i)->age - 0.05;
				
				if ( 0 >= pararray.at(i)->age){
					pop_front(pararray);
				}
		
		
		}
	}
	
	glutTimerFunc(30, timer, 0);
	glutPostRedisplay();

}



int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Spinning Cube");

	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_BACK);
	
	printf("\ncontrol instructions:\n left, right, up, and down keys: rotate camera\n q or Q: quit program\n r or R: reset particles\n f or F: add friction to the system\n spacebar: pause the system\n w,a,s,d: control the cannon\n o or O: adds wind to the system\n +: add speed to the particles\n -: remove speed from the particles\n\n system specifications: Windows operating system\n\n");
	
	
	
	
	
	//setup the initial view
	// change to projection matrix mode, set the extents of our viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);


	glMatrixMode(GL_MODELVIEW);
	//move away from the origin an rotate around it
	glTranslatef(0,0,-35);
	glRotatef(40, 1, 0, 0);
	glRotatef(10, 0, 1, 0);
	


	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	
	
	glutTimerFunc(8, timer, 0);
	//start the program
	glutMainLoop();

	return 0;
}



//The pop front code was taken from this site http://stackoverflow.com/questions/9445327/fast-way-to-implement-pop-front-to-a-stdvector