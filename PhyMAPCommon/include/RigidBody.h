#pragma once

#include "Body.h"
#include "TriSurfaceMesh.h"

namespace PhyMAP
{
namespace Common
{

class RigidBody : public Body
{
public:
  RigidBody(void) : Body(new TriSurfaceMesh()) {}
  virtual ~RigidBody(void) {}

};

class StaticRigidBody : public Body
{
public:
  StaticRigidBody(void) : Body(new TriSurfaceMesh()) {}
  virtual ~StaticRigidBody(void) {}

};

}//namespace Common
}//namespace PhyMAP
