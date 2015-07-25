using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnderstandingArrays
{
    class Program
    {
        static void Main(string[] args)
        {
            //int[] numbers = new int[5];
            //numbers[0] = 5;
            //numbers[1] = 8;
            //int[] numbers = new int[] {1, 2, 3, 4, 5};
            //Console.WriteLine(numbers[4].ToString());
            /*
             * string[] names = new string[] { "David", "Elex", "Ron", "Trever" };
            foreach (string name in names)
            {
                Console.WriteLine(name);
            }
            Console.ReadLine();
             */
            string str = "This is a really long sentence so, " + 
                "cut in half";
            char[] strChar = str.ToCharArray();

            Array.Reverse(strChar);
            foreach (char c in strChar)
            {
                Console.Write(c);
            }
            Console.ReadLine();
        }
    }
}
