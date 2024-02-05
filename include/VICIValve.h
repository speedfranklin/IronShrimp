// (C) Copyright 2016-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "USBSerialDevice.h"
#ifdef LINUX
#include <cstring>
#endif

/// <summary>Defines the current position of the VICI valve.</summary>
typedef enum
{
    PositionA,         ///< Valve at position A.
    PositionB,         ///< Valve at position B.
    PositionUnknown    ///< Valve position could not be read.
} VICIValvePosition;

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Provides limited control of a VICI valve  NOTE:  Not currently supported on Linux.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API VICIValve : public AdvionCommon::USBSerialDevice
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// The default constructor for an object that controls a VICI valve.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        VICIValve();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.  Disconnects from the VICI valve.</summary>
        ///-------------------------------------------------------------------------------------------------
        ~VICIValve();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Read current position of VICI Valve (A or B) using "CP" command.</summary>
        /// <param name="responseCopy">(optional) string to hold raw output from device.</param>
        /// <param name="responseLength">(optional) length of string to hold raw output from device.</param>
        /// <returns>An enum defining the valve position (A, B, or unknown).</returns>
        ///-------------------------------------------------------------------------------------------------
        VICIValvePosition  readCurrentPosition(char* responseCopy = NULL, int responseLength = 0);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Move valve to position A using command "GOA".</summary>
        ///-------------------------------------------------------------------------------------------------
        void   setPositionA();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Move valve to position B using command "GOB".</summary>
        ///-------------------------------------------------------------------------------------------------
        void   setPositionB();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Read current position of VICI Valve (A or B) using "CP" command.</summary>
        /// <param name="pos">Enum defining valve position.</param>
        /// <returns>A human-readable string describing the valve position (A, B, or Unknown).</returns>
        ///-------------------------------------------------------------------------------------------------
        const char*  positionToString(VICIValvePosition pos);

    protected:

        // Implementation of abstract methods from USBSerialDevice.
        virtual unsigned long   getDefaultBaudRate() /*override*/;
        virtual const char      getResponseTerminator() /*override*/;
        virtual const char*     getValidationCommand() /*override*/;
        virtual const char*     getValidationResponse() /*override*/;
        virtual int             getValidationLength() /*override*/;
        virtual bool            secondaryValidationCheck(const char* response) /*override*/;

    private:

        // Buffer to hold responses from valve.
        char response[BUFFER_LEN];
    };
}
