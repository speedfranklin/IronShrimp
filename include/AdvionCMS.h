// (C) Copyright 2012-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

namespace AdvionCMS
{
    enum SeverityCode
    {
        CMS_SEVERITY_INFORMATION        = 1,
        CMS_SEVERITY_WARNING            = 2,
        CMS_SEVERITY_ERROR              = 3,
        CMS_SEVERITY_FATAL              = 4,
    };

    enum ErrorCode
    {
        CMS_OK                          = 0,

        // USB / FIRMWARE
        CMS_NO_USB_CONNECTION           = 1,
        CMS_USB_CONNECTED               = 2,
        CMS_LOST_USB_CONNECTION         = 3,
        CMS_INCOMPATIBLE_FIRMWARE       = 4,

        // Instrument condition
        CMS_HIVOLT_OFF_BAD_VACUUM       = 10,
        CMS_STANDBY_IONSOURCE_REMOVED   = 11,
        CMS_STANDBY_IONSOURCE_UNPLUGGED = 12,
        CMS_VACUUM_TOO_LOW              = 13,
        CMS_VACUUM_OK                   = 14,

        // Acquisition errors
        CMS_ALREADY_ACQUIRING           = 20,
        CMS_ALREADY_PAUSED              = 21,
        CMS_NOT_ACQUIRING               = 22,
        CMS_NOT_PAUSED                  = 23,
        CMS_NOT_WRITING_DATA            = 24,
        CMS_WRITE_FAILED                = 25,
        CMS_SWITCHING_NOT_ALLOWED       = 26,
        CMS_SEGMENTS_NOT_ALLOWED        = 27,
        CMS_SCAN_MODE_OUT_OF_RANGE      = 28,

        // Tune scanning errors
        CMS_TUNE_INDEX_OUT_OF_RANGE     = 30,

        // Instrument controller errors
        CMS_CONTROLLER_ALREADY_STARTED  = 40,
        CMS_CONTROLLER_NOT_STARTED      = 41,
        CMS_INSTRUMENT_IS_OPERATING     = 42,
        CMS_PUMP_ALREADY_ON             = 43,
        CMS_OPERATING_NOT_ALLOWED       = 44,
        CMS_STANDBY_NOT_ALLOWED         = 45,
        CMS_INSTRUMENT_NOT_OPERATING    = 46,
        CMS_PARSING_FAILED              = 47,
        CMS_INDEX_OUT_OF_RANGE          = 48,
        CMS_INSTRUMENT_TYPE_UNKNOWN     = 49,

        // AutoTune and Calibration Errors
        CMS_ALREADY_AUTO_TUNING         = 50,
        CMS_CANCELLED                   = 51,
        CMS_PEAKS_NOT_FOUND             = 52,
        CMS_COULD_NOT_AUTOTUNE          = 53,
        CMS_NOT_ENOUGH_TUNING_MASSES    = 54,

        // Acquisition limitations
        CMS_RANGE_SCAN_TIME_TOO_LOW     = 60,
        CMS_RANGE_SCAN_TIME_TOO_HIGH    = 61,
        CMS_SIM_DWELL_TIME_TOO_LOW      = 62,
        CMS_SIM_DWELL_TIME_TOO_HIGH     = 63,
        CMS_SCAN_SPEED_TOO_HIGH         = 64,
        CMS_SIM_NO_MASSES               = 65,

        // Data processing
        CMS_DATA_READ_FAIL              = 70,
        CMS_INVALID_FILTER_PARAMS       = 71,

        // General
        CMS_PARAMETER_OUT_OF_RANGE      = 80,
        CMS_DATASET_FOLDER_LOCKED       = 81,
        CMS_PATH_TOO_LONG               = 82,
        CMS_NOT_LICENSED                = 83,
        CMS_NOT_SUPPORTED               = 84,
    };
}

//=================================================================================================

#ifdef LINUX
    #define ADVION_CMS_API
#else
    #ifdef ADVION_CMS_DLL
        #define ADVION_CMS_API __declspec (dllexport)
    #else
        #define ADVION_CMS_API __declspec (dllimport)
    #endif // ADVION_CMS_DLL
#endif // LINUX
