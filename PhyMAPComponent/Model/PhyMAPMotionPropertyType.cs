using System;
using GH_IO.Serialization;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;
using System.Collections.Generic;

namespace PhyMAPComponent.Model
{
    public class PhyMAPMotionPropertyType : IGH_Goo
    {
//        public Transform start_transform_ = Transform.Identity;
        public Vector3d local_inertia_ = Vector3d.Zero;

        public bool IsValid
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public string IsValidWhyNot
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public string TypeDescription
        {
            get
            {
                return "PhyMAP MotionPropertyType";
            }
        }

        public string TypeName
        {
            get
            {
                return "MotionPropertyType";
            }
        }

        public bool CastFrom(object source)
        {
            var test = source as PhyMAPMotionPropertyType;
            return test != null;
        }

        public bool CastTo<T>(out T target)
        {
            target = (T)Activator.CreateInstance(typeof(T));
            return true;
        }

        public IGH_Goo Duplicate()
        {
            var goo = new PhyMAPMotionPropertyType()
            {
//                start_transform_ = this.start_transform_,
                local_inertia_ = new Vector3d(this.local_inertia_)
            };

            return goo;
        }

        public IGH_GooProxy EmitProxy()
        {
            throw new NotImplementedException();
        }

        public bool Read(GH_IReader reader)
        {
            throw new NotImplementedException();
        }

        public object ScriptVariable()
        {
            throw new NotImplementedException();
        }

        public bool Write(GH_IWriter writer)
        {
            throw new NotImplementedException();
        }
    }
}
