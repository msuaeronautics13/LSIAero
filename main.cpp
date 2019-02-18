#include <armadillo>
#include "LSIAero.h"

int main()
{
  std::cout << "Local Surface Inclination Aero Solver" << std::endl;
  // Read mesh //
  MeshStruct Mesh;
  ConfigStruct Config;
  DataStruct Data;

  double R, Vinf, alpha, gamma;
  nml_config(&Config.gamma, &Config.Tinf, &R, &Vinf, &alpha);
  
  double a = sqrt( Config.gamma*R*Config.Tinf );

  Config.Vinf.resize(3);
  Config.Vinf(0) = Vinf*cos(alpha*M_PI/180.0);
  Config.Vinf(1) = Vinf*sin(alpha*M_PI/180.0);
  Config.Vinf(2) = 0.0;

  Config.Minf = Vinf/a;
  Config.meshfile = "orion_quad.vtk";

  ReadMesh(Mesh, Config);

  // Compute Modified Newtonian Method (Lees) //
  ModNewt(Mesh, Config, Data);

  OutputToVTK(Mesh, Config, Data);
}
