using System.Collections.Generic;
using PhyMAP.Net;
using PhyMAPComponent.Model;
using RhinoToOgre;
using Rhino.Geometry;
using System;

namespace PhyMAPComponent.Logic
{
    class TransferRigidBody : AbstractTransfer
    {
        public void AddRigidBody(ref int body_index, Session session, List<PhyMAPRigidBodyType> rigid_bodies)
        {
            for (int i = 0; i < rigid_bodies.Count; i++)
            {
                RigidBodyWrapper rigidw = new RigidBodyWrapper();

                var meshes = CreateMesh(rigid_bodies[i].breps_);

                if (!CheckMesh(meshes))
                {
                    continue;
                }
                if (!SetMeshes(rigidw, meshes))
                {
                    continue;
                }
                if (!SetMotionProperty(rigidw, rigid_bodies[i].motion_property_))
                {
                    continue;
                }
                if(!SetMechanicalProperty(rigidw, rigid_bodies[i].mechanical_property_))
                {
                    continue;
                }

                AddRigidBody(i + body_index, rigidw, session);
            }

            body_index += rigid_bodies.Count;
        }

    }
}
