#include "RigidBodyWrapper.h"
#include "Translator.h"

#include <RigidBody.h>

namespace PhyMAP
{

using namespace Common;

namespace Net
{

RigidBodyWrapper::RigidBodyWrapper()
  : rigid_body_(new RigidBody()), meshes_(nullptr)
{
}

RigidBodyWrapper::RigidBodyWrapper(RigidBody* _rigid_body)
  : rigid_body_(_rigid_body), meshes_(nullptr)
{
}

RigidBodyWrapper::~RigidBodyWrapper()
{
  this->!RigidBodyWrapper();
}

RigidBodyWrapper::!RigidBodyWrapper()
{
  if (rigid_body_)
  {
    delete rigid_body_;
    rigid_body_ = nullptr;
  }
}

Mesh* RigidBodyWrapper::getMesh()
{
  return rigid_body_->getMesh();
}

bool RigidBodyWrapper::setMeshes(List<Rhino::Geometry::Mesh^>^ _meshes)
{
  meshes_ = _meshes;

  TriSurfaceMesh* trimesh = static_cast<TriSurfaceMesh*>(rigid_body_->getMesh());
  Translator translator;
  translator.netToNative<List<Rhino::Geometry::Mesh^>, TriSurfaceMesh>(_meshes,
      trimesh);
  return true;
}

bool RigidBodyWrapper::setMechanicalProperty(MechanicalPropertyWrapper^
    _mechanical_property)
{
  rigid_body_->mechanical_property_.assign(
    *(_mechanical_property->mechanical_property_));
  return true;
}
bool RigidBodyWrapper::setMotionProperty(MotionPropertyWrapper^
    _motion_property)
{
  rigid_body_->motion_property_.assign(
    *(_motion_property->motion_property_));
  return true;
}

StaticRigidBodyWrapper::StaticRigidBodyWrapper()
  : RigidBodyWrapper(new StaticRigidBody())
{
}

StaticRigidBodyWrapper::~StaticRigidBodyWrapper()
{
  this->!StaticRigidBodyWrapper();
}

StaticRigidBodyWrapper::!StaticRigidBodyWrapper()
{

}

}//namespace Net
}//namespace PhyMAP
