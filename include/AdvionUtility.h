// (C) Copyright 2017-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCommon.h"

namespace AdvionCommon
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Common utility methods.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_COMMON_API AdvionUtility
    {
    public:
        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the version of the software.</summary>
        /// <returns>A string representing the software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const char* getSoftwareVersion();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the version of the software.</summary>
        /// <returns>A string representing the software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const wchar_t* getSoftwareVersionW();
    };
}
