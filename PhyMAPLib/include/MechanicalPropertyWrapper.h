#pragma once

namespace PhyMAP
{
namespace Common
{
class MechanicalProperty;
}

namespace Net
{

using namespace Common;
using namespace System;
using namespace System::Collections::Generic;

public ref class MechanicalPropertyWrapper
{
public:
  MechanicalPropertyWrapper(
	  Rhino::Geometry::Vector3d^ _gravity_point,
	  double _mass
	  );
  virtual ~MechanicalPropertyWrapper(void);
  !MechanicalPropertyWrapper(void);

internal:
  MechanicalProperty* mechanical_property_;
};

}//namespace Net
}//namespace PhyMAP
