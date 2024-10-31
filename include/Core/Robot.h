/**
 * @file Robot.h
 * @brief Declaration of the concrete Robot class.
 *
 * The Robot class implements the RobotInterface, providing a simplified
 * interface to the underlying subsystems. It uses the Facade design pattern to
 * hide the complexity of the subsystems behind a single interface.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "RobotInterface.h"
#include "Utility/MakeUnique.h"

class Navigation; // Forward declarations
class Temperature;
class SampleAnalysis;

/**
 * @class Robot
 * @brief Implementation of the RobotInterface.
 *
 * The Robot class implements the RobotInterface, providing a simplified
 * interface to the underlying subsystems. It uses the Facade design pattern to
 * hide the complexity of the subsystems behind a single interface.
 */
class Robot : public RobotInterface {
private:
  /** @brief The navigation subsystem. */
  std::unique_ptr<Navigation> navigation;
  /** @brief The temperature subsystem. */
  std::unique_ptr<Temperature> temperature;
  /** @brief The sample analysis subsystem. */
  std::unique_ptr<SampleAnalysis> sampleAnalysis;

 public:
  /**
   * @brief Constructor for the Robot class.
   * @param nav The navigation subsystem.
   * @param temp The temperature subsystem.
   * @param sample The sample analysis subsystem.
   */
  Robot(std::unique_ptr<Navigation> nav,
        std::unique_ptr<Temperature> temp,
        std::unique_ptr<SampleAnalysis> sample);

  /**
   * @brief Processes a record.
   * @param record The record to process.
   */
  void processRecord(const RecordPtr& record) override;

  /**
   * @brief Gets the current SOL data.
   * @param solNumber The SOL number.
   * @return The SOL data.
   */
  SOLData getCurrentSOLData(int solNumber) const override;
  void reset() override;

  void moveToLocation(double x, double y);
  void collectSample();
  void transmitData();

  static std::unique_ptr<Robot> createRobot();
};

#endif  // ROBOT_H