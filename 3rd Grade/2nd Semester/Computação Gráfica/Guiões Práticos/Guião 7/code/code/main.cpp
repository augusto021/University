

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


float camX = 00, camY = 30, camZ = 40;
float lookX = 0, lookY = 0, lookZ = 0;
float upX = 0, upY = 1, upZ = 0;
float angle = 0;

int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

float eye_height = 1.5;

unsigned int t;
int tw, th;
unsigned char * imageData;

GLuint* vertices;
double vertexCount;

int ri = 35;
int rc = 15;

bool terrain_status = false;

std::vector<std::pair<float, float>> trees;

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

float hf(float x,float z);

void drawTerrain() {

    glColor3ub(36,154,39);
	for(int strip = 0;strip < th - 1;strip++){
		glBindBuffer(GL_ARRAY_BUFFER, vertices[strip]);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
	}

	// Grid
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	// Inner teapots
	glColor3ub(0,0,255);
	for(int i = 0;i < 8;i++){
		glPushMatrix();
		glRotatef(45 * i,0,1,0);
		glTranslatef(rc,1,0);
		glutSolidTeapot(2);
		
		glPopMatrix();
	}

	// Outer teapots
	glColor3ub(255,0,0);
	for(int i = 0;i < 16;i++){
		glPushMatrix();
		glRotatef(22.5 * i,0,1,0);
		glTranslatef(ri,1,0);
		glutSolidTeapot(2);
		
		glPopMatrix();
	}

	// Torus
	glColor3ub(255,0,255);
	glutSolidTorus(1,3,10,10);

	// Trees
	for(unsigned int i = 0;i < trees.size();i++){
		glPushMatrix();

		std::pair<float, float> poss = trees.at(i);
		float posx = poss.first, posz = poss.second;
		float posy = hf(posx + tw / 2, posz + th / 2);

		glTranslatef(posx, posy, posz);
		glRotatef(-90, 1, 0, 0);
		glColor3ub(102,62,36);
		glutSolidCone(0.5, 2, 10, 10);
		glTranslatef(0, 0, 2);
		glColor3ub(0,255,0);
		glutSolidCone(2, 4, 10, 10);

		glPopMatrix();
	}
}


void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      lookX, lookY, lookZ,
			  upX, upY, upZ);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	drawTerrain();

	// just so that it renders something before the terrain is built
	// to erase when the terrain is ready
	//glutWireTeapot(2.0);

// End of frame
	glutSwapBuffers();
}

// Go to terrain
void processKeys(unsigned char key, int i, int j){
    switch(key){
        // Press 't' to set player on terrain
        case 't':
            if(terrain_status == false){
                terrain_status = true;
				camX = 0;
				camY = hf(0,0) + eye_height;
				camZ = 0;

				lookX = camX + sin(angle);
				lookY = camY;
				lookZ = camZ + cos(angle);
			}
            glutPostRedisplay();
            break;
		// Look left
		case 'a':
		    angle -= M_PI /30;
			lookX = camX + sin(angle);
			lookY = camY;
			lookZ = camZ + cos(angle);
			glutPostRedisplay();
			break;
		// Look right
		case 'd':
			angle += M_PI /30;
			lookX = camX + sin(angle);
			lookY = camY;
			lookZ = camZ + cos(angle);
			glutPostRedisplay();
			break;
    }
}


void processSpecialKeys(int key, int xx, int yy) {
	float dX,dZ;
	switch (key){
		// case GLUT_KEY_LEFT:
		// 	break;
		// case GLUT_KEY_RIGHT:
		// 	break;

		
		case GLUT_KEY_UP:
			dX = lookX - camX;
			dZ = lookZ - camZ;

			camX = camX + 2 * dX;
			camZ = camZ + 2 * dZ;
			camY = hf(camX, camZ) + eye_height;

			lookX = lookX + 2 * dX;
			lookY = camY;
			lookZ = lookZ + 2 * dZ;
			break;
		case GLUT_KEY_DOWN:
			dX = lookX - camX;
			dZ = lookZ - camZ;

			camX = camX - 2 * dX;
			camZ = camZ - 2 * dZ;
			camY = hf(camX, camZ) + eye_height;

			lookX = lookX - 2 * dX;
			lookY = camY;
			lookZ = lookZ - 2 * dZ;
			break;
	}

}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}

float h(int i, int j) {
	float x = imageData[i * tw + j];
	return x / 255 * 30;
}

float hf(float x,float z){
	float x1 = floor(x);
	float z1 = floor(z);

	float x2 = x1 + 1;
	float z2 = z1 + 1;

	float fx = x - x1;
	float fz = z - z1;

	float h_x1_z = h(x1,z1) * (1-fz) + h(x1,z2) * fz;
	float h_x2_z = h(x2,z1) * (1-fz) + h(x2,z2) * fz;

	return h_x1_z * (1 - fx) + h_x2_z * fx;
}

void init() {

	// 	Load the height map "terreno.jpg"
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)"terreno.jpg");
	ilConvertImage(IL_LUMINANCE,IL_UNSIGNED_BYTE);

	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);

	imageData = ilGetData();

	// 	Build the vertex arrays
	vertices = (GLuint*)calloc(th-1, sizeof(GLuint));
	glGenBuffers(th-1, vertices);

	int halfW = tw / 2;
	int halfH = th / 2;

	vertexCount = 2 * tw;

	for(int n_strip = 0;n_strip < th - 1;n_strip++){
		std :: vector <float> strip;

		for(int j = 0;j < tw;j++){
			strip.push_back(n_strip - halfH);
			strip.push_back(h(n_strip, j));
			strip.push_back(j - halfW);

			strip.push_back(n_strip + 1 - halfH);
			strip.push_back(h(n_strip + 1, j));
			strip.push_back(j - halfW);

		}

		glBindBuffer(GL_ARRAY_BUFFER, vertices[n_strip]);
    	glBufferData(GL_ARRAY_BUFFER, strip.size() * sizeof(float), strip.data(), GL_STATIC_DRAW);

	}

	for(int tree = 0;tree < 300;tree++){
		float posx = 0, posz = 0;
		while(pow(posx,2) + pow(posz,2) < pow(r,2)){
			posx = (rand() % (r * 4)) - (r * 2);
			posz = (rand() % (r * 4)) - (r * 2);
		}
		trees.push_back(std :: make_pair(posx,posz));
	}

	// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		

// Required callback registry 
	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	glewInit();
	glEnableClientState(GL_VERTEX_ARRAY);

	ilInit();

	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

