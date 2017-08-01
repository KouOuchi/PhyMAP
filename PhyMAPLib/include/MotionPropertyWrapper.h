#pragma once

namespace PhyMAP
{
namespace Common
{
class MotionProperty;
}

namespace Net
{

using namespace Common;
using namespace System;
using namespace System::Collections::Generic;

public ref class MotionPropertyWrapper
{
public:
  MotionPropertyWrapper(
	  Rhino::Geometry::Vector3d _local_inertia
  );
  virtual ~MotionPropertyWrapper(void);
  !MotionPropertyWrapper(void);

internal:
  MotionProperty* motion_property_;
};

}//namespace Net
}//namespace PhyMAP
