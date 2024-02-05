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
    /// Provides limited control of a Scientific Systems, Inc. (SSI) HPLC pump connected to the
    /// computer via a USB connection.  NOTE:  Not currently supported on Linux.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API SSIPump : public AdvionCommon::USBSerialDevice
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// The default constructor for an object that controls an SSI pump.  Typically, an
        /// instrument configuration will only contain one SSI pump, but it is allowable to
        /// instantiate more than one if they will be instructed to communicate with devices on
        /// different COM ports.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        SSIPump();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.  Disconnects from the pump.</summary>
        ///-------------------------------------------------------------------------------------------------
        ~SSIPump();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Turns on the pump if it is connected.</summary>
        /// <returns>True if it succeeds, false if it fails.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    turnOn();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Turns off the pump if it is connected.</summary>
        /// <returns>True if it succeeds, false if it fails.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    turnOff();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the pump's flow rate.</summary>
        /// <param name="rate">The flow rate in mL/min.</param>
        /// <returns>
        /// True if it succeeds, false if it fails.  Failure can be due to an unconnected pump
        /// or a specified flow-rate that is out of range for the pump's current configuration.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        bool    setFlowRate(double rate);

        bool    setUpperLimit(double rate);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Query if the pump is turned on.</summary>
        /// <returns>True if turned on, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool    isTurnedOn();

        char* readCurrentCondition();
        char* readCurrentSetup();
        char* readFault();

    protected:

        virtual unsigned long   getDefaultBaudRate() /*override*/;
        virtual const char      getResponseTerminator() /*override*/;
        virtual const char*     getValidationCommand() /*override*/;
        virtual const char*     getValidationResponse() /*override*/;
        virtual int             getValidationStart() /*override*/;
        virtual int             getValidationLength() /*override*/;
        virtual bool            secondaryValidationCheck(const char* response) /*override*/;

    private:

        char            response[BUFFER_LEN];
        bool            sendCommand(const char* command);
        const char*     getOKResponse();
    };
}
