#include "Temperature.h"
#include <algorithm>
#include <numeric>

double Statistics::calculateMean(const std::vector<double>& data) const {
    if (data.empty()) return 0.0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double Statistics::calculateMedian(const std::vector<double>& data) const {
    if (data.empty()) return 0.0;
    
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());
    
    size_t size = sortedData.size();
    if (size % 2 == 0) {
        return (sortedData[size/2 - 1] + sortedData[size/2]) / 2.0;
    } else {
        return sortedData[size/2];
    }
}

std::vector<double> Statistics::findLargestN(const std::vector<double>& data, const int n) const {
    std::vector<double> result = data;
    std::partial_sort(result.begin(), result.begin() + std::min(n, static_cast<int>(result.size())), result.end(), std::greater<double>());
    result.resize(std::min(n, static_cast<int>(result.size())));
    return result;
}

std::vector<double> Statistics::findSmallestN(const std::vector<double>& data, const int n) const {
    std::vector<double> result = data;
    std::partial_sort(result.begin(), result.begin() + std::min(n, static_cast<int>(result.size())), result.end());
    result.resize(std::min(n, static_cast<int>(result.size())));
    return result;
}

void Temperature::addTemperature(const TemperatureRecord& record) {
    temperatures.push_back(record.getTemperature().toBaseUnit());
}


double Temperature::getMeanTemperature() const {
    return stats.calculateMean(temperatures);
}

double Temperature::getMedianTemperature() const {
    return stats.calculateMedian(temperatures);
}

TemperatureData Temperature::getTemperatureData() const {
    return {getMeanTemperature(), getMedianTemperature()};
}

void Temperature::reset() {
    temperatures.clear();
}