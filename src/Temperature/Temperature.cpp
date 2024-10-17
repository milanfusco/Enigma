#include "Subsystems/Temperature.h"

void Temperature::addTemperature(const Measurement& temperature) {
    SOLTemperature = temperature.toBaseUnit();
}



double Temperature::getTemperatureData() const {
    return SOLTemperature;
}

void Temperature::reset() {
    SOLTemperature = 0;
}