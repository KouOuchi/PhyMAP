#include "Session.h"

#include <windows.h>

#include <BulletSolverInstance.h>

#include <wincon.h>
#include <stdexcept>
#include <iostream>

#include <TriSurfaceMesh.h>
#include <RigidBody.h>
#include <Transform.h>
#include <SolverInformation.h>

#include "Translator.h"
namespace PhyMAP
{

using namespace Common;

namespace Net
{

Session::Session(SolverInformationWrapper^ _info) :
  info_(_info),
  bullet_instance_(new Bullet::BulletSolverInstance(_info->solver_info_)),
  rigid_bodies_(gcnew Dictionary<int, RigidBodyWrapper^>())
{
  if (info_->solver_info_->debug_)
  {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::cout << "start session." << std::endl;
  }
}

Session::~Session()
{
  FreeConsole();
  this->!Session();
}

Session::!Session()
{
  std::cout << "Session::finalizer start." << std::endl;

  if (bullet_instance_)
  {
    bullet_instance_->deinitialize();
    delete bullet_instance_;
  }

  bullet_instance_ = nullptr;

  std::cout << "Session::finalizer end." << std::endl;
}

void Session::initialize(void)
{
  std::cout << "Session::initialize() start." << std::endl;

  rigid_bodies_->Clear();
  bullet_instance_->initialize();

  std::cout << "Session::initialize() end." << std::endl;
}

void Session::deinitialize(void)
{
  std::cout << "Session::deinitialize() start." << std::endl;

  rigid_bodies_->Clear();

  std::cout << "Session::deinitialize() end." << std::endl;
}


void Session::update(float _time_since_last)
{
  // check
  if (bullet_instance_)
  {
    std::cout << "Session::update() start in bullet_instance_." << std::endl;

    // start automatically
    if (bullet_instance_->getAcceptUpdate())
    {
      bullet_instance_->update(_time_since_last);

      Translator translator;
      for each(auto kv in rigid_bodies_)
      {
        Transform trans_native;
        kv.Value->rigid_body_->getTransform(&trans_native);

#ifdef _DEBUG
        std::cout << "rigid_body transform(vec) :" << trans_native.position_.v_[0] <<
                  "," <<
                  trans_native.position_.v_[1] << "," << trans_native.position_.v_[2] <<
                  std::endl;
        std::cout << "rigid_body transform(qt) :" << trans_native.orientation_.q_[0] <<
                  "," <<
                  trans_native.orientation_.q_[1] << "," << trans_native.orientation_.q_[2] 
			      << "," << trans_native.orientation_.q_[3] << std::endl;
#endif

		Rhino::Geometry::Transform^ trans_net = gcnew Rhino::Geometry::Transform();
        Translator().nativeToNet<Transform, Rhino::Geometry::Transform>(trans_native,
            trans_net);

#ifdef _DEBUG
        {
          std::string mes;
          translator.netToNative<System::String, std::string>(trans_net->ToString(),
              &mes);
          std::cout << "internal transform(debug) :" << mes.c_str() << std::endl;
        }
#endif

        if (!trans_net->IsValid)
        {
          std::cout << "transform invalid." << std::endl;
          continue;
        }
        else
        {
          std::string mes;
          translator.netToNative<System::String, std::string>(trans_net->ToString(),
              &mes);
          std::cout << "internal transform :" << mes.c_str() << std::endl;
        }

        for each(auto mesh in kv.Value->meshes_)
        {
          if (!mesh || !mesh->IsValid)
          {
            std::cout << "mesh is invalid." << std::endl;
            continue;
          }

          if (!trans_net->IsValid)
          {
            std::cout << "transform of mesh is invalid." << std::endl;
            continue;
          }

          if (!mesh->Transform(*trans_net))
          {
            std::cout << "internal transform failure." << std::endl;
          }
        }
      }
    }
  }
}

bool Session::addRigidBody(int i, RigidBodyWrapper^ _rigid_body)
{
  if (bullet_instance_)
  {
    if (rigid_bodies_->ContainsKey(i))
    {
      std::cout << "key exists. : " << i << std::endl;
      return false;
    }

    rigid_bodies_->Add(i, _rigid_body);
    bullet_instance_->addRigidBody(_rigid_body->rigid_body_);

    std::cout << "rigid body added : #" << i << std::endl;

    return true;
  }

  return false;
}
bool Session::addStaticRigidBody(int i, RigidBodyWrapper^ _static_rigid_body)
{
  if (bullet_instance_)
  {
    if (static_rigid_bodies_->ContainsKey(i))
    {
      std::cout << "key exists. : " << i << std::endl;
      return false;
    }

    static_rigid_bodies_->Add(i, _static_rigid_body);
    bullet_instance_->addStaticRigidBody(_static_rigid_body->rigid_body_);

    std::cout << "static rigid body added : #" << i << std::endl;

    return true;
  }

  return false;
}
//Rhino::Geometry::Transform Session::getRigidBodyTransform(int i)
//{
//  if (bullet_instance_)
//  {
//    Vector position;
//    Quaternion orientation;
//
//    bullet_instance_->getRigidBodyTransform(i, &position, &orientation);
//
//    Rhino::Geometry::Transform ret = Rhino::Geometry::Transform::Identity;
//    ret.Translation(Rhino::Geometry::Vector3d::Zero);
//
//    return ret;
//  }
//
//  return Rhino::Geometry::Transform::Identity;
//}

void Session::acceptUpdate(bool _accept)
{
  if (bullet_instance_) { bullet_instance_->acceptUpdate(_accept); }
}

}//namespace PhyMAP
}//namespace Net
