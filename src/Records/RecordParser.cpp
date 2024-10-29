/**
 * @file RecordParser.cpp
 * @brief Implementation of the RecordParser class.
 */

#include "Records/RecordParser.h"
#include <sstream>
#include <stdexcept>
#include "Records/RecordFactory.h"

RecordPtr RecordParser::parseRecord(const std::string& record) {
  const std::vector<std::string> parts = splitRecord(record);
  const RecordType type = determineRecordType(parts);
  return RecordFactory::createRecord(type, parts);
}

std::vector<std::string> RecordParser::splitRecord(const std::string& record) {
  std::vector<std::string> parts;
  std::istringstream iss(record);
  std::string part;
  while (std::getline(iss, part, ',')) {
    parts.push_back(part);
  }
  return parts;
}

RecordType RecordParser::determineRecordType(
    const std::vector<std::string>& parts) {
  if (parts.empty()) {
    throw std::invalid_argument("Empty record");
  }

  if (parts[0] == "d")
    return RecordType::Navigation;
  if (parts[0] == "t")
    return RecordType::Temperature;
  if (parts[0] == "w")
    return RecordType::SampleAnalysis;

  throw std::invalid_argument("Unknown record type");
}

Measurement RecordParser::parseMeasurement(const std::string& value,
                                           const std::string& unit) {
  std::string trimmedValue = trim(value);
  if (trimmedValue.empty()) {
    throw std::invalid_argument("Empty measurement value");
  }
  std::string trimmedUnit = trim(unit);
  if (trimmedUnit.empty()) {
    throw std::invalid_argument("Empty measurement unit");
  }

  double val = std::stod(value);
  if (trimmedUnit == "m" || trimmedUnit == "meters" || trimmedUnit == "cm" ||
      trimmedUnit == "nanometers" || trimmedUnit == "nm" ||
      trimmedUnit == "micrometers" || trimmedUnit == "um" ||
      trimmedUnit == "centimeters" || trimmedUnit == "km" ||
      trimmedUnit == "kilometers") {
    return Measurement(val, UnitType::Distance,
                       stringToDistanceUnit(trimmedUnit));
  } else if (trimmedUnit == "C" || trimmedUnit == "celsius" ||
             trimmedUnit == "K" || trimmedUnit == "kelvin") {
    return Measurement(val, UnitType::Temperature,
                       stringToTemperatureUnit(trimmedUnit));
  }
  throw std::invalid_argument("Invalid unit string");
}

int RecordParser::stringToDistanceUnit(const std::string& unit) {
  if (unit == "m" || unit == "meters")
    return static_cast<int>(DistanceUnit::Meter);
  if (unit == "nm" || unit == "nanometers")
    return static_cast<int>(DistanceUnit::Nanometer);
  if (unit == "um" || unit == "micrometers")
    return static_cast<int>(DistanceUnit::Micrometer);
  if (unit == "cm" || unit == "centimeters")
    return static_cast<int>(DistanceUnit::Centimeter);
  if (unit == "km" || unit == "kilometers")
    return static_cast<int>(DistanceUnit::Kilometer);
  throw std::invalid_argument("Invalid distance unit string");
}

int RecordParser::stringToTemperatureUnit(const std::string& unit) {
  if (unit == "C" || unit == "celsius")
    return static_cast<int>(TemperatureUnit::Celsius);
  if (unit == "K" || unit == "kelvin")
    return static_cast<int>(TemperatureUnit::Kelvin);
  throw std::invalid_argument("Invalid temperature unit string");
}

Direction RecordParser::stringToDirection(const std::string& direction) {
  if (direction == "Forward" || direction == "forward")
    return Direction::Forward;
  if (direction == "Backward" || direction == "backward")
    return Direction::Backward;
  if (direction == "Left" || direction == "left")
    return Direction::Left;
  if (direction == "Right" || direction == "right")
    return Direction::Right;
  throw std::invalid_argument("Invalid direction string");
}

std::vector<std::pair<Measurement, Direction>>
RecordParser::parseDistanceMeasurements(const std::vector<std::string>& data) {
  std::vector<std::pair<Measurement, Direction>> measurements;
  for (size_t i = 1; i < data.size(); i += 3) {
    if (i + 2 < data.size()) {
      std::string unit = trim(data[i + 1]);
      if (unit == "seconds" || unit == "minutes" || 
          unit == "hours" || unit == "sols") {
            i -= 1;
        continue;
      }
      Measurement distance = parseMeasurement(data[i], unit);
      Direction direction = stringToDirection(data[i + 2]);
      measurements.emplace_back(distance, direction);
    }
  }
  return measurements;
}
