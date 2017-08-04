﻿using System;
using System.Collections.Generic;

using Grasshopper.Kernel;
using Rhino.Geometry;
using PhyMAPComponent.Model;
using System.Threading;
using Rhino;
using RhinoToOgre;
using PhyMAP.Net;
using System.Collections;
using PhyMAPComponent.Logic;
using PhyMAPComponent.Properties;
using System.Windows.Forms;

namespace PhyMAPComponent
{
    public class PhyMAPWorldComponent : GH_Component
    {
        private bool debug = true;
        private ShapeBuilder shape_builder = new ShapeBuilder();

        // CLR objects
        private Session session = null;
        private SolverInformationWrapper info = null;

        // output meshes
        List<Mesh> session_meshes = new List<Mesh>();

        EventHandler DebugSimulationClick;
        EventHandler RunSimulationClick;
        EventHandler PauseSimulationClick;
        private ToolStripMenuItem mnuDebugSimulation = null;
        private ToolStripMenuItem mnuRunSimulation = null;
        private ToolStripMenuItem mnuPauseSimulation = null;

        /// <summary>
        /// Each implementation of GH_Component must provide a public 
        /// constructor without any arguments.
        /// Category represents the Tab in which the component will appear, 
        /// Subcategory the panel. If you use non-existing tab or panel names, 
        /// new tabs/panels will automatically be created.
        /// </summary>
        public PhyMAPWorldComponent()
          : base("PhysicsWorld", "Phyisics World",
              "",
              "PhyMAP", "Physics")
        {
            DebugSimulationClick += new EventHandler(DebugSimulationClickEventHander);
            RunSimulationClick += new EventHandler(RunSimulationClickEventHander);
            PauseSimulationClick += new EventHandler(PauseSimulationClickEventHander);
        }

        private void SetLogLevel(bool d)
        {
            if (d)
            {
                RhinoLogger.CurrentLogLevel = LogLevel.Debug;
            }
            else
            {
                RhinoLogger.CurrentLogLevel = LogLevel.Info;
            }
        }

        /// <summary>
        /// Registers all the input parameters for this component.
        /// </summary>
        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            pManager.AddNumberParameter("Time Step", "TS", "Time Steps(sec)", GH_ParamAccess.item, 0.1);
            pManager.AddNumberParameter("Simulation Duration", "DU", "Simulation Dulation(sec)", GH_ParamAccess.item, 5);
            pManager.AddVectorParameter("Gravity", "G", "Gravity Vector.", GH_ParamAccess.item, new Vector3d(0, 0, -9.8));

            PhyMAPRigidBodyParam p1 = new PhyMAPRigidBodyParam("RigidBydy", "RB", "Rigid Body", /*category*/"", /*sub category*/"", GH_ParamAccess.list);
            pManager.AddParameter(p1);

            PhyMAPStaticRigidBodyParam p2 = new PhyMAPStaticRigidBodyParam("StaticRigidBydy", "SR", "Static Rigid Body", /*category*/"", /*sub category*/"", GH_ParamAccess.list);
            var index_p2 = pManager.AddParameter(p2);
            pManager[index_p2].Optional = true;
        }

        /// <summary>
        /// Registers all the output parameters for this component.
        /// </summary>
        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {
            pManager.AddMeshParameter("ResultMesh", "M", "Result Meshes", GH_ParamAccess.list);
            pManager.AddNumberParameter("Elapsed Time", "E", "Erapsed Time", GH_ParamAccess.item);
        }

        /// <summary>
        /// This is the method that actually does the work.
        /// </summary>
        /// <param name="DA">The DA object can be used to retrieve data from input parameters and 
        /// to store data in output parameters.</param>
        protected override void SolveInstance(IGH_DataAccess DA)
        {
            shape_builder.Initialize();
            double time_step = 0.1f;
            double simulation_duration = 5.0;
            Vector3d gravity = new Vector3d(0, 0, -9.8);

            if (!DA.GetData(0, ref time_step)) return;
            if (!DA.GetData(1, ref simulation_duration)) return;
            if (!DA.GetData(2, ref gravity)) return;
            if (!DA.GetDataList<PhyMAPRigidBodyType>(3, shape_builder.Rigid_bodies)) return;
            DA.GetDataList<PhyMAPStaticRigidBodyType>(4, shape_builder.Static_rigid_bodies);

            // build args
            info = new SolverInformationWrapper(debug, Convert.ToSingle(time_step), simulation_duration, gravity);
            BuildSession();

            DA.SetDataList(0, session_meshes);
            DA.SetData(1, 1.0);
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
                return Resources.PhyMAPWorld;
            }
        }

        /// <summary>
        /// Each component must have a unique Guid to identify it. 
        /// It is vital this Guid doesn't change otherwise old ghx files 
        /// that use the old ID will partially fail during loading.
        /// </summary>
        public override Guid ComponentGuid
        {
            get { return new Guid("417d072a-2cbe-4bd7-9a03-60beb4192a58"); }
        }

        private void BuildSession()
        {
            session_meshes.Clear();

            // log level
            SetLogLevel(info.getInfo().Item1);

            session = new PhyMAP.Net.Session(info);

            InitializeSession();

            AddShape();

            BuildSessionMeshes();

            session.acceptUpdate(true);
        }

        private void BuildSessionMeshes()
        {
            foreach (var rb in session.getRigidBodies().Values)
            {
                session_meshes.AddRange(rb.meshes_);
            }
        }
        protected override void AfterSolveInstance()
        {

            base.AfterSolveInstance();
        }

        private bool ValidateRunCondition()
        {
            if (session == null)
            {
                RhinoLogger.Fatal("no session.");
                return false;
            }

            if (!shape_builder.IsRunnable())
            {
                RhinoLogger.Warn("no shape.");
                return false;
            }

            return true;
        }

        private void AddShape()
        {
            shape_builder.AddShape(session);
        }

        private void DeinitializeSession()
        {
            if (session != null)
            {
                session.acceptUpdate(false);
                session.deinitialize();
                session = null;
            }
        }

        private void SleepSession()
        {
            Thread.Sleep(1);
        }

        private void UpdateSession()
        {
            if (session != null)
            {
                session.update(info.getInfo().Item2);
                RhinoDoc.ActiveDoc.Views.Redraw();
            }
        }

        private void InitializeSession()
        {
            RhinoLogger.Info("start session initialize.");
            session.initialize();
        }

        public override void ComputeData()
        {
            base.ComputeData();
        }
        public override BoundingBox ClippingBox
        {
            get
            {
                return base.ClippingBox;
            }
        }

        public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
        {
            base.AppendAdditionalMenuItems(menu);

            mnuRunSimulation = Menu_AppendItem(menu, "Run PyMAP", RunSimulationClick, true, false);
            mnuPauseSimulation = Menu_AppendItem(menu, "Pause PyMAP", PauseSimulationClick, true, false);
            Menu_AppendSeparator(menu);
            mnuDebugSimulation = Menu_AppendItem(menu, "Debug PyMAP", DebugSimulationClick, true, debug);
        }
        private void DebugSimulationClickEventHander(object sender, EventArgs e)
        {
            debug = !mnuDebugSimulation.Checked;
            if(debug)
            {
                mnuDebugSimulation.CheckState = CheckState.Checked;
            }
            else
            {
                mnuDebugSimulation.CheckState = CheckState.Unchecked;
            }
        }

        private void RunSimulationClickEventHander(object sender, EventArgs e)
        {
            try
            {
                mnuRunSimulation.Checked = true;
                mnuRunSimulation.Enabled = false;
                mnuPauseSimulation.Checked = false;

                if (!ValidateRunCondition()) return;

                double total_duration = 0;
                while (true)
                {
                    UpdateSession();

                    SleepSession();

                    total_duration += info.getInfo().Item2;
                    if (total_duration > info.getInfo().Item3)
                    {
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                RhinoLogger.Fatal(ex.Message);
            }
            finally
            {
                DeinitializeSession();
                mnuRunSimulation.Checked = false;
                mnuRunSimulation.Enabled = true;
                mnuPauseSimulation.Checked = false;
            }
        }
        private void PauseSimulationClickEventHander(object sender, EventArgs e)
        {
            mnuPauseSimulation.Checked = !mnuPauseSimulation.Checked;
        }
    }
}
