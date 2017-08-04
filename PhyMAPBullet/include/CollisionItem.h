#pragma once

#include "MechanicalProperty.h"
#include "MotionProperty.h"
#include "RigidBodyState.h"
#include "RigidBody.h"
#include "Converter.h"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

//class btRigidBody;
//class btCollisionShape;
//class btVector3;
//class btBvhTriangleMeshShape;

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

//class RigidBodyState;

class CollisionItem
{
public:
  CollisionItem(TriSurfaceMesh* _mesh/*,
                const MechanicalProperty& _mechanical_property,
                const MotionProperty& _motion_property*/);
  virtual ~CollisionItem();

  btCollisionObject* body_;
  btCollisionShape* shape_;
  RigidBodyState* body_state_;

  btVector3 min_vec_;
  btVector3 max_vec_;

  void deinitialize(void);


  template<typename T>
  typename std::enable_if<
  std::is_same<RigidBody, T>::value
  >::type initialize(T* _rigid_body, btDynamicsWorld* _phy_world)
  {
    btVector3 inertia;
    Converter().Convert<Vector, btVector3>
    (_rigid_body->motion_property_.local_inertia_, &inertia);

    //Create the Body.
    btRigidBody::btRigidBodyConstructionInfo
    binfo(btScalar(_rigid_body->mechanical_property_.mass_),
          body_state_,
          shape_,
          inertia
         );

    body_ = new btRigidBody(binfo);

    body_->setCollisionFlags(body_->getCollisionFlags() |
                             btCollisionObject::CF_CHARACTER_OBJECT
                            );

    body_->setActivationState(DISABLE_DEACTIVATION);

    _phy_world->addRigidBody(static_cast<btRigidBody*>(body_));

  }

  template<typename T>
  typename std::enable_if<
  std::is_same<StaticRigidBody, T>::value
  >::type initialize(T* _static_rigid_body, btDynamicsWorld* _phy_world)
  {
    btVector3 inertia;
    Converter().Convert<Vector, btVector3>
    (_rigid_body->motion_property_.local_inertia_, &inertia);

    //Create the Body.
    btRigidBody::btRigidBodyConstructionInfo
    binfo(btScalar(1/*_static_rigid_body->mechanical_property_.mass_*/),
          body_state_,
          shape_,
          inertia
         );

    body_ = new btGhostObject(info);

    body_->setCollisionFlags(body_->getCollisionFlags() |
                             btCollisionObject::CF_CHARACTER_OBJECT
                            );

    body_->setActivationState(DISABLE_DEACTIVATION);

    _phy_world->addRigidBody(static_cast<btGhostObject*>(body_));
  }

  void update();
  void getTrasnform(Vector* _position, Quaternion* _orientation);
protected:

  btBvhTriangleMeshShape* CollisionItem::createTriMesh(TriSurfaceMesh* _mesh);

  //  MechanicalProperty mechanical_property_;
//  MotionProperty motion_property_;
};

}//namespace Common
}//namespace PhyMAP
