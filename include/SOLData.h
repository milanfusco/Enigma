#ifndef SOLDATA_h
#define SOLDATA_h

#include "Navigation.h"
#include "Records.h"
#include "SampleAnalysis.h"
#include "Temperature.h"

#include <optional>

/**
 * @struct TemperatureData
 * @brief Contains temperature statistics for a Sol.
 */
struct TemperatureData {
  double meanTemperature;
  double medianTemperature;
};

/**
 * @struct NavigationData
 * @brief Contains navigation data for a Sol.
 */
struct NavigationData {
  double finalDistance;
  Direction finalDirection;
};

/**
 * @class SOLData
 * @brief Encapsulates all data collected during a single Sol.
 */
class SOLData {
 private:
  int solNumber;
  TemperatureData temperatureData;
  std::optional<NavigationData> navigationData;
  std::optional<SampleClassification> sampleData;

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
  void storeTemperatureData(TemperatureData& data);

  /**
   * @brief Stores navigation data for the Sol.
   * @param data The NavigationData to store.
   */
  void storeNavigationData(NavigationData& data);

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
   * @brief Gets the temperature data.
   * @return Constant reference to the TemperatureData.
   */
  const TemperatureData& getTemperatureData() const;

  /**
   * @brief Gets the navigation data.
   * @return Constant reference to the optional NavigationData.
   */
  const std::optional<NavigationData>& getNavigationData() const;

  /**
   * @brief Gets the sample analysis data.
   * @return Constant reference to the optional SampleClassification.
   */
  const std::optional<SampleClassification>& getSampleData() const;
};

#endif  // SOLDATA_h