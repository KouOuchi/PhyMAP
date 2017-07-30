using System;
using GH_IO.Serialization;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;
using System.Collections.Generic;

namespace PhyMAPComponent.Model
{
    public class PhyMAPStaticRigidBodyType : IGH_Goo
    {
        public List<Brep> breps_ = new List<Brep>();

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
                return "PhyMAP StaticRigidBodyType";
            }
        }

        public string TypeName
        {
            get
            {
                return "StaticRigidBodyType";
            }
        }

        public bool CastFrom(object source)
        {
            var test = source as PhyMAPStaticRigidBodyType;
            return test != null;
        }

        public bool CastTo<T>(out T target)
        {
            target = (T)Activator.CreateInstance(typeof(T));
            return true;
        }

        public IGH_Goo Duplicate()
        {
            var goo = new PhyMAPStaticRigidBodyType()
            {
            };

            this.breps_.ForEach(p => goo.breps_.Add(p.DuplicateBrep()));
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
