/**
 * @file Navigation.h
 * @brief Declaration of the Navigation class.
 *
 * The navigation subsystem manages the robot's position and direction.
 * It provides methods to update the position based on movement records and
 * to calculate distances and final positions.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Records.h"
#include "SOLData.h"
#include "Units.h"

/**
 * @class Position
 * @brief Represents the robot's position in a 2D coordinate system.
 */
class Position {
 private:
  double x =
      0;  ///> Default x-coordinate is 0 (Origin A.K.A. Rover Landing Site)
  double y =
      0;  ///> Default y-coordinate is 0 (Origin A.K.A. Rover Landing Site)
 public:
  /**
   * @brief Updates the position based on a movement.
   * Forward (+) and Backward (-) are along the y-axis.
   * Left (-) and Right (+) are along the x-axis.
   * @param direction The direction of movement.
   * @param distance The distance moved.
   */
  void update(const Direction direction, const double distance);

  /**
   * @brief Calculates the distance to another position.
   * @param p The other position.
   * Uses euclidean distance formula to calculate distance.
   * \f$ distance_p = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \f$
   * @return The distance between this position and p.
   */
  double calculateDistance(const Position& p) const;

  /**
   * @brief Calculates the distance from the origin (0, 0).
   * Uses pythagorean theorem to calculate distance.
   * \f$ distance_o = \sqrt{x^2 + y^2} \f$
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
  ///> Angle starts at North (Rover alligned North when lowered from sky-crane)
  double currentAngle = 0;

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
  Position position;
  DirectionManager directionManager;

 public:
  /**
   * @brief Adds a new navigation record.
   * @param direction The direction of the movement.
   * @param distance The distance of the movement.
   */
  void addRecord(Direction direction, const Measurement& distance);

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

#endif  // NAVIGATION_H