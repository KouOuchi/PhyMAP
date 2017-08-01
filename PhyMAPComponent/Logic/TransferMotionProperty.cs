using System;
using PhyMAP.Net;
using PhyMAPComponent.Model;

namespace PhyMAPComponent.Logic
{
    internal class TransferMotionProperty
    {
        public TransferMotionProperty()
        {
        }

        internal MotionPropertyWrapper Create(PhyMAPMotionPropertyType motion_prop)
        {
            return new MotionPropertyWrapper(
                motion_prop.local_inertia_);
        }
    }
}