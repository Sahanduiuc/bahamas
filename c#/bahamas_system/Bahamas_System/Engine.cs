using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using bahamas_system.Bahamas_System.GE;

namespace bahamas_system.Bahamas_System
{
    public class Engine
    {
        private GESystem geSystem;

        public Engine()
        {
            geSystem = new GESystem(0.1,0.9,100,10,0);
            geSystem.Initiate();
        }
    }
}
