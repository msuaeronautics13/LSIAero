#ifndef LSIAERO_H
#define LSIAERO_H

#include <armadillo>

using namespace std;
using namespace arma;

typedef unsigned int UInt;

struct MeshStruct {
  mat coords;
  umat conn;
  mat normals;
  uvec coordid;
  UInt num_nodes;
  UInt num_elem;
};
struct ConfigStruct {
  string meshfile;
  vec Vinf;
  double Tinf;
  double Minf;
  double gamma;
};
struct DataStruct {
  vec Cp;
  mat Vsurf;
};


void ReadMesh(MeshStruct &mesh, ConfigStruct &config);

void ModNewt(MeshStruct &mesh, ConfigStruct &config, DataStruct &data);

void ComputeNormals(MeshStruct &mesh);

void OutputToVTK(MeshStruct &mesh, ConfigStruct &config, DataStruct &data);

extern "C" {
void nml_config(double *gamma, double *Tinf, double *R, double *Vinf, double *a);
}
#endif
