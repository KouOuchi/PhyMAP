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

CollisionItem::CollisionItem(TriSurfaceMesh* _mesh, float _mass) :
  mass_(_mass)
{
  Converter().Convert<Vector, btVector3>(_mesh->min_vec_, &min_vec_);
  Converter().Convert<Vector, btVector3>(_mesh->max_vec_, &max_vec_);

  shape_ = createTriMesh(_mesh);
  body_state_ = new RigidBodyState(_mesh);
}

CollisionItem::~CollisionItem()
{}
int x = 0;
void CollisionItem::initialize()
{
  //Create the Body.
  mBody = new btRigidBody(btScalar(mass_), body_state_, shape_);

  if (mass_ == 0)
  {
    mBody->setCollisionFlags(mBody->getCollisionFlags() |
                             btCollisionObject::CF_CHARACTER_OBJECT
                            );
  }
  else
  {
    mBody->setCollisionFlags(mBody->getCollisionFlags() |
                             btCollisionObject::CF_CHARACTER_OBJECT
                            );
  }
  mBody->setActivationState(DISABLE_DEACTIVATION);
}
void CollisionItem::deinitialize(void)
{
  if (mBody)
  {
    mBody->getMotionState();
    delete mBody;
    mBody = nullptr;
  }
  if (shape_)
  {
    delete shape_;
    shape_ = nullptr;
  }
}

void CollisionItem::update()
{
  if (mBody)
  {
    btVector3 minVec, maxVec;
    mBody->getAabb(minVec, maxVec);

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
    mBody->getWorldTransform();

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
