#include <Vector.h>

namespace PhyMAP
{
namespace Common
{

Vector::Vector()
{
  for (int i = 0; i < 3; i++) { v_[i] = 0.0f; }
}
Vector::Vector(const Vector& _v)
{
  assign(_v);
}
Vector::Vector(double _x, double _y, double _z)
{
  v_[0] = _x;
  v_[1] = _y;
  v_[2] = _z;
}

void Vector::assign(const Vector& _v)
{
  for (int i = 0; i < 3; i++) { v_[i] = _v.v_[i]; }
}

Vector::~Vector()
{}

}//namespace Common
}//namespace PhyMAP
