#include "MotionPropertyWrapper.h"

#include <MotionProperty.h>
#include "Translator.h"

namespace PhyMAP
{

using namespace Common;

namespace Net
{

MotionPropertyWrapper::MotionPropertyWrapper(
  Rhino::Geometry::Vector3d _local_inertia)
  : motion_property_(new MotionProperty())
{
	Translator().netToNative<Rhino::Geometry::Vector3d, Vector>
		(_local_inertia, &(motion_property_->local_inertia_));
}

MotionPropertyWrapper::~MotionPropertyWrapper()
{
  this->!MotionPropertyWrapper();
}

MotionPropertyWrapper::!MotionPropertyWrapper()
{
  if (motion_property_)
  {
    delete motion_property_;
    motion_property_ = nullptr;
  }
}

}//namespace Net
}//namespace PhyMAP
