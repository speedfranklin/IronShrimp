// (C) Copyright 2012-2018 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionData.h"

namespace AdvionData
{
    class DataWriterImpl;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// DataWriter allows applications to create mass spectrometry data sets in the Advion data
    /// format. Such data sets can be read by applications via the DataReader class.  Advion data
    /// sets contain all of the experiment parameters that were used to generate the data as well as
    /// all spectral information that was generated during the experiment.  They may also contain
    /// auxiliary text files and channels of scalar data that an application chooses to include with
    /// the data.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_DATA_API DataWriter
    {

    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Constructs a DataWriter, which manages the creation of a data set.  While it is being
        /// created, the data set is stored as several files in folder.  The data set is
        /// maintained in a valid state throughout its creation.  A data set can be bound into a
        /// single DATX file for easy portability.
        /// </summary>
        /// <param name="folder">      Path to the parent folder where the data set will be created.</param>
        /// <param name="rootName">    Name of the data set to be created.  During creation of
        ///                            the data set, a folder of this name will be created under
        ///                            the specified parent folder.  The folder will contain data
        ///                            files using this name as their root.  When a DATX file is
        ///                            created from this folder, it will have this root name.</param>
        /// <param name="isCentroid">  True if this data set will contain only one sample per
        ///                            mass unit.</param>
        /// <param name="debugOutput"> (optional) If true, debug output will be printed to
        ///                            stdout.  The default is false.  Mainly for use by Advion
        ///                            developers.</param>
        ///-------------------------------------------------------------------------------------------------
        DataWriter(const char* folder, const char* rootName, bool isCentroid, bool debugOutput = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Constructs a DataWriter, which manages the creation of a data set.  While it is being
        /// created, the data set is stored as several files in folder.  The data set is
        /// maintained in a valid state throughout its creation.  A data set can be bound into a
        /// single DATX file for easy portability.
        /// </summary>
        /// <param name="folder">      Path to the parent folder where the data set will be created.</param>
        /// <param name="rootName">    Name of the data set to be created.  During creation of
        ///                            the data set, a folder of this name will be created under
        ///                            the specified parent folder.  The folder will contain data
        ///                            files using this name as their root.  When a DATX file is
        ///                            created from this folder, it will have this root name.</param>
        /// <param name="isCentroid">  True if this data set will contain only one sample per
        ///                            mass unit.</param>
        /// <param name="debugOutput"> (optional) If true, debug output will be printed to
        ///                            stdout.  The default is false.  Mainly for use by Advion
        ///                            developers.</param>
        ///-------------------------------------------------------------------------------------------------
        DataWriter(const wchar_t* folder, const wchar_t* rootName, bool isCentroid, bool debugOutput = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Frees the resources used by a DataWriter.  Removes the temporary folder where files
        /// were stored during the creation of the data set if that folder is not currently being
        /// used by a DataReader object.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        ~DataWriter();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assign several meta-data values to be stored with the data set.</summary>
        /// <param name="software">   The software version used to produce the data set.</param>
        /// <param name="firmware">   The firmware version on the instrument that produced the data.</param>
        /// <param name="instrument"> An identifier for the instrument that produced the data set.</param>
        /// <param name="hardware">   (optional) The CMS hardware type used to produce the data set.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode setMetadata(const char* software, const char* firmware,
                              const char* instrument, const char* hardware = "CMS");

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assign several meta-data values to be stored with the data set.</summary>
        /// <param name="software">   The software version used to produce the data set.</param>
        /// <param name="firmware">   The firmware version on the instrument that produced the data.</param>
        /// <param name="instrument"> An identifier for the instrument that produced the data set.</param>
        /// <param name="hardware">   (optional) The CMS hardware type used to produce the data set.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode setMetadata(const wchar_t* software, const wchar_t* firmware,
                              const wchar_t* instrument, const wchar_t* hardware = L"CMS");

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Creates a new scalar channel to be saved with the data set.</summary>
        /// <param name="name"> The name of the channel.</param>
        /// <returns>
        /// An integer ID for the new scalar channel, to be used in later calls to
        /// writeScalarEntry.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        int createScalarChannel(const char* name);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Creates a new scalar channel to be saved with the data set.</summary>
        /// <param name="name"> The name of the channel.</param>
        /// <returns>
        /// An integer ID for the new scalar channel, to be used in later calls to
        /// writeScalarEntry.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        int createScalarChannel(const wchar_t* name);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Creates a new auxiliary text file to be saved with the data set.</summary>
        /// <param name="name"> The name of the auxiliary file.</param>
        /// <param name="type"> The type of the data to be stored in the file.  The Advion Data
        ///                     Express application recognizes two values for the purposes of
        ///                     displaying the text: "text" for plain text and "text/html" for
        ///                     HTML data.  At this time, binary data cannot be stored in
        ///                     auxiliary files.</param>
        /// <returns>
        /// An integer ID for the new auxiliary file, to be used in later calls to
        /// writeTextToFile.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        int createAuxiliaryFile(const char* name, const char* type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Creates a new auxiliary text file to be saved with the data set.</summary>
        /// <param name="name"> The name of the auxiliary file.</param>
        /// <param name="type"> The type of the data to be stored in the file.  The Advion Data
        ///                     Express application recognizes two values for the purposes of
        ///                     displaying the text: "text" for plain text and "text/html" for
        ///                     HTML data.  At this time, binary data cannot be stored in
        ///                     auxiliary files.</param>
        /// <returns>
        /// An integer ID for the new auxiliary file, to be used in later calls to
        /// writeTextToFile.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        int createAuxiliaryFile(const wchar_t* name, const wchar_t* type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Adds the CMS method for the data set.</summary>
        /// <param name="methodXML"> The XML content specifying a method.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeMethod(const char* methodXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Adds the CMS method for the data set.</summary>
        /// <param name="methodXML"> The XML content specifying a method.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeMethod(const wchar_t* methodXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Write the CMS experiment data to a file (.expr)</summary>
        /// <param name="experimentXML">The XML content specifying a CMS experiment.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeExperiment(const char* experimentXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Write the CMS experiment data to a file (.expr)</summary>
        /// <param name="experimentXML">The XML content specifying a CMS experiment.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeExperiment(const wchar_t* experimentXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assigns the CMS ion source optimization for the data set.</summary>
        /// <param name="ionSourceXML"> XML content specifying an ion source optimization.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeIonSourceOpt(const char* ionSourceXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assigns the CMS ion source optimization for the data set.</summary>
        /// <param name="ionSourceXML"> XML content specifying an ion source optimization.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeIonSourceOpt(const wchar_t* ionSourceXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assigns the CMS tune parameters for the data set.</summary>
        /// <param name="tuneXML"> XML content specifying the tune parameters.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeTuneParams(const char* tuneXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Assigns the CMS tune parameters for the data set.</summary>
        /// <param name="tuneXML"> XML content specifying the tune parameters.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeTuneParams(const wchar_t* tuneXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes the index of the scan mode in the method that was used to produce the data set.
        /// </summary>
        /// <param name="scanModeIndex">The index of the scan mode used to produce the data set.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeScanModeIndex(int scanModeIndex);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes the acquisition segment information into the data set.  Each acquisition
        /// segment includes a start time, an ion source optimization and a set of tune
        /// parameters.
        /// </summary>
        /// <param name="numSegments">  Number of segments.</param>
        /// <param name="times">        The start times for each segment, in minutes.</param>
        /// <param name="ionSourceXMLs">XML representations of the ion source optimizations for
        ///                             each segment.</param>
        /// <param name="tuneXMLs">     XML representations of the tune parameters for each
        ///                             segment.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeSegments(int numSegments, double* times, const char** ionSourceXMLs, const char** tuneXMLs);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes the acquisition segment information into the data set.  Each acquisition
        /// segment includes a start time, an ion source optimization and a set of tune
        /// parameters.
        /// </summary>
        /// <param name="numSegments">  Number of segments.</param>
        /// <param name="times">        The start times for each segment, in minutes.</param>
        /// <param name="ionSourceXMLs">XML representations of the ion source optimizations for
        ///                             each segment.</param>
        /// <param name="tuneXMLs">     XML representations of the tune parameters for each
        ///                             segment.</param>
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeSegments(int numSegments, double* times, const wchar_t** ionSourceXMLs, const wchar_t** tuneXMLs);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a log message.</summary>
        /// <param name="text"> The text to be added to the log file.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeLogMessage(const char* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a log message.</summary>
        /// <param name="text"> The text to be added to the log file.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeLogMessage(const wchar_t* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes to the data set the masses that are used for all spectral data in the set.
        /// Should only be called once during the creation of a data set.  At present, each
        /// spectrum of the data set is presumed to store intensity values for exactly the same
        /// set of masses.
        /// </summary>
        /// <param name="masses"> The array of masses to write.</param>
        /// <param name="num">    The number of masses to write.  Must be the same value used in
        ///                       later calls to writeScanData.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeSpectrumMasses(const float* masses, int num);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes to the data set the data for a single scan.  Scan data must be written in
        /// chronological order.
        /// </summary>
        /// <param name="intensities">   The array of spectral intensities to store for this scan,
        ///                              specified as unsigned integers.</param>
        /// <param name="num">           The number of intensities to store.  Must be the same
        ///                              value as used in the call to writeSpectrumMasses.</param>
        /// <param name="retentionTime"> The retention time to store with this scan.</param>
        /// <param name="tic">           The total ion current value to store for this scan.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeScanData(const unsigned int* intensities, int num, double retentionTime, double tic);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes to the data set the data for a single scan.  Scan data must be written in
        /// chronological order.
        /// </summary>
        /// <param name="intensities">   The array of spectral intensities to store for this scan,
        ///                              specified as floats.</param>
        /// <param name="num">           The number of intensities to store.  Must be the same
        ///                              value as used in the call to writeSpectrumMasses.</param>
        /// <param name="retentionTime"> The retention time to store with this scan.</param>
        /// <param name="tic">           The total ion current value to store for this scan.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeScanData(const float* intensities, int num, double retentionTime, double tic);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Add a numeric attribute to a scalar channel.
        /// Must be called before writing entries to this channel.
        /// Scalar channels with attribute "wavelength" defined are treated as
        /// UV data by Data Express.
        /// </summary>
        /// <param name="id">    The ID of the channel.</param>
        /// <param name="name">  The name of the attribute.</param>
        /// <param name="value"> The value for this attribute</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// Will return ADVIONDATA_CHANNEL_HEADER_CLOSED if writeScalarEntry has already been
        /// called for this channel.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode addScalarChannelAttribute(int id, const char* name, double value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Add a numeric attribute to a scalar channel.
        /// Must be called before writing entries to this channel.
        /// Scalar channels with attribute "wavelength" defined are treated as
        /// UV data by Data Express.
        /// </summary>
        /// <param name="id">    The ID of the channel.</param>
        /// <param name="name">  The name of the attribute.</param>
        /// <param name="value"> The value for this attribute</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// Will return ADVIONDATA_CHANNEL_HEADER_CLOSED if writeScalarEntry has already been
        /// called for this channel.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode addScalarChannelAttribute(int id, const wchar_t* name, double value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes an entry to a previously defined scalar channel.</summary>
        /// <param name="id">    The ID of the channel.</param>
        /// <param name="time">  The time stamp to store for the entry.</param>
        /// <param name="value"> The channel value to store.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeScalarEntry(int id, double time, double value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes the array of the entries to a previously defined scalar channel.</summary>
        /// <param name="id">    The ID of the channel.</param>
        /// <param name="times">  The array of the time-stamps. </param>
        /// <param name="values"> The array of the data values.</param>
        /// <param name="numEntries"> The number of the entries.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeScalarEntries(int id, double* times, double* values, int numEntries);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes text to a previously defined auxiliary file.</summary>
        /// <param name="id">   The ID of the channel.</param>
        /// <param name="text"> The text to write.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeTextToFile(int id, const char* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes text to a previously defined auxiliary file.</summary>
        /// <param name="id">   The ID of the channel.</param>
        /// <param name="text"> The text to write.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode writeTextToFile(int id, const wchar_t* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a DATX file from the temporary folder of data files that have been created
        /// using other methods. Any further calls to those methods will alter the contents of
        /// the temporary folder, but not the DATX file that is created here.
        /// </summary>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode createDatxFile();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if it is possible to create a DataWriter that will write to the given
        /// folder.  Currently verifies that no other active data reader or writer references
        /// files in the folder.
        /// </summary>
        /// <param name="folder"> Path to the folder.</param>
        /// <returns>True if we can create such a DataWriter, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        static bool canWriteData(const char* folder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if it is possible to create a DataWriter that will write to the given
        /// folder.  Currently verifies that no other active data reader or writer references
        /// files in the folder.
        /// </summary>
        /// <param name="folder"> Path to the folder.</param>
        /// <returns>True if we can create such a DataWriter, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        static bool canWriteData(const wchar_t* folder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if it is possible to create a DataWriter that will write to the given
        /// parent folder and data set.  Currently verifies that 1) path lengths do not exceed
        /// operating system limits, and 2) no other active data reader or writer references
        /// the supplied data set.
        /// </summary>
        /// <param name="folder">   Path to the parent folder where the data set will be created.</param>
        /// <param name="rootName"> Name of the data set to be created.  During creation of
        ///                         the data set, a folder of this name will be created under
        ///                         the specified parent folder.  The folder will contain data
        ///                         files using this name as their root.  When a DATX file is
        ///                         created from this folder, it will have this root name.</param>
        /// <returns>
        /// ADVIONDATA_OK if we can create such a DataWriter, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode canWriteData(const char* folder, const char* rootName);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if it is possible to create a DataWriter that will write to the given
        /// parent folder and data set.  Currently verifies that 1) path lengths do not exceed
        /// operating system limits, and 2) no other active data reader or writer references
        /// the supplied data set.
        /// </summary>
        /// <param name="folder">   Path to the parent folder where the data set will be created.</param>
        /// <param name="rootName"> Name of the data set to be created.  During creation of
        ///                         the data set, a folder of this name will be created under
        ///                         the specified parent folder.  The folder will contain data
        ///                         files using this name as their root.  When a DATX file is
        ///                         created from this folder, it will have this root name.</param>
        /// <returns>
        /// ADVIONDATA_OK if we can create such a DataWriter, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode canWriteData(const wchar_t* folder, const wchar_t* rootName);

    private:

        // hide copy constructor
        DataWriter(const DataWriter&);

        // hide assignment operator
        DataWriter& operator=(const DataWriter&);

    private:

        DataWriterImpl* impl;
    };
}
