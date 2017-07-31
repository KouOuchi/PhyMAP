#pragma once

#include <Vector.h>
#include <Transform.h>

namespace PhyMAP
{
namespace Common
{

class MotionProperty
{
public:
  MotionProperty(void) {}
  virtual ~MotionProperty(void) {}

  Transform start_transform_;
  Vector local_inertia_;
};

}//namespace Net
}//namespace PhyMAP
