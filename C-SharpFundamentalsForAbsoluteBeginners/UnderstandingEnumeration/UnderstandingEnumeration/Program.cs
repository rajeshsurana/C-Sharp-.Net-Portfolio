using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnderstandingEnumeration
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter Superhero's name to see his nickname");
            string userValue = Console.ReadLine();
            SuperHero myHero;
            if (Enum.TryParse<SuperHero>(userValue, true, out myHero))
            {
                switch (myHero)
                {
                    case SuperHero.Batman:
                        Console.WriteLine("Caped Crusader");
                        break;
                    case SuperHero.Superman:
                        Console.WriteLine("Man of Steel");
                        break;
                    case SuperHero.GreenLantern:
                        Console.WriteLine("Emerald Knight");
                        break;
                    default:
                        break;
                }
            }
            else
            {
                Console.WriteLine("Does not Compute");
            }

            Console.ReadLine();
        }
    }
    enum SuperHero
    {
        Batman,
        Superman,
        GreenLantern
    }
}
