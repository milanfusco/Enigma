#include "Data/SOLData.h"

SOLData::SOLData(int solNumber) : solNumber(solNumber) {}

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
