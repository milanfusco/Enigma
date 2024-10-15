/**
 * @file DataStorage.h
 * @brief Declaration of the DataStorage class.
 *
 * The DataStorage class manages the storage and retrieval of SOL (Sol or Solar
 * day) data.
 */

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include "SOLData.h"

/**
 * @class DataStorage
 * @brief Manages the storage and retrieval of SOL (Sol or Solar day) data.
 *
 * This class provides functionality to store SOL data and retrieve it either
 * as a complete set or for a specific SOL number.
 */
class DataStorage {
 private:
  std::vector<SOLData> masterSOLData;
 public:
  /**
   * @brief Stores a new SOL data entry.
   * @param solData The SOL data to be stored.
   */
  void storeSOLData(const SOLData& solData);

  /**
   * @brief Retrieves all stored SOL data.
   * @return A vector containing all stored SOL data entries.
   */
  std::vector<SOLData> getAllSOLData() const;

  /**
   * @brief Retrieves SOL data for a specific SOL number.
   * @param solNumber The SOL number to retrieve data for.
   * @return The SOL data for the specified SOL number.
   * @throw std::out_of_range if the SOL number is not found.
   */
  SOLData getSOLData(int solNumber) const;
};

/**
 * @brief Creates a master temperature data vector from SOL data to be used for
 * temperature analysis and statistics.
 * @param solData The SOL data to create the master temperature data from.
 * @return A vector of pairs containing SOL number and temperature.
 */
std::vector<double> createMasterTemperatureData(const std::vector<SOLData>& solData);

#endif  // DATASTORAGE_H