#pragma once

#include <Quaternion.h>

namespace PhyMAP
{
namespace Common
{

Quaternion::Quaternion()
{
  for (int i = 0; i < 3; i++) { q_[i] = 0.0f; }
  q_[3] = 1.0f;
}
Quaternion::Quaternion(const Quaternion& _q)
{
  assign(_q);
}
Quaternion::Quaternion(double _x, double _y, double _z, double _w)
{
  q_[0] = _x;
  q_[1] = _y;
  q_[2] = _z;
  q_[3] = _w;
}
void Quaternion::assign(const Quaternion& _q)
{
  for (int i = 0; i < 4; i++) { q_[i] = _q.q_[i]; }
}
Quaternion::~Quaternion()
{}

}//namespace Common
}//namespace PhyMAP
