#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Records.h"
#include "SOLData.h"

/**
 * @class Position
 * @brief Represents the robot's position in a 2D coordinate system.
 */
class Position {
private:
    double x;
    double y;
public:
    /**
     * @brief Updates the position based on a movement.
     * @param direction The direction of movement.
     * @param distance The distance moved.
     */
    void update(const Direction direction, const double distance);

    /**
     * @brief Calculates the distance to another position.
     * @param p The other position.
     * @return The distance between this position and p.
     */
    double calculateDistance(const Position &p) const;

    /**
     * @brief Calculates the distance from the origin (0, 0).
     * @return The distance from the origin.
     */
    double calculateDistanceFromOrigin() const;
};

/**
 * @class DirectionManager
 * @brief Manages the robot's current direction and rotation.
 */
class DirectionManager {
    private:
        double currentAngle;
    public:
        /**
         * @brief Rotates the robot in a given direction.
         * @param direction The direction to rotate (left or right).
         * @param angle The angle to rotate by.
         */
        void rotate(const Direction direction, const double angle);

        /**
         * @brief Gets the current angle of the robot.
         * @return The current angle in degrees.
         */
        double getCurrentAngle() const;
};

/**
 * @class Navigation
 * @brief Manages the robot's navigation, including position and direction.
 */
class Navigation {
private:
    std::vector<NavigationRecord> records;
    Position position;
    DirectionManager directionManager;

public:
    /**
     * @brief Adds a new navigation record.
     * @param record The navigation record to add.
     */
    void addRecord(const NavigationRecord &record);

    /**
     * @brief Calculates the final position of the robot.
     * @return The distance from the starting point.
     */
    double calculateFinalPosition() const;

    /**
     * @brief Gets the final direction of the robot.
     * @return The final direction.
     */
    Direction getFinalDirection() const;

    /**
     * @brief Gets the complete navigation data.
     * @return A NavigationData object containing final position and direction.
     */
    NavigationData getNavigationData() const;

    /**
     * @brief Resets the navigation data to initial state.
     */
    void reset();
};

#endif // NAVIGATION_H