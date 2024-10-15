#include "Records/RecordParser.h"
#include "Records/RecordFactory.h"
#include <sstream>
#include <stdexcept>

RecordPtr RecordParser::parseRecord(const std::string& record) {
    std::vector<std::string> parts = splitRecord(record);
    RecordType type = determineRecordType(parts);
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

RecordType RecordParser::determineRecordType(const std::vector<std::string>& parts) {
    if (parts.empty()) {
        throw std::invalid_argument("Empty record");
    }


    if (parts[0] == "d") return RecordType::Navigation;
    if (parts[0] == "t") return RecordType::Temperature;
    if (parts[0] == "w") return RecordType::SampleAnalysis;
    
    throw std::invalid_argument("Unknown record type");
}

Measurement RecordParser::parseMeasurement(const std::string& value,
                                           const std::string& unit) {
  double val = std::stod(value);
  if (unit == "m" || unit == "meter" || unit == "cm" || unit == "centimeter" || unit == "km" || unit == "kilometer") {
    return Measurement(val, UnitType::Distance, stringToDistanceUnit(unit));
  } else if (unit == "C" || unit == "celsius" || unit == "K" || unit == "kelvin") {
    return Measurement(val, UnitType::Temperature, stringToTemperatureUnit(unit));
  } else if (unit == "s" || unit == "second" || unit == "min" || unit == "minute" || unit == "h" || unit == "hour") {
    return Measurement(val, UnitType::Time, stringToTimeUnit(unit));
  }
  throw std::invalid_argument("Invalid unit string");
}

int RecordParser::stringToDistanceUnit(const std::string& unit) {
  if (unit == "m" || unit == "meter") return static_cast<int>(DistanceUnit::Meter);
  if (unit == "cm" || unit == "centimeter") return static_cast<int>(DistanceUnit::Centimeter);
  if (unit == "km" || unit == "kilometer") return static_cast<int>(DistanceUnit::Kilometer);
  throw std::invalid_argument("Invalid distance unit string");
}

int RecordParser::stringToTemperatureUnit(const std::string& unit) {
  if (unit == "C" || unit == "celsius") return static_cast<int>(TemperatureUnit::Celsius);
  if (unit == "K" || unit == "kelvin") return static_cast<int>(TemperatureUnit::Kelvin);
  throw std::invalid_argument("Invalid temperature unit string");
}

int RecordParser::stringToTimeUnit(const std::string& unit) {
  if (unit == "s" || unit == "second") return static_cast<int>(TimeUnit::Second);
  if (unit == "min" || unit == "minute") return static_cast<int>(TimeUnit::Minute);
  if (unit == "h" || unit == "hour") return static_cast<int>(TimeUnit::Hour);
  throw std::invalid_argument("Invalid time unit string");
}

Direction RecordParser::stringToDirection(const std::string& direction) {
  if (direction == "Forward") return Direction::Forward;
  if (direction == "Backward") return Direction::Backward;
  if (direction == "Left") return Direction::Left;
  if (direction == "Right") return Direction::Right;
  throw std::invalid_argument("Invalid direction string");
}

std::vector<std::pair<Measurement, Direction>> RecordParser::parseDistanceMeasurements(const std::vector<std::string>& data) {
    std::vector<std::pair<Measurement, Direction>> measurements;
    for (size_t i = 1; i < data.size(); i += 3) {
        if (i + 2 < data.size()) {
            Measurement distance = parseMeasurement(data[i], data[i+1]);
            Direction direction = stringToDirection(data[i+2]);
            measurements.push_back({distance, direction});
        }
    }
    return measurements;
}
