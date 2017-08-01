#include "MechanicalPropertyWrapper.h"

#include <MechanicalProperty.h>
#include "Translator.h"

namespace PhyMAP
{

using namespace Common;

namespace Net
{

MechanicalPropertyWrapper::MechanicalPropertyWrapper(
  Rhino::Geometry::Vector3d^ _gravity_point,
  double _mass)
  : mechanical_property_(new MechanicalProperty())
{
	Translator().netToNative<Rhino::Geometry::Vector3d, Vector>
		(_gravity_point, &(mechanical_property_->gravity_point_));
	mechanical_property_->mass_ = _mass;
}

MechanicalPropertyWrapper::~MechanicalPropertyWrapper()
{
  this->!MechanicalPropertyWrapper();
}

MechanicalPropertyWrapper::!MechanicalPropertyWrapper()
{
  if (mechanical_property_)
  {
    delete mechanical_property_;
    mechanical_property_ = nullptr;
  }
}

}//namespace Net
}//namespace PhyMAP
