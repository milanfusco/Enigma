#include "Subsystems/Temperature.h"

void Temperature::addTemperature(const Measurement& temperature) {
    temperatures.push_back(temperature.toBaseUnit());
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