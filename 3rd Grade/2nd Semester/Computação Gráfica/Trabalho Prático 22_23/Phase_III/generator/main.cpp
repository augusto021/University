#include <iostream>
#include <cstring>
#include <ios>
#include <math.h>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <algorithm>
#include <vector>
#include <sstream>

enum shapes{
    sphere,
    plane,
    cone,
    box,
	cylinder,
	torus,
	bezier
};

typedef struct point {
	float x;
	float y;
	float z;
} Point;

std :: vector<std :: vector<int>> patches;
std :: vector<Point> controlPoints;


bool is_number(const char* string) {
  const int string_len = strlen(string);
  for(int i = 0; i < string_len; ++i) {
    if(!isdigit(string[i])) 
      return false;
  }
  return true;
}

int validate_args(int argc, char**argv){

    if(!argv[1] || !*argv[1]){
        return -1;
    }

    std::string shape = argv[1];

    if(shape == "sphere" 
        && is_number(argv[2]) 
        && is_number(argv[3]) 
        && is_number(argv[4])
        && argv[5] && *argv[5])
            return sphere;
    
    else if(shape == "plane"
        && is_number(argv[2])
        && is_number(argv[3])
        && argv[4] && *argv[4])
            return plane;
    
    else if(shape == "cone"
        && is_number(argv[2])
        && is_number(argv[3])
        && is_number(argv[4])
        && is_number(argv[5])
        && argv[6] && *argv[6])
            return cone;
    
    else if(shape == "box"
        && is_number(argv[2])
        && is_number(argv[3])
        && argv[4] && *argv[4])
            return box;

	else if(shape == "cylinder"
        && is_number(argv[2]) 
        && is_number(argv[3]) 
        && is_number(argv[4])
        && argv[5] && *argv[5])
            return cylinder;
	
	else if(shape == "torus"
        && is_number(argv[2]) 
        && is_number(argv[3]) 
        && is_number(argv[4])
		&& is_number(argv[5])
        && argv[6] && *argv[6])
            return torus;
	else if(shape == "patch"
        && argv[2] && *argv[2] 
        && is_number(argv[3])
        && argv[4] && *argv[4])
            return bezier;

    else
        return -1;
    
}


std :: string toString(Point p){
	std :: string s;
	s = std :: to_string(p.x)+" "+ std :: to_string(p.y)+" "+ std :: to_string(p.z);
	return s;
}

bool readBezierPatches(const std :: string filename){
	std :: ifstream file(filename);

	if (!file) {
        std :: cerr << "Error opening patch file!\n";
        return false;
    }
	std :: string line, number;
	int nr_patches, nr_ControlPoints;

	for(int i = 0;getline(file,line,'\n');i++){
		if(i == 0){
			nr_patches = std :: stoi(line);
		}

		else if(i <= nr_patches){
			std :: istringstream iss(line);
			std :: vector<int> patch;

			while(getline(iss,number,',')){
				patch.push_back(std :: stoi(number));
			}
			patches.push_back(patch);
		}

		else if(i > nr_patches + 1){
			Point p;
			p = {0};
			std :: istringstream iss(line);

			for(int j = 0;getline(iss,number,',');j++){
				if(j == 0)
					p.x = std :: stof(number);
				else if(j == 1)
					p.y = std :: stof(number);
				else if(j == 2)
					p.z = std :: stof(number);
			}
			controlPoints.push_back(p);
		}

	}
	file.close();
	return true;
}




void generate_sphere(char**args){
    float radius = atof(args[2]);
    float slices = atof(args[3]);
    float stacks = atof(args[4]);
    std::string filename = args[5];
	Point vertices[2][2];

    std :: ofstream sphereFile(filename);

	float alpha;
    float aStep = (2*M_PI)/slices;
    float beta;
    float bStep = M_PI/stacks;

    for (int j = -stacks/2; j < stacks/2;j++) {
		beta=(j*bStep);
        for (int i = 0; i < slices; i++) {
			alpha=(aStep*i);

           //P1
		    vertices[0][0].x = radius*cosf(beta)*sinf(alpha); 
			vertices[0][0].y = radius*sinf(beta); 
			vertices[0][0].z = radius*cosf(beta)*cosf(alpha);
           
		    //P2
		    vertices[0][1].x = radius*cosf(beta)*sinf(aStep*(i+1)); 
			vertices[0][1].y = vertices[0][0].y; 
			vertices[0][1].z = radius*cosf(beta)*cosf(aStep*(i+1));
           
		   	//P3
		    vertices[1][0].x = radius*cosf((j+1)*bStep)*sinf(aStep*(i+1)); 
			vertices[1][0].y = radius*sinf((j+1)*bStep); 
			vertices[1][0].z = radius*cosf((j+1)*bStep)*cosf(aStep*(i+1));
           
			//P4
		    vertices[1][1].x = radius*cosf((j+1)*bStep)*sinf(alpha); 
			vertices[1][1].y = vertices[1][0].y; 
			vertices[1][1].z = radius*cosf((j+1)*bStep)*cosf(alpha);

			//				 P1									P2							P3
            sphereFile << toString(vertices[0][0]) + " " + toString(vertices[0][1]) + " " + toString(vertices[1][0]) << std::endl;
			//				P3									P4							P1
            sphereFile << toString(vertices[1][0]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][0]) << std::endl;

        }
    }
    sphereFile.close();
	std :: cout << "Generator: " + filename + " written successfully!\n";
}



void generate_plane(char**args){
    float i,j;
	float length = atof(args[2]);
    float divisions = atof(args[3]);
	float slice = length/divisions;
    std::string filename = args[4];
	Point vertices[2][2];

    std :: ofstream planeFile(filename);

     
    for(i=-divisions/2; i*slice<length/2; i++){
        for(j=-divisions/2; j*slice<length/2; j++){

            //P1.
            vertices[0][0].x = j*slice;
            vertices[0][0].y = 0;
            vertices[0][0].z = i*slice;

            //P2.
            vertices[0][1].x = (j+1)*slice;
            vertices[0][1].y = 0;
            vertices[0][1].z = i*slice;

            //P3.
            vertices[1][0].x = (j+1)*slice;
            vertices[1][0].y = 0;
            vertices[1][0].z = (i+1)*slice;

            //P4.
            vertices[1][1].x = j*slice;
            vertices[1][1].y = 0;
            vertices[1][1].z = (i+1)*slice;

            //              P1.                                 P4.                                 P2.
            planeFile << toString(vertices[0][0]) << " " << toString(vertices[1][1]) << " " << toString(vertices[0][1]) << std::endl;
            //              P4.                                 P3.                                 P2.
            planeFile << toString(vertices[1][1]) << " " << toString(vertices[1][0]) << " " << toString(vertices[0][1]) << std::endl;
        }

    }

    planeFile.close();
	std :: cout << "Generator: " + filename + " written successfully!\n";

}

void generate_cone(char**args){	
	int i, j;
    float radius = atoi(args[2]);
    float height = atoi(args[3]);
    float slices = atoi(args[4]);
    float stacks = atoi(args[5]);
	float angle = 2 * M_PI  / slices;;
    std::string filename = args[6];
	Point vertices[2][2];

    std:: ofstream coneFile(filename);

	float stackHeight = height / stacks;

	for (float i = 0; i < stacks; i++) {
		float stackRadius = ((radius * (height - (stackHeight * i))) / height);
        float stackRadius2 = ((radius * (height - (stackHeight * (i + 1)))) / height);

		for (int c = 0; c < slices; c++) {
			float alpha = angle * c;
            float alpha2 = angle * (c + 1);
			
			vertices[0][0].x = cos(alpha) * stackRadius;
			vertices[0][0].y = stackHeight * i;
			vertices[0][0].z = -sin(alpha) * stackRadius;

			vertices[0][1].x = cos(alpha2) * stackRadius;
			vertices[0][1].y = stackHeight * i;
			vertices[0][1].z = -sin(alpha2) * stackRadius;

			vertices[1][0].x = cos(alpha) * stackRadius2;
			vertices[1][0].y = stackHeight * (i + 1);
			vertices[1][0].z = -sin(alpha) * stackRadius2;

			vertices[1][1].x = cos(alpha2) * stackRadius2;
			vertices[1][1].y = stackHeight * (i + 1);
			vertices[1][1].z = -sin(alpha2) * stackRadius2;

			
            if (i == 0) {
				coneFile << toString(vertices[1][0]) + " " + toString(vertices[0][0]) + " " + toString(vertices[0][1]) << std :: endl;
				coneFile << toString(vertices[1][0]) + " " + toString(vertices[0][1]) + " " + toString(vertices[1][1]) << std :: endl;
				// base
				Point p;
				p.x = 0.000000; p.y = 0.000000; p.z = 0.000000;
				coneFile << toString(p) + " " + toString(vertices[0][1]) + " " + toString(vertices[0][0]) << std :: endl;
            }
            else if (i != (stacks - 1)) {
				coneFile << toString(vertices[1][0]) + " " + toString(vertices[0][0]) + " " + toString(vertices[0][1]) << std :: endl;
				coneFile << toString(vertices[1][0]) + " " + toString(vertices[0][1]) + " " + toString(vertices[1][1]) << std :: endl;
            }
            else {
				coneFile << toString(vertices[1][0]) + " " + toString(vertices[0][0]) + " " + toString(vertices[0][1]) << std :: endl;
            }
		}
	}

    coneFile.close();
	std :: cout << "Generator: " + filename + " written successfully!\n";
}

void generate_box(char**args){
    float length = atof(args[2]);
    float grid = atof(args[3]);
	float slice = length/grid;
    std::string filename = args[4];
    Point vertices[2][2];

	std :: ofstream boxFile(filename);

	//Top side: reutilizamos a logica do plano, apenas mudamos o valor do y.
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//Pt1.
			vertices[0][0].x=j*slice;
			vertices[0][0].y=length/2;
			vertices[0][0].z=i*slice;
			
            //Pt2.
			vertices[0][1].x=(j+1)*slice;
			vertices[0][1].y=length/2;
			vertices[0][1].z=i*slice;
			
            //Pt3.
			vertices[1][0].x=(j+1)*slice;
			vertices[1][0].y=length/2;
			vertices[1][0].z=(i+1)*slice;
			
            //Pt4.
			vertices[1][1].x=j*slice;
			vertices[1][1].y=length/2;
			vertices[1][1].z=(i+1)*slice;

			//Escreve os pontos no ficheiro, respeitando a regra da mao direita. Cada linha e um triangle.
			boxFile << toString(vertices[0][0]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][1]) << std:: endl;
			boxFile << toString(vertices[1][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[0][1]) << std::endl;	
		}
	}

	//Bot Side: reutilizamos a logica do plano, mudamos o valor de y e escrevemos os pontos tendo em consideraçao que este lado apenas ´e visivel por baixo.
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//P1.
			vertices[0][0].x=j*slice;
			vertices[0][0].y=-length/2;
			vertices[0][0].z=i*slice;
			
            //P2.
			vertices[0][1].x=(j+1)*slice;
			vertices[0][1].y=-length/2;
			vertices[0][1].z=i*slice;
			
            //P3.
			vertices[1][0].x=(j+1)*slice;
			vertices[1][0].y=-length/2;
			vertices[1][0].z=(i+1)*slice;
			
            //P4.
			vertices[1][1].x=j*slice;
			vertices[1][1].y=-length/2;
			vertices[1][1].z=(i+1)*slice;

			//Escreve os pontos no ficheiro, respeitando a regra da mao direita. Cada linha e um triangle.
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][0]) << std::endl;
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[1][1]) << std::endl;	
		}
	}

	//Right side: logica do plano, mas tendo em consideraçao a orientaçao deste lado. o z comporta-se como o y do plano, etc.
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//P1.
			vertices[0][0].x=j*slice;
			vertices[0][0].y=i*slice;
			vertices[0][0].z=-length/2;
			
            //P2.
			vertices[0][1].x=(j+1)*slice;
			vertices[0][1].y=i*slice;
			vertices[0][1].z=-length/2;
			
            //P3.
			vertices[1][0].x=(j+1)*slice;
			vertices[1][0].y=(i+1)*slice;
			vertices[1][0].z=-length/2;
			
            //P4.
			vertices[1][1].x=j*slice;
			vertices[1][1].y=(i+1)*slice;
			vertices[1][1].z=-length/2;

			//Escreve os pontos no ficheiro, respeitando a regra da mao direita. Cada linha e um triangle.
			boxFile << toString(vertices[0][0]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][1]) << std::endl;
			boxFile << toString(vertices[1][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[0][1]) << std:: endl;	
		}
	}
	//Left side: logica do plano, mas tendo em consideraçao a orientaçao deste lado. o z comporta-se como o y do plano, etc.
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//P1.
			vertices[0][0].x=j*slice;
			vertices[0][0].y=i*slice;
			vertices[0][0].z=length/2;
			
            //P2.
			vertices[0][1].x=(j+1)*slice;
			vertices[0][1].y=i*slice;
			vertices[0][1].z=length/2;
			
            //P3.
			vertices[1][0].x=(j+1)*slice;
			vertices[1][0].y=(i+1)*slice;
			vertices[1][0].z=length/2;
			
            //P4.
			vertices[1][1].x=j*slice;
			vertices[1][1].y=(i+1)*slice;
			vertices[1][1].z=length/2;

			//Escreve os pontos tendo em consideraçao a prespectiva
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][0]) << std ::endl;
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[1][1]) << std:: endl;	
		}
	}
	//Front side: logica do plano, mas tendo em consideraçao a orientaçao deste lado. o x comporta-se como o y do plano, etc.
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//P1.
			vertices[0][0].x=length/2;
			vertices[0][0].y=j*slice;
			vertices[0][0].z=i*slice;
			
            //P2.
			vertices[0][1].x=length/2;
			vertices[0][1].y=(j+1)*slice;
			vertices[0][1].z=i*slice;
			
            //P3.
			vertices[1][0].x=length/2;
			vertices[1][0].y=(j+1)*slice;
			vertices[1][0].z=(i+1)*slice;
			
            //P4.
			vertices[1][1].x=length/2;
			vertices[1][1].y=j*slice;
			vertices[1][1].z=(i+1)*slice;

			//Escreve os pontos no ficheiro, respeitando a regra da mao direita. Cada linha e um triangle.
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][0]) << std::endl;
			boxFile << toString(vertices[0][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[1][1]) << std::endl;	
		}
	}
	//Back side: logica do plano, mas tendo em consideraçao a orientaçao deste lado. o x comporta-se como o y do plano, etc. 
	for(float i=-grid/2;i*slice<length/2;i++){
		for(float j=-grid/2;j*slice<length/2;j++){
			//P1.
			vertices[0][0].x=-length/2;
			vertices[0][0].y=j*slice;
			vertices[0][0].z=i*slice;
			
            //P2.
			vertices[0][1].x=-length/2;
			vertices[0][1].y=(j+1)*slice;
			vertices[0][1].z=i*slice;
			
            //P3.
			vertices[1][0].x=-length/2;
			vertices[1][0].y=(j+1)*slice;
			vertices[1][0].z=(i+1)*slice;
			
            //P4.
			vertices[1][1].x=-length/2;
			vertices[1][1].y=j*slice;
			vertices[1][1].z=(i+1)*slice;

			//Escreve os pontos tendo em consideraçao a prespectiva
			boxFile << toString(vertices[0][0]) + " " + toString(vertices[1][1]) + " " + toString(vertices[0][1]) <<std:: endl;
			boxFile << toString(vertices[1][1]) + " " + toString(vertices[1][0]) + " " + toString(vertices[0][1]) <<std:: endl;	
		}
	}


	boxFile.close();
	std :: cout << "Generator: " + filename + " written successfully!\n";
}

void generate_cylinder(char**args) {
	float radius = atof(args[2]);
    float heigth = atof(args[3]);
	float slices = atof(args[4]);
    std::string filename = args[5];

	Point p1,p2,p3;

	std :: ofstream cylinderFile(filename);

    float sectorStep = M_PI * 2 / slices;

    for (int i = 0; i <= slices; i++) {
        float alpha = i * sectorStep;
        float nextAlpha = sectorStep + alpha;

		p1.x = radius * sin(alpha); p1.y = heigth; p1.z =radius * cos(alpha);
		p2.x = radius * sin(nextAlpha); p2.y = heigth;p2.z = radius * cos(nextAlpha);

		p3.x = 0.0; p3.y = heigth; p3.z = 0.0;

		// base top
		cylinderFile << toString(p3) + " " + toString(p1) + " " + toString(p2) << std::endl;

		p3.y = 0.0;
		p2.y = 0.0;
		p1.y = 0.0;
		// base bot
		cylinderFile << toString(p3) + " " + toString(p1) + " " + toString(p2) << std::endl;

		p3.x = p1.x; p3.z = p1.z;
		p2.y = heigth;
		p1.y = heigth;
		// side1
		cylinderFile << toString(p3) + " " + toString(p2) + " " + toString(p1) << std::endl;

		p1.x = p2.x; p1.y = 0.0; p1.z = p2.z;
		// side2
		cylinderFile << toString(p3) + " " + toString(p1) + " " + toString(p2) << std::endl;
		
    }

    cylinderFile.close();
    std :: cout << "Generator: " + filename + " written successfully!\n";
}

void generate_torus(char**args){
	float in_radius = atof(args[2]);
    float out_radius = atof(args[3]);
	float slices = atof(args[4]);
	float stacks = atof(args[5]);
    std::string filename = args[6];

	std :: ofstream torusFile(filename);

    float R = ((out_radius - in_radius) / 2) + in_radius;
    float r = ((out_radius - in_radius) / 2);
    float teta = (M_PI * 2) / slices;
    float fi = (M_PI * 2) / stacks;
    Point p1, p2, p3, p4;

    for (float i = 0; i < slices; i++) {
        float tStep = i * teta;
        float next_tStep = tStep + teta;
        for (float j = 0; j < stacks; j++) {
            float fStep = j * fi;
            float next_fStep = fStep + fi;

            p1 = {R*cosf(tStep) + r * cosf(fStep) * cosf(tStep),
                  R*sinf(tStep) + r * cosf(fStep) * sinf(tStep),
                  r* sinf(fStep)};
            p2 = {R*cosf(next_tStep) + r * cosf(fStep) * cosf(next_tStep),
                  R*sinf(next_tStep) + r * cosf(fStep) * sinf(next_tStep),
                  r* sinf(fStep)};
            p3 = {R*cosf(next_tStep) + r * cosf(next_fStep) * cosf(next_tStep),
                  R*sinf(next_tStep) + r * cosf(next_fStep) * sinf(next_tStep),
                  r* sinf(next_fStep)};
            p4 = {R*cosf(tStep) + r * cosf(next_fStep) * cosf(tStep),
                  R*sinf(tStep) + r * cosf(next_fStep) * sinf(tStep),
                  r* sinf(next_fStep)};

			torusFile << toString(p1) + " " + toString(p2) + " " + toString(p3) << std::endl;
			torusFile << toString(p1) + " " + toString(p3) + " " + toString(p4) << std::endl;	

        }
    }
    torusFile.close();
    std :: cout << "Generator: " + filename + " written successfully!\n";
}

Point bezierCurve(float u, Point p0,Point p1,Point p2,Point p3){
	float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
    float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
    float b2 = 3 * u * u * (1.0 - u);
    float b3 = u * u * u;

    return Point{p0.x * b0 + p1.x * b1 + p2.x * b2 + p3.x * b3,
				 p0.y * b0 + p1.y * b1 + p2.y * b2 + p3.y * b3,
				 p0.z * b0 + p1.z * b1 + p2.z * b2 + p3.z * b3};
}

Point bezierPatch(float u, float v,std :: vector<int> patch){
	int j = 0, k = 0;

	Point pts_u[4];
    Point pts_v[4];

	for(int i = 0;i < 16;i++){
		Point aux = controlPoints[patch[i]];
		pts_u[j] = aux;
		j++;

		if(j == 4){
			pts_v[k++] = bezierCurve(u, pts_u[0], pts_u[1], pts_u[2], pts_u[3]);
			j = 0;
		}
	}
	Point res = bezierCurve(v, pts_v[0], pts_v[1], pts_v[2], pts_v[3]);
	return res;
}

void generate_bezier(char**args){
    std::string filename = args[4];
    std :: ofstream bezierFile(filename);

	if(!readBezierPatches(args[2])){
		std :: cerr << "Generator: Error opening file!\n";
		return ;
	}

	Point matrix[4][4] = {0};
	int tessellation = atoi(args[3]);
	float divisions = 1.0 / tessellation, u, u2, v, v2;

	for(int i = 0;i < patches.size();i++){
		std :: vector<int> patch = patches[i];
		for(int vs = 0;vs < tessellation;vs++){
			for(int us = 0;us < tessellation;us++){
				u = us * divisions;
				u2 = (us + 1) * divisions;
				v = vs * divisions;
				v2 = (vs + 1) * divisions;
				Point p1, p2, p3, p4;
				p1 = bezierPatch(u,v,patch);
				p2 = bezierPatch(u2,v,patch);
				p3 = bezierPatch(u,v2,patch);
				p4 = bezierPatch(u2,v2,patch);
				bezierFile << toString(p2) + " " + toString(p1) + " " + toString(p4) << std::endl;
				bezierFile << toString(p1) + " " + toString(p3) + " " + toString(p4) << std::endl;	
			}
		}

	}

    bezierFile.close();
	std :: cout << "Generator: " + filename + " written successfully!\n";
}


int main(int argc, char**argv) {
    switch (validate_args(argc, argv)){
    case sphere:
        generate_sphere(argv);
        break;

    case plane:
        generate_plane(argv);
        break;
    
    case cone:
        generate_cone(argv);
        break;
    
    case box:
        generate_box(argv);
        break;

	case cylinder:
        generate_cylinder(argv);
        break;

	case torus:
        generate_torus(argv);
        break;
	
	case bezier:
		generate_bezier(argv);
		break;
    
    default:
		std :: cerr << "Generator invalid input!\n";
        break;
    }
    return 0;
}
