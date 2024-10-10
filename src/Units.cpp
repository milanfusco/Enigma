#include "Units.h"
#include <stdexcept>

std::shared_ptr<UnitConverter> UnitConverter::instance = nullptr;

UnitConverter::UnitConverter() {
    initializeUnits();
}

void UnitConverter::initializeUnits() {
    distanceUnits = {
        {static_cast<int>(DistanceUnit::Meter), {1.0, "meter"}},
        {static_cast<int>(DistanceUnit::Centimeter), {0.01, "centimeter"}},
        {static_cast<int>(DistanceUnit::Kilometer), {1000.0, "kilometer"}}
    };

    temperatureUnits = {
        {static_cast<int>(TemperatureUnit::Kelvin), {1.0, "kelvin"}},
        {static_cast<int>(TemperatureUnit::Celsius), {1.0, "celsius"}}
    };

    timeUnits = {
        {static_cast<int>(TimeUnit::Second), {1.0, "second"}},
        {static_cast<int>(TimeUnit::Minute), {60.0, "minute"}},
        {static_cast<int>(TimeUnit::Hour), {3600.0, "hour"}}
    };
}

std::shared_ptr<UnitConverter> UnitConverter::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<UnitConverter>(new UnitConverter());
    }
    return instance;
}

double UnitConverter::convertToBaseUnit(double value, UnitType type, int unitEnum) const {
    switch (type) {
        case UnitType::Distance:
            return value * distanceUnits.at(unitEnum).baseUnitFactor;
        case UnitType::Temperature:
            if (unitEnum == static_cast<int>(TemperatureUnit::Celsius)) {
                return value + 273.15; // Convert Celsius to Kelvin
            }
            return value; // Kelvin is already the base unit
        case UnitType::Time:
            return value * timeUnits.at(unitEnum).baseUnitFactor;
        default:
            throw std::invalid_argument("Invalid unit type");
    }
}

std::string UnitConverter::getUnitName(UnitType type, int unitEnum) const {
    switch (type) {
        case UnitType::Distance:
            return distanceUnits.at(unitEnum).name;
        case UnitType::Temperature:
            return temperatureUnits.at(unitEnum).name;
        case UnitType::Time:
            return timeUnits.at(unitEnum).name;
        default:
            throw std::invalid_argument("Invalid unit type");
    }
}
