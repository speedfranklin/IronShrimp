// (C) Copyright 2017 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#ifdef LINUX
    #define ADVION_COMMON_API
#else
    #ifdef ADVION_COMMON_DLL
        #define ADVION_COMMON_API __declspec (dllexport)
    #else
        #define ADVION_COMMON_API __declspec (dllimport)
    #endif // ADVION_CMS_DLL
#endif // LINUX