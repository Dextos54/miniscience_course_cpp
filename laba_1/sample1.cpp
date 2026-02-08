
#include <set>
#include <iostream>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();
  gmsh::model::add("t16");
  gmsh::option::setNumber("Mesh.MeshSizeFactor", 0.3);

  double lc = 1e-2;

  int outer = gmsh::model::occ::addTorus(0, 0, 0, 1.0, 0.6);
  int inner = gmsh::model::occ::addTorus(0, 0, 0, 1.0, 0.3);

  std::vector<std::pair<int, int> > ov;
  std::vector<std::vector<std::pair<int, int> > > ovv;
  gmsh::model::occ::cut({{3, outer}}, {{3, inner}}, ov, ovv, -1);



  gmsh::model::occ::synchronize();


  



  gmsh::model::mesh::generate(3);

  gmsh::write("t16.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}