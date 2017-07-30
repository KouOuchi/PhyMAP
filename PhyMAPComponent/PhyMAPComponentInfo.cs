using System;
using System.Drawing;
using Grasshopper.Kernel;

namespace PhyMAPComponent
{
    public class PhyMAPComponentInfo : GH_AssemblyInfo
    {
        public override string Name
        {
            get
            {
                return "PhyMAP";
            }
        }
        public override Bitmap Icon
        {
            get
            {
                //Return a 24x24 pixel bitmap to represent this GHA library.
                return null;
            }
        }
        public override string Description
        {
            get
            {
                //Return a short string describing the purpose of this GHA library.
                return "";
            }
        }
        public override Guid Id
        {
            get
            {
                return new Guid("ee2be1dc-533b-4437-84c2-fec9d75dce4e");
            }
        }

        public override string AuthorName
        {
            get
            {
                //Return a string identifying you or your company.
                return "Kou Ouchi";
            }
        }
        public override string AuthorContact
        {
            get
            {
                //Return a string representing your preferred contact details.
                return "kou.ouchi@division-engineering.com";
            }
        }
    }
}
