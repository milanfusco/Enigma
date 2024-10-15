#ifndef RECORDS_h
#define RECORDS_h

#include <memory>
#include <string>
#include <vector>
#include "Measurement.h"
#include "Navigation.h"
#include "SampleAnalysis.h"
#include "Temperature.h"

enum class RecordType { Navigation, Temperature, SampleAnalysis };

/**
 * @class RecordProcessingStrategy
 * @brief Interface for processing records.
 */
class RecordProcessingStrategy {
 public:
  /**
   * @brief Abstract method for processing records.
   * @param navigation The navigation subsystem.
   * @param temperature The temperature subsystem.
   * @param sampleAnalysis The sample analysis subsystem.
   */
  virtual void process(Navigation& navigation,
                       Temperature& temperature,
                       SampleAnalysis& sampleAnalysis) const = 0;
  /**
   * @brief Destructor for the RecordProcessingStrategy.
   */
  virtual ~RecordProcessingStrategy() = default;
};

/**
 * @class Records
 * @brief Base class for all types of records.
 */
class Records {
 private:
  RecordType type; /**< The type of the record. */
  std::unique_ptr<RecordProcessingStrategy> processingStrategy; /**< The processing strategy for the record. */

 public:
  /**
   * @brief Constructor for Records.
   * @param type The type of the record.
   * @param strategy The processing strategy for the record.
   */
  Records(RecordType type, std::unique_ptr<RecordProcessingStrategy> strategy)
      : type(type), processingStrategy(std::move(strategy)) {}

  /**
   * @brief Gets the type of the record.
   * @return The type of the record.
   */
  RecordType getType() const { return type; }

  /**
   * @brief Processes the record.
   * @param navigation The navigation subsystem.
   * @param temperature The temperature subsystem.
   * @param sampleAnalysis The sample analysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const {
    processingStrategy->process(navigation, temperature, sampleAnalysis);
  }
};

/**
 * @brief Alias for a unique pointer to a Records object.
 */
using RecordPtr = std::unique_ptr<Records>;

#endif  // RECORDS_H