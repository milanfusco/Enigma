/**
 * @file SOLData.h
 * @brief Encapsulates all data collected during a single Sol.
 * 
 * The SOLData class stores all data collected during a single Sol, including
 * temperature, navigation, and sample analysis data.
 */
#ifndef SOLDATA_H
#define SOLDATA_H

#include "Records/Records.h"
#include "Subsystems/Navigation.h"
#include "Subsystems/SampleAnalysis.h"
#include "Subsystems/Temperature.h"

#include <optional>



/**
 * @class SOLData
 * @brief Encapsulates all data collected during a single Sol.
 */
class SOLData {
 private:
  int solNumber;         /**< The Sol number. */
  double SOLTemperature{}; /**< The temperature of the Sol. */
  NavigationRecord navigationData;   /**< The navigation data. */
  SampleClassification sampleData; /**< The sample data. */

 public:
  /**
   * @brief Constructs a new SOLData object.
   * @param solNum The Sol number.
   */
  SOLData(int solNum);

  /**
   * @brief Stores temperature data for the Sol.
   * @param data The TemperatureData to store.
   */
  void storeTemperatureData(const double& data);

  /**
   * @brief Stores navigation data for the Sol.
   * @param data The NavigationData to store.
   */
  void storeNavigationData(const NavigationRecord& data);

  /**
   * @brief Stores sample analysis data for the Sol.
   * @param data The SampleClassification data to store.
   */
  void storeSampleData(const SampleClassification& data);

  /**
   * @brief Gets the Sol number.
   * @return The Sol number.
   */
  int getSolNumber() const;

  /**
   * @brief Gets the temperature data to store.
   * @return Constant reference to the TemperatureData.
   */
  const double& getTemperatureData() const;

  /**
   * @brief Gets the final navigation Record to store.
   * @return Constant reference to the optional NavigationRecord.
   */
  const NavigationRecord& getNavigationData() const;

  /**
   * @brief Gets the sample analysis classification to store.
   * @return Constant reference to the optional SampleClassification.
   */
  const SampleClassification& getSampleData() const;
};

#endif  // SOLDATA_H
