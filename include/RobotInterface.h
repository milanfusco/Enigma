#ifndef ROBOTINTERFACE_H
#define ROBOTINTERFACE_H

#include <memory>
#include "Records.h"
#include "SOLData.h"

/**
 * @class RobotInterface
 * @brief Abstract interface for robot operations.
 *
 * This interface defines the core functionality that any robot
 * implementation must provide.
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

    virtual ~RobotInterface() = default;
};

using RobotInterfacePtr = std::unique_ptr<RobotInterface>;

#endif  // RobotInterface_h