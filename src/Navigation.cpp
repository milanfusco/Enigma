#include "Navigation.h"
#include <cmath>

void Position::update(const Direction direction, const double distance) {
    switch (direction) {
        case Direction::Forward:
            y += distance;
            break;
        case Direction::Backward:
            y -= distance;
            break;
        case Direction::Left:
            x -= distance;
            break;
        case Direction::Right:
            x += distance;
            break;
    }
}

double Position::calculateDistance(const Position &p) const {
    return std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
}

double Position::calculateDistanceFromOrigin() const {
    return std::sqrt(x*x + y*y);
}

void DirectionManager::rotate(const Direction direction, const double angle) {
    if (direction == Direction::Left) {
        currentAngle += angle;
    } else if (direction == Direction::Right) {
        currentAngle -= angle;
    }
    
    // Normalize angle to [0, 360)
    currentAngle = std::fmod(currentAngle + 360.0, 360.0);
}

double DirectionManager::getCurrentAngle() const {
    return currentAngle;
}

void Navigation::addRecord(const NavigationRecord &record) {
    records.push_back(record);
    // Update position and direction based on the record
    position.update(record.getDirection(), record.getDistance().toBaseUnit());
    directionManager.rotate(record.getDirection(), 90.0); // Assuming 90 degree turns
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
    records.clear();
    position = Position();
    directionManager = DirectionManager();
}