#include "BulletSolverInstance.h"
#include <Mesh.h>
#include <TriSurfaceMesh.h>
#include "CollisionItem.h"
#include <iostream>
#include "Converter.h"

#include "btBulletDynamicsCommon.h"

namespace PhyMAP
{
namespace Bullet
{

void NearCallback(btBroadphasePair& collisionPair,
                  btCollisionDispatcher& dispatcher, btDispatcherInfo& dispatchInfo)
{
  std::cout << "detect collision." << std::endl;
  dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
}

BulletSolverInstance::BulletSolverInstance(SolverInformation* _info)
  : SolverInstance(_info)
{
  gravity_.assign(_info->gravity_);
}

BulletSolverInstance::~BulletSolverInstance() {}


void BulletSolverInstance::initialize()
{
  std::cout << "BulletSolverInstance::initialize() start.";

  update_enabled_ = false;

  //Bullet initialisation.
  mBroadphase = new btDbvtBroadphase();
//	  btAxisSweep3(btVector3(-10000, -10000, -10000),
//                                 btVector3(10000, 10000, 10000), 1024);
  mCollisionConfig = new btDefaultCollisionConfiguration();
  mDispatcher = new btCollisionDispatcher(mCollisionConfig);
  mSolver = new btSequentialImpulseConstraintSolver();

  phyWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver,
                                         mCollisionConfig);

  btVector3 btGravity;
  Converter().Convert<Vector, btVector3>(gravity_, &btGravity);
  std::cout << "BulletSolverInstance::gravity is set to " << btGravity.x() << "," <<
            btGravity.y() << "," << btGravity.z() << std::endl;

  phyWorld->setGravity(btGravity);
  mDispatcher->setNearCallback((btNearCallback)
                               PhyMAP::Bullet::NearCallback);

}
void BulletSolverInstance::deinitialize(void)
{
  std::cout << "BulletSolverInstance::deinitialize() start." << std::endl;

  //Free rigid bodies
  for (std::map<RigidBody*, CollisionItem*>::iterator it = items_.begin();
       it != items_.end(); ++it)
  {
    if (it->second->mBody)
    {
      phyWorld->removeRigidBody(it->second->mBody);
    }
    it->second->deinitialize();

    delete it->second;
  }

  items_.clear();

  //Free Bullet stuff.
  delete phyWorld;

  delete mSolver;
  delete mDispatcher;
  delete mCollisionConfig;
  delete mBroadphase;

}

//void BulletSolverInstance::createWorld(void) {}

void BulletSolverInstance::addRigidBody(RigidBody* _rigid_body)
{
  auto mesh = _rigid_body->getMesh();
  if (mesh == nullptr)
  {
    throw std::runtime_error(std::string("arg mesh is null."));
  }

  TriSurfaceMesh* tri_mesh = static_cast<TriSurfaceMesh*>(mesh);
  CollisionItem* item = new CollisionItem(tri_mesh, 1);

  // init
  item->initialize();
  phyWorld->addRigidBody(item->mBody);

  items_.insert(std::pair<RigidBody*, CollisionItem*>(_rigid_body, item));
}

void BulletSolverInstance::addStaticRigidBody(RigidBody* _rigid_body)
{
  auto mesh = _rigid_body->getMesh();
  if (mesh == nullptr)
  {
    throw std::runtime_error(std::string("arg mesh is null."));
  }

  TriSurfaceMesh* tri_mesh = static_cast<TriSurfaceMesh*>(mesh);
  CollisionItem* item = new CollisionItem(tri_mesh, 0);

  // init
  item->initialize();
  phyWorld->addRigidBody(item->mBody);

  items_.insert(std::pair<RigidBody*, CollisionItem*>(_rigid_body, item));
}

void BulletSolverInstance::getRigidBodyTransform(int _mesh_id,
    Vector* _position, Quaternion* _orientation)
{

}

//void BulletSolverInstance::destroyWorld(void) {}

void BulletSolverInstance::update(float timeSinceLast)
{
  if (update_enabled_)
  {
    for (std::map<RigidBody*, CollisionItem*>::iterator it = items_.begin();
         it != items_.end(); ++it)
    {
      it->second->update();
    }

    if (phyWorld)
    {
      phyWorld->stepSimulation(btScalar(timeSinceLast));
    }

    for (std::map<RigidBody*, CollisionItem*>::iterator it = items_.begin();
         it != items_.end(); ++it)
    {
      Vector position;
      Quaternion orientation;
      it->second->getTrasnform(&position, &orientation);

      std::cout << "bullet transform1: " << position.v_[0] << "," << position.v_[1] <<
                "," << position.v_[2] << std::endl;

      it->first->setTransform(position, orientation);
    }
  }
}




///////////////////////////////
// graphicsSystemのcollisionState　サブクラスへ
// collision関係は別名前空間にまとめる

}//namespace Bullet
}//namespace PhyMAP
