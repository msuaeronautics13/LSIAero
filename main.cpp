#include <armadillo>
#include "LSIAero.h"

int main()
{
  std::cout << "Local Surface Inclination Aero Solver" << std::endl;
  // Read mesh //
  MeshStruct Mesh;
  ConfigStruct Config;
  DataStruct Data;

  Config.gamma = 1.4;
  Config.Tinf = 237.0;
  double R = 287.0;
  double a = sqrt( Config.gamma*R*Config.Tinf );

  double Vinf = 2017.0;
  double alpha = -5.0;
  Config.Vinf.resize(3);
  Config.Vinf(0) = Vinf*cos(alpha*M_PI/180.0);
  Config.Vinf(1) = Vinf*sin(alpha*M_PI/180.0);
  Config.Vinf(2) = 0.0;

  Config.Minf = Vinf/a;
  Config.meshfile = "double_wedge.lsi";
  ReadMesh(Mesh, Config);

  // Compute Modified Newtonian Method (Lees) //
  ModNewt(Mesh, Config, Data);

  OutputToVTK(Mesh, Config, Data);
}
