// =============================================================================
//
// Program for generating XIC data from a datX.
//
// Prepared by Advion software development team.
//
// Usage:
//   GenerateXIC <datX> <minMass> <maxMass>
// where:
//   datX      name of datX file to process
//   minMass   minimum mass to include in XIC
//   maxMass   maximum mass to include in XIC
//
// Output is a list of (time, XIC) values.  Time units are seconds, and XIC units are
// counts per second.
//
// Examples:
//   GenerateXIC "Test.datx" 45 55      // generate XIC data using masses in range [45, 55]
//   GenerateXIC "Test.datx" 45 45      // generate XIC data using single mass nearest to 45
//   GenerateXIC "Test.datx" 44.5 45.5  // generate XIC data using masses in 1 m/Z range about 45
//   GenerateXIC "Test.datx" 0 2000     // generate XIC data using all masses (same as TIC)
//
// =============================================================================

#include <fstream>
#include <string>

#include "DataReader.h"
using namespace AdvionData;


// -----------------------------------------------------------------------------
// Parses supplied string to a float.  Returns true if parsing was succesful.
// -----------------------------------------------------------------------------
bool parseDouble(const std::string& in, float& res)
{
    try
    {
        size_t read = 0;
        res = std::stof(in, &read);
        if (in.size() != read)
            return false;
    }
    catch (std::invalid_argument)
    {
        return false;
    }
    return true;
}


// -----------------------------------------------------------------------------
// Reads supplied datX file and outputs XIC data for the supplied mass range.
// -----------------------------------------------------------------------------
void generateXIC(const char* pathName, float minMass, float maxMass)
{
    bool decodeSpectra = false;
    DataReader reader(pathName, false, decodeSpectra);

    int numMasses = reader.getNumMasses();
    int numScans = reader.getNumSpectra();
    if (numMasses == 0 || numScans == 0)
        return;

    int* massIndices = (int*)calloc(numMasses, sizeof(int));
    float* masses = (float*)calloc(numMasses, sizeof(float));
    float* times = (float*)calloc(numScans, sizeof(float));
    float* xics = (float*)calloc(numScans, sizeof(float));

    reader.getMasses(masses);
    reader.getRetentionTimes(times);

    // find nearest mass indices for minimum and maximum
    int minIndex = -1;
    int maxIndex = -1;
    float minError = FLT_MAX;
    float maxError = FLT_MAX;
    for (int i = 0; i < numMasses; ++i)
    {
        float dMinMass = fabs(masses[i] - minMass);
        if (dMinMass < minError)
        {
            minError = dMinMass;
            minIndex = i;
        }

        float dMaxMass = fabs(masses[i] - maxMass);
        if (dMaxMass < maxError)
        {
            maxError = dMaxMass;
            maxIndex = i;
        }
    }

    // build array of indices
    int numIndices = 0;
    for (int i = minIndex; i <= maxIndex; ++i)
    {
        massIndices[numIndices++] = i;
    }

    reader.generateXIC(massIndices, numIndices, xics);

    //printf("Data set   = %s\n", pathName);
    //printf("Num scans  = %d\n", numScans);
    //printf("Num masses = %d\n", numMasses);
    //printf("Min mass   = %7.2f\n", minMass);
    //printf("Max mass   = %7.2f\n", maxMass);
    //printf("Min index  = %d\n", minIndex);
    //printf("Max index  = %d\n", maxIndex);

    // output the XIC
    // - time units are seconds
    // -  XIC units are counts per second
    for (int i = 0; i < numScans; ++i)
        printf("%.2f, %.0f\n", times[i], xics[i]);

    fflush(stdout);

    // clean up
    free(xics);
    free(times);
    free(masses);
    free(massIndices);
}


// -----------------------------------------------------------------------------
// Main entry point for the application.
// -----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Error: incorrect number of arguments.\n");
        printf("\n");
        printf("Usage:\n");
        printf("  GenerateXIC <datX> <minMass> <maxMass>\n");
        printf("\n");
        return -1;
    }

    const char* datXFile = argv[1];
    const char* sMinMass = argv[2];
    const char* sMaxMass = argv[3];

    // validate supplied datX
    {
        std::ifstream file;
        file.open(datXFile);
        if (!file.is_open())
        {
            printf("Error: datX file not found.\n");
            printf("\n");
            return -1;
        }
    }

    // validate supplied minMass
    float minMass = -1.0f;
    if (!parseDouble(sMinMass, minMass))
    {
        printf("Error: invalid minMass value.\n");
        printf("\n");
        return -1;
    }

    // validate supplied maxMass
    float maxMass = -1.0f;
    if (!parseDouble(sMaxMass, maxMass))
    {
        printf("Error: invalid maxMass value.\n");
        printf("\n");
        return -1;
    }

    // validate range
    if (minMass > maxMass)
    {
        printf("Error: minMass is greater than maxMass.\n");
        printf("\n");
        return -1;
    }

    // generate the XIC data
    generateXIC(datXFile, minMass, maxMass);

    return 0;
}
