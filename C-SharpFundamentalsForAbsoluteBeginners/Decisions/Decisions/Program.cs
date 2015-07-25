using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Decisions
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter your options - 1, 2, 3:");
            string userValue = Console.ReadLine();

            string message = (userValue == "1") ? "boat" : "cat";
            Console.WriteLine("You got {0}", message);
            Console.ReadLine();
        }
    }
}
