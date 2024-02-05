// (C) Copyright 2014-2016 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

namespace AdvionObjects
{
    /// <summary>Defines the different types of error codes which be returned when parsing XML.</summary>
    enum ErrorCode
    {
        ADVIONOBJECTS_OK                       = 0, ///< No errors from parsing XML.
        ADVIONOBJECTS_PARSING_FAILED           = 1, ///< Parsing by LMX failed and reported an error.
        ADVIONOBJECTS_MINOR_VERSION_WARNING    = 2, ///< The minor version number of the file does not match the expected version.  This may be safely ignored.
        ADVIONOBJECTS_MAJOR_VERSION_ERROR      = 3, ///< The major version number of the file does not match the expected version, so the file cannot be parsed.
        ADVIONOBJECTS_NO_VERSION               = 4, ///< The version number of the file cannot be read.  This file cannot be parsed.
    };
}

//=================================================================================================

#ifdef LINUX
    #define ADVION_OBJECTS_API
#else
    #ifdef ADVION_OBJECTS_DLL
        #define ADVION_OBJECTS_API __declspec (dllexport)
    #else
        #define ADVION_OBJECTS_API __declspec (dllimport)
        #define LMX_WANT_GEN_IMPORT_DLL 1
    #endif // ADVION_OBJECTS_DLL
#endif // LINUX
