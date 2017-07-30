#pragma once

namespace PhyMAP
{
namespace Common
{
class RigidBody;
class Mesh;
}

namespace Net
{

using namespace Common;
using namespace System;
using namespace System::Collections::Generic;

public ref class RigidBodyWrapper
{
public:
  RigidBodyWrapper(void);
  virtual ~RigidBodyWrapper(void);
  !RigidBodyWrapper(void);

  bool setMeshes(List<Rhino::Geometry::Mesh^>^ _meshes);
  //bool setTransform(Rhino::Geometry::Transform^ _transform);

  List<Rhino::Geometry::Mesh^>^ meshes_;

internal:
  Mesh* getMesh();
  RigidBody* rigid_body_;
};

}//namespace Net
}//namespace PhyMAP
