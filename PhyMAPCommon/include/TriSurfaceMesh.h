#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include "Mesh.h"

#include <vector>

namespace PhyMAP
{
namespace Common
{

struct TriSurfaceMeshFace
{
  int vertex_indicies_[3];
};


class TriSurfaceMesh : public Mesh
{
public:
  TriSurfaceMesh(void);
  virtual ~TriSurfaceMesh(void);

//  long getTriangleCount();

  virtual int getVertexCount(void) { return (int)verticies_.size(); }
  virtual int getFaceCount(void) { return (int)faces_.size(); }

//  void setDerivedOrientation(const Quaternion& _qt);
//  void setDerivedPosition(const Vector& _pos);

  std::vector<Vector> verticies_;
  std::vector<TriSurfaceMeshFace> faces_;

  Vector min_vec_;
  Vector max_vec_;
};

}//namespace Bullet
}//namespace PhyMAP
