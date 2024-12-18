/**
 * @file RecordFactory.cpp
 * @brief Implementation of the RecordFactory class.
 */

#include "Records/RecordFactory.h"
#include "Records/RecordParser.h"
#include <stdexcept>

RecordPtr RecordFactory::createRecord(RecordType type,
                                      const std::vector<std::string>& data) {
  switch (type) {
    case RecordType::Navigation:
      return make_unique_ptr<Records>(type,
                                       createNavigationRecordStrategy(data));
    case RecordType::Temperature:
      return make_unique_ptr<Records>(type,
                                       createTemperatureRecordStrategy(data));
    case RecordType::SampleAnalysis:
      return make_unique_ptr<Records>(
          type, createSampleAnalysisRecordStrategy(data));
    default:
      throw std::invalid_argument("Unknown record type");
  }
}

std::unique_ptr<NavigationRecordStrategy>
RecordFactory::createNavigationRecordStrategy(
    const std::vector<std::string>& data) {
  if (data.size() < 21) {
    throw std::invalid_argument("Invalid navigation record data");
  }
  auto measurements = RecordParser::parseDistanceMeasurements(data);
  for (const auto& measurement : measurements) {
    if (measurement.first.getUnitName() != "meters") {
      measurement.first.toBaseUnit();
    }
  }
  return make_unique_ptr<NavigationRecordStrategy>(measurements);
}

std::unique_ptr<TemperatureRecordStrategy>
RecordFactory::createTemperatureRecordStrategy(
    const std::vector<std::string>& data) {
  if (data.size() < 2) {
    throw std::invalid_argument("Invalid temperature record data");
  }
  Measurement temperature = RecordParser::parseMeasurement(data[1], data[2]);
  return make_unique_ptr<TemperatureRecordStrategy>(temperature);
}

std::unique_ptr<SampleAnalysisRecordStrategy>
RecordFactory::createSampleAnalysisRecordStrategy(
    const std::vector<std::string>& data) {
  if (data.size() < 3) {
    throw std::invalid_argument("Invalid sample analysis record data");
  }
  Measurement wavelength = RecordParser::parseMeasurement(data[1], data[2]);
  double intensity = std::stod(data[3]);
  return make_unique_ptr<SampleAnalysisRecordStrategy>(wavelength, intensity);
}
