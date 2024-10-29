#include "Utility/Units.h"
#include <stdexcept>

std::shared_ptr<UnitConverter> UnitConverter::instance = nullptr;

UnitConverter::UnitConverter() {
  initializeUnits();
}

void UnitConverter::initializeUnits() {
  distanceUnits = {
      {static_cast<int>(DistanceUnit::Meter), {1.0, "meters"}},
      {static_cast<int>(DistanceUnit::Nanometer), {1e-9, "nanometers"}},
      {static_cast<int>(DistanceUnit::Micrometer), {1e-6, "micrometers"}},
      {static_cast<int>(DistanceUnit::Centimeter), {0.01, "centimeters"}},
      {static_cast<int>(DistanceUnit::Kilometer), {1000.0, "kilometers"}}};

  temperatureUnits = {
      {static_cast<int>(TemperatureUnit::Kelvin), {1.0, "kelvin"}},
      {static_cast<int>(TemperatureUnit::Celsius), {1.0, "celsius"}}};
}

std::shared_ptr<UnitConverter> UnitConverter::getInstance() {
  if (!instance) {
    instance = std::shared_ptr<UnitConverter>(new UnitConverter());
  }
  return instance;
}

double UnitConverter::convertToBaseUnit(const double value,
                                        const UnitType type,
                                        const int unitEnum) const {
  switch (type) {
    case UnitType::Distance:
      return value * distanceUnits.at(unitEnum).baseUnitFactor;
    case UnitType::Temperature:
      if (unitEnum == static_cast<int>(TemperatureUnit::Celsius)) {
        return value + 273.15;  // Convert Celsius to Kelvin
      }
      return value;  // Kelvin is already the base unit
    default:
      throw std::invalid_argument("Invalid unit type");
  }
}

std::string UnitConverter::getUnitName(const UnitType type,
                                       const int unitEnum) const {
  switch (type) {
    case UnitType::Distance:
      return distanceUnits.at(unitEnum).name;
    case UnitType::Temperature:
      return temperatureUnits.at(unitEnum).name;
    default:
      throw std::invalid_argument("Invalid unit type");
  }
}

std::string UnitConverter::directionToString(Direction direction) {
  switch (direction) {
    case Direction::Forward:
      return "Forward";
    case Direction::Backward:
      return "Backward";
    case Direction::Left:
      return "Left";
    case Direction::Right:
      return "Right";
    default:
      throw std::invalid_argument("Invalid direction");
  }
}
