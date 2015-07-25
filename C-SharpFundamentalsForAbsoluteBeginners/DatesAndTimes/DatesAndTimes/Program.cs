using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DatesAndTimes
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime myValue = DateTime.Now;
            //Console.WriteLine(myValue);
            DateTime birthDay = DateTime.Parse("7/14/1990");
            
            Console.WriteLine(myValue.Subtract(birthDay).TotalDays);
            
            Console.ReadLine();
        }
    }
}
