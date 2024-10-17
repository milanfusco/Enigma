/**
 * @file RecordProcessingStrategies.h
 * @brief Declaration of the RecordProcessingStrategy class and its derived
 * classes.
 *
 * The RecordProcessingStrategy class is an abstract base class for processing
 * different types of records. Derived classes implement the specific processing
 * logic for each type of record.
 */

#ifndef RECORDPROCESSINGSTRATEGIES_H
#define RECORDPROCESSINGSTRATEGIES_H

#include "Records/Records.h"
#include "Subsystems/Navigation.h"
#include "Subsystems/SampleAnalysis.h"
#include "Subsystems/Temperature.h"
#include "Utility/Measurement.h"
#include "Utility/Units.h"

/**
 * @class NavigationRecordStrategy
 * @brief Concrete strategy for processing navigation records.
 */
class NavigationRecordStrategy : public RecordProcessingStrategy {
 private:
  std::vector<std::pair<Measurement, Direction>> measurements;

 public:
  /**
   * @brief Constructor for NavigationRecordStrategy.
   * @param measurements The vector of measurements and directions.
   */
  NavigationRecordStrategy(
      const std::vector<std::pair<Measurement, Direction>>& measurements)
      : measurements(measurements) {}

  /**
   * @brief Processes the navigation record.
   * @param navigation The navigation subsystem.
   * @param temperature The temperature subsystem.
   * @param sampleAnalysis The sample analysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const override {
    navigation.addRecord(measurements);
  }
};

class TemperatureRecordStrategy : public RecordProcessingStrategy {
 private:
  Measurement temperature; /**< The temperature measurement. */
 public:
  /**
   * @brief Constructor for TemperatureRecordStrategy.
   * @param temp The temperature measurement.
   */
  TemperatureRecordStrategy(const Measurement& temp) : temperature(temp) {}

  /**
   * @brief Processes the temperature record.
   * @param navigation The navigation subsystem.
   * @param temperature The temperature subsystem.
   * @param sampleAnalysis The sample analysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const override {
    temperature.addTemperature(this->temperature);
  }
};

/**
 * @class SampleAnalysisRecordStrategy
 * @brief Concrete strategy for processing sample analysis records.
 */
class SampleAnalysisRecordStrategy : public RecordProcessingStrategy {
 private:
  Measurement wavelength; /**< The wavelength measurement. */
  double intensity;

 public:
  /**
   * @brief Constructor for SampleAnalysisRecordStrategy.
   * @param wave The wavelength measurement.
   * @param intense The intensity measurement.
   */
  SampleAnalysisRecordStrategy(const Measurement& wave, double intense)
      : wavelength(wave), intensity(intense) {}

  /**
   * @brief Processes the sample analysis record.
   * @param navigation The navigation subsystem.
   * @param temperature The temperature subsystem.
   * @param sampleAnalysis The sample analysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const override {
    sampleAnalysis.addRecord(wavelength, intensity);
  }
};
#endif  // RECORDPROCESSINGSTRATEGIES_H
