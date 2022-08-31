// EnergyPlus, Copyright (c) 1996-2022, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef PollutionModule_hh_INCLUDED
#define PollutionModule_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus/Data/BaseData.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/EnergyPlus.hh>

namespace EnergyPlus {

namespace PollutionModule {

    enum class PollFactor
    {
        Invalid = -1,
        Elec,
        NatGas,
        FuelOil1,
        FuelOil2,
        Coal,
        Gasoline,
        Propane,
        Diesel,
        OtherFuel1,
        OtherFuel2,
        Num
    };

    enum class Pollutant
    {
        Invalid = -1,
        CO2,
        CO,
        CH4,
        NOx,
        N2O,
        SO2,
        PM,
        PM10,
        PM25,
        NH3,
        NMVOC,
        Hg,
        Pb,
        Water,
        NucHi,
        NucLo,
        Num
    };

    std::array <std::string, static_cast<int>(Pollutant::Num)> namePollutant = {"CO2", "CO", "CH4", "NOx", "N2O", "SO2",
                                                                                "PM", "PM10", "PM2.5", "NH3", "NMVOC",
                                                                                "Hg", "Pb", "WaterEnvironmentalFactors",
                                                                                "Nuclear High", "Nuclear Low"
    };

    // MODULE VARIABLE DECLARATIONS:
    // Total for all of the Pollutants
    // Total Carbon Equivalent Components
    //  !Fuel Types
    // Total Carbon Equivalent Coeffs
    // Purchased Efficiencies

    // Fuel Types used with the Pollution Factors
    // Facility Meter Indexes
    // Facility Meter Values used in Pollution Calcs

    struct ComponentProps
    {
        // Members
        Real64 Source = 0.0;
        std::array <Real64, static_cast<int>(Pollutant::Num)> PollComp = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    };

    struct CoefficientProps
    {
        // Members
        bool FuelFactorUsed = false;
        Real64 Source = 0.0;
        std::array <Real64, static_cast<int>(Pollutant::Num)> PollCoef = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        int SourceSched = 0;
        std::array <int, static_cast<int>(Pollutant::Num)> PollSched = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    };

    struct PollutionProps
    {
        // Members
        // Components
        ComponentProps ElecComp;
        ComponentProps ElecPurchComp;
        ComponentProps ElecSurplusSoldComp;
        ComponentProps NatGasComp;
        ComponentProps FuelOil1Comp;
        ComponentProps FuelOil2Comp;
        ComponentProps CoalComp;
        ComponentProps GasolineComp;
        ComponentProps PropaneComp;
        ComponentProps DieselComp;
        ComponentProps OtherFuel1Comp;
        ComponentProps OtherFuel2Comp;
        // Total for all of the Pollutants
        Real64 N2OPollutTotal = 0.0;
        Real64 CH4PollutTotal = 0.0;
        Real64 CO2PollutTotal = 0.0;
        // Total Carbon Equivalent Components
        Real64 TotCarbonEquivFromN2O = 0.0;
        Real64 TotCarbonEquivFromCH4 = 0.0;
        Real64 TotCarbonEquivFromCO2 = 0.0;
        // Fuel Type Coefficients
        CoefficientProps ElecCoef;
        CoefficientProps NatGasCoef;
        CoefficientProps FuelOil1Coef;
        CoefficientProps FuelOil2Coef;
        CoefficientProps CoalCoef;
        CoefficientProps GasolineCoef;
        CoefficientProps PropaneCoef;
        CoefficientProps DieselCoef;
        CoefficientProps OtherFuel1Coef;
        CoefficientProps OtherFuel2Coef;
        // Total Carbon Equivalent Coeffs
        Real64 CarbonEquivN2O = 0.0;
        Real64 CarbonEquivCH4 = 0.0;
        Real64 CarbonEquivCO2 = 0.0;
        Real64 PurchHeatEffic = 0.0;
        Real64 PurchCoolCOP = 0.0;
        Real64 SteamConvEffic = 0.0;
    };

    struct FuelTypeProps
    {
        // Members
        // FuelType Names
        Array1D_string FuelTypeNames;
        // Fuel Types used with the Pollution Factors
        Real64 Elec;
        Real64 NatGas;
        Real64 FuelOil1;
        Real64 FuelOil2;
        Real64 Coal;
        Real64 Gasoline;
        Real64 Propane;
        Real64 Diesel;
        Real64 OtherFuel1;
        Real64 OtherFuel2;
        Real64 ElecPurch;
        Real64 ElecSold;
        // Facility Meter Indexes
        int ElecFacilityIndex;
        int DieselFacilityIndex;
        int PurchCoolFacilityIndex;
        int PurchHeatFacilityIndex;
        int NatGasFacilityIndex;
        int GasolineFacilityIndex;
        int CoalFacilityIndex;
        int FuelOil1FacilityIndex;
        int FuelOil2FacilityIndex;
        int PropaneFacilityIndex;
        int OtherFuel1FacilityIndex;
        int OtherFuel2FacilityIndex;
        int ElecProducedFacilityIndex;
        int SteamFacilityIndex;
        int ElecPurchasedFacilityIndex;
        int ElecSurplusSoldFacilityIndex;
        // Facility Meter Values used in Pollution Calcs
        Real64 ElecFacility;
        Real64 DieselFacility;
        Real64 PurchCoolFacility;
        Real64 PurchHeatFacility;
        Real64 NatGasFacility;
        Real64 GasolineFacility;
        Real64 CoalFacility;
        Real64 FuelOil1Facility;
        Real64 FuelOil2Facility;
        Real64 PropaneFacility;
        Real64 OtherFuel1Facility;
        Real64 OtherFuel2Facility;
        Real64 ElecProducedFacility;
        Real64 SteamFacility;
        Real64 ElecPurchasedFacility;
        Real64 ElecSurplusSoldFacility;

        // Default Constructor
        FuelTypeProps()
            : FuelTypeNames({1, static_cast<int>(PollFactor::Num)}), Elec(0.0), NatGas(0.0), FuelOil1(0.0), FuelOil2(0.0), Coal(0.0), Gasoline(0.0),
              Propane(0.0), Diesel(0.0), OtherFuel1(0.0), OtherFuel2(0.0), ElecPurch(0.0), ElecSold(0.0), ElecFacilityIndex(0),
              DieselFacilityIndex(0), PurchCoolFacilityIndex(0), PurchHeatFacilityIndex(0), NatGasFacilityIndex(0), GasolineFacilityIndex(0),
              CoalFacilityIndex(0), FuelOil1FacilityIndex(0), FuelOil2FacilityIndex(0), PropaneFacilityIndex(0), OtherFuel1FacilityIndex(0),
              OtherFuel2FacilityIndex(0), ElecProducedFacilityIndex(0), SteamFacilityIndex(0), ElecPurchasedFacilityIndex(0),
              ElecSurplusSoldFacilityIndex(0), ElecFacility(0.0), DieselFacility(0.0), PurchCoolFacility(0.0), PurchHeatFacility(0.0),
              NatGasFacility(0.0), GasolineFacility(0.0), CoalFacility(0.0), FuelOil1Facility(0.0), FuelOil2Facility(0.0), PropaneFacility(0.0),
              OtherFuel1Facility(0.0), OtherFuel2Facility(0.0), ElecProducedFacility(0.0), SteamFacility(0.0), ElecPurchasedFacility(0.0),
              ElecSurplusSoldFacility(0.0)
        {
        }
    };

    void CalculatePollution(EnergyPlusData &state);

    void SetupPollutionCalculations(EnergyPlusData &state);

    void GetPollutionFactorInput(EnergyPlusData &state);

    void pushFuelTypeDataToPollutionConstruct(EnergyPlusData &state,
                                              bool &isFuelUsed,
                                              std::string const fuelName,
                                              Real64 &source,
                                              std::array <Real64, static_cast<int>(Pollutant::Num)> &coefData,
                                              int &sourceSched,
                                              std::array <int, static_cast<int>(Pollutant::Num)> &schedData,
                                              bool &errorsInput);

    void SetupPollutionMeterReporting(EnergyPlusData &state);

    void CheckPollutionMeterReporting(EnergyPlusData &state);

    void CheckFFSchedule(EnergyPlusData &state,
                         std::string const &currentModuleObject, // the module Object
                         std::string const &resourceType,        // resource type (Natural Gas, etc)
                         std::string const &fieldName,           // Actual field name
                         std::string const &ScheduleName,        // Schedule Name as input
                         int &SchedulePtr,                       // Schedule Index
                         bool &ErrorsFound                       // true if errors found
    );

    void CalcPollution(EnergyPlusData &state);

    void ReadEnergyMeters(EnergyPlusData &state);

    void GetFuelFactorInfo(EnergyPlusData &state,
                           std::string const &fuelName,  // input fuel name  (standard from Tabular reports)
                           bool &fuelFactorUsed,         // return value true if user has entered this fuel
                           Real64 &fuelSourceFactor,     // if used, the source factor
                           bool &fuelFactorScheduleUsed, // if true, schedules for this fuel are used
                           int &ffScheduleIndex          // if schedules for this fuel are used, return schedule index
    );

    void GetEnvironmentalImpactFactorInfo(EnergyPlusData &state,
                                          Real64 &efficiencyDistrictHeating, // if entered, the efficiency of District Heating
                                          Real64 &efficiencyDistrictCooling, // if entered, the efficiency of District Cooling
                                          Real64 &sourceFactorSteam          // if entered, the source factor for Steam
    );

} // namespace PollutionModule

struct PollutionModuleData : BaseGlobalStruct
{

    bool PollutionReportSetup = false;
    bool GetInputFlagPollution = true;
    int NumEnvImpactFactors = 0;
    int NumFuelFactors = 0;

    // Object Data
    PollutionModule::PollutionProps Pollution;
    PollutionModule::FuelTypeProps FuelType;

    void clear_state() override
    {
        this->PollutionReportSetup = false;
        this->GetInputFlagPollution = true;
        this->NumEnvImpactFactors = 0;
        this->NumFuelFactors = 0;
        new (&(this->Pollution)) PollutionModule::PollutionProps();
        this->FuelType = {};
    }
};

} // namespace EnergyPlus

#endif
