#pragma once

#include "Vector.h"
#include "Quaternion.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "SolverInformation.h"

namespace PhyMAP
{

using namespace Common;

namespace Common
{

//typedef long MESH_ID;

class SolverInstance
{
public:
  SolverInstance (SolverInformation* _info) : update_enabled_(false), gravity_() {}
  virtual ~SolverInstance() {};

  virtual void initialize(void) = 0;
  virtual void deinitialize(void) = 0;

  virtual void addRigidBody(RigidBody* _rigid_body) {}
//  virtual void addStaticRigidBody(RigidBody* _rigid_body) {}

  virtual void update(float timeSinceLast) {}
  virtual void getRigidBodyTransform(int _mesh_id, const Vector* _translation,
                                     const Quaternion* _rotation) {}
  virtual void getUpdatedSoftBody(int _mesh_id, Mesh* _mesh) {}
  virtual void acceptUpdate(bool _t) { update_enabled_ = _t; }
  virtual bool getAcceptUpdate() { return update_enabled_; }

protected:
  Vector gravity_;
  bool update_enabled_;

  // TODO:
  //virtual bool addSoftBody(Rhino::Geometry::Mesh^ _mesh) = 0;
  //virtual bool addConstraints() = 0;


};

}//namespace Common
}//namespace PhyMAP
