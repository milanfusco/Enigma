/**
 * @file RecordFactory.h
 * @brief Declaration of the RecordFactory class.
 *
 * The RecordFactory class is responsible for creating instances of different
 * types of records based on the provided data. It uses the Factory design
 * pattern to encapsulate the creation logic for each type of record. It
 * delegates the actual creation to the appropriate strategy classes.
 */

#ifndef RECORDFACTORY_H
#define RECORDFACTORY_H

#include <string>
#include <vector>
#include "Records/RecordProcessingStrategies.h"
#include "Records/Records.h"

/**
 * @class RecordFactory
 * @brief Factory class for creating different types of records.
 */
class RecordFactory {
 private:
  /**
   * @brief Creates a navigation record strategy.
   * @param data Vector of strings containing the record data.
   * @return A unique pointer to the created NavigationRecordStrategy object.
   */
  static std::unique_ptr<NavigationRecordStrategy>
  createNavigationRecordStrategy(const std::vector<std::string>& data);

  /**
   * @brief Creates a temperature record strategy.
   * @param data Vector of strings containing the record data.
   * @return A unique pointer to the created TemperatureRecordStrategy object.
   */
  static std::unique_ptr<TemperatureRecordStrategy>
  createTemperatureRecordStrategy(const std::vector<std::string>& data);

  /**
   * @brief Creates a sample analysis record strategy.
   * @param data Vector of strings containing the record data.
   * @return A unique pointer to the created SampleAnalysisRecordStrategy
   * object.
   */
  static std::unique_ptr<SampleAnalysisRecordStrategy>
  createSampleAnalysisRecordStrategy(const std::vector<std::string>& data);

 public:
  /**
   * @brief Creates a record of the specified type.
   * @param type The type of record to create.
   * @param data Vector of strings containing the record data.
   * @return A unique pointer to the created Record object.
   * @throw std::invalid_argument if the record type is unknown.
   */
  static RecordPtr createRecord(RecordType type,
                                const std::vector<std::string>& data);
};



#endif  // RECORDFACTORY_H
