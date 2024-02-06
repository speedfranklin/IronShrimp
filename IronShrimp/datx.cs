using System.IO;

namespace IronShrimp
{
    public class Datx
    {
        public string Description
        {
            get; set;
        }

        public float Concentration
        {
            get; set;
        }

        public string Filename
        {
            get; set;
        }

        public string Filepath
        {
            get; set;
        }

        public string EscapedFilePath
        {
            get
            {
                return this.Filepath.Replace(@"\", @"\\");
            }
        }

        public SampleTypes SampleType
        {
            get; set;
        }

        public enum SampleTypes
        {
            Blank,
            Unknown,
            QC,
            Cal
        }
    }
}