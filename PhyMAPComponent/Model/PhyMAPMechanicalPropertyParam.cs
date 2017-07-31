using Grasshopper.Kernel;
using System;
using Rhino.Geometry;

namespace PhyMAPComponent.Model
{
    public class PhyMAPMechanicalPropertyParam : GH_Param<PhyMAPRigidBodyType>, IGH_Param
    {
        public PhyMAPMechanicalPropertyParam(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) 
            : base(name, nickname, description, category, subcategory, access)
        { } 

        public PhyMAPMechanicalPropertyParam(IGH_InstanceDescription tag) : base(tag) { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("9C1D35DA-4125-4340-AC69-9288A9A1B762");
            }
        }
    }
}
