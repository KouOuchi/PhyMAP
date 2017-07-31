#pragma once

#include <Transform.h>
#include <TriSurfaceMesh.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace PhyMAP
{

using namespace Common;

namespace Net
{

using namespace System;
using namespace System::Collections::Generic;

ref struct Translator
{
  template <typename T, typename U>
  void netToNative(T^ _source, U* _target)
  {
    throw std::runtime_error("generic converte is not implemented.");
  }

  template <typename T, typename U>
  void nativeToNet(const T& _source, U^ _target)
  {
    throw std::runtime_error("generic converte is not implemented.");
  }

  template <>
  void netToNative<Rhino::Geometry::Vector3d, Vector>(
    Rhino::Geometry::Vector3d^ _source, Vector* _target)
  {
    _target->assign(Vector(_source->X, _source->Y, _source->Z));
  }

  template <>
  void netToNative<Rhino::Geometry::Point3f, Vector>(
    Rhino::Geometry::Point3f^ _source, Vector* _target)
  {
    _target->assign(Vector(_source->X, _source->Y, _source->Z));
  }

  template <>
  void netToNative<Rhino::Geometry::Mesh, TriSurfaceMesh>(
    Rhino::Geometry::Mesh^
    _source, TriSurfaceMesh* _target)
  {

    // copy vertex
    for (int i = 0; i < _source->Vertices->Count; i++)
    {
      Vector v;
      netToNative<Rhino::Geometry::Point3f, Vector>
      (_source->Vertices[i], &v);
      _target->verticies_.push_back(v);
    }

    // copy face
    for (int i = 0; i < _source->Faces->Count; i++)
    {
      if (_source->Faces[i].IsTriangle || _source->Faces[i].IsQuad)
      {
        TriSurfaceMeshFace f;

        f.vertex_indicies_[0] = _source->Faces[i].A;
        f.vertex_indicies_[1] = _source->Faces[i].B;
        f.vertex_indicies_[2] = _source->Faces[i].C;

        _target->faces_.push_back(f);
      }
      if (_source->Faces[i].IsQuad)
      {
        TriSurfaceMeshFace f;

        f.vertex_indicies_[0] = _source->Faces[i].A;
        f.vertex_indicies_[1] = _source->Faces[i].C;
        f.vertex_indicies_[2] = _source->Faces[i].D;

        _target->faces_.push_back(f);
      }
    }

    // copy bounding box
    Rhino::Geometry::BoundingBox box = _source->GetBoundingBox(true);
    Rhino::Geometry::Point3d min = box.Corner(true, true, true);
    Rhino::Geometry::Point3d max = box.Corner(false, false, false);
  }

  template <>
  void netToNative<List<Rhino::Geometry::Mesh^>, TriSurfaceMesh>(
    List<Rhino::Geometry::Mesh^>^ _source, TriSurfaceMesh* _target)
  {
    int vertex_offset = 0;
    Rhino::Geometry::BoundingBox box = Rhino::Geometry::BoundingBox::Empty;

    for (int m = 0; m < _source->Count; m++)
    {
      auto mesh = _source[m];

      for (int i = 0; i < mesh->Vertices->Count; i++)
      {
        Vector v;
        netToNative<Rhino::Geometry::Point3f, Vector>
        (mesh->Vertices[i], &v);
        _target->verticies_.push_back(v);
      }

      // copy face
      for (int i = 0; i < mesh->Faces->Count; i++)
      {
        if (mesh->Faces[i].IsTriangle || mesh->Faces[i].IsQuad)
        {
          TriSurfaceMeshFace f;

          f.vertex_indicies_[0] = mesh->Faces[i].A + vertex_offset;
          f.vertex_indicies_[1] = mesh->Faces[i].B + vertex_offset;
          f.vertex_indicies_[2] = mesh->Faces[i].C + vertex_offset;

          _target->faces_.push_back(f);
        }
        if (mesh->Faces[i].IsQuad)
        {
          TriSurfaceMeshFace f;

          f.vertex_indicies_[0] = mesh->Faces[i].A + vertex_offset;
          f.vertex_indicies_[1] = mesh->Faces[i].C + vertex_offset;
          f.vertex_indicies_[2] = mesh->Faces[i].D + vertex_offset;

          _target->faces_.push_back(f);
        }
      }

      vertex_offset += mesh->Vertices->Count;
      box.Union(mesh->GetBoundingBox(true));
    }

    // copy bounding box
    Rhino::Geometry::Point3d min = box.Corner(true, true, true);
    Rhino::Geometry::Point3d max = box.Corner(false, false, false);
  }

  template <>
  void nativeToNet<Transform, Rhino::Geometry::Transform>(const Transform&
      _source,
      Rhino::Geometry::Transform^ _target)
  {
    *_target = Rhino::Geometry::Transform::Identity;

    Rhino::Geometry::Quaternion^ orientation =
      gcnew Rhino::Geometry::Quaternion(_source.orientation_.q_[3],
                                        _source.orientation_.q_[0],
                                        _source.orientation_.q_[1],
                                        _source.orientation_.q_[2]);

    /*
      double angle;
      Rhino::Geometry::Vector3d axis;
      auto rot_trans = orientation->MatrixForm();
      if (!orientation->GetRotation(angle, axis))
      {
        throw std::runtime_error("getting orientation failure.");
      }
    */
    _target->Translation(Rhino::Geometry::Vector3d(_source.position_.v_[0],
                         _source.position_.v_[1],
                         _source.position_.v_[2]));
//    _target->Rotation(angle, axis,
//                      Rhino::Geometry::Point3f(_source.position_.v_[0], _source.position_.v_[1],
//                          _source.position_.v_[2]));
    /*

          for (const int row : { 0, 1, 2 })
          {
            for (const int col : { 0, 1, 2, 3})
            {
              (*_target)[row, col] = rot_trans[row, col];
            }
          }
          (*_target)[3, 0] = _source.position_.v_[0];
          (*_target)[3, 1] = _source.position_.v_[1];
          (*_target)[3, 2] = _source.position_.v_[2];
          (*_target)[3, 3] = 1.0;
    */
  }

  template <>
  void netToNative<System::String, std::string>( System::String^ s,
      std::string* os )
  {
    using namespace Runtime::InteropServices;
    const char* chars =
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    *os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
  }

  template <>
  void netToNative<System::String, std::wstring>( System::String^ s,
      std::wstring* os )
  {
    using namespace Runtime::InteropServices;
    const wchar_t* chars =
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
    *os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
  }


};

}//namespace Net
}//namespace PhyMAP
