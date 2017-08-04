using System.Collections.Generic;
using PhyMAP.Net;
using PhyMAPComponent.Model;
using Rhino.Geometry;
using RhinoToOgre;

namespace PhyMAPComponent.Logic
{
    class TransferStaticRigidBody : AbstractTransfer
    {
        internal void AddStaticRigidBody(ref int body_index, Session session, List<PhyMAPStaticRigidBodyType> static_rigid_bodies)
        {
            for (int i = 0; i < static_rigid_bodies.Count; i++)
            {
                StaticRigidBodyWrapper rigidw = new StaticRigidBodyWrapper();

                List<Mesh> meshes = CreateMesh(static_rigid_bodies[i].breps_);

                if (!CheckMesh(meshes))
                {
                    continue;
                }
                if (!SetMeshes(rigidw, meshes))
                {
                    continue;
                }

                AddRigidBody(i + body_index, rigidw, session);
            }
            
            body_index += static_rigid_bodies.Count;
        }
        protected override void AddRigidBody(int i, RigidBodyWrapper w, Session session)
        {
            if (session.addRigidBody(i, w))
            {
                RhinoLogger.ErrorFormat("Brep {0} : addRigidBody() failure.", i);
            }
        }
    }
}
