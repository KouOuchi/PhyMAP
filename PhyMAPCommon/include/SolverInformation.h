#pragma once

#include "Common.h"
#include "Vector.h"

namespace PhyMAP
{
namespace Common
{

class SolverInformation
{
public:
  SolverInformation(void) :
    debug_(false),
    gravity_(0.0, 0.0, 9.8),
    duration_(5.0),
    time_step_(0.1f)
  {}

  virtual ~SolverInformation(void) {}
  bool debug_;
  Vector gravity_;
  double duration_;
  float time_step_;
};

}//namespace Common
}//namespace PhyMAP
