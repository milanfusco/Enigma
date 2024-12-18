/**
 * @file Measurement.h
 * @brief Declaration of the Measurement class.
 *
 * The Measurement class represents a measurement with a value, unit type, and
 * specific unit.
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <memory>
#include "Utility/Units.h"

/**
 * @class Measurement
 * @brief Represents a measurement with a value, unit type, and specific unit.
 *
 * This class encapsulates a measurement, providing methods to convert it to
 * a base unit and retrieve the unit name.
 */
class Measurement {
 private:
  double value;
  UnitType unitType;
  int unitEnum;

 public:
  Measurement() : value(0), unitType(UnitType::None), unitEnum(0) {}

  /**
   * @brief Constructs a new Measurement object.
   * @param val The numerical value of the measurement.
   * @param type The type of unit (e.g., Distance, Temperature, Time).
   * @param unit The specific unit enum value.
   */
  Measurement(double val, UnitType type, int unit);

  /**
   * @brief Converts the measurement to its base unit.
   * @return The value in the base unit of the measurement's type.
   */
  double toBaseUnit() const;

  /**
   * @brief Gets the name of the measurement's unit.
   * @return A string representation of the unit name.
   */
  std::string getUnitName() const;

  /**
   * @brief Gets the value of the measurement.
   * @return The value of the measurement.
   */
  double getValue() const;
};

#endif  // MEASUREMENT_H