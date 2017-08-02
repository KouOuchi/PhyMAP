using PhyMAP.Net;
using PhyMAPComponent.Model;
using Rhino.Geometry;
using RhinoToOgre;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PhyMAPComponent.Logic
{
    abstract class AbstractTransfer
    {
        protected virtual List<Mesh> CreateMesh(List<Brep> breps)
        {
            List<Mesh> meshes = new List<Mesh>();
            foreach (var b in breps)
            {
                var ms = Rhino.Geometry.Mesh.CreateFromBrep(b);
                meshes.AddRange(ms);
            }

            return meshes;
        }
        protected virtual bool CheckMesh(List<Mesh> meshes)
        {
            if (meshes.Count == 0)
            {
                RhinoLogger.WarnFormat("no meshes. skipped");
                return false;
            }
            return true;
        }

        protected virtual bool SetMeshes(RigidBodyWrapper w, List<Mesh> meshes)
        {
            if (!w.setMeshes(meshes))
            {
                RhinoLogger.ErrorFormat("SetMeshes() failure.");
                return false;
            }
            return true;
        }

        protected virtual void AddRigidBody(int i, RigidBodyWrapper w, Session session)
        {
            if (session.addRigidBody(i, w))
            {
                RhinoLogger.ErrorFormat("Brep {0} : addRigidBody() failure.", i);
            }
        }
        protected virtual bool SetMechanicalProperty(RigidBodyWrapper w, PhyMAPMechanicalPropertyType mechanical_prop)
        {
            MechanicalPropertyWrapper mec_wrap = 
                new TransferMechanicalProperty().Create(mechanical_prop);

            if (!w.setMechanicalProperty(mec_wrap))
            {
                RhinoLogger.ErrorFormat("SetMechanicalProperty() failure.");
                return false;
            }
            return true;
        }

        protected virtual bool SetMotionProperty(RigidBodyWrapper w, PhyMAPMotionPropertyType motion_prop)
        {
            MotionPropertyWrapper motion_wrap = 
                new TransferMotionProperty().Create(motion_prop);

            if (!w.setMotionProperty(motion_wrap))
            {
                RhinoLogger.ErrorFormat("SetMotionProperty() failure.");
                return false;
            }
            return true;
        }

    }
}
