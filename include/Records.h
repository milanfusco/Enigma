#ifndef RECORDS_h
#define RECORDS_h

#include <memory>
#include <string>
#include <vector>
#include "Measurement.h"
#include "Navigation.h"
#include "SampleAnalysis.h"
#include "Temperature.h"

enum class RecordType { Navigation, Temperature, SampleAnalysis };

/**
 * @class Records
 * @brief Base class for all types of records.
 */
class Records {
public:
    RecordType type;

    /**
     * @brief Constructs a new Records object.
     * @param recordType The type of the record.
     */
    Records(RecordType recordType);

    virtual ~Records() = default;

    /**
     * @brief Processes the record, updating relevant subsystems.
     * @param navigation Reference to the Navigation subsystem.
     * @param temperature Reference to the Temperature subsystem.
     * @param sampleAnalysis Reference to the SampleAnalysis subsystem.
     */
    virtual void process(Navigation& navigation,
                         Temperature& temperature,
                         SampleAnalysis& sampleAnalysis) const = 0;
};

enum class Direction { Forward, Backward, Left, Right };

/**
 * @class NavigationRecord
 * @brief Represents a navigation record.
 */
class NavigationRecord : public Records {
 private:
  Measurement distance;
  Direction direction;
  Measurement time;

 public:
  /**
   * @brief Constructs a new NavigationRecord.
   * @param dist The distance measurement.
   * @param dir The direction of movement.
   * @param t The time measurement.
   */
  NavigationRecord(const Measurement& dist,
                   Direction dir,
                   const Measurement& t);

  /**
   * @brief Processes the navigation record.
   * @param navigation Reference to the Navigation subsystem.
   * @param temperature Reference to the Temperature subsystem.
   * @param sampleAnalysis Reference to the SampleAnalysis subsystem.
   */
  void process(Navigation& navigation, Temperature& temperature, SampleAnalysis& sampleAnalysis) const override;

  /**
   * @brief Get the distance measurement.
   * @return Measurement object representing the distance.
   */
  Measurement getDistance() const;

  /**
   * @brief Get the Direction object
   * @return Direction
   */
  Direction getDirection() const;

  /**
   * @brief Get the time measurement.
   * @return Measurement object representing the time.
   */
  Measurement getTime() const;
};

/**
 * @class TemperatureRecord
 * @brief Represents a temperature record.
 */
class TemperatureRecord : public Records {
 private:
  Measurement temperature;

 public:
  /**
   * @brief Constructs a new TemperatureRecord.
   * @param temp The temperature measurement.
   */
  TemperatureRecord(const Measurement& temp);

  /**
   * @brief Processes the temperature record.
   * @param navigation Reference to the Navigation subsystem.
   * @param temperature Reference to the Temperature subsystem.
   * @param sampleAnalysis Reference to the SampleAnalysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const override;


  Measurement getTemperature() const;
};

/**
 * @class SampleAnalysisRecord
 * @brief Represents a sample analysis record.
 */
class SampleAnalysisRecord : public Records {
 private:
  double wavelength;
  double intensity;

 public:
  /**
   * @brief Constructs a new SampleAnalysisRecord.
   * @param wave The wavelength of the sample.
   * @param inten The intensity of the sample.
   */
  SampleAnalysisRecord(double wavelength, double intensity);
  
  /**
   * @brief Processes the sample analysis record.
   * @param navigation Reference to the Navigation subsystem.
   * @param temperature Reference to the Temperature subsystem.
   * @param sampleAnalysis Reference to the SampleAnalysis subsystem.
   */
  void process(Navigation& navigation,
               Temperature& temperature,
               SampleAnalysis& sampleAnalysis) const override;
};

using RecordPtr = std::unique_ptr<Records>;

#endif  // RECORDS_H