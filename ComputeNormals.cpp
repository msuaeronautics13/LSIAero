#include "LSIAero.h"

void ComputeNormals(MeshStruct &mesh)
{

  printf("Computing surface normals...\n");
  vec u(3);
  vec v(3);
  vec product(3);
  mat normals(mesh.num_elem,3);

  for (UInt i=0; i<mesh.num_elem; i++) {
    u(0) = mesh.coords(mesh.conn(i,2),0) - mesh.coords(mesh.conn(i,1),0);
    u(1) = mesh.coords(mesh.conn(i,2),1) - mesh.coords(mesh.conn(i,1),1);
    u(2) = mesh.coords(mesh.conn(i,2),2) - mesh.coords(mesh.conn(i,1),2);

    v(0) = mesh.coords(mesh.conn(i,0),0) - mesh.coords(mesh.conn(i,1),0);
    v(1) = mesh.coords(mesh.conn(i,0),1) - mesh.coords(mesh.conn(i,1),1);
    v(2) = mesh.coords(mesh.conn(i,0),2) - mesh.coords(mesh.conn(i,1),2);

    product(0) = u(1)*v(2) - u(2)*v(1);
    product(1) = u(2)*v(0) - u(0)*v(2);
    product(2) = u(0)*v(1) - u(1)*v(0);

    float len = sqrt(product(0)*product(0) + product(1)*product(1) + product(2)*product(2));

    normals(i,0) = product(0)/len;
    normals(i,1) = product(1)/len;
    normals(i,2) = product(2)/len;
  }

  double sumnormx,sumnormy,sumnormz,shared;
  for (UInt i=0; i<mesh.num_nodes; i++) {
    for (UInt j=0; j<mesh.num_elem; j++) {
      if ((mesh.conn(j,0) == i) || (mesh.conn(j,1) == i) || (mesh.conn(j,2) == i) ||
	  (mesh.conn(j,3) == i)) {
	sumnormx += normals(j,0);
	sumnormy += normals(j,1);
	sumnormz += normals(j,2);
	shared++;
      }
    }
    mesh.normals.resize(mesh.num_nodes,3);
    if (shared == 0) {
      mesh.normals(i,0) = sumnormx/((double)1e-6);
      mesh.normals(i,1) = sumnormy/((double)1e-6);
      mesh.normals(i,2) = sumnormz/((double)1e-6);
    } else {
      mesh.normals(i,0) = sumnormx/((double)shared);
      mesh.normals(i,1) = sumnormy/((double)shared);
      mesh.normals(i,2) = sumnormz/((double)shared);
    }
    shared = 0;
    sumnormx = 0;
    sumnormy = 0;
    sumnormz = 0;
 //   std::cout << mesh.normals(i,0) << " " << mesh.normals(i,1) << " " << mesh.normals(i,2) << std::endl;
  }
}
