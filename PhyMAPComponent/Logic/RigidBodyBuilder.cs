using System.Collections.Generic;
using PhyMAP.Net;
using PhyMAPComponent.Model;
using RhinoToOgre;
using Rhino.Geometry;

namespace PhyMAPComponent.Logic
{
    class RigidBodyBuilder
    {
        internal void AddRigidBody(ref int body_index, Session session, List<PhyMAPRigidBodyType> rigid_bodies)
        {
            for (int i = 0; i < rigid_bodies.Count; i++)
            {
                RigidBodyWrapper rigidw = new RigidBodyWrapper();

                List<Mesh> meshes = new List<Mesh>();
                foreach(var b in rigid_bodies[i].breps_)
                {
                   var ms = Rhino.Geometry.Mesh.CreateFromBrep(b);
                    meshes.AddRange(ms);
                }

                var add_to_meshes = meshes;
                // check
                if (add_to_meshes.Count == 0)
                {
                    RhinoLogger.WarnFormat("Brep {0} : no meshes. skipped", i);
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

                // build transform
//                movew.setTransform();
//                rigidw.setTransform(Transform.Identity);

                // register
                session.addRigidBody(i + body_index, rigidw);
            }

            body_index += rigid_bodies.Count;
        }
    }
}
