// (C) Copyright 2011-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"
#include "Instrument.h"

namespace AdvionCMS
{
    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// An implementation of the Instrument base class that simulates the behavior of a real
    /// Advion CMS instrument.  The instrument has fixed behavior, but can be useful for testing
    /// an application's overall framework.  The instrument's tune scans only see peaks at the
    /// locations of the four masses in the Advion Positive calibrant.  Its range acquisition
    /// scans return a simulation of an LC acquisition, with peaks appearing in the mass range
    /// m/z 100 to 600.  When performing acquisitions using a Selected Ion Monitoring (SIM) method,
    /// signals are returned for all specified SIM masses, with intensity proportional to the
    /// dwell time at the mass.  Methods are provided to simulate the state of various physical
    /// aspects of a real CMS.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API SimulatedInstrument : public Instrument
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Constructor.</summary>
        /// <param name="tempFolder">Path of a folder where the engine can save a file representing
        ///                          its state. This state file is loaded in later invocations of
        ///                          the instrument, allowing one to test the application's
        ///                          response to various system configuration conditions.</param>
        ///-------------------------------------------------------------------------------------------------
        explicit SimulatedInstrument(const char* tempFolder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Constructor.</summary>
        /// <param name="tempFolder">Path of a folder where the engine can save a file representing
        ///                          its state. This state file is loaded in later invocations of
        ///                          the instrument, allowing one to test the application's
        ///                          response to various system configuration conditions.</param>
        ///-------------------------------------------------------------------------------------------------
        explicit SimulatedInstrument(const wchar_t* tempFolder);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.</summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~SimulatedInstrument();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the CMS hardware type for the instrument.</summary>
        /// <param name="type">Type of the CMS hardware.</param>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        void setHardwareType(HardwareType type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the ion source type for the instrument.</summary>
        /// <param name="type">Type of the ion source.</param>
        ///-------------------------------------------------------------------------------------------------
        /// \deprecated This method has been deprecated and will be removed in an upcoming release.
        void setSourceType(SourceType type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the simulated CMS hardware type for the instrument.</summary>
        /// <param name="type">Type of the CMS hardware to simulate.</param>
        ///-------------------------------------------------------------------------------------------------
        void setSimulatedHardwareType(HardwareType type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the simulated CMS hardware type for the instrument.</summary>
        /// <returns>The simulated CMS hardware type.</returns>
        ///-------------------------------------------------------------------------------------------------
        HardwareType getSimulatedHardwareType();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the simulated ion source type for the instrument.</summary>
        /// <param name="type">Type of the ion source to simulate.</param>
        ///-------------------------------------------------------------------------------------------------
        void setSimulatedSourceType(SourceType type);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the simulated ion source type for the instrument.</summary>
        /// <returns>The simulated ion source type.</returns>
        ///-------------------------------------------------------------------------------------------------
        SourceType getSimulatedSourceType();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets whether the specified upgrade is licensed on the current instrument.</summary>
        /// <param name="upgrade">The upgrade to set.</param>
        /// <param name="value">True to enable the upgrade, false to disable it.</param>
        ///-------------------------------------------------------------------------------------------------
        void setSimulatedLicensedUpgrade(LicensableUpgrade upgrade, bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets whether the specified upgrade is licensed on the current instrument.</summary>
        /// <param name="upgrade">The upgrade to check.</param>
        /// <returns>True if the upgrade is licensed.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getSimulatedLicensedUpgrade(LicensableUpgrade upgrade);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the condition of the simulated USB communications.</summary>
        /// <param name="value">True for working communication, false otherwise.</param>
        ///-------------------------------------------------------------------------------------------------
        void setCommOK(bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the condition of the simulated USB communications.</summary>
        /// <returns>True for working communication, false otherwise.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getCommOK();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the state of the simulated ion source safety switch.</summary>
        /// <param name="value">True for correctly seated ion source, false otherwise.</param>
        ///-------------------------------------------------------------------------------------------------
        void setSafetySwitch(bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the state of the simulated ion source safety switch.</summary>
        /// <returns>True for correctly seated ion source, false otherwise.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getSafetySwitch();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Produces a simulated contact closure on the Flow Injection Analysis (FIA) line.  This
        /// line can be used by experiment methods to signal the start of an acquisition.
        /// </summary>
        /// <param name="value">True if contact is closed, false otherwise.</param>
        ///-------------------------------------------------------------------------------------------------
        void setFiaSignal(bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the simulated contact closure state on the Flow Injection Analysis (FIA) line.
        /// </summary>
        /// <returns>True if contact is closed, false otherwise.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getFiaSignal();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Set the state of a digital input.</summary>
        /// <param name="index">Index of the input to set (0-3).</param>
        /// <param name="value">True if the input is "closed", otherwise false.</param>
        ///-------------------------------------------------------------------------------------------------
        void setDigitalInput(int index, bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Cause the next scan to return a failure condition.  Useful for testing conditions
        /// that sometimes occur with USB instruments.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        void forceScanFailure();
    };
}
