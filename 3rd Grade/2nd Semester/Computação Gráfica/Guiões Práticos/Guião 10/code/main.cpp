#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>

#define _PI_ 3.14159

float alfa = sqrt(75), beta = M_PI_4, radius = M_PI_4;
//float camX, camY, camZ;

GLuint buffers[2];
std :: vector<float> vertexB;
std :: vector<float> normalB;
int verticeCount;

int timebase = 0, frame = 0;

float camX = sqrt(75), camY = M_PI_4, camZ = M_PI_4;
int slices = 50;

// float polarX(Polar polar) { return polar.radius * cos(polar.beta) * sin(polar.alpha); }
// float polarY(Polar polar) { return polar.radius * sin(polar.beta); }
// float polarZ(float radius,float alpha,float beta) { return polar.radius * cos(polar.beta) * cos(polar.alpha); }


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void genCylinder(float radius, float height, unsigned int slices) {
    vertexB.clear();
    normalB.clear();

	float hh = height / 2;
	float sliceStep = M_PI * 2 / slices;

	float baseRadius = hh, baseAlpha = 0, baseBeta = - M_PI / 2;
	float topRadius = hh, topAlpha = 0, topBeta = M_PI / 2;


	// BASE
	for(unsigned int slice = slices; slice > 0; slice--) {
		float pRadius = sqrt(pow(hh, 2) + pow(radius,2)), pAlpha = sliceStep * slice, pBeta = - atan(hh / radius);
		float ppRadius = sqrt(pow(hh, 2) + pow(radius,2)), ppAlpha = sliceStep * (slice + 1), ppBeta = - atan(hh / radius);

        vertexB.push_back(baseRadius * cos(baseBeta) * sin(baseAlpha));
        vertexB.push_back(baseRadius * sin(baseBeta));
        vertexB.push_back(baseRadius * cos(baseBeta) * cos(baseAlpha));

        normalB.push_back(0);normalB.push_back(-1);normalB.push_back(1);

        vertexB.push_back(ppRadius * cos(ppBeta) * sin(ppAlpha));
        vertexB.push_back(ppRadius * sin(ppBeta));
		vertexB.push_back(ppRadius * cos(ppBeta) * cos(ppAlpha));

        normalB.push_back(0);normalB.push_back(-1);normalB.push_back(1);

        vertexB.push_back(pRadius * cos(pBeta) * sin(pAlpha));
		vertexB.push_back(pRadius * sin(pBeta));
		vertexB.push_back(pRadius * cos(pBeta) * cos(pAlpha));

        normalB.push_back(0);normalB.push_back(-1);normalB.push_back(1);
	}

	// TOP
	//glVertex3d(polarX(topP), polarY(topP), polarZ(topP));
	for(unsigned int slice = 0; slice < slices; slice++) {
		float pRadius = sqrt(pow(hh, 2) + pow(radius,2)), pAlpha = sliceStep * slice, pBeta = atan(hh / radius);
		float ppRadius = sqrt(pow(hh, 2) + pow(radius,2)), ppAlpha = sliceStep * (slice + 1), ppBeta = atan(hh / radius);

		vertexB.push_back(topRadius * cos(topBeta) * sin(topAlpha));
		vertexB.push_back(topRadius * sin(topBeta));
		vertexB.push_back(topRadius * cos(topBeta) * cos(topAlpha));

        normalB.push_back(0);normalB.push_back(1);normalB.push_back(1);

        vertexB.push_back(pRadius * cos(pBeta) * sin(pAlpha));
		vertexB.push_back(pRadius * sin(pBeta));
		vertexB.push_back(pRadius * cos(pBeta) * cos(pAlpha));
        
        normalB.push_back(0);normalB.push_back(1);normalB.push_back(1);

        vertexB.push_back(ppRadius * cos(ppBeta) * sin(ppAlpha));
		vertexB.push_back(ppRadius * sin(ppBeta));
		vertexB.push_back(ppRadius * cos(ppBeta) * cos(ppAlpha));

        normalB.push_back(0);normalB.push_back(1);normalB.push_back(1);
	}

	// SIDE
	for(unsigned int slice = 0; slice < slices; slice++) {
		float pbRadius = sqrt(pow(hh, 2) + pow(radius,2)), pbAlpha = sliceStep * slice, pbBeta = -atan(hh / radius);
		float ptRadius = sqrt(pow(hh, 2) + pow(radius,2)), ptAlpha = sliceStep * slice , ptBeta = atan(hh / radius);

		float ppbRadius = sqrt(pow(hh, 2) + pow(radius,2)), ppbAlpha = sliceStep * (slice + 1), ppbBeta = -atan(hh / radius);
		float pptRadius = sqrt(pow(hh, 2) + pow(radius,2)), pptAlpha = sliceStep * (slice + 1), pptBeta = atan(hh / radius);

		vertexB.push_back(ptRadius * cos(ptBeta) * sin(ptAlpha));
		vertexB.push_back(ptRadius * sin(ptBeta));
		vertexB.push_back(ptRadius * cos(ptBeta) * cos(ptAlpha));

        normalB.push_back(sin(ptAlpha));normalB.push_back(0);normalB.push_back(cos(ptAlpha));

		vertexB.push_back(pbRadius * cos(pbBeta) * sin(pbAlpha));
		vertexB.push_back(pbRadius * sin(pbBeta));
		vertexB.push_back(pbRadius * cos(pbBeta) * cos(pbAlpha));

        normalB.push_back(sin(pbAlpha));normalB.push_back(0);normalB.push_back(cos(pbAlpha));

		vertexB.push_back(ppbRadius * cos(ppbBeta) * sin(ppbAlpha));
		vertexB.push_back(ppbRadius * sin(ppbBeta));
		vertexB.push_back(ppbRadius * cos(ppbBeta) * cos(ppbAlpha));


        normalB.push_back(sin(ppbAlpha));normalB.push_back(0);normalB.push_back(cos(ppbAlpha));

		vertexB.push_back(ppbRadius * cos(ppbBeta) * sin(ppbAlpha));
		vertexB.push_back(ppbRadius * sin(ppbBeta));
		vertexB.push_back(ppbRadius * cos(ppbBeta) * cos(ppbAlpha));

        normalB.push_back(sin(ppbAlpha));normalB.push_back(0);normalB.push_back(cos(ppbAlpha));

		vertexB.push_back(pptRadius * cos(pptBeta) * sin(pptAlpha));
		vertexB.push_back(pptRadius * sin(pptBeta));
		vertexB.push_back(pptRadius * cos(pptBeta) * cos(pptAlpha));

        normalB.push_back(sin(pptAlpha));normalB.push_back(0);normalB.push_back(cos(pptAlpha));

		vertexB.push_back(ptRadius * cos(ptBeta) * sin(ptAlpha));
		vertexB.push_back(ptRadius * sin(ptBeta));
		vertexB.push_back(ptRadius * cos(ptBeta) * cos(ptAlpha));

        normalB.push_back(sin(ptAlpha));normalB.push_back(0);normalB.push_back(cos(ptAlpha));
	}

    verticeCount = vertexB.size() / 3;

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexB.size() * sizeof(float), vertexB.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, normalB.size() * sizeof(float), normalB.data(), GL_STATIC_DRAW);
}

void renderScene(void) {

	float fps;
	int time;
	char s[64];

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(camX * cos(camZ) * sin(camY), camX * sin(camZ), camX * cos(camZ) * cos(camY), 
		      0.0,0.0,0.0,
			  0.0f,camZ > M_PI_2 ? -1.0f : 1.0f,0.0f);

	float pos[4] = {3.0,3.0,3.0,0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    float dark[4] = {0.2,0.2,0.2,1.0};
    float white[4] = {0.8,0.8,0.8,1.0};
    float red[4] = {0.8,0.2,0.2,1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glNormalPointer(GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, verticeCount);


	frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0; 
		sprintf(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	} 

// End of frame
	glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch(key) {
		case 'a':
			camY -= M_PI / 16;
			break;
		case 'd':
			camY += M_PI / 16;
			break;
		case 's':
			camZ -= M_PI / 16;
			break;
		case 'w':
			camZ += M_PI / 16;
			break;
        case '+':
            slices *= 2;
            genCylinder(1, 2, slices);
            printf("slices = %d\n", slices);
            break;
        case '-':
            slices /= 2;
            genCylinder(1, 2, slices);
            printf("slices = %d\n", slices);
            break;
	}
	if (camY< 0) camY += M_PI * 2;
	else if (camY > M_PI * 2) camY -= M_PI * 2;
    if (camZ < - M_PI_2) camZ += M_PI * 2;
    else if (camZ > (3 * M_PI_2)) camZ -= M_PI * 2;
	glutPostRedisplay();
}

int oldx = 0, oldy = 0;
bool firstMouse = true;

void mouseFunc(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN)
            firstMouse = true;
    }
}

void motionFunc(int x, int y) {
    if(firstMouse) {
        oldx = x;
        oldy = y;
        firstMouse = false;
        return;
    }
    int deltax = x - oldx;
    int deltay = oldy - y;

    camY += 2 * M_PI * deltax * 0.1 / 360;
    camZ -= 2 * M_PI * deltay * 0.1 / 360;

    if (camZ < - M_PI_2) camZ += M_PI * 2;
    else if (camZ > (3 * M_PI_2)) camZ -= M_PI * 2;

    oldx = x;
    oldy = y;

    glutPostRedisplay();
}




void processKeys(int key, int xx, int yy) 
{
	switch(key) {
	
		case GLUT_KEY_RIGHT: 
						alfa += M_PI / 16; break;

		case GLUT_KEY_LEFT: 
						alfa -= M_PI / 16; break;

		case GLUT_KEY_UP : 
						beta +=  M_PI / 16; break;

		case GLUT_KEY_DOWN: 
						beta -= M_PI / 16; break;

		case GLUT_KEY_PAGE_DOWN : radius -= 0.1f; 
			if (radius < 0.1f)
				radius = 0.1f;
			break;

		case GLUT_KEY_PAGE_UP: radius += 0.1f; break;

	}
	//sphericalToCartesian();

}



void initGL() {

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	GLfloat dark[4] = {0.2,0.2,0.2,1.0};
    GLfloat white[4] = {1.0,1.0,1.0,1.0};

	// light colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);


	// init
	//sphericalToCartesian();

}


int main(int argc, char **argv) {

// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// callback registration
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardFunc);
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);

// keyboard callback registration
	glutSpecialFunc(processKeys);

#ifndef __APPLE__	
// init GLEW
	glewInit();
#endif	

	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

	glGenBuffers(2, buffers);
	genCylinder(1,2,slices);

	initGL();

	glutMainLoop();
	
	return 1;
}

