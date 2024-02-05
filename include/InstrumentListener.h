// (C) Copyright 2012-2018 by Advion, Inc. All Rights Reserved.
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
    /// Virtual class that provides callbacks when the instrument status values have been updated
    /// and when error messages are reported.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API InstrumentListener
    {

    protected:

        friend class InstrumentControllerImpl;

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Default constructor.  Derived classes must ensure that this constructor is called, as
        /// it registers the object with the InstrumentController.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        InstrumentListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Destructor.  Derived classes must ensure that this destructor is called, as it
        /// unregisters the object with the InstrumentController.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~InstrumentListener();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called whenever the InstrumentController has updated the instrument's
        /// status data.  By overriding this method, derived classes can be notified of status
        /// updates.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        virtual void onStatusUpdated();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// This method is called whenever the InstrumentController has an error to report. By
        /// overriding this method, derived classes can be notified of InstrumentController
        /// errors.
        /// </summary>
        /// <param name="code">     The error code from AdvionCMS.h.</param>
        /// <param name="severity"> The severity code from AdvionCMS.h.</param>
        ///-------------------------------------------------------------------------------------------------
        virtual void onErrorReported(int code, int severity);

    private:
        int numThreads;
    };
}
