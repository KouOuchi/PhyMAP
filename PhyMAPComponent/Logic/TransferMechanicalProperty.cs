using System;
using PhyMAP.Net;
using PhyMAPComponent.Model;

namespace PhyMAPComponent.Logic
{
    internal class TransferMechanicalProperty
    {
        public TransferMechanicalProperty()
        {
        }

        internal MechanicalPropertyWrapper Create(PhyMAPMechanicalPropertyType mechanical_prop)
        {
            return new MechanicalPropertyWrapper(
                mechanical_prop.gravity_point_,
                mechanical_prop.mass_
                );
        }
    }
}