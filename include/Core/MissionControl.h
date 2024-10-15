/**
 * @file MissionControl.h
 * @brief Declaration of the MissionControl class.
 *
 * The MissionControl class coordinates the robot's activities, manages SOL
 * data, and handles record processing and storage.
 */

#ifndef MISSIONCONTROL_H
#define MISSIONCONTROL_H

#include "Robot.h"
#include "SOLManager.h"
#include "SOLData.h"
#include "DataStorage.h"
#include "RecordParser.h"
#include <memory>

/**
 * @class MissionControl
 * @brief Central control system for managing robot operations and data collection.
 *
 * This class coordinates the robot's activities, manages SOL data, and handles
 * record processing and storage.
 */
class MissionControl : public SOLObserver {
private:
    RobotInterfacePtr robot;
    std::unique_ptr<SOLManager> solManager;
    std::unique_ptr<DataStorage> dataStorage;
    std::unique_ptr<RecordParser> recordParser;

public:
    /**
     * @brief Constructs a new MissionControl object.
     * @param robot Pointer to the robot interface.
     * @param solManager Unique pointer to the SOL manager.
     * @param dataStorage Unique pointer to the data storage system.
     * @param recordParser Unique pointer to the record parser.
     */
    MissionControl(RobotInterfacePtr robot,
                   std::unique_ptr<SOLManager> solManager,
                   std::unique_ptr<DataStorage> dataStorage,
                   std::unique_ptr<RecordParser> recordParser);

    /**
     * @brief Processes a received record.
     * @param record The record string to be processed.
     */
    void handleRecord(const std::string& record);

    /**
     * @brief Finalizes the current SOL's data collection.
     */
    void finalizeCurrentSOL();

    /**
     * @brief Retrieves all stored observations.
     * @return A vector of all SOL data collected.
     */
    std::vector<SOLData> getObservations() const;

    /**
     * @brief Callback method invoked when a SOL is finalized.
     * @param solData The finalized SOL data.
     */
    void onSOLFinalized(const SOLData& solData) override;
};

#endif // MISSIONCONTROL_H