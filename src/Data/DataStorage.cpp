/**
 * @file DataStorage.cpp
 * @brief Implementation of the DataStorage class.
 */

#include "Data/DataStorage.h"
#include <stdexcept>

void DataStorage::storeSOLData(const SOLData& solData) {
  masterSOLData.push_back(solData);
}

std::vector<SOLData> DataStorage::getAllSOLData() const {
  return masterSOLData;
}

SOLData DataStorage::getSOLData(const int solNumber) const {
  for (const auto& solData : masterSOLData) {
    if (solData.getSolNumber() == solNumber) {
      return solData;
    }
  }
  throw std::out_of_range("SOL number not found");
}

std::vector<double> createMasterTemperatureData(const std::vector<SOLData>& solData) {
  std::vector<double> MasterTemperatureData;
  for (const auto& data : solData) {
    MasterTemperatureData.push_back(data.getTemperatureData());
  }
  return MasterTemperatureData;
}

