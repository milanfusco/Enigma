#include "Robot.h"
#include "RobotInterface.h"

#include <memory>

// Factory function to create a Robot instance
RobotInterfacePtr createRobot() {
  return std::make_unique<Robot>(std::make_unique<Navigation>(),
                                 std::make_unique<Temperature>(),
                                 std::make_unique<SampleAnalysis>());
}
Robot::Robot(std::unique_ptr<Navigation> nav,
      std::unique_ptr<Temperature> temp,
      std::unique_ptr<SampleAnalysis> sample)
    : navigation(std::move(nav)),
      temperature(std::move(temp)),
      sampleAnalysis(std::move(sample)) {}

void Robot::processRecord(const RecordPtr& record) {
  record->process(*navigation, *temperature, *sampleAnalysis);
}

SOLData Robot::getCurrentSOLData(int solNumber) const  {
  SOLData solData(solNumber);
  solData.storeTemperatureData(temperature->getTemperatureData());
  solData.storeNavigationData(navigation->getNavigationData());
  solData.storeSampleData(sampleAnalysis->getSampleClassification());
  return solData;
}

void Robot::reset() {
  navigation->reset();
  temperature->reset();
  sampleAnalysis->reset();
}


