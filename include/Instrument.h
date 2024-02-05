// (C) Copyright 2011-2019 by Advion, Inc. All Rights Reserved.
// The information contained herein is confidential, proprietary to Advion, Inc.
// Use of this information by anyone other than authorized employees or contractors
// of Advion, Inc. is granted only under a written non-disclosure agreement,
// expressly prescribing the scope and manner of such use.

#pragma once

#include "AdvionCMS.h"

namespace AdvionCMS
{
    /// <summary>
    /// Defines the possible types of CMS hardware.
    /// </summary>
    typedef enum
    {
        CMS,                        ///< The original expression CMS.
        CMS_S,                      ///< Second generation expression-S CMS for small molecules.
        CMS_L,                      ///< Second generation expression-L CMS for large molecules.
        CMS_OEM,                    ///< The original expression CMS-OEM.
        CMS_S_OEM,                  ///< Second generation expression-S CMS-OEM for small molecules.
        CMS_L_OEM,                  ///< Second generation expression-L CMS-OEM for large molecules.
        CMS_C                       ///< Second generation expression-C CMS.
    } HardwareType;

    /// <summary>
    /// Defines the possible types of ion sources attached to a system.
    /// </summary>
    typedef enum
    {
        NO_SOURCE,                  ///< No ion source.
        ESI_SOURCE,                 ///< An ESI ion source.
        APCI_SOURCE,                ///< An APCI ion source.
        DART_SOURCE,                ///< A DART ion source.
        VAPCI_SOURCE,               ///< An APCI ion source with additional control (transfer line temperature).
        ESI_OPSI_SOURCE             ///< An ESI-OPSI ion source.
    } SourceType;

    /// <summary>
    /// Defines the possible ion source and peripheral upgrades which can be licensed
    /// for expression-C CMS instruments.
    /// </summary>
    typedef enum
    {
        APCI_IonSource,             ///< APCI ion source.
        ASAP_IonSource,             ///< ASAP ion source.
        ESI_OPSI_IonSource,         ///< ESI-OPSI ion source.
        Plate_Express_Peripheral,   ///< Plate Express peripheral.
        Isocratic_Pump_Peripheral,  ///< Isocratic pump peripheral.
        MRA_Valve_Peripheral,       ///< MRA valve peripheral.
        Avant_HPLC_Peripheral,      ///< Avant HPLC peripheral.

        NumLicensableUpgrades       ///< Utility definition - number of licensable upgrades.
    } LicensableUpgrade;

    /// <summary>
    /// Defines the binary switches that can be changed.
    /// </summary>
    typedef enum
    {
        PositiveIon,                ///< Ion source operating with positive polarity.
        FullNebulizationGas,        ///< Nebulization gas flow at full level.
        StandbyNebulizationGas,     ///< Nebulization gas flow at standby level.
        SourceGas,                  ///< Ion source gas flow.
        CapillaryHeater,            ///< Capillary heater.
        SourceGasHeater,            ///< Ion source gas heater.
        TransferLineHeater,         ///< Transfer line gas heater, for vAPCI source.
        PositiveCalibrant,          ///< Positive (left) calibrant vial flow.
        NegativeCalibrant,          ///< Negative (right) calibrant vial flow.
        UsingHelium,                ///< Source gas is helium.

        NumInstrumentSwitches       ///< Utility definition - number of binary switches for CMS.
    } InstrumentSwitch;

    /// <summary>
    /// Defines the available heaters.
    /// </summary>
    typedef enum
    {
        CapillaryHeaterId,          ///< Capillary heater.
        SourceGasHeaterId,          ///< Ion source gas heater.
        TransferLineHeaterId        ///< Transfer line gas heater, for vAPCI source.
    } HeaterId;

    /// <summary>
    /// Defines the binary read-backs that are available.
    /// </summary>
    typedef enum
    {
        // Read-backs only
        CommunicationOK,            ///< USB communication is working.
        FirmwareVersionOK,          ///< Firmware and application versions are compatible.
        PumpSpeedOK,                ///< Internal pump speed is sufficient.
        VacuumOK,                   ///< Chamber vacuum is sufficient.
        SafetySwitchOK,             ///< Ion source is seated in the housing.

        FIASignal,                  ///< Flow Injection Analysis (FIA) contact is closed.
        DigitalInput1,              ///< Digital input 1 is closed.
        DigitalInput2,              ///< Digital input 2 is closed.
        DigitalInput3,              ///< Digital input 3 is closed.
        DigitalInput4,              ///< Digital input 4 is closed.

        // Set internally only
        PumpPowerRB,                ///< Internal pump is turned on.
        HighVoltagesRB,             ///< High voltages are being applied to the instrument.

        // Set via public API
        PositiveIonRB,              ///< Ion source polarity is positive.
        FullNebulizationGasRB,      ///< Nebulization gas is flowing at full level.
        StandbyNebulizationGasRB,   ///< Nebulization gas is flowing at standby level.
        SourceGasRB,                ///< Ion source gas is flowing.
        CapillaryHeaterRB,          ///< Capillary heater is on.
        SourceGasHeaterRB,          ///< Ion source gas heater is on.
        TransferLineHeaterRB,       ///< Ion source transfer line heater is on, for vAPCI source.
        PositiveCalibrantRB,        ///< Positive (left) calibrant vial is flowing.
        NegativeCalibrantRB,        ///< Negative (right) calibrant vial is flowing.
        UsingHeliumRB,              ///< Source gas is helium.

        NumBinaryReadbacks          ///< Utility definition - number of binary read-backs for CMS.
    } BinaryReadback;

    /// <summary>
    /// Defines the real number tune and ion source parameters that may be set.
    /// </summary>
    typedef enum
    {
        CapillaryTemperature,       ///< Capillary temperature, in degrees C.
        CapillaryVoltage,           ///< Capillary voltage, in V.
        SourceGasTemperature,       ///< Ion source gas temperature, in degrees C.
        TransferLineTemperature,    ///< Ion source transfer line temperature, in degrees C, for vAPCI source.
        ESIVoltage,                 ///< ESI ion source voltage, in V.
        APCICoronaDischarge,        ///< APCI corona discharge current, in uA.
        SourceVoltageOffset,        ///< Ion source voltage ramp offset, in V.
        SourceVoltageSpan,          ///< Ion source voltage ramp span, in V.
        ExtractionElectrode,        ///< Extraction electrode voltage, in V.
        HexapoleBias,               ///< Hexapole bias voltage, in V.
        HexapoleRFOffset,           ///< Hexapole RF ramp offset, in V.
        HexapoleRFSpan,             ///< Hexapole RF ramp span, in V.
        IonEnergyOffset,            ///< Ion energy ramp offset, in V.
        IonEnergySpan,              ///< Ion energy ramp span, in V.
        ResolutionOffset,           ///< Resolution ramp offet, in V.
        ResolutionSpan,             ///< Resolution ramp span, in V.
        DetectorVoltage,            ///< Detector voltage, in V.

        NumTuneParameters           ///< Utility definition - number of tune parameters for CMS.
    } TuneParameter;

    /// <summary>
    /// Defines the real number read-backs that are available.
    /// </summary>
    typedef enum
    {
        PiraniPressureRB,           ///< Chamber pressure, in Torr.
        TurboSpeedRB,               ///< Internal pump speed, in percent of maximum.
        CapillaryTemperatureRB,     ///< Capillary temperature, in degrees C.
        SourceGasTemperatureRB,     ///< Ion source gas temperature, in degrees C.
        TransferLineTemperatureRB,  ///< Ion source transfer line temperature, in degrees C, for vAPCI source.
        CapillaryVoltageRB,         ///< Capillary voltage, in V.
        SourceVoltageRB,            ///< Ion source voltage, in V.
        ExtractionElectrodeRB,      ///< Extraction electrode voltage, in V.
        HexapoleBiasRB,             ///< Hexapole bias voltage, in V.
        PoleBiasRB,                 ///< Pole bias voltage, in V.
        HexapoleRFRB,               ///< Hexapole RF voltage, in V.
        RectifiedRFRB,              ///< Rectified RF voltage, in V.
        ESIVoltageRB,               ///< ESI ion source voltage, in kV.
        APCICurrentRB,              ///< APCI ion source current, in uA.
        DetectorVoltageRB,          ///< Detector voltage, in kV.
        DynodeVoltageRB,            ///< Dynode voltage, in kV.
        DC1RB,                      ///< DC 1 voltage, in V.
        DC2RB,                      ///< DC 2 voltage, in V.

        NumNumberReadbacks          ///< Utility definition - number of real number read-backs for CMS.
    } NumberReadback;

    class InstrumentImpl;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>
    /// Abstract base class for instruments that can be controlled by the AdvionCMS API.  Provides
    /// methods to set switches and tune parameters and to return switch states and floating point
    /// readbacks of voltages and temperatures.  Also returns configuration information about the
    /// instrument.
    /// </summary>
    ///-------------------------------------------------------------------------------------------------
    class ADVION_CMS_API Instrument
    {

    public:

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Destructor.</summary>
        ///-------------------------------------------------------------------------------------------------
        virtual ~Instrument();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the state of a binary instrument switch.</summary>
        /// <param name="id">The switch identifier.</param>
        /// <param name="value">New switch state.</param>
        ///-------------------------------------------------------------------------------------------------
        void setInstrumentSwitchOn(InstrumentSwitch id, bool value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the state of a binary instrument read-back.</summary>
        /// <param name="id">The read-back identifier.</param>
        /// <returns>The read-back state.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool getBinaryReadback(BinaryReadback id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Sets the value of a real-number tune parameter.</summary>
        /// <param name="id">The parameter identifier.</param>
        /// <param name="value">The new value.</param>
        ///-------------------------------------------------------------------------------------------------
        void setTuneParameter(TuneParameter id, double value);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the current value of a real-number tune parameter.</summary>
        /// <param name="id">The parameter identifier.</param>
        /// <returns>The tune parameter value.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getTuneParameter(TuneParameter id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the minimum allowable value for setting a real-number tune parameter.</summary>
        /// <param name="id">The parameter identifier.</param>
        /// <returns>The minimum allowable value.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getTuneParameterUserMin(TuneParameter id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the maximum allowable value for setting a real-number tune parameter.</summary>
        /// <param name="id">The parameter identifier.</param>
        /// <returns>The maximum allowable value.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getTuneParameterUserMax(TuneParameter id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the maximum allowable temperature for the specified ion source type.</summary>
        /// <param name="source">The ion source identifier.</param>
        /// <returns>The maximum allowable temperature.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getSourceGasTemperatureUserMax(SourceType source);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the real number value of an instrument read-back.</summary>
        /// <param name="id">The read-back identifier.</param>
        /// <returns>The read-back value.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getNumberReadback(NumberReadback id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the real-number value of an analog input line on the instrument.</summary>
        /// <param name="line">The analog input line (0-3) whose value is returned.</param>
        /// <returns>The analog input value.</returns>
        ///-------------------------------------------------------------------------------------------------
        double readAnalogInput(int line);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's firmware version.</summary>
        /// <returns>The firmware version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getFirmwareVersion();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's firmware version.</summary>
        /// <returns>The firmware version.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getFirmwareVersionW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's serial number.</summary>
        /// <returns>The serial number.</returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getSerialNumber();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's serial number.</summary>
        /// <returns>The serial number.</returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getSerialNumberW();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's minimum allowable scan mass, in m/z.</summary>
        /// <returns>The minimum mass.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getMinMass();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's maximum allowable scan mass, in m/z.</summary>
        /// <returns>The maximum mass.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getMaxMass();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the minimum allowable instrument mass, in m/z.</summary>
        /// <returns>The minimum instrument mass.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getMinInstrumentMass();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the maximum allowable instrument mass, in m/z.</summary>
        /// <returns>The maximum instrument mass.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getMaxInstrumentMass();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's maximum allowable scan speed, in m/z per second.</summary>
        /// <returns>The maximum scan speed.</returns>
        ///-------------------------------------------------------------------------------------------------
        double getMaxScanSpeed();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's hardware type.</summary>
        /// <returns>The hardware type.</returns>
        ///-------------------------------------------------------------------------------------------------
        HardwareType getHardwareType();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Gets the instrument's current ion source type.</summary>
        /// <returns>The ion source type.</returns>
        ///-------------------------------------------------------------------------------------------------
        SourceType getSourceType();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Gets the time remaining until an instrument that has been pumped down can be operated,
        /// in seconds. If the instrument was not recently pumped down, this value is 0.
        /// </summary>
        /// <returns>The remaining pump down time, in seconds.</returns>
        ///-------------------------------------------------------------------------------------------------
        int getPumpDownRemainingSeconds();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Instructs the instrument to ignore the remaining pump down time and allow itself to
        /// be put into operate mode. Use of this method is not recommended, as premature
        /// operation after pumping down may damage the instrument if the chamber vacuum is
        /// insufficient.
        /// </summary>
        ///-------------------------------------------------------------------------------------------------
        void ignoreRemainingPumpDownTime();

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Returns an XML string representing the tune parameters saved in the flash memory.
        /// </summary>
        /// <param name="isEsi">true for ESI, false for APCI</param>
        /// <param name="isNegative">true for negative, false for positive</param>
        /// <returns>
        /// The tune parameters as XML.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getDefaultTuneParameters(bool isEsi, bool isNegative);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Returns an XML string representing the tune parameters saved in the flash memory.
        /// </summary>
        /// <param name="isEsi">true for ESI, false for APCI</param>
        /// <param name="isNegative">true for negative, false for positive</param>
        /// <returns>
        /// The tune parameters as XML.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getDefaultTuneParametersW(bool isEsi, bool isNegative);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Returns an XML string representing the ion source optimization parameters saved in the flash memory.
        /// </summary>
        /// <param name="isEsi">true for ESI, false for APCI</param>
        /// <param name="isNegative">true for negative, false for positive</param>
        /// <returns>
        /// The ion source optimization as XML.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const char* getDefaultIonSourceOptimization(bool isEsi, bool isNegative);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Returns an XML string representing the ion source optimization parameters saved in the flash memory.
        /// </summary>
        /// <param name="isEsi">true for ESI, false for APCI</param>
        /// <param name="isNegative">true for negative, false for positive</param>
        /// <returns>
        /// The ion source optimization as XML.
        /// </returns>
        ///-------------------------------------------------------------------------------------------------
        const wchar_t* getDefaultIonSourceOptimizationW(bool isEsi, bool isNegative);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Indicates if the temperature for the specified heater is within 10% of its target temperature.
        /// NOTE: If the heater is not enabled then the method returns true (no temperature check is
        ///       performed).
        /// </summary>
        /// <param name="id">The id of the heater to check.</param>
        /// <returns>True if the heater temperature is within 10% of its current target temperature.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool isHeaterTemperatureEquilibrated(HeaterId id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>
        /// Indicates if temperature for the specified heater is within 10% of its maximum temperature.
        /// NOTE: If the heater is not enabled then the method returns true (no temperature check is
        ///       performed).
        /// </summary>
        /// <param name="id">The id of the heater to check.</param>
        /// <returns>True if the heater temperature is within 10% of its maximum temperature.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool isHeaterTemperatureWithinMaximum(HeaterId id);

        ///-------------------------------------------------------------------------------------------------
        /// <summary>Checks if the specified upgrade is licensed on the current instrument.</summary>
        /// <param name="upgrade">The upgrade to check.</param>
        /// <returns>True if the upgrade is licensed.</returns>
        ///-------------------------------------------------------------------------------------------------
        bool isLicensedUpgrade(LicensableUpgrade upgrade);

    protected:

        explicit Instrument(InstrumentImpl*);

        InstrumentImpl* impl;

    private:

        friend class InstrumentController;

        InstrumentImpl* getImpl();
    };
}
