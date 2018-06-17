using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    class Program
    {
        static void Main(string[] args)
        {
            BahamasEngine engine = new BahamasEngine();
            engine.Execute();

            Console.ReadKey();
        }
    }
}
