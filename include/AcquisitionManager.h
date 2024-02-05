// (C) Copyright 2012-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"

#ifdef LINUX
#include <cstring> // For NULL
#endif

namespace AdvionCMS
{
    /// <summary>
    /// Defines the set of states for the AcquisitionManager.
    /// </summary>
    typedef enum
    {
        Prevented,      ///< Acquisition cannot be started because of the instrument state or operation mode.
        Ready,          ///< The controller is ready to start an acquisition.
        Waiting,        ///< An acquisition is started, and scanning will begin when a digital input is seen.
        Underway,       ///< An acquisition is started, and scanning is underway.
        Paused,         ///< An acquisition is started, and scanning is paused.
    } AcquisitionState;


    /// <summary>
    /// Defines the different types of acquisition scan modes.
    /// </summary>
    typedef enum
    {
        ASM_Unknown,            /// An unknown scan mode.
        ASM_CMS_SIM,            /// A Selected Ion Monitoring (SIM) scan mode.  Used with CMS.
        ASM_CMS_Range,          /// A range scan mode.  Used with CMS.
    } AcquisitionScanMode;


    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// The static AcquisitionManager class controls the data acquisition scanning that is
    /// performed on the Advion CMS and reports its results.  Acquisition scanning produces range
    /// or SIM data for a fixed amount of time, as specified by a CMS method.  An application can
    /// access the data through methods in this class, and the data can optionally be
    /// automatically saved to a file during the acquisition.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API AcquisitionManager
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determines if a given system folder path can be used as the data destination when
        /// starting an acquisition.
        /// </summary>
        /// <param name="folder"> Path of the folder.</param>
        /// <returns>True if we can acquire to the folder, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canAcquireToFolder(const char* folder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determines if a given system folder path can be used as the data destination when
        /// starting an acquisition.
        /// </summary>
        /// <param name="folder"> Path of the folder.</param>
        /// <returns>True if we can acquire to the folder, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canAcquireToFolder(const wchar_t* folder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if the connected CMS can perform acquisitions using ion source switching.
        /// </summary>
        /// <returns>True if ion source switching can be used, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canPerformSwitching();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if the connected CMS can calculate Peak Express delta spectra and chromatograms.
        /// </summary>
        /// <returns>True if Peak Express data can be returned, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canCalculateDeltaData();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets minimum allowable scan time for range scans.</summary>
        /// <returns>The minimum range scan time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMinRangeScanTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets minimum allowable dwell time for SIM scans.</summary>
        /// <returns>The minimum SIM mass dwell time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMinSIMDwellTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets maximum allowable scan time for range scans.</summary>
        /// <returns>The maximum range scan time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxRangeScanTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets maximum allowable dwell time for SIM scans.</summary>
        /// <returns>The maximum SIM mass dwell time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxSIMDwellTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method, ion source, and tune
        /// parameters.  The data that is produced can optionally be saved to a data set file on
        /// the disk.
        /// </summary>
        /// <param name="methodXML">     XML text defining the method to use for the acquisition.</param>
        /// <param name="ionSourceXML">  XML text defining the ion source optimization to load before
        ///                              performing the acquisition.</param>
        /// <param name="tuneXML">       XML text defining the tune parameters to load before
        ///                              performing the acquisition.</param>
        /// <param name="name">          Name of the acquisition, also used to determine an optional
        ///                              output file name.</param>
        /// <param name="folder">        (optional) Path to the folder where the acquisition data will
        ///                              be stored.  If NULL, no data set will be stored on disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode start(const char* methodXML,
                               const char* ionSourceXML, const char* tuneXML,
                               const char* name, const char* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method, ion source, and tune
        /// parameters.  The data that is produced can optionally be saved to a data set file on
        /// the disk.
        /// </summary>
        /// <param name="methodXML">     XML text defining the method to use for the acquisition.</param>
        /// <param name="ionSourceXML">  XML text defining the ion source optimization to load before
        ///                              performing the acquisition.</param>
        /// <param name="tuneXML">       XML text defining the tune parameters to load before
        ///                              performing the acquisition.</param>
        /// <param name="name">          Name of the acquisition, also used to determine an optional
        ///                              output file name.</param>
        /// <param name="folder">        (optional) Path to the folder where the acquisition data will
        ///                              be stored.  If NULL, no data set will be stored on disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode start(const wchar_t* methodXML,
                               const wchar_t* ionSourceXML, const wchar_t* tuneXML,
                               const wchar_t* name, const wchar_t* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method, two ion sources, and
        /// two sets of tune parameters.  Alternating scans will switch between the provided ion
        /// source optimizations and tune parameters.  This allows for positive/negative scanning
        /// or high/low source voltage scanning.  The data that is produced can optionally be
        /// saved to two data set files on the disk, where the text "_is1" and "_is2" is appended
        /// to the provided file name for the two data files.  The ion source and capillary
        /// temperature settings from the first ion source optimization are used for all scans,
        /// and those from the second ion source optimization are ignored.  May only be called
        /// for "high performance" instruments.
        /// </summary>
        /// <param name="methodXML">      XML text defining the method to use for the acquisition.</param>
        /// <param name="ionSource1XML">  XML text defining the first ion source optimization to
        ///                               use when performing the acquisition.</param>
        /// <param name="ionSource2XML">  XML text defining the second ion source optimization to
        ///                               use when performing the acquisition.</param>
        /// <param name="tune1XML">       XML text defining the first tune parameters to use when
        ///                               performing the acquisition.</param>
        /// <param name="tune2XML">       XML text defining the second tune parameters to use when
        ///                               performing the acquisition.</param>
        /// <param name="name">           Name of the acquisition, also used to determine an
        ///                               optional output file name.</param>
        /// <param name="folder">         (optional) Path to the folder where the acquisition data
        ///                               will be stored.  If NULL, no data set will be stored on
        ///                               disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode startWithSwitching(const char* methodXML,
                                            const char* ionSource1XML, const char* ionSource2XML,
                                            const char* tune1XML, const char* tune2XML,
                                            const char* name, const char* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method, two ion sources, and
        /// two sets of tune parameters.  Alternating scans will switch between the provided ion
        /// source optimizations and tune parameters.  This allows for positive/negative scanning
        /// or high/low source voltage scanning.  The data that is produced can optionally be
        /// saved to two data set files on the disk, where the text "_is1" and "_is2" is appended
        /// to the provided file name for the two data files.  The ion source and capillary
        /// temperature settings from the first ion source optimization are used for all scans,
        /// and those from the second ion source optimization are ignored.  May only be called
        /// for "high performance" instruments.
        /// </summary>
        /// <param name="methodXML">      XML text defining the method to use for the acquisition.</param>
        /// <param name="ionSource1XML">  XML text defining the first ion source optimization to
        ///                               use when performing the acquisition.</param>
        /// <param name="ionSource2XML">  XML text defining the second ion source optimization to
        ///                               use when performing the acquisition.</param>
        /// <param name="tune1XML">       XML text defining the first tune parameters to use when
        ///                               performing the acquisition.</param>
        /// <param name="tune2XML">       XML text defining the second tune parameters to use when
        ///                               performing the acquisition.</param>
        /// <param name="name">           Name of the acquisition, also used to determine an
        ///                               optional output file name.</param>
        /// <param name="folder">         (optional) Path to the folder where the acquisition data
        ///                               will be stored.  If NULL, no data set will be stored on
        ///                               disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode startWithSwitching(const wchar_t* methodXML,
                                            const wchar_t* ionSource1XML, const wchar_t* ionSource2XML,
                                            const wchar_t* tune1XML, const wchar_t* tune2XML,
                                            const wchar_t* name, const wchar_t* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method and applying the
        /// specified ion sources and tune parameters starting at the given times (the
        /// acquisition segments).  Acquisition segments should be sorted from low to high start
        /// times.  Before the first scan after a segment start time, the given ion source and
        /// tune parameters will be assigned to the instrument.  The data that is produced by the
        /// acquisition can optionally be saved to file with the specified name located in the
        /// specified folder.
        /// </summary>
        /// <param name="methodXML">    XML text defining the method to use for the acquisition.</param>
        /// <param name="numSegments">  The number of acquisition segments.</param>
        /// <param name="times">        The acquisition start times, in minutes.</param>
        /// <param name="ionSourceXMLs">XML representations of the ion source optimizations for
        ///                             each segment.</param>
        /// <param name="tuneXMLs">     XML representations of the tune parameters for each
        ///                             segment.</param>
        /// <param name="name">         Name of the acquisition, also used to determine an
        ///                             optional output file name.</param>
        /// <param name="folder">       (optional) Path to the folder where the acquisition data
        ///                             will be stored.  If NULL, no data set will be stored on
        ///                             disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode startWithSegments(const char* methodXML,
                                           int numSegments, double* times,
                                           const char** ionSourceXMLs, const char** tuneXMLs,
                                           const char* name, const char* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Requests that an acquisition be started using the given method and applying the
        /// specified ion sources and tune parameters starting at the given times (the
        /// acquisition segments).  Acquisition segments should be sorted from low to high start
        /// times.  Before the first scan after a segment start time, the given ion source and
        /// tune parameters will be assigned to the instrument.  The data that is produced by the
        /// acquisition can optionally be saved to file with the specified name located in the
        /// specified folder.
        /// </summary>
        /// <param name="methodXML">    XML text defining the method to use for the acquisition.</param>
        /// <param name="numSegments">  The number of acquisition segments.</param>
        /// <param name="times">        The acquisition start times, in minutes.</param>
        /// <param name="ionSourceXMLs">XML representations of the ion source optimizations for
        ///                             each segment.</param>
        /// <param name="tuneXMLs">     XML representations of the tune parameters for each
        ///                             segment.</param>
        /// <param name="name">         Name of the acquisition, also used to determine an
        ///                             optional output file name.</param>
        /// <param name="folder">       (optional) Path to the folder where the acquisition data
        ///                             will be stored.  If NULL, no data set will be stored on
        ///                             disk.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode startWithSegments(const wchar_t* methodXML,
                                           int numSegments, double* times,
                                           const wchar_t** ionSourceXMLs, const wchar_t** tuneXMLs,
                                           const wchar_t* name, const wchar_t* folder = NULL);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Stop the current acquisition.</summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode stop();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Pauses the current acquisition, allowing it to be resumed at a later time.  If no
        /// acquisition is underway, the next one that is started will be immediately paused.
        /// </summary>
        /// <param name="resumeOnDigitalInput"> (optional) If true, acquisition will begin with
        ///                                     either a call to resume() or a digital input
        ///                                     signal as specified in the method.  Otherwise,
        ///                                     only a call to resume() will cause the
        ///                                     acquisition to continue.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode pause(bool resumeOnDigitalInput = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Resumes a paused acquisition.</summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode resume();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Extends an acquisition by the specified number of seconds.</summary>
        /// <returns>Current total acquisition time (in seconds) after the increment.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int extend(int seconds);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Query if the manager is currently finalizing data from a previous acquisition.  If the
        /// InstrumentController is stopped while data is being finalized, the resulting DATX
        /// file may be incomplete and invalid.
        /// </summary>
        /// <returns>True if finalizing data, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool isFinalizingData();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a new scalar data channel into which an application may store time-stamped
        /// values during an acquisition.  The data in the channel is stored with the data set on
        /// disk.  May only be called after an acquisition is started.
        /// </summary>
        /// <param name="name"> The channel name.</param>
        /// <returns>The ID of the new scalar data channel.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int createScalarChannel(const char* name);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a new scalar data channel into which an application may store time-stamped
        /// values during an acquisition.  The data in the channel is stored with the data set on
        /// disk.  May only be called after an acquisition is started.
        /// </summary>
        /// <param name="name"> The channel name.</param>
        /// <returns>The ID of the new scalar data channel.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int createScalarChannel(const wchar_t* name);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes an entry into a previously defined scalar data channel.  May only be called
        /// after an acquisition is started and a channel is created.
        /// </summary>
        /// <param name="id">    The channel ID for a previously created channel.</param>
        /// <param name="time">  The time-stamp for this entry.</param>
        /// <param name="value"> The data value for this entry.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode writeScalarEntry(int id, double time, double value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Writes the array of the entries into a previously defined scalar data channel.  May only
        /// be called after an acquisition is started and a channel is created.
        /// </summary>
        /// <param name="id">    The channel ID for a previously created channel.</param>
        /// <param name="times">  The array of the time-stamps. </param>
        /// <param name="values"> The array of the data values.</param>
        /// <param name="numEntries"> The number of entries.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode writeScalarEntries(int id, double* times, double* values, int numEntries);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a new auxiliary file into which an application may store text during an
        /// acquisition.  The auxiliary file is stored with the data set on disk.  May only be
        /// called after an acquisition is started.
        /// </summary>
        /// <param name="name"> The name of the auxiliary data.</param>
        /// <param name="type"> The type of data to be stored in the file.  At present, only text
        ///                     data is allowed.  The Advion Data Express application recognizes
        ///                     two type strings when it displays auxiliary data: "text" for
        ///                     plain text, and "text/html" for HTML data.</param>
        /// <returns>The ID of the new auxiliary file.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int createAuxiliaryFile(const char* name, const char* type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Creates a new auxiliary file into which an application may store text during an
        /// acquisition.  The auxiliary file is stored with the data set on disk.  May only be
        /// called after an acquisition is started.
        /// </summary>
        /// <param name="name"> The name of the auxiliary data.</param>
        /// <param name="type"> The type of data to be stored in the file.  At present, only text
        ///                     data is allowed.  The Advion Data Express application recognizes
        ///                     two type strings when it displays auxiliary data: "text" for
        ///                     plain text, and "text/html" for HTML data.</param>
        /// <returns>The ID of the new auxiliary file.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int createAuxiliaryFile(const wchar_t* name, const wchar_t* type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes text to a previously created auxiliary file.</summary>
        /// <param name="id">   The auxiliary file ID.</param>
        /// <param name="text"> The text to write to the auxiliary file.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode writeTextToFile(int id, const char* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes text to a previously created auxiliary file.</summary>
        /// <param name="id">   The auxiliary file ID.</param>
        /// <param name="text"> The text to write to the auxiliary file.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode writeTextToFile(int id, const wchar_t* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a message into the acquisition experiment log.</summary>
        /// <param name="text"> The text to write to the log file.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeLogMessage(const char* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a message into the acquisition experiment log.</summary>
        /// <param name="text"> The text to write to the log file.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeLogMessage(const wchar_t* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a message into the acquisition experiment log.</summary>
        /// <param name="text"> The text to write to the log file.</param>
        /// <param name="notify">Specifies whether to raise the onWriteLogMessage event.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeLogMessage(const char* text, bool notify);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Writes a message into the acquisition experiment log.</summary>
        /// <param name="text"> The text to write to the log file.</param>
        /// <param name="notify">Specifies whether to raise the onWriteLogMessage event.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeLogMessage(const wchar_t* text, bool notify);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Write the CMS experiment data to a file (.expr)</summary>
        /// <param name="experimentXML">The XML content specifying a CMS experiment.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeExperiment(const char* experimentXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Write the CMS experiment data to a file (.expr)</summary>
        /// <param name="experimentXML">The XML content specifying a CMS experiment.</param>
        ///-------------------------------------------------------------------------------------------------
        static void writeExperiment(const wchar_t* experimentXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the state of the AcquisitionManager.</summary>
        /// <returns>The state.</returns>
        ///-------------------------------------------------------------------------------------------------
        static AcquisitionState getState();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Query if the current acquisition is using two ion sources.</summary>
        /// <returns>True if using two ion sources, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool isUsingTwoIonSources();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the number of scan modes defined in the acquisition.</summary>
        /// <returns>The number of scan modes in the current acquisition.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumScanModes();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets information on the types of scan modes in the acquisition.</summary>
        /// <param name="scanModeIndex"> Index of the scan mode whose type is desired.</param>
        /// <returns>The type of acquisition scan mode.</returns>
        ///-------------------------------------------------------------------------------------------------
        static AcquisitionScanMode getScanMode(int scanModeIndex);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current acquisition's name.</summary>
        /// <param name="ionSourceIndex"> (optional) Index of the ion source associated with the name.</param>
        /// <param name="scanModeIndex"> (optional) Index of the scan mode associated with the name.</param>
        /// <returns>The name.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const char* getCurrentName(int ionSourceIndex = 0, int scanModeIndex = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current acquisition's name.</summary>
        /// <param name="ionSourceIndex"> (optional) Index of the ion source associated with the name.</param>
        /// <param name="scanModeIndex"> (optional) Index of the scan mode associated with the name.</param>
        /// <returns>The name.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const wchar_t* getCurrentNameW(int ionSourceIndex = 0, int scanModeIndex = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current acquisition's folder path.</summary>
        /// <returns>The folder path, or NULL if none was assigned.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const char* getCurrentFolder();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current acquisition's folder path.</summary>
        /// <returns>The folder path, or NULL if none was assigned.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const wchar_t* getCurrentFolderW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the maximum number of scans that may be performed during the acquisition.  This
        /// value is useful for preallocating memory when an acquisition starts.  Frequently, the
        /// actual number of scans performed will be less than the theoretical maximum returned
        /// by this method.
        /// </summary>
        /// <returns>The maximum number of scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxNumScans();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the maximum number of masses (samples) that may be returned with any scan of
        /// the acquisition.  Should be called after setting binning using setAcquisitionBinsPerAMU(int binsPerAMU).
        /// </summary>
        /// <returns>The maximum number of masses.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxNumMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current runtime of the acquisition.</summary>
        /// <returns>The time since the current run was started, in seconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getRuntime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the total runtime of the acquisition unless stopped by user.  It includes
        /// the extended time.
        /// </summary>
        /// <returns>The total time to complete the current run, in seconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getTotalRunTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the number of scans that have been completed so far in an acquisition.</summary>
        /// <returns>The number scans done.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumScansDone();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the index of the last completed acquisition scan.</summary>
        /// <returns>The last scan index.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getLastScanIndex();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the scan mode index of the last completed acquisition scan.</summary>
        /// <returns>The last scan mode index.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getLastScanModeIndex();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the index of the ion source used by the last completed acquisition scan.  When
        /// performing an acquisition using ion source switching this will be either 0 or 1.
        /// When performing an acquisition using segments this will be 0.
        /// </summary>
        /// <returns>The index of the last scan's ion source.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getLastScanIonSource();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the retention time of the last completed acquisition scan.</summary>
        /// <returns>The last retention time, in seconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastRetentionTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of masses (samples) in the last completed acquisition scan.  This number
        /// is guaranteed to be no greater than the value returned by getMaxNumMasses.
        /// </summary>
        /// <returns>The last number of masses.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getLastNumMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Total Ion Current (TIC) from the last completed acquisition scan.
        /// </summary>
        /// <returns>The last TIC.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastTIC();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Calculates an Extracted Ion Current (XIC) value from the last completed acquisition scan.
        /// </summary>
        /// <param name="startMass"> The start mass of the XIC range.</param>
        /// <param name="endMass">   The end mass of the XIC range.</param>
        /// <returns>The XIC value.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastXIC(double startMass, double endMass);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Peak Express delta total chromatogram value from the last completed acquisition scan.
        /// </summary>
        /// <returns>The last DeltaIC value.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastDeltaIC();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Calculates a Peak Express delta extracted chromatogram value from the last completed
        /// acquisition scan.
        /// </summary>
        /// <param name="startMass"> The start mass of the DeltaXIC range.</param>
        /// <param name="endMass">   The end mass of the DeltaXIC range.</param>
        /// <returns>The last DeltaXIC value.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastDeltaXIC(double startMass, double endMass);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Returns the analog output signal value for the specified line from the last
        /// completed acquisition scan.
        /// </summary>
        /// <param name="line"> The analog output line (0-3) whose value is returned.</param>
        /// <param name="returnProcessed">
        /// If false, returns the raw value (from TIC or XIC),
        /// otherwise returns the value after optional baseline subtraction and smoothing have been applied.
        /// </param>
        /// <returns>The analog output signal value.</returns>
        ///-------------------------------------------------------------------------------------------------
        static double getLastAnalogOutput(int line, bool returnProcessed);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the spectrum masses from the last completed acquisition scan.
        /// </summary>
        /// <param name="masses">     If non-null, will be filled with the mass values.  Must be
        ///                           allocated by the application to be at least as large as
        ///                           the value returned by getLastNumMasses().</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode getLastSpectrumMasses(double* masses);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the spectrum intensities from the last completed acquisition scan.
        /// </summary>
        /// <param name="intensities"> If non-null, will be filled with the intensity values.
        ///                            Must be allocated by the application to be at least as
        ///                            large as the value returned by getLastNumMasses().</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode getLastSpectrumIntensities(double* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Peak Express delta spectrum intensities from the last completed acquisition scan.
        /// If called before the delta background has been calculated, all values are epsilon.
        /// </summary>
        /// <param name="intensities"> If non-null, will be filled with the intensity values.
        ///                            Must be allocated by the application to be at least as
        ///                            large as the value returned by getLastNumMasses().</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode getLastDeltaSpectrumIntensities(double* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of samples in the Peak Express delta background spectrum for the given scan mode index.
        /// </summary>
        /// <param name="scanModeIndex">The scan mode entry of the method for which the
        ///                             background spectrum size will be returned.
        ///                             Must be >= zero and < the current number of scan modes.</param>
        /// <returns>The number of samples in the specified Peak Express delta background spectrum.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getDeltaBackgroundSize(int scanModeIndex);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the Peak Express delta background spectrum intensities that will be subtracted from delta spectra.
        /// If called before the delta background has been calculated, all values are zero.
        /// </summary>
        /// <param name="intensities"> If non-null, will be filled with the intensity values.
        ///                            Must be allocated by the application to be at least as
        ///                            large as the value returned by getDeltaBackgroundSize()
        ///                            for the same scan mode index.</param>
        /// <param name="scanModeIndex">The scan mode entry of the method for which the
        ///                             background spectrum will be returned.
        ///                             Must be >= zero and < the current number of scan modes.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode getDeltaBackgroundSpectrum(double* intensities, int scanModeIndex);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of bins per atomic mass unit being used when writing datx files for
        /// range scans.
        /// </summary>
        /// <returns>The number of bins used when writing datx files for range scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getWriteBinsPerAMU();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Sets the number of bins per atomic mass unit to use when writing datx files for
        /// range scans.
        /// </summary>
        /// <param name="binsPerAMU">  The number of "bins" into which samples are to be
        ///                            filtered.  The Advion Mass Express application uses a
        ///                            value of 20 for this parameter.  A value of 1 will
        ///                            produce "centroided" data.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setWriteBinsPerAMU(int binsPerAMU);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of bins per atomic mass unit being used when returning real-time data
        /// for range scans.  This is the binning used by all AcquisitionManager methods which
        /// return mass spectrum data, including getLastSpectrumMasses and getLastSpectrumIntensities.
        /// </summary>
        /// <returns>The number of bins used when returning real-time data for range scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getAcquisitionBinsPerAMU();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Sets the number of bins per atomic mass unit to use when returning real-time data for
        /// range scans.  This sets the binning used by all AcquisitionManager methods which
        /// return mass spectrum data, including getLastSpectrumMasses and getLastSpectrumIntensities.
        /// </summary>
        /// <param name="binsPerAMU">  The number of "bins" into which samples are to be
        ///                            filtered.  The Advion Mass Express application uses a
        ///                            value of 20 for this parameter.  A value of 1 will
        ///                            produce "centroided" data.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setAcquisitionBinsPerAMU(int binsPerAMU);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Updates ion source optimizations used with the current acquisition.  This is supported
        /// for non-switching acquisitions and acquisitions using ion source switching, but not for
        /// acquisitions using segments.  The new ion source settings will be applied when the next
        /// scan is scheduled.
        /// </summary>
        /// <param name="ionSourceIndex">Index of the ion source to be updated.  For non-switching
        ///                              acquisitions this should be 0, while for acquisitions using
        ///                              ion source switching this should be 0 or 1.</param>
        /// <param name="ionSourceXML">  XML text defining the updated ion source optimization to apply.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode updateIonSourceOptimization(int ionSourceIndex, const char* ionSourceXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Updates ion source optimizations used with the current acquisition.  This is supported
        /// for non-switching acquisitions and acquisitions using ion source switching, but not for
        /// acquisitions using segments.  The new ion source settings will be applied when the next
        /// scan is scheduled.
        /// </summary>
        /// <param name="ionSourceIndex">Index of the ion source to be updated.  For non-switching
        ///                              acquisitions this should be 0, while for acquisitions using
        ///                              ion source switching this should be 0 or 1.</param>
        /// <param name="ionSourceXML">  XML text defining the updated ion source optimization to apply.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode updateIonSourceOptimization(int ionSourceIndex, const wchar_t* ionSourceXML);
    };
}
