using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

using AdvionData_NET;

namespace IronShrimp
{
    class DeterministicDetection : DetectionAlgorithm
    {
        // TODO: Maybe make a "DeterministicDetection" object for each compound, so the constructor might simply set
        // that up and the processing/output/etc. happen in a later step.
        public DeterministicDetection(List<Datx> files)
        {
            // TODO: Use a Path that the User might be able to access
            //string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string outputFilePath = String.Format("../Data/Results/{0}.tsv", DateTime.Now.ToString("yyyy_MM_dd-hh_mm_ss"));
            using (StreamWriter outputFile = new StreamWriter(outputFilePath))
            {
                // TODO: Use a proper CSV writer to avoid ugly tabbing problems
                outputFile.WriteAsync(String.Format("{0}", DateTime.Now));
                outputFile.WriteAsync("\nRules Applied:");
                outputFile.WriteAsync("\n\tRDX\tI(257)/I(259)>3.13 AND I(257)>5.4e6");
                outputFile.WriteAsync(String.Format("\n\nfilename\t\tI({0})\t\tI({1})\t\tRatio({0}/{1})\tPass/Fail", 257, 259));
                outputFile.WriteAsync("\n------------------------------------------------------------");

                int positiveForRDX = 0;
                int negativeForRDX = 0;
                foreach (Datx file in files)
                {
                    // TODO: Make Range scans work
                    if (file.ScanType == Datx.ScanTypes.SIM)
                    {
                        DataReader datxReader = new DataReader(file.Filepath, false, false);
                        string lineToWriteToFile;

                        if (ProcessDataForRDX(file, datxReader, out lineToWriteToFile))
                        {
                            positiveForRDX++;
                        }
                        else
                        {
                            negativeForRDX++;
                        }
                        outputFile.WriteAsync("\n" + lineToWriteToFile);
                    }
                }

                float ratioPositive = (float)positiveForRDX / (float)files.Count;
                outputFile.WriteAsync("\n\n\nTotals:");
                string totals = String.Format("\n\tFiles: {0} \tPos(RDX): {1} \tNeg(RDX): {2} \tPct Pos(RDX): {3:P}\n", files.Count, positiveForRDX, negativeForRDX, ratioPositive);
                outputFile.WriteAsync(totals);
                Console.WriteLine("\nResults added to {0}", outputFilePath);
            }
        }

        // TODO: Abstract the "Ratio and single mass intensity threshold" ruleset to remove the "RDX" aspect and take in only a datx object, two masses, and a ratio
        public bool ProcessDataForRDX(Datx metadata, DataReader reader, out string outputLine)
        {
            outputLine = String.Format("{0}\t\t", metadata.Filename);
            Console.Write(String.Format("Analyzing {0}.datx for RDX --> ", metadata.Filename));
            //Console.WriteLine(String.Format("\tConcentration: {0}", metadata.Concentration));
            //Console.WriteLine(String.Format("\tIon Source index: {0}", metadata.IonSourceIndex));
            //Console.WriteLine(String.Format("\tIteration: {0}", metadata.Iteration));
            //Console.WriteLine(String.Format("\tScan Type: {0}", metadata.ScanType));
            //Console.WriteLine(String.Format("\tScan mode index: {0}", reader.getScanModeIndex()));

            // TODO: If we don't get data from these, bail out
            int numMasses = reader.getNumMasses(); // number of SIM masses or the "whole range"
            int numSpectra = reader.getNumSpectra(); // number of points in each XIC
            //Console.WriteLine(String.Format("Total spectra measured in file: {0}", numSpectra));

            float[] masses = new float[numMasses];
            reader.getMasses(masses);

            //float[] retentionTimes = new float[numSpectra];
            //reader.getRetentionTimes(retentionTimes);

            //Console.WriteLine(String.Format("The first and last masses scanned: {0} ...({1} other masses)... {2}", masses[0], (numMasses - 2), masses[numMasses - 1]));

            // The generateXIC method expects an int[] 
            int[] mass257Index = new int[1] { Array.IndexOf(masses, 257) };
            int[] mass259Index = new int[1] { Array.IndexOf(masses, 259) };

            float[] xic257 = new float[numSpectra];
            float[] xic259 = new float[numSpectra];

            // TODO: check error code being returned
            reader.generateXIC(mass257Index, 1, xic257);
            reader.generateXIC(mass259Index, 1, xic259);

            float maxIntensityOf257 = xic257.Max();
            float maxIntensityOf259 = xic259.Max();

            //Console.WriteLine(String.Format("Maximum intensity of mass 257: {0}", maxIntensityOf257));
            //Console.WriteLine(String.Format("Maximum intensity of mass 259: {0}", maxIntensityOf259));

            outputLine += String.Format("{0:e1}\t", maxIntensityOf257);
            outputLine += String.Format("{0:e1}\t", maxIntensityOf259);

            double ratioOfRelevantMasses = 0;
            if (maxIntensityOf259 != 0)
            {
                ratioOfRelevantMasses = maxIntensityOf257 / maxIntensityOf259;
                outputLine += String.Format("{0:F2}\t\t\t", ratioOfRelevantMasses);
                //Console.WriteLine(String.Format("Ideal Ratio of intensities 257/259 for positive RDX: 3.13 (2.83-3.43)"));
                //Console.WriteLine(String.Format("Measured Ratio of intensities 257/259 in dataset: {0}", ratioOfRelevantMasses.ToString("F2")));
            }
            else
            {
                outputLine += String.Format("0\t");
            }

            if (ratioOfRelevantMasses < 2.83 || ratioOfRelevantMasses > 3.43)
            {
                //Console.WriteLine(String.Format("Dataset falls outside the criteria based on the ratio."));
                Console.Write("(-) RDX\n");
                outputLine += "NEG";
                return false;
            }
            else
            {
                //Console.WriteLine(String.Format("Minimum threshold for Intensity at mass 257 to positively ID RDX: 5.4e6"));
                if (maxIntensityOf257 < (5.4e6))
                {
                    //Console.WriteLine(String.Format("Dataset falls outside the criteria based on the intensity at mass 257."));
                    Console.Write("(-) RDX\n");
                    outputLine += "NEG";
                    return false;
                }
                else
                {
                    //Console.WriteLine(String.Format("Dataset is within the criteria."));
                    Console.Write("(+) RDX\n");
                    outputLine += "POS";
                    return true;
                }
            }
        }

    }
}
