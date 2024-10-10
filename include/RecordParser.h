#ifndef RECORDPARSER_H
#define RECORDPARSER_H

#include <string>
#include <vector>
#include "Measurement.h"
#include "Records.h"

/**
 * @class RecordParser
 * @brief Parses raw record strings into structured Record objects.
 */
class RecordParser {
public:
    /**
     * @brief Parses a raw record string into a structured Record object.
     * @param record The raw record string to parse.
     * @return A unique pointer to the parsed Record object.
     * @throw std::invalid_argument if the record format is invalid.
     */
    static RecordPtr parseRecord(const std::string& record);

private:
    /**
     * @brief Parses a navigation record.
     * @param parts Vector of string parts from the raw record.
     * @return A unique pointer to the parsed NavigationRecord.
     */
    static std::unique_ptr<NavigationRecord> parseNavigationRecord(
        const std::vector<std::string>& parts);

    /**
     * @brief Parses a temperature record.
     * @param parts Vector of string parts from the raw record.
     * @return A unique pointer to the parsed TemperatureRecord.
     */
    static std::unique_ptr<TemperatureRecord> parseTemperatureRecord(
        const std::vector<std::string>& parts);

    /**
     * @brief Parses a sample analysis record.
     * @param parts Vector of string parts from the raw record.
     * @return A unique pointer to the parsed SampleAnalysisRecord.
     */
    static std::unique_ptr<SampleAnalysisRecord> parseSampleAnalysisRecord(
        const std::vector<std::string>& parts);

    /**
     * @brief Parses a measurement from a value and unit string.
     * @param value The numerical value as a string.
     * @param unit The unit as a string.
     * @return A Measurement object.
     */
    static Measurement parseMeasurement(const std::string& value,
                                        const std::string& unit);
};

#endif  // RECORDPARSER_H
