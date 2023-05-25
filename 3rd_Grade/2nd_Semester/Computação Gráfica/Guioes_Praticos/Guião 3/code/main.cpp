#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>

float alpha = 0.0f, beta = 0.0f, radius = 5.0f;
float camX, camY, camZ;

void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alpha);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alpha);
}

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


void drawCylinder(float radius, float height, int slices) {
	// put code to draw cylinder in here

	float angle = 360.0 / slices;
	for(int i = 0;i < slices;i++){

		// base cima
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f,height/2,0.0f);
		glVertex3f(radius*sin(i * angle * M_PI / 180.0),height/2,radius * cos(i * angle * M_PI / 180.0));
		glVertex3f(radius*sin((i+1) * angle * M_PI / 180.0),height/2,radius * cos((i+1) * angle * M_PI / 180.0));
		glEnd();

		// base baixo
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f,-(height/2),0.0f);
		glVertex3f(radius*sin((i+1) * angle * M_PI / 180.0),-(height/2),radius * cos((i+1) * angle * M_PI / 180.0));
		glVertex3f(radius*sin(i * angle * M_PI / 180.0),-(height/2),radius * cos(i * angle * M_PI / 180.0));
		glEnd();

		//corpo
		glBegin(GL_TRIANGLES);
		glVertex3f(radius*sin((i+1) * angle * M_PI / 180.0),height/2,radius * cos((i+1) * angle * M_PI / 180.0));
		glVertex3f(radius*sin(i * angle * M_PI / 180.0),height/2,radius * cos(i * angle * M_PI / 180.0));
		glVertex3f(radius*sin(i * angle * M_PI / 180.0),-(height/2),radius * cos(i * angle * M_PI / 180.0));
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(radius*sin(i * angle * M_PI / 180.0),-(height/2),radius * cos(i * angle * M_PI / 180.0));
		glVertex3f(radius*sin((i+1) * angle * M_PI / 180.0),-(height/2),radius * cos((i+1) * angle * M_PI / 180.0));
		glVertex3f(radius*sin((i+1) * angle * M_PI / 180.0),height/2,radius * cos((i+1) * angle * M_PI / 180.0));
		glEnd();
	}
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
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	axisystem();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0f,1.0f,1.0f);
	drawCylinder(1,2,20);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key){
		case GLUT_KEY_UP:
			beta += 0.1;
			if(beta > 1.5) beta = 1.5;
			break;

		case GLUT_KEY_DOWN:
			beta -= 0.1;
			if(beta < -1.5) beta = -1.5;
			break;
		case GLUT_KEY_LEFT:
			alpha += 0.1;
			break;
		case GLUT_KEY_RIGHT:
			alpha -= 0.1;
			break;
		default:
			break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Page Up and Page Down control the distance from the camera to the origin");
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
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	spherical2Cartesian();
	printInfo();
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
