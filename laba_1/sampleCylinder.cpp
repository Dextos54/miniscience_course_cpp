
#include <set>

#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();
  gmsh::model::add("t1");

  double lc = 1e-2;
  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  gmsh::model::geo::addPoint(0, .1, 0, lc, 3);
  gmsh::model::geo::addPoint(0, -.1, 0, lc, 4);
  gmsh::model::geo::addPoint(-.1, 0, 0, lc, 5);

  gmsh::model::geo::addCircleArc(2, 1, 3, 1);
  gmsh::model::geo::addCircleArc(3, 1, 5, 2);
  gmsh::model::geo::addCircleArc(5, 1, 4, 3);
  gmsh::model::geo::addCircleArc(4, 1, 2, 4);


  gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
  gmsh::model::geo::addPlaneSurface({1}, 1);


    // As in `t2.cpp', we plan to perform an extrusion along the z axis.  But
    // here, instead of only extruding the geometry, we also want to extrude the
    // 2D mesh. This is done with the same `extrude()' function, but by
    // specifying element 'Layers' (2 layers in this case, the first one with 8
    // subdivisions and the second one with 2 subdivisions, both with a height
    // of h/2). The number of elements for each layer and the (end) height of
    // each layer are specified in two vectors:
    double h = 0.1;
    std::vector<std::pair<int, int> > ov;
    gmsh::model::geo::extrude({{2, 1}}, 0, 0, h, ov, {8, 2}, {0.5, 1});

  
  gmsh::model::geo::synchronize();


  gmsh::model::mesh::generate(3);

  gmsh::write("t1.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}