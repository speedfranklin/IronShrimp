// (C) Copyright 2012-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "Instrument.h"

namespace AdvionCMS
{
    /// <summary>
    /// Defines the different types of auto-tuning operations.  ResolutionOnlyTune is the only level which currently
    /// works reliably.  All other parameters besides resolution should not need to be adjusted regularly, and
    //  the corresponding auto-tune levels are experimental and their use is not recommended.
    /// </summary>
    enum TuningLevel
    {
        ResolutionOnlyTune,             ///< Only tune the two resolution parameters.  This level has been tested carefully and works reliably.
        RegularTune,                    ///< Tune all parameters, but assume peaks can be seen.  This level is experimental and does not work reliably.
        FindPeaksTune,                  ///< Search for peaks, then tune all parameters.  This level is experimental and does not work reliably.
        DetectorGainTune                ///< Only tune the detector gain parameter.  This level is experimental and does not work reliably.
    };

    /// <summary>
    /// Defines the individual tasks that can make up an auto-tuning operation.
    /// </summary>
    enum TuningTask
    {
        TestingPerformance,             ///< Evaluating peak location, intensity, and resolution.
        Calibrating,                    ///< Calculating a mass calibration.
        CalculatingBaseline,            ///< Calculating a signal baseline to aid in peak detection.
        CenteringPeaks,                 ///< Finding nearby peaks and centering the tune windows on those peaks.
        TuningExtractionElectrode,      ///< Tuning the Extraction Electrode parameter.
        TuningHexapoleBias,             ///< Tuning the Hexapole Bias parameter.
        TuningResolution,               ///< Tuning the ramping Resolution parameters.
        TuningIonEnergyAndResolution,   ///< Simultaneously tuning the Ion Energy and Resolution ramping parameters.
        TuningDetectorGain              ///< Tuning the Detector Gain parameter.
    };

    /// <summary>
    /// Defines the different mass calibration levels.
    /// </summary>
    enum MassCalibrationLevel
    {
        SlowSpeed,                      ///< Performs a calibration at 40 m/z per second.
        DefaultSpeed,                   ///< Performs calibrations at 40, 1000, and 2000 m/z per second.
        HighSpeed                       ///< Performs calibrations at 40, 1000, 2000, 5000, and 10000 m/z per second.
    };

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// The static TuneScanManager class controls the tune scanning that is performed on the
    /// Advion CMS and reports its results.  Tune scanning allows an application to easily get
    /// real-time scanning results while ion source or tune parameters are interactively changed.
    /// This class provides methods that define the way the tuning scans are to be performed.  Other
    /// methods allow an application to retrieve the spectral data produced by the most recent
    /// tuning scans.  Tuning scans are performed whenever the InstrumentController state is Operate
    /// and there is no acquisition underway.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API TuneScanManager
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the maximum number of tuning masses that may be specified in setTuningMasses().
        /// </summary>
        /// <returns>The maximum number of tuning masses.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxNumTuneMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the maximum number of samples that will be returned by any tuning scan.  This
        /// value is useful for allocating memory before retrieving scan results.
        /// </summary>
        /// <returns>The maximum number of samples per scan.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxNumSamples();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the minimum scan time for a tuning mass.</summary>
        /// <returns>The minimum scan time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMinScanTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the maximum scan time for a tuning mass.</summary>
        /// <returns>The maximum scan time in milliseconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getMaxScanTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Sets the smoothing parameters to be used when tune scanning.  If radius or times are
        /// zero, no smoothing will be performed. Values of 7 for radius and 1 for times are
        /// recommended for adequate tune scan smoothing.
        /// </summary>
        /// <param name="radius">[in] The radius, in samples, over which to perform smoothing.</param>
        /// <param name="times"> [in] The number of times to smooth the spectral data.</param>
        ///-------------------------------------------------------------------------------------------------
        static void setSmoothing(int radius, int times);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Defines the set of masses that will be scanned during successive tuning scans.
        /// The massSpans, scanTimes, and delays are reset to fixed values when auto-tuning,
        /// so values set with this method are used only when operating the instrument in tuning
        /// mode without invoking the auto-tuner.  The startMasses are used by the auto-tuner.
        /// </summary>
        /// <param name="num">        [in] Number of masses being specified.  Must be no greater
        ///                                than the value returned by getMaxNumTuneMasses().</param>
        /// <param name="startMasses">[in] An array of the starting mass values for each scan, in m/z.</param>
        /// <param name="massSpans">  [in] An array of the mass spans for each scan, in m/z.</param>
        /// <param name="scanTimes">  [in] An array of the durations for each scan, in milliseconds.</param>
        /// <param name="delays">     [in] An array of the pre-scan delay times for each scan, in
        ///                                microseconds.  The recommended value is 10.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setTuningMasses(int num, double startMasses[], double massSpans[],
                                         double scanTimes[], double delays[]);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current number of tuning masses.</summary>
        /// <returns>The number of tuning masses.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumTuningMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the number of samples produced by the last scan of the identified tuning mass.
        /// </summary>
        /// <param name="index">[in] Index of the tuning mass.  Must be less than the number of masses
        ///                          passed in setTuningMasses().</param>
        /// <returns>The number of samples in the tuning scan.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getLastNumSamples(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the sample masses from the last scan of the identified tuning mass.
        /// </summary>
        /// <param name="index"> [in] Index of the tuning mass.  Must be less than the number of masses
        ///                           passed in setTuningMasses().</param>
        /// <param name="masses">[out] If non-null, will be filled with the mass values.  Must be
        ///                            allocated by the application to be at least as large as the
        ///                            value returned by getLastNumSamples().</param>
        ///-------------------------------------------------------------------------------------------------
        static void getLastMasses(int index, double* masses);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the last intensities.</summary>
        /// <param name="index">      [in] Index of the tuning mass.  Must be less than the number of
        ///                                masses passed in setTuningMasses().</param>
        /// <param name="intensities">[out] If non-null, will be filled with the intensity values.
        ///                                 Must be allocated by the application to be at least as
        ///                                 large as the value returned by getLastNumSamples().</param>
        ///-------------------------------------------------------------------------------------------------
        static void getLastIntensities(int index, double* intensities);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if the API will accept a request to calibrate or auto-tune right now.
        /// </summary>
        /// <returns>true if we can calibrate and auto-tune, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canCalibrateAndAutoTune();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the approximate number of tuning scans that would be performed by a test
        /// performance operation.  Can be used to present progress information during the
        /// operation.
        /// </summary>
        /// <returns>The number of tuning scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumTestPerformanceScans();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Tests the performance of the current instrument tuning.  A series of tuning scans
        /// are performed on the current set of tuning masses and the results are analyzed to
        /// determine each peak's centroid (mass), maximum intensity, and resolution.  Results
        /// are returned in the preallocated arrays, which are assumed to be as large as the
        /// current number of tuning masses.  Blocks the current thread until the operation is
        /// complete or canceled.  Operation progress can be monitored by overriding
        /// TuneScanListener::onProgressUpdated.
        /// </summary>
        /// <param name="masses">     [out] The peak mass centroids.</param>
        /// <param name="intensities">[out] The peak intensities.</param>
        /// <param name="resolutions">[out] The peak resolutions.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode testPerformance(double* masses, double* intensities, double* resolutions);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the approximate number of tuning scans that would be performed by a mass
        /// calibration operation.  The calibration is performed at a scan speed of 40 m/z
        /// per second.  Can be used to present progress information during the operation.
        /// </summary>
        /// <returns>The number of tuning scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        static int getNumCalibrateMassesScans();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Calculates a mass calibration for the current instrument settings using the current tuning
        /// masses.  The calibration is performed at a scan speed of 40 m/z per second.  A series of
        /// tuning scans are performed and the results are analyzed to determine a piece-wise linear
        /// calibration transformation.  This transformation is applied to the current tuning parameters,
        /// and may be retrieved as an XML string by calling InstrumentController::getTuneParameters.
        /// Blocks the current thread until the operation is complete or canceled.  Operation progress
        /// can be monitored by overriding TuneScanListener::onProgressUpdated.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        static ErrorCode calibrateMasses();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the approximate number of tuning scans that would be performed by a multi-speed
        /// mass calibration operation.  Can be used to present progress information during the
        /// operation.
        /// </summary>
        /// <param name="calibrationLevel">[in] Level of the mass calibration.</param>
        /// <returns>The number of tuning scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumCalibrateMassesScans(MassCalibrationLevel calibrationLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Calculates a multi-speed mass calibration for the current instrument settings using the
        /// current tuning masses.  The calibration is performed at scan speeds determined by the
        /// mass calibration level.  At each speed, a series of tuning scans are performed and the
        /// results are analyzed to determine a piece-wise linear calibration transformation.  The
        /// overall transformation is applied to the current tuning parameters, and may be retrieved
        /// as an XML string by calling InstrumentController::getTuneParameters.  Blocks the current
        /// thread until the operation is complete or canceled.  Operation progress can be monitored
        /// by overriding TuneScanListener::onProgressUpdated.
        /// </summary>
        /// <param name="calibrationLevel">[in] Level of the mass calibration.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode calibrateMasses(MassCalibrationLevel calibrationLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the approximate number of tuning scans that would be performed by an auto-tuning
        /// operation of the specified type.  Can be used to present progress information during
        /// the operation.
        /// </summary>
        /// <param name="tuningLevel">[in] The tune level for the auto-tune.</param>
        /// <returns>The number of tuning scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumAutoTuneInstrumentScans(TuningLevel tuningLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Automatically determines the best values for some or all of the instrument's tune
        /// parameters, as determined by the "tuningLevel" parameter.  Currently only resolution tuning
        /// is stable, and the use of other levels is experimental.  A series of tuning scans are
        /// performed using the current tuning masses and the results are analyzed to determine the
        /// optimal parameter values.  The resulting values are assigned to the instrument, and
        /// may be retrieved as an XML string by calling InstrumentController::getTuneParameters.
        /// Blocks the current thread until the operation is complete or canceled.  Operation
        /// progress can be monitored by overriding TuneScanListener's onProgressUpdated,
        /// onAutoTuneSweepStarting, onAutoTuneScanFinished and onTuneParameterChanged methods.
        /// Should not be invoked when using a SimulatedInstrument, as that instrument does not
        /// alter its simulated signal in response to tune parameter changes.
        /// </summary>
        /// <param name="tuningLevel">[in] Level of the tune.  Use of levels other than ResolutionOnlyTune is not recommended.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode autoTuneInstrument(TuningLevel tuningLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the approximate number of tuning scans that would be performed by an auto-tuning
        /// operation of the specified type.  Can be used to present progress information during
        /// the operation.
        /// </summary>
        /// <param name="tuningLevel">     [in] The tune level for the auto-tune.</param>
        /// <param name="calibrationLevel">[in] Level of the mass calibration performed after the auto-tune completes.</param>
        /// <returns>The number of tuning scans.</returns>
        ///-------------------------------------------------------------------------------------------------
        static int getNumAutoTuneInstrumentScans(TuningLevel tuningLevel, MassCalibrationLevel calibrationLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Automatically determines the best values for some or all of the instrument's tune
        /// parameters, as determined by the "tuningLevel" parameter.  Currently only resolution tuning
        /// is stable, and the use of other levels is experimental.  A series of tuning scans are
        /// performed using the current tuning masses and the results are analyzed to determine the
        /// optimal parameter values.  The resulting values are assigned to the instrument, and
        /// may be retrieved as an XML string by calling InstrumentController::getTuneParameters.
        /// Blocks the current thread until the operation is complete or canceled.  Operation
        /// progress can be monitored by overriding TuneScanListener's onProgressUpdated,
        /// onAutoTuneSweepStarting, onAutoTuneScanFinished and onTuneParameterChanged methods.
        /// Should not be invoked when using a SimulatedInstrument, as that instrument does not
        /// alter its simulated signal in response to tune parameter changes.
        /// </summary>
        /// <param name="tuningLevel">     [in] Level of the tune.  Use of levels other than ResolutionOnlyTune is not recommended.</param>
        /// <param name="calibrationLevel">[in] Level of the mass calibration performed after the auto-tune completes.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode autoTuneInstrument(TuningLevel tuningLevel, MassCalibrationLevel calibrationLevel);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Cancels any Test Performance, Calibrate, or Auto-Tune operation that is currently
        /// underway.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        static void cancel();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Set the output location for auto-tuner log files.  If not set, logs will not be saved.
        /// </summary>
        /// <param name="logFilePath">[in] The path where log files should be saved.</param>
        ///-------------------------------------------------------------------------------------------------
        static void setLogFile(const char* logFilePath);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Set the output location for auto-tuner log files.  If not set, logs will not be saved.
        /// </summary>
        /// <param name="logFilePath">[in] The path where log files should be saved.</param>
        ///-------------------------------------------------------------------------------------------------
        static void setLogFile(const wchar_t* logFilePath);
    };
}
