using System;
using Grasshopper.Kernel;
using Rhino.Geometry;
using PhyMAPComponent.Model;
using Grasshopper.Kernel.Data;
using System.Collections.Generic;
using PhyMAPComponent.Properties;

namespace ToolStudio
{
    public class PhyMAPRigidBodyComponent : GH_Component
    {
        /// <summary>
        /// Each implementation of GH_Component must provide a public 
        /// constructor without any arguments.
        /// Category represents the Tab in which the component will appear, 
        /// Subcategory the panel. If you use non-existing tab or panel names, 
        /// new tabs/panels will automatically be created.
        /// </summary>
        public PhyMAPRigidBodyComponent()
          : base("Rigid Body", "RigidBody",
              "",
              "PhyMAP", "Physics")
        {
        }

        /// <summary>
        /// Registers all the input parameters for this component.
        /// </summary>
        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            // Use the pManager object to register your input parameters.
            // You can often supply default values when creating parameters.
            // All parameters must have the correct access type. If you want 
            // to import lists or trees of values, modify the ParamAccess flag.
            pManager.AddBrepParameter("Brep", "BRP", "Brep List", GH_ParamAccess.list);

            var mec_param = new PhyMAPMechanicalPropertyParam("MechanicalProperty", "Mec", "Mechanical Prop", /*category*/"", /*sub category*/"", GH_ParamAccess.item);
            var mec_index = pManager.AddParameter(mec_param);
            pManager[mec_index].Optional = true;

            var motion_param = new PhyMAPMotionPropertyParam("MotionProperty", "Mot", "Mechanical Prop", /*category*/"", /*sub category*/"", GH_ParamAccess.item);
            var motion_index = pManager.AddParameter(motion_param);
            pManager[motion_index].Optional = true;

            // If you want to change properties of certain parameters, 
            // you can use the pManager instance to access them by index:
            //pManager[0].Optional = true;
        }

        /// <summary>
        /// Registers all the output parameters for this component.
        /// </summary>
        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {
            // Use the pManager object to register your output parameters.
            // Output parameters do not have default values, but they too must have the correct access type.

            // Sometimes you want to hide a specific parameter from the Rhino preview.
            // You can use the HideParameter() method as a quick way:
            //pManager.HideParameter(0);
            PhyMAPRigidBodyParam p = new PhyMAPRigidBodyParam("RigidBydy", "RB", "Rigid Body", /*category*/"", /*sub category*/"", GH_ParamAccess.item);
            pManager.AddParameter(p);
        }

        /// <summary>
        /// This is the method that actually does the work.
        /// </summary>
        /// <param name="DA">The DA object can be used to retrieve data from input parameters and 
        /// to store data in output parameters.</param>
        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // First, we need to retrieve all data from the input parameters.
            // We'll start by declaring variables and assigning them starting values.
            List<Brep> breps = new List<Brep>();
            PhyMAPMechanicalPropertyType mec_prop = new PhyMAPMechanicalPropertyType();
            PhyMAPMotionPropertyType motion_prop = new PhyMAPMotionPropertyType();

            if (!DA.GetDataList<Brep>(0, breps)) return;
            DA.GetData<PhyMAPMechanicalPropertyType>(1,ref mec_prop);
            DA.GetData<PhyMAPMotionPropertyType>(2,ref motion_prop);

            if (breps == null) return;

            var rigid_body = new PhyMAPRigidBodyType()
            {
                breps_ = breps,
                mechanical_property_ = mec_prop,
                motion_property_ = motion_prop,
            };
            //p.AddVolatileData(new GH_Path(0), 0, rigidtype);

            // Finally assign the spiral to the output parameter.
            DA.SetData(0, rigid_body);
        }


        /// <summary>
        /// The Exposure property controls where in the panel a component icon 
        /// will appear. There are seven possible locations (primary to septenary), 
        /// each of which can be combined with the GH_Exposure.obscure flag, which 
        /// ensures the component will only be visible on panel dropdowns.
        /// </summary>
        public override GH_Exposure Exposure
        {
            get { return GH_Exposure.primary; }
        }

        /// <summary>
        /// Provides an Icon for every component that will be visible in the User Interface.
        /// Icons need to be 24x24 pixels.
        /// </summary>
        protected override System.Drawing.Bitmap Icon
        {
            get
            {
                // You can add image files to your project resources and access them like this:
                //return Resources.IconForThisComponent;
                return Resources.PhyMAPRigidBody;
            }
        }

        /// <summary>
        /// Each component must have a unique Guid to identify it. 
        /// It is vital this Guid doesn't change otherwise old ghx files 
        /// that use the old ID will partially fail during loading.
        /// </summary>
        public override Guid ComponentGuid
        {
            get { return new Guid("0DA24CAF-4B1C-4B0E-841E-88DE09572724"); }
        }
    }
}
