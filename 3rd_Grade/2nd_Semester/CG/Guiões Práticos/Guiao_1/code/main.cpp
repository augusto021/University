#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <chrono>

auto begin = std::chrono::high_resolution_clock::now();

void axisystem(void);

void changeSize(int w, int h){
	// prevent a divide by zero, when window is too short
	// (you can not make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;

	// set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// et the viewport to be the entire window
	glViewport(0, 0, w, h);
}


void renderScene(void){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(2.0f, 1.0f, 5.0f, // onde a cãmara está
		0.0f, 0.0f, -1.0f, // onde a câmara está a olhar, a direção
		0.0f, 1.0f, 0.0f);
		
	// put drawing instructions here
	axisystem();

	glColor3f(1.0f,1.0f,1.0f);

	auto end = std::chrono::high_resolution_clock::now();
	float elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;

	glutWireTeapot(abs(sinf(elapsed)));
	
	// End of frame
	glutSwapBuffers();
}

void axisystem(void){
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glBegin(GL_LINES);

	glColor3f( 1, 0, 0 ); // red
	glVertex3f(0,0,0);
	glVertex3f(3,0,0);

	glColor3f( 0, 1, 0 ); // green
	glVertex3f(0,0,0);
	glVertex3f(0,3,0);

	glColor3f( 0, 0, 1 ); // blue
	glVertex3f(0,0,0);
	glVertex3f( 0, 0,3);

	glEnd();
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv){
	// put GLUT init here
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");

	// put callback registry here
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUTs main cycle
	glutMainLoop();
	
	return 1;
}