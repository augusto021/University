#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h> 
#include <algorithm>
#include <math.h>

#include <GL/glut.h>
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
std :: string pathModels;

// Permite atualizar a posição de visão do observador.
float alpha;
float beta;
float radius;

// Indica o estado dos eixos, se estão visíveis ou não.
bool axes_state = false;



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
    float x;
    float y;
    float z;
    float angle;
    transformation type;
};

/* Representação de um Group, do ficheiro xml, com as transformações geométricas que são aplicadas,
triângulos necessários para a construção da figura e subgrupos que possa conter. */
struct Group{
    std :: vector<Transform> transformations;
    std :: vector<Triangle> triangles;
    std :: vector<Group> subGroups;
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
                    
                    float x, y, z;
                    Transform t;

                    switch (validate_transformation(transformElement)){
                    case translate:
                        x = transformElement->FloatAttribute("x");
                        y = transformElement->FloatAttribute("y");
                        z = transformElement->FloatAttribute("z");

                        t = {x,y,z,0,translate};
                        g.transformations.push_back(t);
                        
                        break;
                    case rotate:
                        float angle;
                        angle = transformElement->FloatAttribute("angle");
                        x = transformElement->FloatAttribute("x");
                        y = transformElement->FloatAttribute("y");
                        z = transformElement->FloatAttribute("z");

                        t = {x,y,z,angle,rotate};
                        g.transformations.push_back(t);

                        break;
                    case scale:
                        x = transformElement->FloatAttribute("x");
                        y = transformElement->FloatAttribute("y");
                        z = transformElement->FloatAttribute("z");

                        t = {x,y,z,0,scale};
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
                        std :: vector<Triangle> tri = readTrianglesFromFile(pathModels + modelsElement->Attribute("file"));
                        g.triangles.insert(g.triangles.end(),tri.begin(),tri.end());
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

void drawPrimitives(std :: vector<Triangle> triangles){
    glBegin(GL_TRIANGLES);
    for(Triangle t : triangles){
        glVertex3f(t.p1.x, t.p1.y, t.p1.z);
        glVertex3f(t.p2.x, t.p2.y, t.p2.z);
        glVertex3f(t.p3.x, t.p3.y, t.p3.z);
    }
    glEnd();
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
            if(t.type == translate) glTranslatef(t.x,t.y,t.z);
            else if(t.type == rotate) glRotatef(t.angle,t.x,t.y,t.z);
            else if(t.type == scale) glScalef(t.x,t.y,t.z);
        }
        drawGroup(g.subGroups);
        drawPrimitives(g.triangles);
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
    
    if(axes_state) axisystem();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0f,1.0f,1.0f);
    drawGroup(world.groups);
	
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

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();
    
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

    char tmp[2048];
    getcwd(tmp, 2048); //tmp which contains the directory
    std :: string path(tmp);
    int found = path.find("engine"); // finds engine's localization

    replace(path.begin(), path.end(), '\\', '/');
    path.erase(path.begin() + found, path.end());

    pathModels = path + "Models/";

    parseWorldInfo(worldElement);

    initGlut(argc,argv);
    return 0;
}
