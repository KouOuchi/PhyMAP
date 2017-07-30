using Grasshopper.Kernel;
using System;
using Rhino.Geometry;

namespace PhyMAPComponent.Model
{
    public class PhyMAPRigidBodyParam : GH_Param<PhyMAPRigidBodyType>, IGH_Param
    {
        public PhyMAPRigidBodyParam(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) 
            : base(name, nickname, description, category, subcategory, access)
        { } 

        public PhyMAPRigidBodyParam(IGH_InstanceDescription tag) : base(tag) { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("A97E9B91-C923-43BB-A73B-D4F228292252");
            }
        }
    }
}
