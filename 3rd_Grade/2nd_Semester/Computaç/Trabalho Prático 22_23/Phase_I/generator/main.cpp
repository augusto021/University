#include <iostream>
#include <cstring>
#include <ios>
#include <math.h>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <algorithm>


enum shapes{
    sphere,
    plane,
    cone,
    box,
	cylinder
};

typedef struct point {
	float x;
	float y;
	float z;
} Point;


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

    else
        return -1;
    
}


std :: string toString(Point p){
	std :: string s;
	s = std :: to_string(p.x)+" "+ std :: to_string(p.y)+" "+ std :: to_string(p.z);
	return s;
}



void generate_sphere(char**args){
    float radius = atof(args[2]);
    float slices = atof(args[3]);
    float stacks = atof(args[4]);
    std::string filename = args[5];
	Point vertices[2][2];

	char tmp[256];
    getcwd(tmp, 256); //tmp which contains the directory
    std :: string path(tmp);
	int found = path.find("generator"); // finds generator's localization
	replace(path.begin(), path.end(), '\\', '/');
	path.erase(path.begin() + found, path.end());
    std :: string path3d = path + "Models/" + filename;

    std :: ofstream sphereFile(path3d);

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

	char tmp[256];
    getcwd(tmp, 256); //tmp which contains the directory
    std :: string path(tmp);
	int found = path.find("generator"); // finds generator's localization
	replace(path.begin(), path.end(), '\\', '/');
	path.erase(path.begin() + found, path.end());
    std :: string path3d = path + "Models/" + filename;

    std :: ofstream planeFile(path3d);


     
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

	char tmp[256];
    getcwd(tmp, 256); //tmp which contains the directory
    std :: string path(tmp);
	int found = path.find("generator"); // finds generator's localization
	replace(path.begin(), path.end(), '\\', '/');
	path.erase(path.begin() + found, path.end());
    std :: string path3d = path + "Models/" + filename;

    std:: ofstream coneFile(path3d);

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

	char tmp[256];
    getcwd(tmp, 256); //tmp which contains the directory
    std :: string path(tmp);
	int found = path.find("generator"); // finds generator's localization
	replace(path.begin(), path.end(), '\\', '/');
	path.erase(path.begin() + found, path.end());
    std :: string path3d = path + "Models/" + filename;

	std :: ofstream boxFile(path3d);

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

	char tmp[256];
    getcwd(tmp, 256); //tmp which contains the directory
    std :: string path(tmp);
	int found = path.find("generator"); // finds generator's localization
	replace(path.begin(), path.end(), '\\', '/');
	path.erase(path.begin() + found, path.end());
    std :: string path3d = path + "Models/" + filename;

	std :: ofstream cylinderFile(path3d);

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
    
    default:
		std :: cerr << "Generator invalid input!\n";
        break;
    }

    return 0;
}
