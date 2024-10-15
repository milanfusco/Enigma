#include "Utility/Measurement.h"
#include "Utility/Units.h"

Measurement::Measurement(double val, UnitType type, int unit)
    : value(val), unitType(type), unitEnum(unit) {}

double Measurement::toBaseUnit() const {
  auto converter = UnitConverter::getInstance();
  return converter->convertToBaseUnit(value, unitType, unitEnum);
}

std::string Measurement::getUnitName() const {
  auto converter = UnitConverter::getInstance();
  return converter->getUnitName(unitType, unitEnum);
}
