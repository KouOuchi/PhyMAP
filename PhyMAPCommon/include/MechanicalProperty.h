#pragma once

#include <Vector.h>

namespace PhyMAP
{
namespace Common
{

class MechanicalProperty
{
public:
  MechanicalProperty(void) {}
  virtual ~MechanicalProperty(void) {}

  Vector gravity_point_;
  float mass_;
};

}//namespace Net
}//namespace PhyMAP
