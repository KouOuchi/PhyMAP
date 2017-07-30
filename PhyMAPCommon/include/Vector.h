#pragma once

#include "Common.h"

namespace PhyMAP
{
namespace Common
{

class Vector
{
public:
  Vector(void);
  Vector(const Vector& _v);
  Vector(double _x, double _y, double _z);
  virtual ~Vector(void);
  void assign(const Vector& _v);

  double v_[3];
};

}//namespace Common
}//namespace PhyMAP
