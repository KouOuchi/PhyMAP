#pragma once

#include "Vector.h"
#include "Quaternion.h"

namespace PhyMAP
{
namespace Common
{

class Mesh
{
public:
  Mesh(void);
  virtual ~Mesh(void);

  /* quatanion*/
//  virtual const Quaternion& getOrientation(void);

  /* vec */
//  virtual const Vector& getPosition(void);

  virtual int getVertexCount(void) = 0;
  virtual int getFaceCount(void) = 0;

//  virtual void setOrientation(const Quaternion& _qt);
//  virtual void setPosition(const Vector& _pos);

protected:
  bool isSoftBody_;
//  Vector position_;
//  Quaternion orientation_;


};

}//namespace Bullet
}//namespace PhyMAP
