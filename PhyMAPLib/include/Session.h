#pragma once

#include "RigidBodyWrapper.h"
#include "SolverInformationWrapper.h"

namespace PhyMAP
{
namespace Bullet
{
class	BulletSolverInstance;
}
namespace Net
{

using namespace System;
using namespace System::Collections::Generic;

public ref class Session 
{
public:
  Session(SolverInformationWrapper^ _info);
  virtual ~Session();
  !Session();

  void initialize(void);
  void deinitialize(void);

  bool addRigidBody(int i, RigidBodyWrapper^ _rigid_body);
//  bool addStaticRigidBody(int i, RigidBodyWrapper^ _staic_rigid_body);

  //Rhino::Geometry::Transform getRigidBodyTransform(int i);
  Dictionary<int, RigidBodyWrapper^>^ getRigidBodies() { return rigid_bodies_; };
  void update(float timeSinceLast);
  void acceptUpdate(bool _accept);

private:
  Bullet::BulletSolverInstance* bullet_instance_;

  Dictionary<int, RigidBodyWrapper^>^ rigid_bodies_;
//  Dictionary<int, RigidBodyWrapper^>^ static_rigid_bodies_;

  SolverInformationWrapper^ info_;
};

}//namespace Net
}//namespace PhyMAP
