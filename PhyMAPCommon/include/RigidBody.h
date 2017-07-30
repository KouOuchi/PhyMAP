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

}//namespace Common
}//namespace PhyMAP
