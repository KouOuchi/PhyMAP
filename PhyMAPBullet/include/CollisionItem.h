#pragma once

#include "MechanicalProperty.h"
#include "MotionProperty.h"

class btRigidBody;
class btCollisionShape;
class btVector3;
class btBvhTriangleMeshShape;

namespace PhyMAP
{

namespace Common
{
class TriSurfaceMesh;
class Vector;
class Quaternion;
}
using namespace Common;

namespace Bullet
{

class RigidBodyState;

class CollisionItem
{
public:
  CollisionItem(TriSurfaceMesh* _mesh,
                const MechanicalProperty& _mechanical_property,
                const MotionProperty& _motion_property);
  virtual ~CollisionItem();

  btRigidBody* body_;
  btCollisionShape* shape_;
  RigidBodyState* body_state_;

  btVector3 min_vec_;
  btVector3 max_vec_;

  void initialize();
  void deinitialize(void);
  void update();
  void getTrasnform(Vector* _position, Quaternion* _orientation);
protected:
  btBvhTriangleMeshShape* CollisionItem::createTriMesh(TriSurfaceMesh* _mesh);

  MechanicalProperty mechanical_property_;
  MotionProperty motion_property_;
};

}//namespace Common
}//namespace PhyMAP
