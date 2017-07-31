using System;
using GH_IO.Serialization;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;
using System.Collections.Generic;

namespace PhyMAPComponent.Model
{
    public class PhyMAPMechanicalPropertyType : IGH_Goo
    {
        public Vector3d gravity_point_ = Vector3d.Zero;
        public double mass_ = 1.0;

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
                return "PhyMAP MechanicalPropertyType";
            }
        }

        public string TypeName
        {
            get
            {
                return "MechanicalPropertyType";
            }
        }

        public bool CastFrom(object source)
        {
            var test = source as PhyMAPMechanicalPropertyType;
            return test != null;
        }

        public bool CastTo<T>(out T target)
        {
            target = (T)Activator.CreateInstance(typeof(T));
            return true;
        }

        public IGH_Goo Duplicate()
        {
            var goo = new PhyMAPMechanicalPropertyType()
            {
                gravity_point_ = new Vector3d(this.gravity_point_),
                mass_ = this.mass_
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
