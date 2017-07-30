#include "TriSurfaceMesh.h"

namespace PhyMAP
{
namespace Common
{

TriSurfaceMesh::TriSurfaceMesh() : Mesh()
{}

TriSurfaceMesh::~TriSurfaceMesh()
{
  faces_.clear();
  verticies_.clear();
}


}//namespace Common
}//namespace PhyMAP
