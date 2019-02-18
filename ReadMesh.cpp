#include "LSIAero.h"

typedef unsigned int UInt;

void ReadMesh(MeshStruct &mesh, ConfigStruct &config)
{
  FILE *fp;
  fp = fopen(config.meshfile.c_str(), "r");
  printf("Reading mesh file %s\n", config.meshfile.c_str());
  char buf[256];
  for (UInt iline=0; iline<4; iline++) {
    fgets(buf, 256, fp);
  }
  fscanf(fp, "%*s %u %*s", &mesh.num_nodes);

  mesh.coords.resize(mesh.num_nodes, 3);
  mesh.coordid.resize(mesh.num_nodes);
  
  for (UInt i=0; i<mesh.num_nodes; i++) {
    fscanf(fp, "%lf %lf %lf", &mesh.coords(i,0), 
	   &mesh.coords(i,1), &mesh.coords(i,2));
    mesh.coordid(i) = i;
  }

  fgets(buf, 256, fp);
  fscanf(fp, "%*s %u %*u", &mesh.num_elem);

  printf("Number of nodes=%u, Number of elements=%u\n",
	 mesh.num_nodes, mesh.num_elem);

  mesh.conn.resize(mesh.num_elem, 4);

  for (UInt i=0; i<mesh.num_elem; i++) {
    fscanf(fp, "%*u %u %u %u %u",
	   &mesh.conn(i,0), &mesh.conn(i,1), &mesh.conn(i,2), &mesh.conn(i,3));
  }

  /*umat tmp_conn(mesh.conn);
  // Make node numbering contigious //
  for (UInt i=0; i<mesh.num_nodes; i++) {
    UInt test = mesh.coordid(i);
    for (UInt j=0; j<mesh.num_elem; j++) {
      if (tmp_conn(j,0) == test) mesh.conn(j,0) = i+1;
      if (tmp_conn(j,1) == test) mesh.conn(j,1) = i+1;
      if (tmp_conn(j,2) == test) mesh.conn(j,2) = i+1;
    }
  }
*/


  fclose(fp);
  printf("Mesh import successful!\n");
}
