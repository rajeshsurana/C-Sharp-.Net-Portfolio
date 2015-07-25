using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnderstandingInheritance
{
    class Program
    {
        static void Main(string[] args)
        {
            Car myCar = new Car();
            myCar.Make = "BMW";
            myCar.Model = "745li";
            myCar.Color = "Black";
            myCar.Year = 2005;
            printVehicleDetails(myCar);
            Console.ReadLine();
            
        }

        public static void printVehicleDetails(Vehicle vehicle) {
            Console.WriteLine("Here are the vehicle details: {0}", vehicle.formatMe());
        }
    }

    abstract class Vehicle
    {
        public string Make { get; set; }
        public string Model { get; set; }
        public int Year { get; set; }
        public string Color { get; set; }

        public abstract string formatMe();
    }

    class Car:Vehicle
    {
        public override string formatMe()
        {
            return String.Format("{0} - {1} - {2} - {3}",
                this.Make,
                this.Model,
                this.Year,
                this.Color);
        }
    }

    sealed class Truck : Vehicle {
        public int TowingCapacity { get; set; }

        public override string formatMe()
        {
            return String.Format("{0} - {1} - {2} Towing Units",
                this.Make,
                this.Model,
                this.TowingCapacity);
        }
    }
}
