using PhyMAPComponent.Model;
using System.Collections.Generic;
using PhyMAP.Net;

namespace PhyMAPComponent.Logic
{
    class ShapeBuilder
    {
        int body_index = 0;
        List<PhyMAPRigidBodyType> rigid_bodies = new List<PhyMAPRigidBodyType>();
        List<PhyMAPStaticRigidBodyType> static_rigid_bodies = new List<PhyMAPStaticRigidBodyType>();

        public bool IsRunnable()
        {
            return rigid_bodies.Count > 0;
        }

        public List<PhyMAPRigidBodyType> Rigid_bodies
        {
            get
            {
                return rigid_bodies;
            }

            set
            {
                rigid_bodies = value;
            }
        }

        public List<PhyMAPStaticRigidBodyType> Static_rigid_bodies
        {
            get
            {
                return static_rigid_bodies;
            }

            set
            {
                static_rigid_bodies = value;
            }
        }

        public void Initialize()
        {
            Rigid_bodies.Clear();
            Static_rigid_bodies.Clear();
        }
        public void DeInitialize()
        {
            Rigid_bodies.Clear();
            Static_rigid_bodies.Clear();
        }

        internal void AddShape(Session session)
        {
            body_index = 0;
            new TransferRigidBody().AddRigidBody(ref body_index, session, rigid_bodies);
            new TransferStaticRigidBody().AddStaticRigidBody(ref body_index, session, static_rigid_bodies);
        }
    }
}
