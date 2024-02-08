using System;
using System.IO;
using System.Collections.Generic;

namespace IronShrimp
{
    class Program
    {
        private static DatabaseWriter writer;
        private static List<Datx> filesToProcess = new List<Datx>();

        static void Main(string[] args)
        {
            Console.WriteLine("Connecting to database...");

            // TODO: get better password storage and make more fine-graned roles
            //writer = new DatabaseWriter("Server=localhost;Port=5432;User Id=postgres;Password=1wants2cut2theFeeling;Database=ironshrimp;");

            Console.WriteLine("Connected.");

            Console.WriteLine("Enter 'xx' to exit. Provide datx file path to process one or directory with datx files to process all within.");
            string line;
            while ((line = Console.ReadLine()) != "xx")
            {
                filesToProcess.Clear();
                Program.ProcessUserInput(line);

                if (filesToProcess.Count > 0)
                {
                    DeterministicDetection rulesBasedDetection = new DeterministicDetection(filesToProcess);
                    // then process whatever's in filesToProcess
                }

                Console.WriteLine("\n\nEnter 'xx' to exit. Type datx file path to process another file.");
            }
        }

        private static void ProcessUserInput(string input)
        {
            if (!File.Exists(input))
            {
                if (Directory.Exists(input))
                {
                    string[] files = Directory.GetFiles(input);
                    foreach (string file in files)
                    {
                        ProcessUserInput(file);
                    }
                    string[] directories = Directory.GetDirectories(input);
                    foreach (string folder in directories)
                    {
                        ProcessUserInput(folder);
                    }
                }
                else
                {
                    Console.WriteLine(String.Format("Path was invalid: {0}", input));
                }
            }
            else
            {
                SingleFileAddToProcessQueue(input);
            }
        }

        private static void SingleFileAddToProcessQueue(string pathToSingleDatx)
        {
            if (Path.GetExtension(pathToSingleDatx) == ".datx")
            {
                Console.WriteLine(String.Format("Processing {0}...", pathToSingleDatx));
                Datx datxFileData = ParseFileName(pathToSingleDatx);
                filesToProcess.Add(datxFileData);

                //writer.InsertDatxFile(datxFileData);
            }
            else
            {
                Console.WriteLine(String.Format("File extension was invalid: {0}", pathToSingleDatx));
            }
        }

        private static Datx ParseFileName(string pathToSingleDatx)
        {
            string strippedFileName = Path.GetFileNameWithoutExtension(pathToSingleDatx);
            string[] explodedFileName = strippedFileName.Split('_');
            int ionSource;
            int.TryParse(explodedFileName[2].Substring(explodedFileName[2].Length - 1), out ionSource);
            Datx.ScanTypes type;
            Enum.TryParse<Datx.ScanTypes>(explodedFileName[2].Substring(0, explodedFileName[2].Length - 1), out type);

            return new Datx()
            {
                Filepath = pathToSingleDatx,
                Filename = strippedFileName,
                Concentration = explodedFileName[0],
                Iteration = explodedFileName[1],
                ScanType = type,
                IonSourceIndex = ionSource
            };
        }
    }
}
