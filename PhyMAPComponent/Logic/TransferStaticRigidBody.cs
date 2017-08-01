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
                RigidBodyWrapper rigidw = new RigidBodyWrapper();

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
    }
}
