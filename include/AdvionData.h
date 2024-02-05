// (C) Copyright 2012-2018 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

namespace AdvionData
{
    enum ErrorCode
    {
        ADVIONDATA_OK                       =  0,
        ADVIONDATA_FILE_OPEN_FAILED         =  1,
        ADVIONDATA_FILE_WRITE_FAILED        =  2,
        ADVIONDATA_OUT_OF_MEMORY            =  3,
        ADVIONDATA_CREATE_DATX_FAILED       =  4,
        ADVIONDATA_OPEN_DATX_FAILED         =  5,
        ADVIONDATA_CHANNEL_NOT_DEFINED      =  6,
        ADVIONDATA_AUX_FILE_NOT_DEFINED     =  7,
        ADVIONDATA_DATA_VERSION_TOO_HIGH    =  8,
        ADVIONDATA_DATA_PARAMETER_IS_NULL   =  9,
        ADVIONDATA_PARSING_FAILED           = 10,
        ADVIONDATA_INDEX_OUT_OF_RANGE       = 11,
        ADVIONDATA_PARAMETER_OUT_OF_RANGE   = 12,
        ADVIONDATA_NO_SPECTRA               = 13,
        ADVIONDATA_CHANNEL_HEADER_CLOSED    = 14,
        ADVIONDATA_DATASET_FOLDER_LOCKED    = 15,
        ADVIONDATA_PATH_TOO_LONG            = 16,
    };
}

//=================================================================================================

#ifdef LINUX
    #define ADVION_DATA_API
#else
    #ifdef ADVION_DATA_DLL
        #define ADVION_DATA_API __declspec (dllexport)
    #else
        #define ADVION_DATA_API __declspec (dllimport)
        #define LMX_WANT_GEN_IMPORT_DLL 1
    #endif // ADVION_DATA_DLL
#endif // LINUX
