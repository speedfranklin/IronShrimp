// (C) Copyright 2013-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "USBSerialDevice.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Provides limited control of a Rheodyne MRA valve connected to the computer via a
    /// serial-to-USB connection.  NOTE:  Not currently supported on Linux.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API MRAValve : public AdvionCommon::USBSerialDevice
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// The default constructor for an object that controls an MRA valve.  Typically, an
        /// instrument configuration will only contain one MRA valve, but it is allowable to
        /// instantiate more than one if they will be instructed to communicate with devices on
        /// different COM ports.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        MRAValve();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.  Disconnects from the valve.</summary>
        ///-------------------------------------------------------------------------------------------------
        ~MRAValve();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Connects to the device if possible.  The given default port number is tried first,
        /// followed by all valid COM ports.
        /// </summary>
        /// <param name="defaultPortNum"> (optional) The first port number to try when connecting.  Can
        ///                               be used to connect two different objects to different
        ///                               devices, or to speed up the connection process.</param>
        /// <returns>true if it succeeds, false if it fails.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    connect(int defaultPortNum = 1);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Turns on the valve if it is connected.</summary>
        /// <returns>true if it succeeds, false if it fails.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    turnOn();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Turns off the valve if it is connected.</summary>
        /// <returns>true if it succeeds, false if it fails.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    turnOff();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the valve's split factor.</summary>
        /// <param name="factor"> The split factor, which can be determined using a table in the
        ///                       Rheodyne documentation for the MRA valve.  Valid split
        ///                       factors range from 1 to 59.</param>
        /// <returns>
        /// true if it succeeds, false if it fails.  Failure can be due to a value out range.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        bool    setSplitFactor(int factor);

    protected:

        virtual unsigned long   getDefaultBaudRate() /*override*/;
        virtual const char      getResponseTerminator() /*override*/;
        virtual const char*     getValidationCommand() /*override*/;
        virtual const char*     getValidationResponse() /*override*/;
        virtual int             getValidationLength() /*override*/;

    private:

        const char*     getSuccessResponse();
        bool            sendCommand(const char* command, bool waitForResponse = true);

    private:

        bool            newFirmware;
    };
}
