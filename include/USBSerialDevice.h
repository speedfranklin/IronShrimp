// (C) Copyright 2013-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCommon.h"

#ifdef LINUX

#define CBR_110             110
#define CBR_300             300
#define CBR_600             600
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_19200           19200
#define CBR_38400           38400
#define CBR_56000           56000
#define CBR_57600           57600
#define CBR_115200          115200
#define CBR_128000          128000
#define CBR_256000          256000

#endif

#define BUFFER_LEN  1024

namespace AdvionCommon
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Virtual class for auxiliary devices that use serial communication over a USB connection.
    /// NOTE: Not currently supported on Linux.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_COMMON_API USBSerialDevice
    {
    public:

        USBSerialDevice();
        virtual ~USBSerialDevice();

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
        virtual bool    connect(int defaultPortNum = 1);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Disconnects from the device.</summary>
        ///-------------------------------------------------------------------------------------------------
        void            disconnect();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Query if this object is connected to the associated device.</summary>
        /// <returns>true if connected, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool            isConnected();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the device's COM port.</summary>
        /// <returns>The device's COM port, which is only valid if the device is connected.</returns>
        ///-------------------------------------------------------------------------------------------------
        int             getCOMPort();

    protected:

        // Sending commands to instrument
        bool            sendCommand(const char* cmd, char* response, bool waitForResponse = true);

        // Sending command with no response expected.
        bool            sendCommand(const char* cmd);

        // Device-specific information
        virtual unsigned long   getDefaultBaudRate()    = 0;
        virtual const char      getResponseTerminator() = 0;

        virtual const char*     getValidationCommand()  = 0;
        virtual const char*     getValidationResponse() = 0; // Expected validation response string.
        virtual int             getValidationStart() { return 0; } // Start comparison at this position.
        virtual int             getValidationLength() = 0; // Compare this many characters.

        /// <summary>Check for other valid responses to validation command.</summary>
        /// <param name="response">The instrument's response to the validation command.</param>
        /// <returns>True if the response if valid, false if invalid.</returns>
        virtual bool            secondaryValidationCheck(const char* response);

        /// The amount of time (in ms) which should be waited after sending a command
        /// for which no reponse is expected using sendCommand(char* cmd).
        /// Default value is 10 ms, and can be overridden with device-specific value.
        virtual int             getCommandDelay();
        virtual bool            testPort(unsigned int i);

    private:

        // Initializing COM port
        bool            findAndOpenPort();
        void            initPortTimeouts(void* port);
        bool            configurePort(void* port);

        // Talk to the instrument
        bool            validate(bool retry);
        virtual bool    writeString(const char* command);
        bool            readString(char* response, bool waitForResponse = false);

        int             comPort;
        void*           port;
        char            buffer[BUFFER_LEN];

        enum ConnectionState
        {
            NOT_CONNECTED,
            CONNECTING,
            ABORTING,
            CONNECTED,
        };
        ConnectionState connectionState;
    };
}
