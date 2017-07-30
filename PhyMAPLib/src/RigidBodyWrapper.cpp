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
  translator.netToNative<List<Rhino::Geometry::Mesh^>, TriSurfaceMesh>(_meshes, trimesh);
  return true;
}

//bool RigidBodyWrapper::setTransform(MovementWrapper^ _move)
//{
//  rigid_body_->setMovement(*(_move->movement_));
//  return true;
//}

}//namespace PhyMAP
}//namespace Net
