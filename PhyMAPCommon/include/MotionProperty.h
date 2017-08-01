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
  MotionProperty(void) : attitude_(), local_inertia_() {}
  MotionProperty(const MotionProperty& _m) :
	  attitude_(_m.attitude_), local_inertia_(_m.local_inertia_)
  {}
  virtual ~MotionProperty(void) {}
  void assign(const MotionProperty& _m)
  {
	  attitude_.assign(_m.attitude_);
	  local_inertia_.assign(_m.local_inertia_);
  }

  Vector attitude_;
  Vector local_inertia_;
};

}//namespace Net
}//namespace PhyMAP
