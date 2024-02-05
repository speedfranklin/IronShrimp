// (C) Copyright 2013-2018 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionObjects.h"
#include "lmxtypes.h"

namespace AdvionObjects
{
    class c_method;
    class c_ionSourceOptimization;
    class c_tuneParameters;
    class c_processMethod;
    class c_peakList;
    class c_peakDetection;

    class ADVION_OBJECTS_API ObjectUtility
    {

    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Serialize a method object model into a text string.  Such strings can be stored in
        /// files or databases for reuse by an application.
        /// </summary>
        /// <param name="method"> The method to serialize.</param>
        /// <returns>
        /// An XML string representing the object, or Null if serialization fails.
        /// The application owns the returned data and is responsible for freeing it.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* serializeMethod(const c_method& method);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Serialize an ion source optimization object model into a text string.  Such strings
        /// can be stored in files or databases for reuse by an application.
        /// </summary>
        /// <param name="ionSource"> The ion source object to serialize.</param>
        /// <returns>
        /// An XML string representing the object, or Null if serialization fails.
        /// The application owns the returned data and is responsible for freeing it.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* serializeIonSource(const c_ionSourceOptimization& ionSource);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Serialize a CMS tune parameters object model into a text string.  Such strings can be
        /// stored in files or databases for reuse by an application.
        /// </summary>
        /// <param name="tuneParams"> The CMS tune parameters object to serialize.</param>
        /// <returns>
        /// An XML string representing the object, or Null if serialization fails.
        /// The application owns the returned data and is responsible for freeing it.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* serializeTuneParameters(const c_tuneParameters& tuneParams);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Serialize a process method object model into a text string.  Such strings can be
        /// stored in files or databases for reuse by an application.
        /// </summary>
        /// <param name="processMethod"> The process method to serialize.</param>
        /// <returns>
        /// An XML string representing the object, or Null if serialization fails. The
        /// application owns the returned data and is responsible for freeing it.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* serializeProcessMethod(const c_processMethod& processMethod);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Serialize a peak list object model into a text string.  Such strings can be
        /// stored in files or databases for reuse by an application.
        /// </summary>
        /// <param name="peakList"> The peak list to serialize.</param>
        /// <returns>
        /// An XML string representing the object, or Null if serialization fails. The
        /// application owns the returned data and is responsible for freeing it.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* serializePeakList(const c_peakList& peakList);


        ///-------------------------------------------------------------------------------------------------
        /// <summary>Create a method object model by parsing the provided XML string.</summary>
        /// <param name="methodXML"> An XML string representing a method.</param>
        /// <param name="errorCode"> Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                          if it failed.</param>
        /// <returns>The method object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_method parseMethod(const char* methodXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Create an ion source optimization object model by parsing the provided XML string.
        /// </summary>
        /// <param name="ionSourceXML"> An XML string representing an ion source optimization.</param>
        /// <param name="errorCode">    Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                             if it failed.</param>
        /// <returns>The ion source optimization object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_ionSourceOptimization parseIonSource(const char* ionSourceXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Create a CMS tune parameters object model by parsing the provided XML string.
        /// </summary>
        /// <param name="tuneXML">   An XML string representing CMS tune parameters.</param>
        /// <param name="errorCode"> Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                          if it failed.</param>
        /// <returns>The CMS tune parameters object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_tuneParameters parseTuneParameters(const char* tuneXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Create a process method object model by parsing the provided XML string.
        /// </summary>
        /// <param name="procMethodXML"> An XML string representing a process method.</param>
        /// <param name="errorCode">     Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                              if it failed.</param>
        /// <returns>The process method object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_processMethod parseProcessMethod(const char* procMethodXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Create a peak list object model by parsing the provided XML string.
        /// </summary>
        /// <param name="peakListXML"> An XML string representing a peak list.</param>
        /// <param name="errorCode">   Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                            if it failed.</param>
        /// <returns>The peak list object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_peakList parsePeakList(const char* peakListXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Create a peak detection object model by parsing the provided XML string.
        /// </summary>
        /// <param name="peakDetectionXML"> An XML string representing a peak detection setup.</param>
        /// <param name="errorCode">        Returns AdvionObjects_OK if parsing succeeded or an error code
        ///                                 if it failed.</param>
        /// <returns>The peak detection object model.</returns>
        ///-------------------------------------------------------------------------------------------------
        static c_peakDetection parsePeakDetection(const char* peakDetectionXML, ErrorCode* errorCode);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Check if the ErrorCode returned from parsing an XML object indicates that
        /// the returned object should not be used.
        /// </summary>
        /// <param name="errorCode"> ErrorCode returned from parsing an XML object.</param>
        /// <returns>False for ADVIONOBJECTS_OK and ADVIONOBJECTS_MINOR_VERSION_WARNING,
        ///        and true for other error codes, which should not be ignored.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static bool isErrorCritical(ErrorCode* errorCode);

    protected:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Parse the major and minor version numbers from the input versionString.
        /// For version XX.YY.ZZ, XX is major version, YY is minor version, and ZZ
        /// is ignored.
        /// </summary>
        /// <param name="versionString">String containing version number.</param>
        /// <param name="majorVersion">Output major version.</param>
        /// <param name="minorVersion">Output minor version.</param>
        /// <returns>False on parse failure.</returns>
        static bool parseVersion(const wchar_t* versionString, int* majorVersion, int* minorVersion);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Check if the version of an XML file matches the version expected by the code.
        /// </summary>
        /// <param name="fileVersion"> A string containing the version of the XML file. </param>
        /// <param name="codeVersion"> A string containing the version expected by the code. </param>
        /// <param name="errorCode"> The errorcode returned when parsing the XML with LMX.
        ///         This will be updated with any version errors detected.
        ///         For version XX.YY.ZZ:
        ///         ADVIONOBJECTS_MAJOR_VERSION_ERROR if XX does not match.
        ///         ADVIONOBJECTS_MINOR_VERSION_WARNING if YY does not match and input errorCode = ADVIONOBJECTS_OK.
        ///         Ignores mismatch of ZZ, and does not alter errorCode.
        /// </param>
        ///-------------------------------------------------------------------------------------------------
        static void checkVersion(const lmx::tlmx_unicode_string& fileVersion,
                                 const lmx::tlmx_unicode_string& codeVersion, ErrorCode* errorCode);
    };
}
