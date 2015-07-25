using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleClasses
{
    class Program
    {
        static void Main(string[] args)
        {
            Car myCar = new Car();
            myCar.Make = "Slim";
            myCar.Model = "Porsche";
            myCar.Year = 2016;
            myCar.Color = "Blue";

            Console.WriteLine("{0} - {1} - {2} - {3} Color",
                myCar.Make,
                myCar.Model,
                myCar.Year,
                myCar.Color);
            Console.WriteLine("Market Value - {0:C}", myCar.determineMarketValue());
            Console.ReadLine();
        }
    }

    class Car
    {
        public string Make { get; set; }
        public string Model { get; set; }
        public int Year { get; set; }
        public string Color { get; set; }

        public double determineMarketValue() { 
            double carValue = 100.0;
            if (this.Year < 2000) {
                carValue = 1000;
            }
            return carValue;
        }
    }
}
