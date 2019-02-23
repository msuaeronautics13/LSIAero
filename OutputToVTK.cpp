#include "LSIAero.h"
typedef unsigned int UInt;

void OutputToVTK(MeshStruct &mesh, ConfigStruct &config, DataStruct &data)
{
  FILE *fp;
  fp = fopen("result.vtk", "w");
  fprintf(fp, "# vtk DataFile Version 3.0\n");
  fprintf(fp, "vtk output\n");
  fprintf(fp, "ASCII\n");
  fprintf(fp, "DATASET UNSTRUCTURED_GRID\n");
  fprintf(fp, "POINTS %u float\n", mesh.num_nodes);
  for (UInt i=0; i<mesh.num_nodes; i++) {
   fprintf(fp, "%lf %lf %lf\n", mesh.coords(i,0), mesh.coords(i,1), mesh.coords(i,2));
  }
  fprintf(fp, "\n"); 
  fprintf(fp, "CELLS %u %u\n", mesh.num_elem, mesh.num_elem*5);
  for (UInt i=0; i<mesh.num_elem; i++) {
    fprintf(fp, "4 %u %u %u %u\n", mesh.conn(i,0), mesh.conn(i,1), mesh.conn(i,2), mesh.conn(i,3));
  }
  fprintf(fp, "\n");
  fprintf(fp, "CELL_TYPES %u\n", mesh.num_elem);
  for (UInt i=0; i<mesh.num_elem; i++) {
   fprintf(fp, "%u\n", 9);
  }
  fprintf(fp, "POINT_DATA %u\n", mesh.num_nodes); 
  fprintf(fp, "SCALARS Cp float 1\n");
  fprintf(fp, "LOOKUP_TABLE default\n");
  for (UInt i=0; i<mesh.num_nodes; i++) {
    fprintf(fp, "%lf\n", data.Cp(i));
  }
  fprintf(fp, "VECTORS Vsurf float\n");
  for (UInt i=0; i<mesh.num_nodes; i++) {
    fprintf(fp, "%lf %lf %lf\n", data.Vsurf(i,0), data.Vsurf(i,1), data.Vsurf(i,2));
  }
  fclose(fp);
}
