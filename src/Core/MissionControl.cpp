/**
 * @file MissionControl.cpp
 * @brief Implementation of the MissionControl class.
 */

#include "MissionControl.h"

MissionControl::MissionControl(RobotInterfacePtr robot,
                               std::unique_ptr<SOLManager> solManager,
                               std::unique_ptr<DataStorage> dataStorage,
                               std::unique_ptr<RecordParser> recordParser)
    : robot(std::move(robot)),
      solManager(std::move(solManager)),
      dataStorage(std::move(dataStorage)),
      recordParser(std::move(recordParser)) {
  // Use shared_from_this() to safely add the current instance as an observer
}

void MissionControl::initialize() {
  solManager->addObserver(shared_from_this());
}

void MissionControl::handleRecord(const std::string& record) const {
  const RecordPtr parsedRecord = RecordParser::parseRecord(record);
  robot->processRecord(parsedRecord);
}

void MissionControl::finalizeCurrentSOL() const {
  const int currentSolNumber = solManager->getCurrentSOL();
  const SOLData currentSOLData = robot->getCurrentSOLData(currentSolNumber);
  dataStorage->storeSOLData(currentSOLData);
  solManager->advanceSOL();
  robot->reset();
}

std::vector<SOLData> MissionControl::getObservations() const {
  return dataStorage->getAllSOLData();
}

void MissionControl::onSOLFinalized(const SOLData& solData) {
  dataStorage->storeSOLData(solData);
  // Additional actions when a SOL is finalized can be added here
}
