#pragma unmanaged

#include "RigidBodyState.h"

#include <Vector.h>
#include <Quaternion.h>
#include "Converter.h"
#include <TriSurfaceMesh.h>

#include <btBulletDynamicsCommon.h>

namespace PhyMAP
{
namespace Bullet
{

using namespace Common;

//RigidBodyState::RigidBodyState(Mesh* node, const btTransform& transform, const btTransform& offset) :
//	mTransform(transform),
//	mCenterOfMassOffset(offset),
//	mNode(node)
//{
//}

RigidBodyState::RigidBodyState(TriSurfaceMesh* _mesh) :
  mCenterOfMassOffset(btTransform::getIdentity()),
  mesh_(_mesh),
  mTransform
  (
    btQuaternion(0, 0, 0, 1),
    btVector3(0, 0, 0)
  )
{
  if (_mesh)
  {
/*
    Converter cv;
    btVector3 pos;
    cv.Convert<Vector, btVector3>(mesh_->getPosition(), &pos);

    btQuaternion rot;
    cv.Convert(mesh_->getOrientation(), &rot);

    mTransform = btTransform(rot, pos);
*/
  }
}

void RigidBodyState::getWorldTransform(btTransform& ret) const
{
  ret = mTransform;
}

void RigidBodyState::setWorldTransform(const btTransform& in)
{
  if (!mesh_) { return; }

  //store transform
  mTransform = in;

  ////extract position and orientation
  //const auto transform = mTransform * mCenterOfMassOffset;
  //const auto rot = transform.getRotation();
  //const auto pos = transform.getOrigin();

  //Converter cv;
  //Vector target_pos;
  //cv.Convert<btVector3, Vector>(pos, &target_pos);
  //Quaternion target_rot;
  //cv.Convert<btQuaternion, Quaternion>(rot, &target_rot);

  ////Set to the node
  //mesh_->setOrientation(target_rot);
  //mesh_->setPosition(target_pos);
}

void RigidBodyState::setMesh(TriSurfaceMesh* _mesh)
{
  if (mesh_)
  {
    throw std::runtime_error(std::string("mesh is exists."));

  }
  mesh_ = _mesh;
}


}//namespace Bullet
}//namespace PhyMAP
