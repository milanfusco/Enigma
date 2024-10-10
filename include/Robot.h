#ifndef ROBOT_H
#define ROBOT_H

#include <memory>
#include "Navigation.h"
#include "RobotInterface.h"
#include "SampleAnalysis.h"
#include "Temperature.h"

class Robot : public RobotInterface {
private:
  std::unique_ptr<Navigation> navigation;
  std::unique_ptr<Temperature> temperature;
  std::unique_ptr<SampleAnalysis> sampleAnalysis;

 public:
  Robot(std::unique_ptr<Navigation> nav,
        std::unique_ptr<Temperature> temp,
        std::unique_ptr<SampleAnalysis> sample);

  void processRecord(const RecordPtr& record) override;
  SOLData getCurrentSOLData(int solNumber) const override;
  void reset() override;
};

 

#endif  // ROBOT_H