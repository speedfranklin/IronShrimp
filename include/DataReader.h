// (C) Copyright 2012-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionData.h"

namespace AdvionData
{
    class DataReaderImpl;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// DataReader allows applications to read mass spectrometry data sets in the Advion CMS format.
    /// Such data sets can be written by applications via the DataWriter class.  Advion data sets
    /// contain all of the experiment parameters that were used to generate the data as well as all
    /// spectral information that was generated during the experiment.  They may also contain
    /// auxiliary text files and channels of scalar data that an application chooses to include with
    /// the data.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_DATA_API DataReader
    {

    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a DataReader, which manages the reading of a data set.  Some aspects of the
        /// data set are loaded immediately, while others are loaded on demand.  If data is being
        /// read from a DATX file, a temporary folder is created to hold the uncompressed data
        /// files.
        /// </summary>
        /// <param name="path">        The path to the DATX file or folder that is to be opened.
        ///                            The folder option is meant mainly for use by the Advion
        ///                            Data Express application, which reads data sets as they
        ///                            are being acquired.</param>
        /// <param name="debugOutput"> (optional) If true, debug output will be printed to
        ///                            stdout. The default is false.  Mainly for use by Advion
        ///                            developers.</param>
        /// <param name="decodeSpectra">  (optional) If true, a temporary decoded spectra file is
        ///                            created.  Spectra can be read more quickly from this file,
        ///                            which is helpful when the spectra are read repeatedly.
        ///                            But, while the file is being created, the very large
        ///                            decoded spectra are held in memory, which can be a
        ///                            problem for some applications.  The default is false.</param>
        ///-------------------------------------------------------------------------------------------------
        DataReader(const char* path, bool debugOutput = false, bool decodeSpectra = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a DataReader, which manages the reading of a data set.  Some aspects of the
        /// data set are loaded immediately, while others are loaded on demand.  If data is being
        /// read from a DATX file, a temporary folder is created to hold the uncompressed data
        /// files.
        /// </summary>
        /// <param name="path">        The path to the DATX file or folder that is to be opened.
        ///                            The folder option is meant mainly for use by the Advion
        ///                            Data Express application, which reads data sets as they
        ///                            are being acquired.</param>
        /// <param name="debugOutput"> (optional) If true, debug output will be printed to
        ///                            stdout. The default is false.  Mainly for use by Advion
        ///                            developers.</param>
        /// <param name="decodeSpectra">  (optional) If true, a temporary decoded spectra file is
        ///                            created.  Spectra can be read more quickly from this file,
        ///                            which is helpful when the spectra are read repeatedly.
        ///                            But, while the file is being created, the very large
        ///                            decoded spectra are held in memory, which can be a
        ///                            problem for some applications.  The default is false.</param>
        ///-------------------------------------------------------------------------------------------------
        DataReader(const wchar_t* path, bool debugOutput = false, bool decodeSpectra = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Frees resources used by the DataReader.  Removes the temporary folder where files
        /// were uncompressed from a DATX input file, if necessary.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        ~DataReader();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Assigns the parameters to be used when the Peak Express delta background is calculated which will be used for
        /// future calls to get Peak Express delta spectrum data.
        /// </summary>
        /// <param name="startTime">   The start time for calculating the background.  Must be non-
        ///                            negative and less than endTime.</param>
        /// <param name="endTime">     The end time for calculating the background.  Must be non-
        ///                            negative and greater than startTime.</param>
        /// <param name="threshold">   The threshold below which delta signals will be zero, as a
        ///                            multiple of the baseline value for a spectrum sample.  Must be 1
        ///                            or greater.</param>
        /// <param name="minWidth">    The minimum width (in m/z) that must be above the threshold for a
        ///                            peak to be included in the delta spectrum  Must be 0.05 or
        ///                            greater.</param>
        /// <param name="noiseOffset"> The amount of signal that is added to each delta background
        ///                            sample to replace noise that was subtracted during the
        ///                            acquisition.</param>
        /// <returns> ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode setDeltaBackgroundParameters(double startTime, double endTime, double threshold,
                                               double minWidth, int noiseOffset);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the validity of the DataReader.</summary>
        /// <returns>
        /// ADVIONDATA_OK if the data set could be opened and contains masses and spectra, or another
        /// error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getDataSetValidity();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the date stored with the data set.</summary>
        /// <returns>The date string or an empty string if none is defined.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getDate();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the date stored with the data set.</summary>
        /// <returns>The date string or an empty string if none is defined.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getDateW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Determines if the data set was stored as centroided values.</summary>
        /// <returns>True if this data set contains only one sample per mass unit.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getIsCentroid();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number masses in every spectrum of the data set.  At present, all spectra in
        /// a data set contain the same number of masses and intensities.
        /// </summary>
        /// <returns>The number masses in every spectrum.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getNumMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the number of spectra stored in the data set.</summary>
        /// <returns>The number of spectra.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getNumSpectra();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the masses for every spectrum of the data set.</summary>
        /// <param name="masses"> [in,out] If non-null, will be filled with the mass values.  Must
        ///                       be allocated by the application to be at least as large as
        ///                       the value returned by getNumMasses.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getMasses(float* masses);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the retention times for all spectra of the data set, in seconds.</summary>
        /// <param name="times"> [in,out] If non-null, will be filled with the retention times.
        ///                      Must be allocated by the application to be at least as large as
        ///                      the value returned by getNumSpectra.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getRetentionTimes(float* times);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the intensities for a single spectrum in the data set.</summary>
        /// <param name="index">       Index of the spectrum to return.</param>
        /// <param name="intensities"> [in,out] If non-null, will be filled with the
        ///                            intensities. Must be allocated by the application to be
        ///                            at least as large as the value returned by getNumMasses.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getSpectrum(int index, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the Peak Express delta signals for a single spectrum in the data set.</summary>
        /// <param name="index">       Index of the spectrum to return.</param>
        /// <param name="intensities"> [in,out] If non-null, will be filled with the delta signals.
        ///                            Must be allocated by the application to be at least as large as
        ///                            the value returned by getNumMasses.</param>
        /// <returns>ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getDeltaSpectrum(int index, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Peak Express delta background for the data set, based on the background parameters.
        /// </summary>
        /// <param name="intensities"> [in,out] If non-null, will be filled with the delta
        ///                            background. Must be allocated by the application to be at least
        ///                            as large as the value returned by getNumMasses.</param>
        /// <returns>ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getDeltaBackgroundSpectrum(float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the average intensities for a set of spectra in the data set.</summary>
        /// <param name="spectraIndices"> Array of indices of the spectra to average.</param>
        /// <param name="num">            Number of spectra indices in the array.</param>
        /// <param name="intensities">    [in,out] If non-null, will be filled with the
        ///                               intensities. Must be allocated by the application to
        ///                               be at least as large as the value returned by
        ///                               getNumMasses.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getAveragedSpectrum(const int* spectraIndices, int num, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary> Gets the average Peak Express delta signal for a set of spectra in the data set.</summary>
        /// <param name="spectraIndices"> Array of indices of the spectra to average.</param>
        /// <param name="num">            Number of spectra indices in the array.</param>
        /// <param name="intensities">    [in,out] If non-null, will be filled with the delta signals.
        ///                               Must be allocated by the application to be at least as large
        ///                               as the value returned by getNumMasses.</param>
        /// <returns> ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getAveragedDeltaSpectrum(const int* spectraIndices, int num, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Generate an extracted ion current (XIC) for the selected masses.
        /// Sums the intensities for all selected masses at each time point.
        /// </summary>
        /// <param name="massIndices"> The indices of the selected masses to include.</param>
        /// <param name="numIndices"> The number of mass indices.</param>
        /// <param name="intensities"> [in,out] If non-null, will be filled with the
        ///                            XIC values. Must be allocated by the application to
        ///                            be at least as large as the value returned by
        ///                            getNumSpectra.</param>
        /// <returns>ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode generateXIC(const int* massIndices, int numIndices, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Generate a Peak Express delta extracted chromatogram value for the selected masses. Sums the
        /// delta signals for all selected masses at each time point.
        /// </summary>
        /// <param name="massIndices"> The indices of the selected masses to include.</param>
        /// <param name="numIndices">  The number of mass indices.</param>
        /// <param name="intensities"> [in,out] If non-null, will be filled with the DeltaXIC values.
        ///                            Must be allocated by the application to be at least as large as
        ///                            the value returned by getNumSpectra.</param>
        /// <returns> ADVIONDATA_OK if successful, or another error code from AdvionData.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode generateDeltaXIC(const int* massIndices, int numIndices, float* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the total ion current for a spectra in the data set.</summary>
        /// <param name="index"> The index of the spectra.</param>
        /// <returns>The total ion current for the spectra.</returns>
        ///-------------------------------------------------------------------------------------------------
        float getTIC(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Peak Express total delta chromatogram value for a spectrum in the data set.
        /// </summary>
        /// <param name="index"> The index of the spectra.</param>
        /// <returns> The total delta chromatogram value for the spectrum.</returns>
        ///-------------------------------------------------------------------------------------------------
        float getDeltaIC(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the software version used to produce the data set.</summary>
        /// <returns>The software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getSoftwareVersion();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the software version used to produce the data set.</summary>
        /// <returns>The software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getSoftwareVersionW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the firmware version on the instrument that produced the data.</summary>
        /// <returns>The firmware version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getFirmwareVersion();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the firmware version on the instrument that produced the data.</summary>
        /// <returns>The firmware version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getFirmwareVersionW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of the type of CMS instrument that produced the data set.</summary>
        /// <returns>The instrument type name.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getHardwareType();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of the type of CMS instrument that produced the data set.</summary>
        /// <returns>The instrument type name.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getHardwareTypeW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the identifier for the instrument that produced the data set.</summary>
        /// <returns>The instrument identifier.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getInstrumentID();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the identifier for the instrument that produced the data set.</summary>
        /// <returns>The instrument identifier.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getInstrumentIdW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the CMS method used to create the data set.</summary>
        /// <returns>The XML representation of the method.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getMethodXML();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the CMS method used to create the data set.</summary>
        /// <returns>The XML representation of the method.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getMethodXmlW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the Experiment used to create the data set.</summary>
        /// <returns>The XML representation of the experiment.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getExperimentXML();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the Experiment used to create the data set.</summary>
        /// <returns>The XML representation of the experiment.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getExperimentXmlW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the ICP-MS experiment associated with the data set.</summary>
        /// <returns>The XML representation of the ICP-MS experiment.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getIcpmsExperimentXML();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the ICP-MS experiment associated with the data set.</summary>
        /// <returns>The XML representation of the ICP-MS experiment.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getIcpmsExperimentXmlW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the ICP-MS instrument settings associated with the data set.</summary>
        /// <returns>The XML representation of the ICP-MS instrument settings.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getIcpmsInstrumentSettingsXML();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the ICP-MS instrument settings associated with the data set.</summary>
        /// <returns>The XML representation of the ICP-MS instrument settings.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getIcpmsInstrumentSettingsXmlW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the index of the scan mode in the method that was used to produce the data set.
        /// </summary>
        /// <returns>The index of the scan mode used to produce the data set.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getScanModeIndex();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of acquisition segments that were used in the data acquisition.
        /// </summary>
        /// <returns>The number of segments.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getNumSegments();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the start time of the specified acquisition segment, in seconds.</summary>
        /// <param name="index"> Zero-based index of the acquisition segment.</param>
        /// <returns>The segment start time, in seconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getSegmentTime(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the CMS ion source optimization used to create the data set during the specified
        /// time segment.
        /// </summary>
        /// <param name="index"> (optional) Zero-based index of the acquisition segment.  Default
        ///                      is 0.</param>
        /// <returns>
        /// The XML representation of the ion source optimization, or NULL if the index is out of
        /// range.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getIonSourceOptimizationXML(int index = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the CMS ion source optimization used to create the data set during the specified
        /// time segment.
        /// </summary>
        /// <param name="index"> (optional) Zero-based index of the acquisition segment.  Default
        ///                      is 0.</param>
        /// <returns>
        /// The XML representation of the ion source optimization, or NULL if the index is out of
        /// range.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getIonSourceOptimizationXmlW(int index = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the CMS tune parameters used to create the data set during the specified time
        /// segment.
        /// </summary>
        /// <param name="index"> (optional) Zero-based index of the acquisition segment.  Default
        ///                      is 0.</param>
        /// <returns>
        /// The XML representation of the tune parameters, or NULL if the index is out of range.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getTuneParametersXML(int index = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the CMS tune parameters used to create the data set during the specified time
        /// segment.
        /// </summary>
        /// <param name="index"> (optional) Zero-based index of the acquisition segment.  Default
        ///                      is 0.</param>
        /// <returns>
        /// The XML representation of the tune parameters, or NULL if the index is out of range.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getTuneParametersXmlW(int index = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the experiment log from the data set acquisition.</summary>
        /// <returns>The text from the experiment log.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getExperimentLog();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the experiment log from the data set acquisition.</summary>
        /// <returns>The text from the experiment log.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getExperimentLogW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the number of scalar data channels in the data set.</summary>
        /// <returns>The number of scalar data channels.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getNumScalarChannels();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of a scalar data channel.</summary>
        /// <param name="index"> The index of the channel.</param>
        /// <returns>The channel name.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getScalarChannelName(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of a scalar data channel.</summary>
        /// <param name="index"> The index of the channel.</param>
        /// <returns>The channel name.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getScalarChannelNameW(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the number of samples in a scalar data channel.</summary>
        /// <param name="index"> The index of the channel.</param>
        /// <returns>The number of samples.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getScalarChannelNumSamples(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the sample times for a scalar data channel, in seconds.</summary>
        /// <param name="index"> The index of the channel.</param>
        /// <param name="times"> [in,out] If non-null, will be filled with the times. Must be
        ///                      allocated by the application to be at least as large as the value
        ///                      returned by getScalarChannelNumSamples.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getScalarChannelTimes(int index, float* times);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the sample values for a scalar data channel.</summary>
        /// <param name="index">  The index of the channel.</param>
        /// <param name="values"> [in,out] If non-null, will be filled with the values. Must be
        ///                       allocated by the application to be at least as large as the
        ///                       value returned by getScalarChannelNumSamples.</param>
        /// <returns>
        /// ADVIONDATA_OK if successful, or another error code from AdvionData.h.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        ErrorCode getScalarChannelValues(int index, float* values);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of attributes defined for a scalar data channel.
        /// Attributes are named numerical values common to all samples in the scalar data channel.
        /// </summary>
        /// <param name="index"> The index of the channel.</param>
        /// <returns>
        /// The number of attributes defined for this channel, or -1 there is no channel at the
        /// specified index.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        int getScalarChannelNumAttributes(int index);

        /// <summary>
        /// Gets the name of the specified attribute of a scalar data channel.
        /// </summary>
        /// <param name="index"> The index of the channel.</param>
        /// <param name="attributeIndex"> The index of the attribute within this channel.</param>
        /// <returns>The name of the attribute, or NULL if the attribute is not defined.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getScalarChannelAttributeName(int index, int attributeIndex);

        /// <summary>
        /// Gets the name of the specified attribute of a scalar data channel.
        /// </summary>
        /// <param name="index"> The index of the channel.</param>
        /// <param name="attributeIndex"> The index of the attribute within this channel.</param>
        /// <returns>The name of the attribute, or NULL if the attribute is not defined.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getScalarChannelAttributeNameW(int index, int attributeIndex);

        /// <summary>
        /// Gets the value of the specified attribute of a scalar data channel.
        /// </summary>
        /// <param name="index"> The index of the channel.</param>
        /// <param name="attributeIndex"> The index of the attribute within this channel.</param>
        /// <returns>The value of the attribute, or 0 if the attribute is not defined.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getScalarChannelAttributeValue(int index, int attributeIndex);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets number of auxiliary files in the data set.</summary>
        /// <returns>The number auxiliary files.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getNumAuxFiles();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of an auxiliary file in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>The name of the file.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getAuxFileName(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the name of an auxiliary file in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>The name of the file.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getAuxFileNameW(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets data type of an auxiliary file in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>
        /// The type of the data stored in the file.  The Advion Data Express application
        /// recognizes two values for the purposes of displaying the text: "text" for plain text
        /// and "text/html" for HTML data.  At this time, binary data cannot be stored in
        /// auxiliary files.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getAuxFileType(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets data type of an auxiliary file in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>
        /// The type of the data stored in the file.  The Advion Data Express application
        /// recognizes two values for the purposes of displaying the text: "text" for plain text
        /// and "text/html" for HTML data.  At this time, binary data cannot be stored in
        /// auxiliary files.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getAuxFileTypeW(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the text contained in an auxiliary text in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>The text.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getAuxFileText(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the text contained in an auxiliary text in the data set.</summary>
        /// <param name="index"> The index of the auxiliary file.</param>
        /// <returns>The text.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getAuxFileTextW(int index);

    private:

        // hide copy constructor
        DataReader(const DataReader&);

        // hide assignment operator
        DataReader& operator=(const DataReader&);

    private:

        DataReaderImpl* impl;
    };
}
