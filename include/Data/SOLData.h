#ifndef SOLDATA_h
#define SOLDATA_h

#include "Navigation.h"
#include "Records.h"
#include "SampleAnalysis.h"
#include "Temperature.h"
#include "DataStorage.h"

#include <optional>


/**
 * @struct NavigationData
 * @brief Contains navigation data for a Sol.
 */
struct NavigationData {
  double finalDistance; /**< The final distance. */
  Direction finalDirection; /**< The final direction. */
};

/**
 * @class SOLData
 * @brief Encapsulates all data collected during a single Sol.
 */
class SOLData {
 private:
  int solNumber; /**< The Sol number. */
  double SOLTemperature; /**< The temperature of the Sol. */
  std::optional<NavigationData> navigationData; /**< The navigation data. */
  std::optional<SampleClassification> sampleData; /**< The sample data. */

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
  void storeNavigationData(const NavigationData& data);

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
  const double& getTemperatureData() const;

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