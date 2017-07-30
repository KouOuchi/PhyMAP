using System;
using GH_IO.Serialization;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;
using System.Collections.Generic;

namespace PhyMAPComponent.Model
{
    public class PhyMAPRigidBodyType : IGH_Goo
    {
        public List<Brep> breps_ = new List<Brep>();
        public Vector3d direction_ = Vector3d.Zero;
        public double velocity_ = 0.0;
        public double accelalation_ = 0.0;

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
                return "PhyMAP RigidBodyType";
            }
        }

        public string TypeName
        {
            get
            {
                return "RigidBodyType";
            }
        }

        public bool CastFrom(object source)
        {
            var test = source as PhyMAPRigidBodyType;
            return test != null;
        }

        public bool CastTo<T>(out T target)
        {
            target = (T)Activator.CreateInstance(typeof(T));
            return true;
        }

        public IGH_Goo Duplicate()
        {
            var goo = new PhyMAPRigidBodyType()
            {
                direction_ = new Vector3d(this.direction_),
                velocity_ = this.velocity_,
                accelalation_ = this.accelalation_
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
