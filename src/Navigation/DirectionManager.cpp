/**
 * @file DirectionManager.cpp
 * @brief Implementation of the DirectionManager class.
 */

#include "Subsystems/Navigation.h"
#include <cmath>
#include <stdexcept>

void DirectionManager::rotate(const Direction direction, const double angle) {
    if (direction == Direction::Left) {
        currentAngle += angle;
    } else if (direction == Direction::Right) {
        currentAngle -= angle;
    }
    
    // Normalize angle to [0, 360)
    // (Add 360 to handle negative angles)
    currentAngle = std::fmod(currentAngle + 360.0, 360.0); 
}

double DirectionManager::getCurrentAngle() const {

    if (currentAngle >= 360.0 || currentAngle < 0.0) {
        throw std::invalid_argument("Invalid angle: " + std::to_string(currentAngle) + " degrees is is outside of domain");
    }
    return currentAngle;
}
