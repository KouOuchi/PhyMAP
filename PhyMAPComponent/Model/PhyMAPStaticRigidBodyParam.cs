using Grasshopper.Kernel;
using System;
using Rhino.Geometry;

namespace PhyMAPComponent.Model
{
    public class PhyMAPStaticRigidBodyParam : GH_Param<PhyMAPStaticRigidBodyType>, IGH_Param
    {
        public PhyMAPStaticRigidBodyParam(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) 
            : base(name, nickname, description, category, subcategory, access)
        { } 

        public PhyMAPStaticRigidBodyParam(IGH_InstanceDescription tag) : base(tag) { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("0F5FCDED-FDC4-4ACE-835B-F822CF8A002B");
            }
        }
    }
}
