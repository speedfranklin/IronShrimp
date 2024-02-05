// (C) Copyright 2012-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Virtual class that provides callbacks when acquisition scanning starts or ends, and after
    /// each acquisition scan is completed.  This constructor for the AcquisitionListener automatically
    /// adds it as a listener to the AcquisitionManager class so that it can provide these callbacks.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API AcquisitionListener
    {

    protected:

        friend class AcquisitionManagerImpl;

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Default constructor.  Derived classes must ensure that this constructor is called, as
        /// it registers the object with the AcquisitionManager.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        AcquisitionListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Destructor.  Derived classes must ensure that this destructor is called, as it
        /// unregisters the object with the AcquisitionManager.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~AcquisitionListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called when the AcquisitionManager begins an acquisition.  By
        /// overriding this method, derived classes can be notified of an acquisition starting.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual void onAcquisitionStarted();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called whenever the AcquisitionManager has completed a scan.  By
        /// overriding this method, derived classes can be notified of acquisition scan
        /// completions.  For SIM scanning, this method is called once after all specified SIM
        /// masses have been scanned (not once for each SIM mass).
        /// </summary>
        /// <param name="index"> The index of the scan in the acquisition.  Values can range from
        ///                      0 to no more than the value returned by
        ///                      AcquisitionManager::getMaxNumScans().  This index is irrespective
        ///                      of which ion source was used for the most recent scan.  To obtain
        ///                      an index relative to the most recent ion source (when using
        ///                      source switching), call AcquisitionManager::getLastScanIndex().</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onScanCompleted(int index);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called when the AcquisitionManager finishes an acquisition.  The
        /// callback is made regardless of whether the acquisition finishes normally or is
        /// terminated early for some reason.  By overriding this method, derived classes can
        /// be notified of an acquisition finishing.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual void onAcquisitionFinished();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called when the AcquisitionManager writes information to the
        /// log of the current data file.  By overriding this method, derived classes can be
        /// notified of all information logged by the AcquisitionManager.
        /// Note that both the narrow and wide versions of this method will be called for all logging events,
        /// so listeners need only to implement the method with the preferred character type.
        /// </summary>
        /// <param name="text">The text that was written to the log file.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onWriteLogMessage(const char* text);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called when the AcquisitionManager writes information to the
        /// log of the current data file.  By overriding this method, derived classes can be
        /// notified of all information logged by the AcquisitionManager.
        /// Note that both the narrow and wide versions of this method will be called for all logging events,
        /// so listeners need only to implement the method with the preferred character type.
        /// </summary>
        /// <param name="text">The text that was written to the log file.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onWriteLogMessage(const wchar_t* text);

    private:
        int numThreads;
    };
}
