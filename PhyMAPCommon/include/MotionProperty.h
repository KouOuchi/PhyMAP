#pragma once

#include <Vector.h>

namespace PhyMAP
{
namespace Common
{

class MotionProperty
{
public:
  MotionProperty(void) {}
  virtual ~MotionProperty(void) {}

  Vector gravity_point_;
  float mass_;
  Transform start_transform_;
  Vector local_inertia_;
};

}//namespace Net
}//namespace PhyMAP
