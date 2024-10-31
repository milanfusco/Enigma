/**
 * @file Navigation.cpp
 * @brief Implementation of the Navigation class.
 */

#include "Subsystems/Navigation.h"
#include <cmath>

void Navigation::addRecord(
    const std::vector<std::pair<Measurement, Direction>>& measurements) {
  for (const auto& measurement : measurements) {
    const Measurement& distance = measurement.first;
    const Direction& direction = measurement.second;

    const double distanceInBaseUnits = distance.toBaseUnit();
    position.update(direction, distanceInBaseUnits);

    if (direction == Direction::Left || direction == Direction::Right) {
      const double angle = (direction == Direction::Left) ? 90.0 : -90.0;
      directionManager.rotate(direction, angle);
    }
  }

  finalDistance = calculateFinalPosition();
  finalDirection = processFinalDirection();
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
  record.finalDistance = Measurement(getFinalDistance(), UnitType::Distance,
                                     static_cast<int>(DistanceUnit::Meter));
  record.finalDirection = finalDirection;
  return record;
}

void Navigation::reset() {
  position = Position();
  directionManager = DirectionManager();
  finalDistance = 0;
  finalDirection = Direction::Forward;
}
