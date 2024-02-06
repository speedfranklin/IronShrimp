using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AdvionData_NET;

using Npgsql;

namespace IronShrimp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Connecting to database...");

            // TODO: get better password storage and make more fine-graned roles
            DatabaseWriter writer = new DatabaseWriter("Server=localhost;Port=5432;User Id=postgres;Password=1wants2cut2theFeeling;Database=ironshrimp;");

            Console.WriteLine("Connected.");

            Console.WriteLine("Enter 'xx' to exit. Type datx file path to process.");
            string line;
            while ((line = Console.ReadLine()) != "xx")
            {
                if (File.Exists(line))
                {
                    if (Path.GetExtension(line) == ".datx")
                    {
                        Console.WriteLine(String.Format("Processing {0}...", line));

                        Datx datxFileData = new Datx()
                        {
                            Filepath = line,
                            Filename = Path.GetFileNameWithoutExtension(line)
                        };

                        DataReader dataReader = new DataReader(line, false, false);
                        Console.WriteLine(dataReader.getNumMasses());

                        if (writer.InsertDatxFile(datxFileData))
                        {
                            Console.WriteLine("Inserted Datx file into database.");
                        }
                        else
                        {
                            Console.WriteLine("Insert was not successful.");
                        }
                    }
                    else
                    {
                        Console.WriteLine(String.Format("File type was invalid: {0}", Path.GetExtension(line)));
                    }
                }
                else
                {
                    Console.WriteLine(String.Format("Path was invalid: {0}", line));
                }
                Console.WriteLine("\n\nEnter 'xx' to exit. Type datx file path to process another file.");
            }
        }
    }
}
