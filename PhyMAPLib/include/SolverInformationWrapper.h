#pragma once
//#include "SolverInformation.h"
//extern "C" class SolverInformation;
//#pragma make_public(SolverInformation)

namespace PhyMAP
{
namespace Common
{
class SolverInformation;
}

using namespace Common;

namespace Net
{

using namespace System;
using namespace System::Collections::Generic;

public ref class SolverInformationWrapper
{
public:
  SolverInformationWrapper(bool _debug, float _time_step, double _duration,
                           Rhino::Geometry::Vector3d^ _gravity);
  virtual ~SolverInformationWrapper(void);
  !SolverInformationWrapper(void);

  Tuple<bool, float, double>^ getInfo();

  //SolverInformation* getValue() { return solver_info_; }

internal:
  SolverInformation* solver_info_;
};

}//namespace Net
}//namespace PhyMAP
