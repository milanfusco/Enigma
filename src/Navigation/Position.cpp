#include "Subsystems/Navigation.h"
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
