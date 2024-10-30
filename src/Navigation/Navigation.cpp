/**
 * @file Navigation.cpp
 * @brief Implementation of the Navigation class.
 */

#include "Subsystems/Navigation.h"
#include <cmath>
#include <iostream> // DEBUG

void Navigation::addRecord(
    const std::vector<std::pair<Measurement, Direction>>& measurements) {
  for (const auto& [distance, direction] : measurements) {
    const double distanceInBaseUnits = distance.toBaseUnit();

    std::cout << "Direction: " << static_cast<int>(direction) 
                  << ", Distance: " << distanceInBaseUnits << std::endl; // DEBUG

    position.update(direction, distanceInBaseUnits);
    if (direction == Direction::Left || direction == Direction::Right) {
      const double angle = (direction == Direction::Left) ? 90.0 : -90.0;
      directionManager.rotate(direction, angle);

      std::cout << "Current Angle after rotation: " << directionManager.getCurrentAngle() << std::endl; // DEBUG
    }
  }  
  finalDistance = calculateFinalPosition();
  finalDirection = processFinalDirection();

  std::cout << "Final Position: " << finalDistance << " meters\n"; // DEBUG
  std::cout << "Final Direction: " << static_cast<int>(finalDirection) << std::endl; // DEBUG
}

double Navigation::calculateFinalPosition() const {
  return position.calculateDistanceFromOrigin();
}

Direction Navigation::processFinalDirection() const {
  const double angle = directionManager.getCurrentAngle();
  if (angle < 45 || angle >= 315)
    return Direction::Forward;
  if (angle < 135)
    return Direction::Right;
  if (angle < 225)
    return Direction::Backward;
  return Direction::Left;
}

NavigationRecord Navigation::getNavigationData() const {
  NavigationRecord record;
  record.finalDistance = Measurement(getFinalDistance(), UnitType::Distance, static_cast<int>(DistanceUnit::Meter));
  record.finalDirection = finalDirection;
  return record;
}

void Navigation::reset() {
  position = Position();
  directionManager = DirectionManager();
  finalDistance = 0;
  finalDirection = Direction::Forward;
}
