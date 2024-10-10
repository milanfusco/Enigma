#ifndef RECORDFACTORY_H
#define RECORDFACTORY_H

#include <string>
#include <vector>
#include "Records.h"

/**
 * @class RecordFactory
 * @brief Factory class for creating different types of records.
 */
class RecordFactory {
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