using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Strings
{
    class Program
    {
        static void Main(string[] args)
        {
            //string myString = "\"Hello World!\"";
            //string myString = string.Format("{0}!", "Hello");
            //string myString = string.Format("{0:C}", 123.78); 
            //string myString = string.Format("{0:N}", 0123456789);
            //string myString = string.Format("{0: (###) ### - ####}", 1234567890);
            //StringBuilder myString = new StringBuilder();
            //for (int i = 0; i < 100; i++)
            //{
            //    myString.Append("--");
            //    myString.Append(i);
            //}
            //string lmyString = string.Format("{2} - {3}", "3", "4", "5");
            string myString = " It was really a sunny day! ";
            myString = myString.Trim().ToUpper().Length.ToString();
            Console.WriteLine(myString);
            Console.ReadLine();
        }
    }
}
