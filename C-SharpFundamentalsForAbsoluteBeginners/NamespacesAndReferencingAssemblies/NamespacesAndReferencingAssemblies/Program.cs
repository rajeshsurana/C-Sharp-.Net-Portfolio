using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tabor;

namespace NamespacesAndReferencingAssemblies
{
    class Program
    {
        static void Main(string[] args)
        {
            //StreamReader myStreamReader = new StreamReader();
            Bob bob = new Bob();
            string html = bob.Lookup("http://www.google.com");
            Console.WriteLine(html);
            Console.ReadLine();
        }
    }
}
