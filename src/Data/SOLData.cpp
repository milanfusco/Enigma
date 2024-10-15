#include "Data/SOLData.h"

SOLData::SOLData(int solNumber) : solNumber(solNumber) {}

void SOLData::storeTemperatureData(const double& data) {
  SOLTemperature = data;
}

void SOLData::storeNavigationData(const NavigationData& data) {
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

const std::optional<NavigationData>& SOLData::getNavigationData() const {
  return navigationData;
}

const std::optional<SampleClassification>& SOLData::getSampleData() const {
  return sampleData;
}
