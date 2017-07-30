#include "SolverInformationWrapper.h"
#include <SolverInformation.h>
#include "Translator.h"

namespace PhyMAP
{

using namespace Common;

namespace Net
{

SolverInformationWrapper::SolverInformationWrapper(bool _debug,
    float _time_step, double _duration, Rhino::Geometry::Vector3d _gravity)
  : solver_info_(new SolverInformation())
{
  solver_info_->debug_ = _debug;
  solver_info_->time_step_ = _time_step;
  solver_info_->duration_ = _duration;

  Translator().netToNative<Rhino::Geometry::Vector3d, Vector>
  (_gravity, &solver_info_->gravity_);
}

SolverInformationWrapper::~SolverInformationWrapper()
{
  this->!SolverInformationWrapper();
}

SolverInformationWrapper::!SolverInformationWrapper()
{
  if (solver_info_)
  {
    delete solver_info_;
    solver_info_ = nullptr;
  }
}

Tuple<bool, float, double>^ SolverInformationWrapper::getInfo()
{
  return gcnew Tuple<bool, float, double>(solver_info_->debug_,
         solver_info_->time_step_, solver_info_->duration_);
}

}//namespace Net
}//namespace PhyMAP
