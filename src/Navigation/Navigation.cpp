#include "Subsystems/Navigation.h"
#include <cmath>

void Navigation::addRecord(
    const std::vector<std::pair<Measurement, Direction>>& measurements) {
  for (const auto& [distance, direction] : measurements) {
    double distanceInBaseUnits = distance.toBaseUnit();
    position.update(direction, distanceInBaseUnits);
    if (direction == Direction::Left || direction == Direction::Right) {
      double angle = (direction == Direction::Left) ? 90.0 : -90.0;
      directionManager.rotate(direction, angle);
    }
  }
}

double Navigation::calculateFinalPosition() const {
  return position.calculateDistanceFromOrigin();
}

Direction Navigation::getFinalDirection() const {
  double angle = directionManager.getCurrentAngle();
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
  record.finalDistance = Measurement(calculateFinalPosition(), UnitType::Distance, static_cast<int>(DistanceUnit::Meter));
  record.finalDirection = getFinalDirection();
  return record;
}

void Navigation::reset() {
  position = Position();
  directionManager = DirectionManager();
}
