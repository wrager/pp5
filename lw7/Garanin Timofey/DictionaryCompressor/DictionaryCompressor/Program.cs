using System;

namespace DictionaryCompressor
{
    class Program
    {

        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("Usage program.exe <input_file.txt> <output_file.txt>");
                return;
            }
            Application app = new Application(new IOManager(args[0], args[1]));
            app.ProcessFile();
            app.OutputResultsInFile();
            Console.WriteLine("Results output in file");
        }
    }
}
