#pragma once

#include "Bullet.h"
#include <btBulletDynamicsCommon.h>


namespace PhyMAP
{

namespace Common
{
class TriSurfaceMesh;
}

using namespace Common;

namespace Bullet
{

class RigidBodyState : public btMotionState
{
protected:

  ///Object transform
  btTransform mTransform;
  ///Relative transform between the RigidBody and the pivor of the Ogre Mesh
  btTransform mCenterOfMassOffset;

  ///Node that this motion state is affecting
  TriSurfaceMesh* mesh_;

public:

  ///Create ea rigid body state with a specified transform and offset
  //RigidBodyState(Ogre::SceneNode* node, const btTransform& transform,
  //               const btTransform& offset = btTransform::getIdentity());

  ///Create a simple rigid body state
  RigidBodyState(TriSurfaceMesh* _mesh);

  ///Get the world transofrm
  /// \param ret : Output parameter where the transform will be written
  BULLET_API virtual void getWorldTransform(btTransform& ret) const;

  ///Set the world transform
  /// \param in : The transform to use. Will change the derivated position in world, not the one relative to the parnet node
  BULLET_API virtual void setWorldTransform(const btTransform& in);

  ///Set the node used by this rigid body state
  void setMesh(TriSurfaceMesh* _mesh);
};

}//namespace Common
}//namespace PhyMAP
