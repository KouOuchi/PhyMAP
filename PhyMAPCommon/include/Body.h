#pragma once

#include <iostream>

#include "Mesh.h"
#include "Transform.h"

namespace PhyMAP
{
namespace Common
{

class Body
{
public:
  Body(Mesh* _mesh) :
    mesh_(_mesh) {}
  virtual ~Body(void)
  {
    if (mesh_) { delete mesh_; }

    mesh_ = nullptr;
  }

  virtual Mesh* getMesh()
  {
    return mesh_;
  }
  virtual void setMesh(Mesh* _mesh)
  {

  }
  virtual void getTransform(Transform* _transform)
  {
    _transform->assign(transform_);
  }
  virtual void setTransform(const Transform& _transform)
  {
    transform_.assign(_transform);
  }
  virtual void setTransform(Vector& _position, Quaternion& _orientation)
  {
    transform_.position_.assign(_position);
    transform_.orientation_.assign(_orientation);
  }

  virtual void getTransform(Vector* _position, Quaternion* _orientation)
  {
    _position->assign(transform_.position_);
    _orientation->assign(transform_.orientation_);
  }

protected:
  Mesh* mesh_;
  Transform transform_;

};

}//namespace Common
}//namespace PhyMAP
