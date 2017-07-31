#pragma once

#include "Common.h"

namespace PhyMAP
{
namespace Common
{

class Quaternion
{
public:
  Quaternion(void);
  Quaternion(const Quaternion& _q);
  Quaternion(double _x, double _y, double _z, double _w);
  virtual ~Quaternion(void);
  void assign(const Quaternion& _q);

  // real part is q_[3]
  double q_[4];

};

}//namespace Common
}//namespace PhyMAP
