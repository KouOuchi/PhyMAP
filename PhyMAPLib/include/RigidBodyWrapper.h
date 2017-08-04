#pragma once

#include "MechanicalPropertyWrapper.h"
#include "MotionPropertyWrapper.h"

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
  RigidBodyWrapper(RigidBody* _rigid_body);
  virtual ~RigidBodyWrapper(void);
  !RigidBodyWrapper(void);

  bool setMeshes(List<Rhino::Geometry::Mesh^>^ _meshes);
  bool setMechanicalProperty(MechanicalPropertyWrapper^ _mechanical_property);
  bool setMotionProperty(MotionPropertyWrapper^ _motion_property);

  List<Rhino::Geometry::Mesh^>^ meshes_;

internal:
  Mesh* getMesh();
  RigidBody* rigid_body_;
};

public ref class StaticRigidBodyWrapper : RigidBodyWrapper
{
public:
  StaticRigidBodyWrapper(void);
  virtual ~StaticRigidBodyWrapper(void);
  !StaticRigidBodyWrapper(void);
};
}//namespace Net
}//namespace PhyMAP
