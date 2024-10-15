/**
 * @file RobotInterface.h
 * @brief Declaration of the RobotInterface class.
 *
 * The RobotInterface class defines the core functionality that any robot
 * implementation must provide. It serves as a facade for the concrete robot
 * class, hiding the complexity of the subsystems behind a single interface.
 * It uses the Facade design pattern, along with the PIMPL idiom to hide the
 * implementation details of the concrete robot class.
 */

#ifndef ROBOTINTERFACE_H
#define ROBOTINTERFACE_H

#include <memory>
#include "Records.h"
#include "SOLData.h"

/**
 * @class RobotInterface
 * @brief Abstract interface for robot operations.
 *
 * The RobotInterface class defines the core functionality that any robot
 * implementation must provide. It serves as a facade for the concrete robot
 * class, hiding the complexity of the subsystems behind a single interface.
 */
class RobotInterface {
public:
    /**
     * @brief Processes a record, updating relevant subsystems.
     * @param record Pointer to the record to be processed.
     */
    virtual void processRecord(const RecordPtr& record) = 0;

    /**
     * @brief Retrieves the current SOL data.
     * @param solNumber The SOL number to retrieve data for.
     * @return SOLData object containing the current SOL information.
     */
    virtual SOLData getCurrentSOLData(int solNumber) const = 0;

    /**
     * @brief Resets all subsystems to their initial state.
     */
    virtual void reset() = 0;

    /**
     * @brief Destructor for the RobotInterface.
     */
    virtual ~RobotInterface() = default;
};

/** @brief A pointer to a RobotInterface. */
using RobotInterfacePtr = std::unique_ptr<RobotInterface>;

#endif  // ROBOTINTERFACE_H
