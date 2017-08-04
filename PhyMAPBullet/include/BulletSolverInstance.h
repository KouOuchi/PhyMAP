#pragma once

#include "Bullet.h"
#include <map>

#include <SolverInstance.h>

class btDynamicsWorld;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btRigidBody;
class btCollisionShape;
class btVector3;

namespace PhyMAP
{

namespace Common
{
class Mesh;
}

using namespace Common;

namespace Bullet
{

class CollisionItem;

class BulletSolverInstance : public SolverInstance
{
public:
  BULLET_API BulletSolverInstance(SolverInformation* _info);
  virtual ~BulletSolverInstance(void);

  BULLET_API virtual void initialize(void);
  BULLET_API virtual void deinitialize(void);

  BULLET_API virtual void update(float timeSinceLast);

  BULLET_API virtual void addRigidBody(RigidBody* _rigid_body);
  //BULLET_API virtual void addStaticRigidBody(RigidBody* _rigid_body);

  BULLET_API virtual void getRigidBodyTransform(int _mesh_id, Vector* _position, Quaternion* _orientation);

  BULLET_API virtual void acceptUpdate(bool _t) { update_enabled_ = _t; }
  BULLET_API virtual bool getAcceptUpdate() { return update_enabled_; }


protected:
  btDynamicsWorld* phyWorld;
  btBroadphaseInterface *mBroadphase;
  btDefaultCollisionConfiguration *mCollisionConfig;
  btCollisionDispatcher *mDispatcher;
  btSequentialImpulseConstraintSolver *mSolver;

  std::map<RigidBody*, CollisionItem*> items_;

};

}//namespace Common
}//namespace PhyMAP
