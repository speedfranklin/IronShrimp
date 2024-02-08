namespace IronShrimp
{
    public class Datx
    {
        public string Description { get; set; }

        public string Iteration { get; set; }

        public ScanTypes ScanType { get; set; }

        public enum ScanTypes
        {
            Unknown,
            SIM,
            Scan
        }

        public int IonSourceIndex { get; set; }

        public string Concentration { get; set; }

        public string Filename { get; set; }

        public string Filepath { get; set; }

        public string EscapedFilePath
        {
            get
            {
                return this.Filepath.Replace(@"\", @"\\");
            }
        }

        public SampleTypes SampleType { get; set; }

        public enum SampleTypes
        {
            Blank,
            Unknown,
            QC,
            Cal
        }
    }
}