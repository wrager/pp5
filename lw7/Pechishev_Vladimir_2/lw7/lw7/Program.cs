using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace app
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Invalid arguments count");
                return;
            }
            try
            {
                CApplication application = new CApplication(args[0]);
                application.SortArray();
            }
            catch (Exception except)
            {
                Console.WriteLine(except.ToString());
            }
        }
    }
}
