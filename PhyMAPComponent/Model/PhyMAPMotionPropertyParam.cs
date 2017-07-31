using Grasshopper.Kernel;
using System;
using Rhino.Geometry;

namespace PhyMAPComponent.Model
{
    public class PhyMAPMotionPropertyParam : GH_Param<PhyMAPMotionPropertyType>, IGH_Param
    {
        public PhyMAPMotionPropertyParam(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) 
            : base(name, nickname, description, category, subcategory, access)
        { } 

        public PhyMAPMotionPropertyParam(IGH_InstanceDescription tag) : base(tag) { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("DC7C597A-755B-4AD3-A471-CE484500844F");
            }
        }
    }
}
