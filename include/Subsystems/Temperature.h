#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Records.h"
#include "SOLData.h"

/**
 * @class Statistics
 * @brief Provides statistical calculations for temperature data.
 */
class Statistics {
public:
    /**
     * @brief Calculates the mean of a dataset.
     * @param data Vector of temperature readings.
     * @return The mean temperature.
     */
    double calculateMean(const std::vector<double>& data) const;

    /**
     * @brief Calculates the median of a dataset.
     * @param data Vector of temperature readings.
     * @return The median temperature.
     */
    double calculateMedian(const std::vector<double>& data) const;

    /**
     * @brief Finds the N largest values in a dataset.
     * @param data Vector of temperature readings.
     * @param n Number of largest values to find.
     * @return Vector of the N largest values.
     */
    std::vector<double> findLargestN(const std::vector<double>& data,
                                     const int n) const;

    /**
     * @brief Finds the N smallest values in a dataset.
     * @param data Vector of temperature readings.
     * @param n Number of smallest values to find.
     * @return Vector of the N smallest values.
     */
    std::vector<double> findSmallestN(const std::vector<double>& data,
                                     const int n) const;

    /**
     * @brief Finds the lowest temperature in the two summers.
     * @param data Vector of temperature readings.
     * @return The lowest temperature in the two summers.
     */
    double calculateLowestSummerTemperature(const std::vector<double>& data) const;

    /**
     * @brief Finds the highest temperature in the two winters.
     * @param data Vector of temperature readings.
     * @return The highest temperature in the two winters.
     */
    double calculateLowestWinterTemperature(const std::vector<double>& data) const;
};

/**
 * @class Temperature
 * @brief Manages temperature data and calculations for a SOL.
 */
class Temperature {
private:
    std::vector<double> temperatures; /**< The temperatures collected. */
    Statistics stats; /**< The statistics for the temperatures. */

public:
    /**
     * @brief Adds a new temperature reading.
     * @param temperature The temperature to add.
     */
    void addTemperature(const Measurement& temperature);

    /**
     * @brief Retrieves the temperature data.
     * @return The temperature data.
     */
    double getTemperatureData() const;

    /**
     * @brief Resets all temperature data.
     */
    void reset();
};

#endif  // TEMPERATURE_H