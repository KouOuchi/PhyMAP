using System;
using Grasshopper.Kernel;
using Rhino.Geometry;
using PhyMAPComponent.Model;
using Grasshopper.Kernel.Data;
using System.Collections.Generic;
using PhyMAPComponent.Properties;

namespace ToolStudio
{
    public class RigidBodyComponent : GH_Component
    {
        /// <summary>
        /// Each implementation of GH_Component must provide a public 
        /// constructor without any arguments.
        /// Category represents the Tab in which the component will appear, 
        /// Subcategory the panel. If you use non-existing tab or panel names, 
        /// new tabs/panels will automatically be created.
        /// </summary>
        public RigidBodyComponent()
          : base("Mechanical Property", "Mechanical Prop",
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

            pManager.AddBrepParameter("Brep", "B", "Brep List", GH_ParamAccess.list);
            pManager.AddVectorParameter("Direction", "D", "Direction Vector", GH_ParamAccess.item, Vector3d.Zero);
            pManager.AddNumberParameter("Velocity", "V", "Verlocity", GH_ParamAccess.item, 0.0);
            pManager.AddNumberParameter("Acceleration", "A", "Acceleration", GH_ParamAccess.item, 0.0);
            // If you want to change properties of certain parameters, 
            // you can use the pManager instance to access them by index:
            //pManager[0].Optional = true;
            pManager[1].Optional = true;
            pManager[2].Optional = true;
            pManager[3].Optional = true;
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
            Vector3d direction = Vector3d.Zero;
            double velocity = 0.0;
            double accelalation = 0.0;

            if (!DA.GetDataList<Brep>(0, breps)) return;
            if (!DA.GetData(1, ref direction)) return;
            if (!DA.GetData(2, ref velocity)) return;
            if (!DA.GetData(3, ref accelalation)) return;

            if (breps == null) return;

            var rigid_body = new PhyMAPRigidBodyType()
            {
                breps_ = breps,
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
                return Resources.PhyMAPMechanicalProperty;
            }
        }

        /// <summary>
        /// Each component must have a unique Guid to identify it. 
        /// It is vital this Guid doesn't change otherwise old ghx files 
        /// that use the old ID will partially fail during loading.
        /// </summary>
        public override Guid ComponentGuid
        {
            get { return new Guid("D7999F21-7FC8-4C0B-9830-33622A4B8592"); }
        }
    }
}
