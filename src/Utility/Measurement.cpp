#include "Utility/Measurement.h"
#include "Utility/Units.h"

Measurement::Measurement(const double val, const UnitType type, const int unit)
    : value(val), unitType(type), unitEnum(unit) {}

double Measurement::toBaseUnit() const {
  const auto converter = UnitConverter::getInstance();
  return converter->convertToBaseUnit(value, unitType, unitEnum);
}

std::string Measurement::getUnitName() const {
  const auto converter = UnitConverter::getInstance();
  return converter->getUnitName(unitType, unitEnum);
}

double Measurement::getValue() const {
  return value;
}
