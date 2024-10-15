#include "Subsystems/Navigation.h"
#include <cmath>

void Navigation::addRecord(Direction direction, const Measurement& distance) {
    position.update(direction, distance.toBaseUnit());
    directionManager.rotate(direction, 90.0); // Assuming 90 degree turns
}

double Navigation::calculateFinalPosition() const {
    return position.calculateDistanceFromOrigin();
}

Direction Navigation::getFinalDirection() const {
    double angle = directionManager.getCurrentAngle();
    if (angle < 45 || angle >= 315) return Direction::Forward;
    if (angle < 135) return Direction::Right;
    if (angle < 225) return Direction::Backward;
    return Direction::Left;
}

NavigationData Navigation::getNavigationData() const {
    return {calculateFinalPosition(), getFinalDirection()};
}

void Navigation::reset() {
    position = Position();
    directionManager = DirectionManager();
}
