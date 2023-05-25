#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float translate_x = 0.0f;
float translate_y = 0.0f;
float translate_z = 0.0f;

float rotate_x = 0.0f;
float rotate_y = 0.0f;
float rotate_z = 0.0f;

float scale_x = 1.0f;
float scale_y = 1.0f;
float scale_z = 1.0f;

float angle = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void axisystem(void){
	glBegin(GL_LINES);
	
	//red
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-100.0f,0.0f,0.0f);
	glVertex3f(100.0f,0.0f,0.0f);

	// green
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,-100.0f,0.0f);
	glVertex3f(0.0f,100.0f,0.0f);

	// blue
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,-100.0f);
	glVertex3f(0.0f,0.0f,100.0f);

	glEnd();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	
	axisystem();

	// put the geometric transformations here
	glTranslatef(translate_x,translate_y,translate_z);
	glScalef(scale_x,scale_y,scale_z);
	glRotatef(angle,rotate_x,rotate_y,rotate_z);

	// put drawing instructions here

	glBegin(GL_TRIANGLES);

		glColor3f(1.0f,0.0f,0.0f);
		// Front-left triangle
		glVertex3f(-1.0f,0.0f,1.0f);
		glVertex3f(1.0f,0.0,1.0f);
		glVertex3f(0.0f,2.0f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		// Front-right triangle
		glVertex3f(1.0f,0.0f,1.0f);
		glVertex3f(1.0f,0.0,-1.0f);
		glVertex3f(0.0f,2.0f,0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		// Back-left triangle
		glVertex3f(-1.0f,0.0f,1.0f);
		glVertex3f(0.0f,2.0f,0.0f);
		glVertex3f(-1.0f,0.0,-1.0f);

		glColor3f(1.0f,1.0f,1.0f);
		// Back-right triangle
		glVertex3f(-1.0f,0.0f,-1.0f);
		glVertex3f(0.0f,2.0f,0.0f);
		glVertex3f(1.0f,0.0,-1.0f);

		glColor3f(1.0f,0.5f,1.0f);
		// Base
		glVertex3f(-1.0f,0.0f,-1.0f);
		glVertex3f(1.0f,0.0f,1.0f);
		glVertex3f(-1.0f,0.0,1.0f);

		glVertex3f(1.0f,0.0f,-1.0f);
		glVertex3f(1.0f,0.0f,1.0f);
		glVertex3f(-1.0f,0.0,-1.0f);


	glEnd();
	glutPostRedisplay();

	// End of frame
	glutSwapBuffers();

}



// write function to process keyboard events
void press_buttons(int key,int x,int y){
	if(key == GLUT_KEY_UP){
		translate_y += 0.1;
	}
	if(key == GLUT_KEY_DOWN){
		translate_y -= 0.1;
	}
	if(key == GLUT_KEY_LEFT){
		translate_x -= 0.1;
	}
	if(key == GLUT_KEY_RIGHT){
		translate_x += 0.1;
	}

	if(key == GLUT_KEY_F1){
		scale_x += 0.2;
		scale_y += 0.2;
		scale_z += 0.2;
	}
	if(key == GLUT_KEY_F2){
		scale_x -= 0.2;
		scale_y -= 0.2;
		scale_z -= 0.2;
	}

	if(key == GLUT_KEY_F5){
		rotate_x = 1;
		rotate_y = 0;
		rotate_z = 0;
	}

	if(key == GLUT_KEY_F6){
		rotate_x = 0;
		rotate_y = 1;
		rotate_z = 0;
	}
	if(key == GLUT_KEY_F7){
		rotate_x = 0;
		rotate_y = 0;
		rotate_z = 1;
	}

	if(key == GLUT_KEY_F3){
		angle += 5;
	}
	if(key == GLUT_KEY_F4){
		angle -= 5;
	}

}





int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutSpecialFunc(press_buttons);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
