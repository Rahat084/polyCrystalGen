#include <iostream>
#include <fstream>
#include "voro++.hh"
#include "vorogmsh.h"
using namespace voro;

/*
Example taken from the Voro++ documentation:
http://math.lbl.gov/voro++/examples/radical/
*/

// Set up constants for the container geometry
double x_min, x_max, y_min, y_max, z_min, z_max;
int n_x, n_y, n_z;
char parameters[256];
//const double y_min=-3,y_max=3;
//const double z_min=0,z_max=6;


 // Set up the number of blocks that the container is divided into.
//const int n_x=3,n_y=3,n_z=3;

int main() {
	std::ifstream infile("../input/geometry.txt");
	std::cout << "Reading parameter values" << std::endl;
	infile.getline( parameters, 256);
	std::cout << parameters << std::endl;
	infile >> x_min >> x_max >> y_min >> y_max >> z_min >> z_max >> n_x >> n_y >> n_z;
	std::cout << "   " << x_min << "     " << x_max  << "      "<< y_min << "      " << y_max << "      " << z_min << "      " << z_max << "      " << n_x << "    " << n_y << "    " << n_z <<std::endl;

	voro::container_poly conp(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,false,false,false,8);
        conp.import("../input/pack_six_cube_poly");
        vorogmsh gmsh(conp);
        gmsh.saveasgeo("pack_six_cube_poly.geo");
        gmsh.saveasgeo("pack_six_cube_poly_01.geo",0.1);
}
