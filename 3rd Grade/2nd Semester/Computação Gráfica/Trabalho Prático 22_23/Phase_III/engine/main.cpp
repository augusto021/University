#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h> 
#include <algorithm>
#include <math.h>
#include <string>  

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
using namespace tinyxml2;

//--------------------------------- - - - - - - - - - -  -  -  -  -   -
// Declarações iniciais

// Enumerator que representa as transformações geométricas das figuras.
enum transformation{
    translate,
    rotate,
    scale
};


// Variáveis globais

// Indica o path dos ficheiros mencionados nos ficheiros xml.
std :: string path = "../";

// Permite atualizar a posição de visão do observador.
float alpha;
float beta;
float radius;

// Indica o estado dos eixos, se estão visíveis ou não.
bool axes_state = false;

// Indica o estado das curvas para serem visíveis.
bool curves = true;

// Variáveis para a construção do VBO.
GLuint vertices;
std :: vector<float> vertexVBO;

// Variáveis para calcular fps.
int frame=0, time_=0, timebase=0;

// Structures (Struct)

// Representação de um ponto num espaço tridemensional.
struct Point {
    float x;
    float y;
    float z;
};

// Representação de um triângulo a partir de três pontos.
struct Triangle {
    Point p1;
    Point p2;
    Point p3;
};

// Representação de transformações geométricas com dados relativos para as mesmas.
struct Transform{
    float time;
    bool align;
    float angle;
    transformation type;
    std :: vector<Point> points;
};

/* Representação de um Group, do ficheiro xml, com as transformações geométricas que são aplicadas,
triângulos necessários para a construção da figura e subgrupos que possa conter. */
struct Group{
    std :: vector<Transform> transformations;
    std :: vector<Group> subGroups;
    std :: vector<std :: pair<int,int>> vboIndexes;
};

// Representação dos parâmetros da câmara necessários para as funções do GLUT.
struct CameraParameters {
    Point position;
    Point lookAt;
    Point up;
    float fov;
    float near;
    float far;
};

// Estrutura que guarda toda a informação pertinente para a representação do problema
struct WorldInfo {
    int width;
    int height;
    CameraParameters camera;
    std :: vector<Group> groups;
};



// Representação do modelo.
WorldInfo world;

//--------------------------------- - - - - - - - - - -  -  -  -  -   -


//--------------------------------- - - - - - - - - - -  -  -  -  -   -
// Funções auxiliares e de leitura de ficheiros

void calcFPS(){
    char s[100];

    frame++;
    time_ = glutGet(GLUT_ELAPSED_TIME);

    if (time_ - timebase > 1000) {
        sprintf(s,"Engine: FPS:%4.2f", frame*1000.0/(time_ - timebase));
        timebase = time_;
        frame = 0;
        glutSetWindowTitle(s);
    }
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

    std::cout << "Width: " << world.width << std::endl;
    std::cout << "Height: " << world.height << std::endl;

	printf("\nUse Arrows to move the camera up/down and left/right");
    printf("\nPress the letter 'a' to turn on/off the axes\n");
}

int validate_transformation(XMLElement* elem){
    if(!strcmp(elem->Name(),"translate")) return translate;
    else if(!strcmp(elem->Name(),"rotate")) return rotate;
    else if(!strcmp(elem->Name(),"scale")) return scale;
    else return -1;
}

std :: vector <Triangle> readTrianglesFromFile(const std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file " << filename << std::endl;
    }
    std :: vector<Triangle> res;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Point p1, p2, p3;
        iss >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z >> p3.x >> p3.y >> p3.z;
        res.push_back({p1,p2,p3});
    }
    file.close();
    return res;
}

//--------------------------------- - - - - - - - - - -  -  -  -  -   -

//--------------------------------- - - - - - - - - - -  -  -  -  -   -
// Catmull-Rom Cubic Curve

void buildRotMatrix(float *x, float *y, float *z, float *m) {
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

float length(float *v) {
	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;
}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    float matrix[4] = {t*t*t, t*t, t, 1};
    float matrixDeriv[4] = {3*t*t, 2*t, 1, 0};

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};

    float P[3][4] = {{p0[0], p1[0], p2[0], p3[0]},
                     {p0[1], p1[1], p2[1], p3[1]},
                     {p0[2], p1[2], p2[2], p3[2]}};
    float A[3][4];
			
	// Compute A = M * P
    for(int i = 0;i < 4;i++){
        multMatrixVector(&m[0][0],P[i],A[i]);
    }

	// Compute pos = T * A
    for(int i = 0;i< 3;i++){
        pos[i] = A[i][0] * matrix[0] + A[i][1] * matrix[1] + A[i][2] * matrix[2] + A[i][3] * matrix[3];
    }
	
	// compute deriv = T' * A
    for(int i = 0;i< 3;i++){
        deriv[i] = A[i][0] * matrixDeriv[0] + A[i][1] * matrixDeriv[1] + A[i][2] * matrixDeriv[2] + A[i][3] * matrixDeriv[3];
    }
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,std :: vector<Point> points) {

    int pointCount = points.size();
	float t = gt * pointCount;
	int index = floor(t); 
	t = t - index; 

	// indices store the points
	int indices[4]; 
	indices[0] = (index + pointCount-1)% pointCount;	
	indices[1] = (indices[0]+1)% pointCount;
	indices[2] = (indices[1]+1)% pointCount; 
	indices[3] = (indices[2]+1)% pointCount;

    float p0[3] = {points[indices[0]].x, points[indices[0]].y, points[indices[0]].z};
    float p1[3] = {points[indices[1]].x, points[indices[1]].y, points[indices[1]].z};
    float p2[3] = {points[indices[2]].x, points[indices[2]].y, points[indices[2]].z};
    float p3[3] = {points[indices[3]].x, points[indices[3]].y, points[indices[3]].z};

	getCatmullRomPoint(t,p0, p1, p2, p3, pos, deriv);
}

void renderCatmullRomCurve(std :: vector<Point> points) {
    // draw curve using line segments with GL_LINE_LOOP
    float t;
    float dir[3], pos[3];
    glBegin(GL_LINE_LOOP);
    for(t = 0.0 ; t < 1.0 ; t += 0.001){
        getGlobalCatmullRomPoint(t,pos,dir, points);
        glVertex3f(pos[0],pos[1],pos[2]);
    }
    glEnd();
}

//--------------------------------- - - - - - - - - - -  -  -  -  -   -


//--------------------------------- - - - - - - - - - -  -  -  -  -   -
// Funções Parse

Point parsePoint(XMLElement* element) {
    return {
        element->FloatAttribute("x"),
        element->FloatAttribute("y"),
        element->FloatAttribute("z")
    };
}

CameraParameters parseCameraParameters(XMLElement* element) {
    CameraParameters camera;
    camera.position = parsePoint(element->FirstChildElement("position"));
    camera.lookAt = parsePoint(element->FirstChildElement("lookAt"));
    camera.up = parsePoint(element->FirstChildElement("up"));
    camera.fov = element->FirstChildElement("projection")->FloatAttribute("fov");
    camera.near = element->FirstChildElement("projection")->FloatAttribute("near");
    camera.far =element->FirstChildElement("projection")->FloatAttribute("far");
    radius = sqrt(pow(camera.position.x, 2) + pow(camera.position.y, 2) + pow(camera.position.z, 2));
    beta = asin(camera.position.y / radius);
    alpha = asin(camera.position.x/ sqrt(pow(camera.position.z, 2) + pow(camera.position.x, 2)));
    return camera;
}


int indexVBO = 0;
Group parseGroups(XMLElement* group,bool flag){
    Group g;

    for(;group != nullptr;group = group->NextSiblingElement()){
        for(XMLElement *elem = group->FirstChildElement();
            elem != nullptr;
            elem = elem->NextSiblingElement()){
            if (!strcmp(elem->Name(), "transform")){
                for (XMLElement *transformElement = elem->FirstChildElement();
                     transformElement != nullptr;
                     transformElement = transformElement->NextSiblingElement()){
                    
                    float time;
                    Point p;
                    std :: vector<Point> points;
                    points.clear();
                    Transform t;

                    switch(validate_transformation(transformElement)){
                        case translate:

                            if(transformElement->Attribute("x") != nullptr && transformElement->Attribute("y") != nullptr &&
                                transformElement->Attribute("z") != nullptr){
                                p.x = transformElement->FloatAttribute("x");
                                p.y = transformElement->FloatAttribute("y");
                                p.z = transformElement->FloatAttribute("z");
                                points.push_back(p);
                                t = {-1,0,0,translate,points};
                                g.transformations.push_back(t);
                            } else{
                                time = -1;
                                bool align = false;
                                if(transformElement->Attribute("time") != nullptr){
                                    time = transformElement->FloatAttribute("time");
                                    if(transformElement->Attribute("align","true")) align = true;

                                    XMLElement *element = transformElement->FirstChildElement();

                                    while (element != nullptr) {
                                    if (!strcmp("point", element->Name())) {
                                        float x = element->FloatAttribute("x");
                                        float y = element->FloatAttribute("y");
                                        float z = element->FloatAttribute("z");

                                        Point p = {x,y,z};
                                        points.push_back(p);
                                    }
                                    element = element->NextSiblingElement();
                                    }   
                                }
                                Transform t = {time,align,0,translate,points};
                                g.transformations.push_back(t);
                            }
                            break;
                        case rotate:
                            float angle;
                            time = -1;
                            
                            if(transformElement->Attribute("angle") != nullptr){
                                angle = transformElement->FloatAttribute("angle");
                            } else{
                                time = transformElement->FloatAttribute("time");
                            }

                            angle = transformElement->FloatAttribute("angle");
                            p.x = transformElement->FloatAttribute("x");
                            p.y = transformElement->FloatAttribute("y");
                            p.z = transformElement->FloatAttribute("z");

                            points.push_back(p);
                            t = {time,0,angle,rotate,points};
                            g.transformations.push_back(t);

                            break;
                        case scale:
                            p.x = transformElement->FloatAttribute("x");
                            p.y = transformElement->FloatAttribute("y");
                            p.z = transformElement->FloatAttribute("z");

                            points.push_back(p);
                            t = {-1,0,0,scale,points};
                            g.transformations.push_back(t);

                            break;
                        default:
                            std :: cerr << "Transformation not valid!\n";
                            break;
                    }
                }
            }

            else if (!strcmp(elem->Name(), "models")){
                for (XMLElement *modelsElement = elem->FirstChildElement("model");
                     modelsElement != nullptr;
                     modelsElement = modelsElement->NextSiblingElement("model")){

                    std :: vector<Triangle> triangles = readTrianglesFromFile(path + modelsElement->Attribute("file"));
                    g.vboIndexes.emplace_back(indexVBO,triangles.size()*3);
                    indexVBO += triangles.size()*3;
                    for (Triangle t : triangles){
                        Point p1 = t.p1;
                        Point p2 = t.p2;
                        Point p3 = t.p3;
                        vertexVBO.push_back(p1.x);
                        vertexVBO.push_back(p1.y);
                        vertexVBO.push_back(p1.z);
                        vertexVBO.push_back(p2.x);
                        vertexVBO.push_back(p2.y);
                        vertexVBO.push_back(p2.z);
                        vertexVBO.push_back(p3.x);
                        vertexVBO.push_back(p3.y);
                        vertexVBO.push_back(p3.z);
                    }
                }
            }

            else if(!strcmp(elem->Name(),"group")){
                Group gr = parseGroups(elem,true);
                g.subGroups.push_back(gr);
            }

            else
                std :: cerr << "Node not valid!\n";
            
            if(elem->NextSiblingElement() == nullptr && flag) return g;
            }
            if(!flag) world.groups.push_back(g);
    }

    return g;
}

void parseWorldInfo(XMLElement* element) {
    world.width = element->FirstChildElement("window")->IntAttribute("width");
    world.height = element->FirstChildElement("window")->IntAttribute("height");
    world.camera = parseCameraParameters(element->FirstChildElement("camera"));
    parseGroups(element->FirstChildElement("group"),false);
}

//--------------------------------- - - - - - - - - - -  -  -  -  -   -


//--------------------------------- - - - - - - - - - -  -  -  -  -   -
// Funções GLUT e de representação de figuras

void animateTranslate(Transform t){
    float yBefore[3] = { 0,1,0 };
    float turnCount = 0;

    float pos[3], deriv[3], Z[3], m[16];

    if(curves) renderCatmullRomCurve(t.points);

    float elapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float actualTime = elapsedTime - t.time * turnCount;

    if(actualTime > t.time){
        turnCount++;
        actualTime = elapsedTime - t.time*turnCount;
    }

    float gt = actualTime/t.time;

    getGlobalCatmullRomPoint(gt, pos, deriv, t.points);

    if(t.align){
        normalize(deriv);

        // Z = X x Yi-1
        cross(deriv, yBefore, Z);
        normalize(Z);

        // Yi = Z x X
        float newY[3] {0,0,0};
        cross(Z, deriv, newY);
        normalize(newY);

        buildRotMatrix(deriv, newY, Z, m);

        glTranslatef(pos[0], pos[1], pos[2]);
        glMultMatrixf(m);
    }else
        glTranslatef(pos[0], pos[1], pos[2]);

}

void animateRotate(Transform t){
    float elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float angle = 360/(t.time * 1000);

    glRotatef(elapsedTime * angle, t.points[0].x, t.points[0].y, t.points[0].z);
}

void axisystem(void){
	glBegin(GL_LINES);
	
	//red
	glColor3f(1.5f,0.0f,0.0f);
	glVertex3f(-100.0f,0.0f,0.0f);
	glVertex3f(100.0f,0.0f,0.0f);

	// green
	glColor3f(0.0f,1.5f,0.0f);
	glVertex3f(0.0f,-100.0f,0.0f);
	glVertex3f(0.0f,100.0f,0.0f);

	// blue
	glColor3f(0.0f,0.0f,1.5f);
	glVertex3f(0.0f,0.0f,-100.0f);
	glVertex3f(0.0f,0.0f,100.0f);

	glEnd();
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
	gluPerspective(world.camera.fov ,ratio, world.camera.near ,world.camera.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawGroup(std :: vector<Group> groups){
    for(Group g : groups){
        glPushMatrix();

        for(int i = 0;i < g.transformations.size();i++){
            Transform t = g.transformations[i];
            if(t.type == translate){
                if (t.time!=-1) animateTranslate(t);
                else glTranslatef(t.points[0].x,t.points[0].y,t.points[0].z);
            } 
            else if(t.type == rotate){
                if(t.time!=-1) animateRotate(t);
                else glRotatef(t.angle,t.points[0].x,t.points[0].y,t.points[0].z);
            }
            else if(t.type == scale) glScalef(t.points[0].x,t.points[0].y,t.points[0].z);
        }
        for (std :: pair<int,int> t : g.vboIndexes) {
            glBindBuffer(GL_ARRAY_BUFFER, vertices);
            glVertexPointer(3, GL_FLOAT, 0, 0);
            glDrawArrays(GL_TRIANGLES, t.first, t.second);
        }
        drawGroup(g.subGroups);
        glPopMatrix();
    }
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(world.camera.position.x,world.camera.position.y,world.camera.position.z, 
		      world.camera.lookAt.x,world.camera.lookAt.y,world.camera.lookAt.z,
			  world.camera.up.x,world.camera.up.y,world.camera.up.z);

    
    // Axis
    if(axes_state) axisystem();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0f,1.0f,1.0f);
    drawGroup(world.groups);

    // End of frame
    calcFPS();
	
	// End of frame
	glutSwapBuffers();
}


// Draw axes with keyboard
void processKeys(unsigned char key, int i, int j){
    switch(key){
        // Press 'a' to set ON and OFF the axes
        case 'a':
            if(axes_state)
                axes_state = false;
            else axes_state = true;
            glutPostRedisplay();
            break;
    }
}


//Move camera with keyboard
void processSpecialKeys(int key, int xx, int yy) {
    
    switch(key){
        case GLUT_KEY_LEFT:
            alpha -= M_PI/30;
            break;

        case GLUT_KEY_RIGHT:
            alpha += M_PI/30;
            break;

        case GLUT_KEY_UP:
            beta += M_PI/30;

            if(beta >= M_PI/2) {
                beta = M_PI/2 - 0.001;
            }

            break;

        case GLUT_KEY_DOWN:
            beta -= M_PI/30;
            
            if(beta <= -M_PI/2) {
                beta = -M_PI/2 + 0.001;
            }

            break;
    }
    world.camera.position.x = radius * cos(beta) * sin(alpha);
    world.camera.position.y = radius * sin(beta);
    world.camera.position.z = radius * cos(beta) * cos(alpha);
    glutPostRedisplay();
}

void initVBO(std :: vector<Group> groups){
    glGenBuffers(1,&vertices);
    glBindBuffer(GL_ARRAY_BUFFER,vertices);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*vertexVBO.size(),vertexVBO.data(),GL_STATIC_DRAW);
}

void initGlut(int argc,char* argv[]){
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(world.width,world.height);
    glutCreateWindow("Engine");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    printInfo();

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initVBO(world.groups);

    // enter GLUT's main cycle
    glutMainLoop();
    time_ = glutGet(GLUT_ELAPSED_TIME);
}

//--------------------------------- - - - - - - - - - -  -  -  -  -   -



int main(int argc, char**argv) {
    XMLDocument doc;
    if (doc.LoadFile(argv[1]) != XML_SUCCESS) {
        std::cerr << "Error loading file " << argv[1] << std::endl;
        return 1;
    }

    XMLElement* worldElement = doc.FirstChildElement("world");
    if (!worldElement) {
        std::cerr << "Invalid file format" << std::endl;
        return 1;
    }

    parseWorldInfo(worldElement);

    initGlut(argc,argv);
    return 0;
}
