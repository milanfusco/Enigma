#ifndef UNITS_H
#define UNITS_H

#include <string>
#include <unordered_map>
#include <memory>


/**
 * @enum UnitType
 * @brief Enumeration of different types of units.
 * i.e. Distance, Temperature, Time
 * None is used to represent no unit type
 */
enum class UnitType {
    Distance,
    Temperature,
    Time,
    None
};

/**
 * @enum DistanceUnit
 * @brief Enumeration of different distance units.
 * i.e. Meter, Centimeter, Kilometer
 */
enum class DistanceUnit { Meter, Centimeter, Kilometer };

/**
 * @enum Direction
 * @brief Enumeration of different directions.
 * i.e. North, South, East, West
 */
enum class Direction { Forward, Backward, Left, Right };

/**
 * @enum TemperatureUnit
 * @brief Enumeration of different temperature units.
 * i.e. Kelvin, Celsius
 */
enum class TemperatureUnit { Kelvin, Celsius };

/**
 * @enum TimeUnit
 * @brief Enumeration of different time units.
 * i.e. Second, Minute, Hour
 */
enum class TimeUnit { Second, Minute, Hour };

/**
 * @struct UnitInfo
 * @brief Structure to hold information about a unit.
 */
struct UnitInfo {
    double baseUnitFactor;
    std::string name;
};

/**
 * @class UnitConverter
 * @brief Singleton class for converting between different units of measurement.
 *
 * This class provides functionality to convert values between different units
 * within the same unit type (e.g., distance, temperature, time).
 */
class UnitConverter {
private:
    UnitConverter();
    static std::shared_ptr<UnitConverter> instance;

    std::unordered_map<int, UnitInfo> distanceUnits;
    std::unordered_map<int, UnitInfo> temperatureUnits;
    std::unordered_map<int, UnitInfo> timeUnits;

    /**
     * @brief Initializes the unit conversion factors and names.
     */
    void initializeUnits();

public:
    /**
     * @brief Gets the singleton instance of UnitConverter.
     * @return Shared pointer to the UnitConverter instance.
     */
    static std::shared_ptr<UnitConverter> getInstance();
    
    /**
     * @brief Converts a value from a specific unit to its base unit.
     * @param value The value to convert.
     * @param type The type of unit (e.g., Distance, Temperature, Time).
     * @param unitEnum The enum value of the specific unit.
     * @return The converted value in the base unit.
     */
    double convertToBaseUnit(double value, UnitType type, int unitEnum) const;

    /**
     * @brief Gets the name of a specific unit.
     * @param type The type of unit (e.g., Distance, Temperature, Time).
     * @param unitEnum The enum value of the specific unit.
     * @return The name of the unit as a string.
     */
    std::string getUnitName(UnitType type, int unitEnum) const;

    // Delete copy constructor and assignment operator
    UnitConverter(const UnitConverter&) = delete;
    
    // Delete assignment operator
    UnitConverter& operator=(const UnitConverter&) = delete;
};

#endif // UNITS_H