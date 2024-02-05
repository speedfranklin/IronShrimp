// (C) Copyright 2012-2018 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "TuneScanManager.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Virtual class that provides callbacks when a tune scan has been completed.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API TuneScanListener
    {

    protected:

        friend class TuneScanManagerImpl;

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Default constructor.  Derived classes must ensure that this constructor is called, as
        /// it registers the object with the TuneScanManager.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        TuneScanListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Destructor.  Derived classes must ensure that this destructor is called, as it
        /// unregisters the object with the TuneScanManager.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~TuneScanListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called whenever the TuneScanManager has completed a tune scan. By
        /// overriding this method, derived classes can be notified of tune scan completions.
        /// </summary>
        /// <param name="index"> The index of the tune mass that was scanned (0-3).</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onTuneScanCompleted(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Called whenever a new progress report is available for the current Test Performance,
        /// Calibrate, or Auto-Tune operation.  Returns the number of tuning scans that have been
        /// completed so far in the operation.  The expected total number of scans in such
        /// operations can be requested from TuneScanManager before beginning the operation.
        /// </summary>
        /// <param name="numScansDone"> The number of scans completed so far.</param>
        /// <param name="task">         Identifies the specific task of the operation that is
        ///                             currently being performed.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onProgressUpdated(int numScansDone, TuningTask task);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Called when each auto-tune "sweep" is beginning.  A sweep is a series of tuning scans
        /// during which the voltage of one tune parameter is incremented for each scan.  The
        /// information provided by this method can be useful when displaying graphs to monitor
        /// the auto-tune operation.
        /// </summary>
        /// <param name="numSteps"> The number of scans that will be performed during the sweep.</param>
        /// <param name="minVolts"> The minimum voltage that will be assigned to the parameter.</param>
        /// <param name="maxVolts"> The maximum voltage that will be assigned to the parameter.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onAutoTuneSweepStarting(int numSteps, double minVolts, double maxVolts);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Called after each scan of an auto-tune operation is completed.  Note that
        /// onTuneScanCompleted will also be called after each tune scan during an auto-tune
        /// operation.  The information provided by this method can be useful when displaying
        /// graphs to monitor the auto-tune operation.
        /// </summary>
        /// <param name="scanIndex">  The index of this scan within its "sweep" (see
        ///                           onAutoTuneSweepStarting).</param>
        /// <param name="voltage">    The tune parameter voltage used for the scan.</param>
        /// <param name="intensity">  The peak signal intensity for the scan.</param>
        /// <param name="resolution"> The peak resolution for the scan (in m/z).  The auto-tuning
        ///                           algorithm targets a resolution of 0.6, with values from
        ///                           0.5 to 0.7 being acceptable.</param>
        /// <param name="shape">      The peak shape for the scan.  The shape is a measure of the
        ///                           peak symmetry around its centroid, taken at half the peak
        ///                           height, with an ideal shape being 0.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onAutoTuneScanFinished(int scanIndex, double voltage, double intensity, double resolution, double shape);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Called when the auto-tune operation sets the value of any tune parameter.  This may
        /// occur during the operation's initialization phase, and again after some component of
        /// the operation has been completed and a new value has been determined.  This method
        /// can be useful for updating a tune parameter user interface during or after the auto-
        /// tune operation.
        /// </summary>
        /// <param name="param"> The tune parameter that changed.</param>
        /// <param name="value"> The new value.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onTuneParameterChanged(TuneParameter param, double value);

    private:
        int numThreads;
    };
}
