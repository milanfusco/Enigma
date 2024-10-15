/**
 * @file RecordParser.h
 * @brief Declaration of the RecordParser class.
 *
 * The RecordParser class is responsible for parsing raw record strings into
 * structured Record objects.
 */
#ifndef RECORDPARSER_H
#define RECORDPARSER_H

#include <string>
#include <vector>
#include "Records.h"
#include "Measurement.h"

/**
 * @class RecordParser
 * @brief Parses raw record strings into structured Record objects.
 */
class RecordParser {
private:
    /**
     * @brief Splits a raw record string into its component parts.
     * @param record The raw record string to split.
     * @return A vector of strings containing the split components.
     */
    static std::vector<std::string> splitRecord(const std::string& record);

    /**
     * @brief Determines the type of record from the split components.
     * @param parts The split components of the record.
     * @return The determined RecordType.
     * @throw std::invalid_argument if the record type cannot be determined.
     */
    static RecordType determineRecordType(const std::vector<std::string>& parts);

    

    /**
     * @brief Converts a string to a DistanceUnit enum.
     * @param unit The string to convert.
     * @return The DistanceUnit enum.
     * @throw std::invalid_argument if the unit string is invalid.
     */
    static int stringToDistanceUnit(const std::string& unit);


    /**
     * @brief Converts a string to a TimeUnit enum.
     * @param unit The string to convert.
     * @return The TimeUnit enum.
     * @throw std::invalid_argument if the unit string is invalid.
     */
    static int stringToTimeUnit(const std::string& unit);

    /**
     * @brief Converts a string to a TemperatureUnit enum.
     * @param unit The string to convert.
     * @return The TemperatureUnit enum.
     * @throw std::invalid_argument if the unit string is invalid.
     */
    static int stringToTemperatureUnit(const std::string& unit);


public:
    /**
     * @brief Parses a raw record string into a structured Record object.
     * @param record The raw record string to parse.
     * @return A unique pointer to the parsed Record object.
     * @throw std::invalid_argument if the record format is invalid.
     */
    static RecordPtr parseRecord(const std::string& record);

    /**
     * @brief Parses a measurement from a value and unit string.
     * @param value The numerical value as a string.
     * @param unit The unit as a string.
     * @return A Measurement object.
     */
  static Measurement parseMeasurement(const std::string& value,
                                    const std::string& unit);

    /**
     * @brief Parses a direction from a string.
     * @param direction The string to parse.
     * @return The Direction enum.
     * @throw std::invalid_argument if the direction string is invalid.
     */
    static Direction stringToDirection(const std::string& direction);

    /**
     * @brief Parses distance measurements from a vector of strings.
     * @param data The vector of strings containing the distance measurements.
     * @return A vector of pairs containing distance and time measurements.
     */
    static std::vector< std::pair<Measurement, Direction> > parseDistanceMeasurements(const std::vector<std::string>& data);

};

#endif  // RECORDPARSER_H