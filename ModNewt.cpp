#include "LSIAero.h"
typedef unsigned int UInt;

void ModNewt(MeshStruct &mesh, ConfigStruct &config, DataStruct &data)
{

  double gm = config.gamma;
  double gp1 = gm + 1.0;
  double gm1 = gm - 1.0;
  double gp1sq = gp1*gp1;
  double Minfsq = config.Minf*config.Minf;
  
  printf("Calculating surface pressure from Modified Newtonian Theory...\n");
  
  // Compute surface normals //
  ComputeNormals(mesh);
  printf("Calculating Cpmax...\n");

  // Compute Cp (eq. 3.15) //

  double Cpmax = 
   (2.0/(gm*Minfsq))*(pow((gp1sq*Minfsq)/(4.0*gm*Minfsq - 2.0*gm1), 
			  gm/gm1)*((1-gm+2*gm*Minfsq)/gp1) - 1.0);
  
  printf("Calculating Cp and Vsurf...\n");
  
  data.Cp.resize(mesh.num_nodes);
  data.Vsurf.resize(mesh.num_nodes,3);
  // Dot Vinf vector with normals vector for each node //  
  for (UInt i=0; i<mesh.num_nodes; i++) {
    double sintheta = dot(normalise(config.Vinf),mesh.normals.row(i));
    data.Cp(i) = Cpmax*pow(sintheta,2.0);
    data.Vsurf.row(i) = cross(cross(mesh.normals.row(i), config.Vinf.t()),mesh.normals.row(i));
  }
}

