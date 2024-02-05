// (C) Copyright 2016-2017 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// A set of utilities for processing mass spectrometry data.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API DataProcessor
    {

    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Detect peaks in the provided data using the provided peak detection setup.
        /// </summary>
        /// <param name="xValues">     An array of x values of the data points.</param>
        /// <param name="yValues">     An array of y values of the data points.</param>
        /// <param name="numIndices">  The number of data points in the provided data set.</param>
        /// <param name="peakDetectionSetup"> XML text defining PeakDetection to use.</param>
        /// <returns>An XML string defining a PeakList which contains detected peaks.
        /// Caller is responsible for freeing this string.</returns>
        ///-------------------------------------------------------------------------------------------------
        static char* detectPeaks(double* xValues, double* yValues, int numIndices, const char* peakDetectionSetup);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Detect peaks in the provided data using the provided peak detection setup.
        /// </summary>
        /// <param name="xValues">     An array of x values of the data points.</param>
        /// <param name="yValues">     An array of y values of the data points.</param>
        /// <param name="numIndices">  The number of data points in the provided data set.</param>
        /// <param name="peakDetectionSetup"> XML text defining PeakDetection to use.</param>
        /// <returns>An XML string defining a PeakList which contains detected peaks.
        /// Caller is responsible for freeing this string.</returns>
        ///-------------------------------------------------------------------------------------------------
        static wchar_t* detectPeaks(double* xValues, double* yValues, int numIndices, const wchar_t* peakDetectionSetup);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Filter the provided data by taking a moving average of radius points on each side
        /// of each data point.  The total filter width is 2*radius +1.
        /// At the ends of the data set, the radius is reduced so that the
        /// filter does not extend beyond the ends of the data set.
        /// </summary>
        /// <param name="yIn">        An array of data points to filter.</param>
        /// <param name="yOut">       An array to hold the filtered data.  Must be allocated
        ///                             hold at least num values.</param>
        /// <param name="numIndices"> Number of points in the data set.</param>
        /// <param name="radius">     Number of points on each side of the current point
        ///                             to include when averaging.</param>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode filterBoxCar(double* yIn, double* yOut, int numIndices, int radius);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Filter the provided data using a quadratic Savitzky-Golay filter.
        /// This filter fits a quadratic function to radius points on each side
        /// of each data point, and then sets the fitered result to the fit value
        /// at the data point.  The total filter width is 2*radius +1.
        /// </summary>
        /// <param name="yIn">        An array of data points to filter.</param>
        /// <param name="yOut">       An array to hold the filtered data.  Must be allocated
        ///                             hold at least num values.</param>
        /// <param name="numIndices"> Number of points in the data set.</param>
        /// <param name="radius">     Number of points on each side of the current point
        ///                             to include when filtering.</param>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode filterQuadraticSG(double* yIn, double* yOut, int numIndices, int radius);
    };
}
