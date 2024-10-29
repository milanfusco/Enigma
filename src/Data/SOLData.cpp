/**
 * @file SOLData.cpp
 * @brief Implementation of the SOLData class.
 */

#include "Data/SOLData.h"

SOLData::SOLData(const int solNum) : solNumber(solNum), SOLTemperature(0), navigationData() {
}

void SOLData::storeTemperatureData(const double& data) {
  SOLTemperature = data;
}

void SOLData::storeNavigationData(const NavigationRecord& data) {
  navigationData = data;
}

void SOLData::storeSampleData(const SampleClassification& data) {
  sampleData = data;
}

int SOLData::getSolNumber() const {
  return solNumber;
}

const double& SOLData::getTemperatureData() const {
  return SOLTemperature;
}

const NavigationRecord& SOLData::getNavigationData() const {
  return navigationData;
}

const SampleClassification& SOLData::getSampleData() const {
  return sampleData;
}
