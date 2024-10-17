#include <algorithm>
#include <numeric>
#include "Data/DataStorage.h"
#include "Subsystems/Temperature.h"

double Statistics::calculateMean(const std::vector<double>& data) {
  if (data.empty())
    return 0.0;
  return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double Statistics::calculateMedian(const std::vector<double>& data) {
  if (data.empty())
    return 0.0;

  std::vector<double> sortedData = data;
  std::sort(sortedData.begin(), sortedData.end());

  size_t size = sortedData.size();
  if (size % 2 == 0) {
    return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2.0;
  } else {
    return sortedData[size / 2];
  }
}

double Statistics::calculateLowestSummerTemperature(
    const std::vector<double>& data) {
  std::vector<double> summer1Temperatures;
  std::vector<double> summer2Temperatures;

  for (size_t i = 0; i < data.size(); ++i) {
    if (i >= 195 && i <= 372) {
      summer1Temperatures.push_back(data[i]);
    } else if (i >= 865 && i <= 1042) {
      summer2Temperatures.push_back(data[i]);
    }
  }

  double lowestSummer1 =
      *std::min_element(summer1Temperatures.begin(), summer1Temperatures.end());
  double lowestSummer2 =
      *std::min_element(summer2Temperatures.begin(), summer2Temperatures.end());

  return std::min(lowestSummer1, lowestSummer2);
}

double Statistics::calculateLowestWinterTemperature(
    const std::vector<double>& data) {
  std::vector<double> winter1Temperatures;
  std::vector<double> winter2Temperatures;

  for (size_t i = 0; i < data.size(); ++i) {
    if (i >= 515 && i <= 669) {
      winter1Temperatures.push_back(data[i]);
    } else if (i >= 1185 && i <= 1374) {
      winter2Temperatures.push_back(data[i]);
    }
  }

  double lowestWinter1 =
      *std::min_element(winter1Temperatures.begin(), winter1Temperatures.end());
  double lowestWinter2 =
      *std::min_element(winter2Temperatures.begin(), winter2Temperatures.end());

  return std::min(lowestWinter1, lowestWinter2);
}

std::vector<double> Statistics::findLargestN(const std::vector<double>& data,
                                             const int n) {
  std::vector<double> result = data;
  std::partial_sort(
      result.begin(),
      result.begin() + std::min(n, static_cast<int>(result.size())),
      result.end(), std::greater<double>());
  result.resize(std::min(n, static_cast<int>(result.size())));
  return result;
}

std::vector<double> Statistics::findSmallestN(const std::vector<double>& data,
                                              const int n) {
  std::vector<double> result = data;
  std::partial_sort(
      result.begin(),
      result.begin() + std::min(n, static_cast<int>(result.size())),
      result.end());
  result.resize(std::min(n, static_cast<int>(result.size())));
  return result;
}
