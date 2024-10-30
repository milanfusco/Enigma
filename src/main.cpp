#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include "Core/MissionControl.h"
#include "Core/Robot.h"
#include "Data/DataStorage.h"
#include "Data/SOLManager.h"
#include "Records/RecordParser.h"
#include "Subsystems/SampleClassification.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::__throw_runtime_error("Usage: ./main <input_file>");
  }

  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    std::__throw_runtime_error("Unable to open input file");
  }

  auto robot = Robot::createRobot();
  auto solManager = std::make_unique<SOLManager>();
  auto dataStorage = std::make_unique<DataStorage>();
  auto recordParser = std::make_unique<RecordParser>();

  auto missionControl = std::make_shared<MissionControl>(
      std::move(robot), std::move(solManager), std::move(dataStorage),
      std::move(recordParser));

  missionControl->initialize();

  std::string record;
  while (std::getline(inputFile, record)) {
    missionControl->handleRecord(record);
    if (record[0] == 't') {
      missionControl->finalizeCurrentSOL();
    }
  }

  // Generate final report
  auto allSOLData = missionControl->getObservations();

  // Process temperature data
  std::vector<double> temperatures;
  for (const auto& solData : allSOLData) {
    temperatures.push_back(solData.getTemperatureData());
  }

  double highestSummerTemperature = Statistics::calculateLowestSummerTemperature(temperatures);
  double lowestWinterTemperature = Statistics::calculateLowestWinterTemperature(temperatures);

  std::sort(temperatures.begin(), temperatures.end());

  // Calculate statistics
  double median = Statistics::calculateMedian(temperatures);
  double mean = Statistics::calculateMean(temperatures);

  // Output report
  std::cout << "Final Report for 1374 Sols:\n\n";

  std::cout << "Temperature Statistics:\n";
  std::cout << "3 Highest Temperatures (K): "
            << temperatures[temperatures.size() - 3] << ", "
            << temperatures[temperatures.size() - 2] << ", "
            << temperatures[temperatures.size() - 1] << "\n";
  std::cout << "3 Lowest Temperatures (K): " << temperatures[0] << ", "
            << temperatures[1] << ", " << temperatures[2] << "\n";
  std::cout << "Median Temperature: " << median << "K (" << (median - 273.15)
            << "C)\n";
  std::cout << "Mean Temperature: " << mean << "C (" << (mean - 273.15)
            << "C)\n";
  std::cout << "Highest Summer Temperature: " << highestSummerTemperature
            << "K (" << (highestSummerTemperature - 273.15) << "C)\n";
  std::cout << "Lowest Winter Temperature: " << lowestWinterTemperature
            << "K (" << (lowestWinterTemperature - 273.15) << "C)\n";


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
                << static_cast<double>(navData.finalDistance.getValue())
                << " meters, "
                << "Direction: "
                << UnitConverter::directionToString(navData.finalDirection)
                << "\n";
    }
  return 0;
}
