#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <memory>
#include "Units.h"

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
};

#endif  // MEASUREMENT_H