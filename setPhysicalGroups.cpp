#include <cmath>
#include <gmsh.h>
#include <iostream>
#include <fstream>

/* Author : Md Shahrier Hasan, UCLA
 * GMSH script to creat physical group in polycrystal external and grain boundaries
 */

const long double ztol = 1E-15;
double xmax, xmin, ymax, ymin, zmax, zmin;
double sxmax, sxmin, symax, symin, szmax, szmin;
gmsh::vectorpair all_surf_dimtags; 
std::vector<int> right_tags, left_tags, top_tags, bottom_tags, front_tags, back_tags, gb_tags;


int main(int argc, char** argv){
if (argc < 2)
{   std::cout << "file not specified";
    return 1;
}
gmsh::initialize();
gmsh::open( argv[1]);
//Get dimtags of all surfaces
gmsh::model::getEntities( all_surf_dimtags, 2);
//Get the global dimension of bounding box
gmsh::model::getBoundingBox(-1, -1, xmin, ymin, zmin, xmax, ymax, zmax);
//separate out dimtags of outer and granin boundary surfaces 
for (const auto& surf_dimtag : all_surf_dimtags){
    gmsh::model::getBoundingBox( surf_dimtag.first, surf_dimtag.second, sxmin, symin, szmin, sxmax, symax, szmax);
    if ((fabs(sxmax - sxmin) < ztol) and (fabs(sxmax - xmax) < ztol))
	right_tags.push_back(surf_dimtag.second); 
    else if ((fabs(sxmax - sxmin) < ztol) and (fabs(sxmin - xmin) < ztol))
	left_tags.push_back(surf_dimtag.second); 
    else if ((fabs(szmax - szmin) < ztol) and (fabs(szmax - zmax) < ztol))
	front_tags.push_back(surf_dimtag.second); 
    else if ((fabs(szmax - szmin) < ztol) and (fabs(szmin - zmin) < ztol))
	back_tags.push_back(surf_dimtag.second); 
    else if ((fabs(symax - symin) < ztol) and (fabs(symax - ymax) < ztol))
	top_tags.push_back(surf_dimtag.second); 
    else if ((fabs(symax - symin) < ztol) and (fabs(symin - ymin) < ztol))
	bottom_tags.push_back(surf_dimtag.second); 
    else
	gb_tags.push_back(surf_dimtag.second); 
	}
const unsigned int right_pg_tag = gmsh::model::addPhysicalGroup( 2, right_tags, -1, "right");
const unsigned int left_pg_tag = gmsh::model::addPhysicalGroup( 2, left_tags, -1, "left");
const unsigned int frong_pg_tag = gmsh::model::addPhysicalGroup( 2, front_tags, -1, "front");
const unsigned int back_pg_tag = gmsh::model::addPhysicalGroup( 2, back_tags, -1, "back");
const unsigned int top_pg_tag = gmsh::model::addPhysicalGroup( 2, top_tags, -1, "top");
const unsigned int bottom_pg_tag = gmsh::model::addPhysicalGroup( 2, bottom_tags, -1, "bottom");
const unsigned int gb_pg_tag = gmsh::model::addPhysicalGroup( 2, gb_tags, -1, "grain_boundary");
gmsh::model::geo::synchronize();
gmsh::model::geo::removeAllDuplicates();
std::cout << "Physical Groups Added" << std::endl;
gmsh::write("output_file.geo_unrolled");

std::ofstream outfile("output_file.geo_unrolled", std::ios::app);

if (outfile.is_open()) {
        // File opened successfully
    } else {
        std::cerr << "Unable to open file for appending." << std::endl;
    }
outfile << "Coherence;" << std::endl;
outfile.close();

return 0;
}

