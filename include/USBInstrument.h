// (C) Copyright 2011-2016 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "Instrument.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Implementation of the Instrument base class that communicates with an Advion CMS via USB.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API USBInstrument : public Instrument
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Constructor.</summary>
        /// <param name="overrideSafeties"> (optional) true to override safeties.</param>
        /// <param name="overridePump">     (optional) true to override pump.</param>
        ///-------------------------------------------------------------------------------------------------
        USBInstrument(bool overrideSafeties = false, bool overridePump = false);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.</summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~USBInstrument();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Instructs the instrument to ignore certain safety-related states related to the ion
        /// source when determining if the instrument can be put into Operate mode. These states
        /// include the absence of an ion source and an indication that the ion source is not
        /// seated in its housing.  Use of this method is not recommended, as it can lead to
        /// operating conditions that are hazardous to users and to the well-being of the CMS
        /// instrument.
        /// </summary>
        /// <param name="value"> True to disable safeties, false to enable them.</param>
        ///-------------------------------------------------------------------------------------------------
        void setOverrideSafeties(bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Instructs the instrument to ignore certain safety-related states related to the turbo
        /// pump when determining if the instrument can be put into Operate mode. These states
        /// include whether the turbo pump is turned on and whether the Pirani pressure reading
        /// is sufficiently low.  Use of this method is not recommended, as it can lead to
        /// operating conditions that are hazardous to users and to the well-being of the CMS
        /// instrument.
        /// </summary>
        /// <param name="value"> True to ignore pump/pressure readings, false to respect them.</param>
        ///-------------------------------------------------------------------------------------------------
        void setOverridePump(bool value);
    };
}
