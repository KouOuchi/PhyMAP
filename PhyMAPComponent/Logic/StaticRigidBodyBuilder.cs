using System.Collections.Generic;
using PhyMAP.Net;
using PhyMAPComponent.Model;
using Rhino.Geometry;
using RhinoToOgre;

namespace PhyMAPComponent.Logic
{
    class StaticRigidBodyBuilder
    {
        internal void AddStaticRigidBody(ref int body_index, Session session, List<PhyMAPStaticRigidBodyType> static_rigid_bodies)
        {
            for (int i = 0; i < static_rigid_bodies.Count; i++)
            {
                RigidBodyWrapper rigidw = new RigidBodyWrapper();

                List<Mesh> meshes = new List<Mesh>();
                foreach(var b in static_rigid_bodies[i].breps_)
                {
                   var ms = Rhino.Geometry.Mesh.CreateFromBrep(b);
                    meshes.AddRange(ms);
                }

                var add_to_meshes = meshes;
                // check
                if (add_to_meshes.Count == 0)
                {
                    continue;
                }
                else
                { 
                    if(!rigidw.setMeshes(add_to_meshes))
                    {
                        RhinoLogger.ErrorFormat("Brep {0} : setMeshes() failure.", i);
                        continue;
                    }
                }

                // register
                session.addStaticRigidBody(i + body_index, rigidw);
            }
            
            body_index += static_rigid_bodies.Count;
        }
    }
}
