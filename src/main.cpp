#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
#include <iomanip>
#include "Core/MissionControl.h"
#include "Core/Robot.h"
#include "Data/DataStorage.h"
#include "Data/SOLManager.h"
#include "Records/RecordParser.h"
#include "Subsystems/SampleClassification.h"

int main() {
  auto robot = Robot::createRobot();
  auto solManager = std::make_unique<SOLManager>();
  auto dataStorage = std::make_unique<DataStorage>();
  auto recordParser = std::make_unique<RecordParser>();

  MissionControl missionControl(std::move(robot), std::move(solManager),
                                std::move(dataStorage),
                                std::move(recordParser));

  std::string record;
  while (std::getline(std::cin, record)) {
    missionControl.handleRecord(record);

    // Increment Sol if temperature is parsed
    if (record[0] == 't') {
      missionControl.finalizeCurrentSOL();
    }
  }

  // Generate final report
  auto allSOLData = missionControl.getObservations();

  // Process temperature data
  std::vector<double> temperatures;
  for (const auto& solData : allSOLData) {
    temperatures.push_back(solData.getTemperatureData());
  }

  std::sort(temperatures.begin(), temperatures.end());

  // Calculate statistics
  double median = Statistics::calculateMedian(temperatures);
  double mean = Statistics::calculateMean(temperatures);

  // Output report
  std::cout << "Final Report for 1374 Sols:\n\n";

  std::cout << "Temperature Statistics:\n";
  std::cout << "3 Highest Temperatures (C): "
            << temperatures[temperatures.size() - 3] << ", "
            << temperatures[temperatures.size() - 2] << ", "
            << temperatures[temperatures.size() - 1] << "\n";
  std::cout << "3 Lowest Temperatures (C): " << temperatures[0] << ", "
            << temperatures[1] << ", " << temperatures[2] << "\n";
  std::cout << "Median Temperature: " << median << "C (" << (median + 273.15)
            << "K)\n";
  std::cout << "Mean Temperature: " << mean << "C (" << (mean + 273.15)
            << "K)\n";

  // Note: Lowest winter and summer temperatures would require additional logic
  // to determine seasons

  std::cout << "\nSample Classifications:\n";
  int count = 0;
  for (auto it = allSOLData.rbegin(); it != allSOLData.rend() && count < 9;
       ++it) {
    if (it->getSampleData().getClassifiedElement() != "Unknown") {
      std::cout << "SOL " << it->getSolNumber() << ": "
                << it->getSampleData().getClassifiedElement() << "\n";
      count++;
    }
  }

  std::cout << "\nDistances Traveled:\n";
  for (const auto& solData : allSOLData) {
    const auto& navData = solData.getNavigationData();
    std::cout << "SOL " << solData.getSolNumber() << ": "
              << std::setprecision(2) << std::fixed
              << static_cast<double>(navData.finalDistance.getValue()) << " meters, "
              << "Direction: " << static_cast<int>(navData.finalDirection)
              << "\n";
  }
  return 0;
}
