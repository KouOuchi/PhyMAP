#pragma once
#include "Bullet.h"

#include "Vector.h"
#include "Quaternion.h"
#include <btBulletDynamicsCommon.h>
#include <stdexcept>

namespace PhyMAP
{
namespace Bullet
{

using namespace Common;

struct Converter
{
  template <typename T, typename U>
  BULLET_API void Convert(const T& _source, U* _target)
  {
    throw std::runtime_error("generic converte is not implemented.");
  }

  template<>
  BULLET_API void Convert<btVector3, Vector>(const btVector3& _source,
      Vector* _target)
  {
    _target->v_[0] = _source.x();
    _target->v_[1] = _source.y();
    _target->v_[2] = _source.z();
  }

  template<>
  BULLET_API void Convert<Vector, btVector3>(const Vector& _source,
      btVector3* _target)
  {
    _target->setValue(
      btScalar(_source.v_[0]), btScalar(_source.v_[1]), btScalar(_source.v_[2]));
  }

  template <>
  BULLET_API void Convert<btQuaternion, Quaternion>(const btQuaternion& _source,
      Quaternion*_target)
  {
    _target->q_[0] = _source.x();
    _target->q_[1] = _source.y();
    _target->q_[2] = _source.z();
    _target->q_[3] = _source.w();
  }

  template <>
  BULLET_API void Convert<Quaternion, btQuaternion>(const Quaternion& _source,
      btQuaternion*_target)
  {
    _target->setValue(
      btScalar(_source.q_[0]),
      btScalar(_source.q_[1]),
      btScalar(_source.q_[2]),
      btScalar(_source.q_[3]));
  }

};
}//namespace Bullet
}//namespace PhyMAP
