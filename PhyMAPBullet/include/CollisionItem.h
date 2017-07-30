#pragma once

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
  CollisionItem(TriSurfaceMesh* _mesh, float _mass);
  virtual ~CollisionItem();

  btRigidBody* mBody;
  btCollisionShape* shape_;
  RigidBodyState* body_state_;
//  TriSurfaceMesh* mesh_;

  btVector3 min_vec_;
  btVector3 max_vec_;

  void initialize();
  void deinitialize(void);
  void update();
  void getTrasnform(Vector* _position, Quaternion* _orientation);
protected:
  btBvhTriangleMeshShape* CollisionItem::createTriMesh(TriSurfaceMesh* _mesh);
//  int mesh_id_;
  float mass_;
};

}//namespace Common
}//namespace PhyMAP
