#pragma once

#include "Vector.h"
#include "Quaternion.h"

namespace PhyMAP
{
namespace Common
{

class Transform
{
public:
  Transform(void) :
    position_(),
    orientation_()
  {}
  virtual ~Transform(void)
  {}
  void assign(const Transform& _transform)
  {
    position_.assign(_transform.position_);
    orientation_.assign(_transform.orientation_);
  }

  Vector position_;
  Quaternion orientation_;
};

}//namespace Common
}//namespace PhyMAP
