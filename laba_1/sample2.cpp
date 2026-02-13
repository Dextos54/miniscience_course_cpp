// -----------------------------------------------------------------------------
//
//  Gmsh C++ tutorial 13
//
//  Remeshing an STL file without an underlying CAD model
//
// -----------------------------------------------------------------------------

#include <set>
#include <cmath>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t13");

  // Let's merge an STL mesh that we would like to remesh (from the parent
  // directory):
  try {
    gmsh::merge("../Whale.stl");
  } catch(...) {
    gmsh::logger::write("Could not load STL mesh: bye!");
    gmsh::finalize();
    return 0;
  }

  

  gmsh::model::geo::synchronize();



  gmsh::model::mesh::generate(3);

  gmsh::write("t4.msh");

  // Launch the GUI to see the results:
  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();
  return 0;
}