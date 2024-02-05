// (C) Copyright 2012-2018 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"

namespace AdvionCMS
{
    class Instrument;

    /// <summary>Defines the set of states for the InstrumentController.</summary>
    typedef enum
    {
        Fault,          ///< Cannot communicate to instrument or its ion source is inoperable.
        Initializing,   ///< Communication is established and the instrument is being initialized.
        Vented,         ///< Instrument's pump is turned off.
        PumpingDown,    ///< Instrument's pump is turned on, but vacuum is not yet sufficient.
        Standby,        ///< Instrument is at vacuum but high voltages are not being applied.
        Operate,        ///< High voltages are being applied to instrument and it is scanning.
    } InstrumentState;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Defines the set of modes for the InstrumentController when it is in the Operate state.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    typedef enum
    {
        Idle,           ///< Instrument is not actively scanning (not in Operate state).
        Tuning,         ///< Instrument is performing routine tune scanning.
        AutoTuning,     ///< Instrument is performing dedicated auto-tune/calibration scanning.
        Acquiring,      ///< Instrument is performing acquisition scanning.
    } OperationMode;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Defines a set of conditions that will prevent an instrument from being placed into
    /// Operate mode. Each condition is represented by a single bit in a bit field, such that
    /// multiple conditions may be represented by a single value of type OperatePreventers.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    typedef enum
    {
        NoCommunication             = 0x00000001, ///< Cannot communicate with instrument (typically, USB error).
        PumpOff                     = 0x00000002, ///< The instrument's pump is turned off.
        PumpSpeedTooLow             = 0x00000004, ///< The turbo pump has not reached a sufficient speed.
        VacuumTooHigh               = 0x00000008, ///< The chamber vacuum is not sufficiently low.
        WaitingAfterPumpDown        = 0x00000010, ///< 30 minutes have not passed since pumping down.
        NoIonSource                 = 0x00000020, ///< No ion source is plugged into the instrument.
        SafetySwitchTripped         = 0x00000040, ///< The instrument's ion source is not seated properly.
        IncompatibleFirmware        = 0x00000080, ///< Firmware and application versions are incompatible.
    } OperatePreventer;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// A bitfield type used to store multiple OperatePreventer values.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    typedef unsigned int OperatePreventers;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// The static InstrumentController class controls the state of the Advion CMS. It provides
    /// methods that change the instrument from one state to another, and coordinates its
    /// operation when tune scanning or acquisition scanning.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API InstrumentController
    {
    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Initializes the controller to work with the provided instrument.  Must be called
        /// before any other InstrumentController methods may be called.  No status or error
        /// events will be fired or acquisition scans will happen before the controller is
        /// started.  Note that stopController() must always be called even if startController()
        /// does not return CMS_OK.
        /// </summary>
        /// <param name="instrument"> The previously initialized instrument to control.  At present,
        ///                           this should be an instance of either SimulatedInstrument
        ///                           or USBInstrument.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode startController(Instrument* instrument);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Stops the controller.  May only be called when the controller has already been
        /// started.  Will terminate any current scanning and put the instrument into Standby mode
        /// before stopping the controller.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode stopController();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Turns off the instrument's internal pump, thereby "venting" it and changing its state
        /// to Vented.  May only be called when canVent() returns true.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode vent();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Turns on the instrument's internal pump and changes its state to PumpingDown. The
        /// instrument will remain in that mode until it has sufficient vacuum and a waiting
        /// period has elapsed. For the USBInstrument, this waiting period is currently 30
        /// minutes.  May only be called if canPumpDown() returns true.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode pumpDown();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Turns on the instrument's high voltages and changes its state to Operate. May only be
        /// called if canOperate() returns true.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode operate();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Turns off the instrument's high voltages and changes its state to Standby. May only
        /// be called if canStandby() returns true.
        /// </summary>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode standby();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Sets all values of the instrument's current ion source optimization.
        /// </summary>
        /// <param name="ionSourceXML"> An XML representation of the ion source optimization to assign.</param>
        /// <returns>
        /// CMS_OK if successful, CMS_PARSING_FAILED if supplied XML was invalid.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setIonSourceOptimization(const char* ionSourceXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Sets all values of the instrument's current ion source optimization.
        /// </summary>
        /// <param name="ionSourceXML"> An XML representation of the ion source optimization to assign.</param>
        /// <returns>
        /// CMS_OK if successful, CMS_PARSING_FAILED if supplied XML was invalid.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setIonSourceOptimization(const wchar_t* ionSourceXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Returns an XML string representing the current ion source optimization parameters.
        /// </summary>
        /// <returns>
        /// The current ion source optimization as XML.  Caller is responsible for freeing this
        /// string.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* getIonSourceOptimization();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Returns an XML string representing the current ion source optimization parameters.
        /// </summary>
        /// <returns>
        /// The current ion source optimization as XML.  Caller is responsible for freeing this
        /// string.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static wchar_t* getIonSourceOptimizationW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets all values of the instrument's current tune parameters.</summary>
        /// <param name="tuneXML"> An XML representation of the tune parameters to assign.</param>
        /// <returns>
        /// CMS_OK if successful, CMS_PARSING_FAILED if supplied XML was invalid.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setTuneParameters(const char* tuneXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets all values of the instrument's current tune parameters.</summary>
        /// <param name="tuneXML"> An XML representation of the tune parameters to assign.</param>
        /// <returns>
        /// CMS_OK if successful, CMS_PARSING_FAILED if supplied XML was invalid.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode setTuneParameters(const wchar_t* tuneXML);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Returns an XML string representing the current tune parameters.</summary>
        /// <returns>
        /// The current tune parameters as XML.  Caller is responsible for freeing this string.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static char* getTuneParameters();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Returns an XML string representing the current tune parameters.</summary>
        /// <returns>
        /// The current tune parameters as XML.  Caller is responsible for freeing this string.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        static wchar_t* getTuneParametersW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if operate() may be called.  Returns true if the following conditions
        /// exist: communication is OK, pump is turned on, pump is at speed, vacuum is OK, time
        /// remaining after pumping down is zero, an ion source is installed in the instrument,
        /// and the ion source safety switch is OK.
        /// </summary>
        /// <returns>True if we can operate, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canOperate();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets operate preventers.</summary>
        /// <returns>The operate preventers.</returns>
        ///-------------------------------------------------------------------------------------------------
        static OperatePreventers getOperatePreventers();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if standby() may be called.  Returns true if the following conditions
        /// exist: communication is OK and there is no acquisition underway or waiting for a
        /// contact closure.
        /// </summary>
        /// <returns>True if we can standby, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canStandby();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if vent() may be called.  Returns true if the following conditions exist:
        /// communication is OK and the instrument is not in operate mode.
        /// </summary>
        /// <returns>True if we can vent, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canVent();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Determine if pumpDown() may be called.  Returns true if the following conditions
        /// exist: communication is OK and the turbo pump is turned off.
        /// </summary>
        /// <returns>True if we can pump down, false if not.</returns>
        ///-------------------------------------------------------------------------------------------------
        static bool canPumpDown();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the state of the instrument.</summary>
        /// <returns>The state.</returns>
        ///-------------------------------------------------------------------------------------------------
        static InstrumentState getState();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the operation mode of the instrument controller.</summary>
        /// <returns>The operation mode.</returns>
        ///-------------------------------------------------------------------------------------------------
        static OperationMode getOperationMode();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the version of the software.</summary>
        /// <returns>A string representing the software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const char* getSoftwareVersion();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the version of the software.</summary>
        /// <returns>A string representing the software version.</returns>
        ///-------------------------------------------------------------------------------------------------
        static const wchar_t* getSoftwareVersionW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Configures the digital output on standby behavior for the specified channel.</summary>
        /// <param name="channel">The digital output channel to configure, ranging from 1 to 4.</param>
        /// <param name="value">The contact closure value to set when the instrument goes to standby.
        ///                     If true, the contact is closed on standby.</param>
        /// <returns>CMS_OK if successful, or another error code from AdvionCMS.h.</returns>
        ///-------------------------------------------------------------------------------------------------
        static ErrorCode configureDigitalOutputOnStandby(int channel, bool value);
    };
}
