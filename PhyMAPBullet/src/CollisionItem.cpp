#include "CollisionItem.h"

#include "Converter.h"
#include <TriSurfaceMesh.h>
#include "RigidBodyState.h"
#include <btBulletDynamicsCommon.h>

namespace PhyMAP
{
using namespace Common;

namespace Bullet
{

CollisionItem::CollisionItem(
  TriSurfaceMesh* _mesh,
  const MechanicalProperty& _mechanical_property,
  const MotionProperty& _motion_property)
  : body_state_(nullptr), shape_(nullptr), body_(nullptr),
    mechanical_property_(_mechanical_property),
    motion_property_(_motion_property)
{
  Converter().Convert<Vector, btVector3>(_mesh->min_vec_, &min_vec_);
  Converter().Convert<Vector, btVector3>(_mesh->max_vec_, &max_vec_);

  shape_ = createTriMesh(_mesh);
  body_state_ = new RigidBodyState(_mesh);
}

CollisionItem::~CollisionItem()
{}

void CollisionItem::initialize()
{
  btVector3 inertia;
  Converter().Convert<Vector, btVector3>
  (motion_property_.local_inertia_, &inertia);

  //Create the Body.
  btRigidBody::btRigidBodyConstructionInfo
  binfo(btScalar(mechanical_property_.mass_),
        body_state_,
        shape_,
        inertia
       );

  body_ = new btRigidBody(binfo);

  body_->setCollisionFlags(body_->getCollisionFlags() |
                           btCollisionObject::CF_CHARACTER_OBJECT
                          );

  body_->setActivationState(DISABLE_DEACTIVATION);
}
void CollisionItem::deinitialize(void)
{
  if (body_)
  {
    body_->getMotionState();
    delete body_;
    body_ = nullptr;
  }
  if (shape_)
  {
    delete shape_;
    shape_ = nullptr;
  }
}

void CollisionItem::update()
{
  if (body_)
  {
    btVector3 minVec, maxVec;
    body_->getAabb(minVec, maxVec);

    if (minVec != min_vec_ || maxVec != max_vec_)
    {
      min_vec_.setValue(minVec.getX(), minVec.getY(), minVec.getZ());
      max_vec_.setValue(maxVec.getX(), maxVec.getY(), maxVec.getZ());

      //        std::cout << "(bt Target) Min :" << minVec.getX() << " " << minVec.getY() << " "
      //                  <<
      //                  minVec.getZ();
      //        std::cout << "Max :" << maxVec.getX() << " " << maxVec.getY() << " " <<
      //                  maxVec.getZ() <<
      //                  std::endl;

    }
  }
}

void CollisionItem::getTrasnform(Vector* _position,
                                 Quaternion* _orientation)
{
  const auto trans =
    body_->getWorldTransform();

  Converter cv;
  cv.Convert<btVector3, Vector>(trans.getOrigin(), _position);
  cv.Convert<btQuaternion, Quaternion>(trans.getRotation(), _orientation);
}

btBvhTriangleMeshShape* CollisionItem::createTriMesh(TriSurfaceMesh* _mesh)
{
  const long num_faces = _mesh->getFaceCount();
  auto trimesh = new btTriangleMesh();

  btVector3 vertexPos[3];
  Converter cv;
  for (auto i = size_t{ 0U }; i < num_faces; ++i)
  {
    for (const int j : { 0, 1, 2 })
    {
      btVector3 bt_vec;
      int vertex_index = _mesh->faces_[i].vertex_indicies_[j];
      cv.Convert<Vector, btVector3>(_mesh->verticies_[vertex_index], &bt_vec);
      vertexPos[j] = bt_vec;
    }
    trimesh->addTriangle(vertexPos[0], vertexPos[1], vertexPos[2]);
  }

  const auto useQuantizedAABB = true;
  auto shape = new btBvhTriangleMeshShape(trimesh, useQuantizedAABB);

  return shape;
}


}//namespace Bullet
}//namespace PhyMAP
