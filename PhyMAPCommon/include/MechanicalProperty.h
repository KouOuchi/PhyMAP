#pragma once

#include <Vector.h>

namespace PhyMAP
{
namespace Common
{

class MechanicalProperty
{
public:
  MechanicalProperty(void) : gravity_point_(), mass_(0) {}
  MechanicalProperty(const MechanicalProperty& _m)
    : gravity_point_(_m.gravity_point_), mass_(_m.mass_)
  {}
  virtual ~MechanicalProperty(void) {}
  void assign(const MechanicalProperty& _m)
  {
    gravity_point_.assign(_m.gravity_point_);
    mass_ = _m.mass_;
  }

  Vector gravity_point_;
  float mass_;
};

}//namespace Net
}//namespace PhyMAP
