using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnderstandingLINQ
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Car> myCars = new List<Car>() {
                new Car() { Make = "BMW", Model= "550i", Color=CarColor.Blue, StickerPrice=55000, Year=2009},
                new Car() { Make="Toyota", Model="4Runner", Color=CarColor.White, StickerPrice=35000, Year=2010},
                new Car() { Make="BMW", Model = "745li", Color=CarColor.Black, StickerPrice=75000, Year=2008},
                new Car() {Make="Ford", Model="Escape", Color=CarColor.White, StickerPrice=25000, Year=2008},
                new Car() {Make="BMW", Model="55i", Color=CarColor.Black, StickerPrice=57000, Year=2010}
            };

            /*var bmws = from car in myCars
                       where car.Make == "BMW"
                       && car.Year == 2010
                       select car;*/
            /*var bmws = from car in myCars
                       orderby car.Year ascending
                       select car;*/
            /*var bmws = myCars.Where(p=> p.Make == "BMW").Where(p => p.Year == 2010);*/
            /*var bmws = myCars.OrderByDescending(p => p.Year);

            foreach (var car in bmws)
                Console.WriteLine("{0} - {1} - {2}", car.Make, car.Model, car.Year);*/


            Console.ReadLine();
        }
    }

    class Car
    {
        public string Make { get; set; }
        public string Model { get; set; }
        public int Year { get; set; }
        public double StickerPrice { get; set; }
        public CarColor Color { get; set; }
    }

    enum CarColor
    {
        White,
        Black,
        Red,
        Blue,
        Yellow
    }

}
