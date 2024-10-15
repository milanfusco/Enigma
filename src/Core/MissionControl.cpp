#include "MissionControl.h"

MissionControl::MissionControl(RobotInterfacePtr robot,
                               std::unique_ptr<SOLManager> solManager,
                               std::unique_ptr<DataStorage> dataStorage,
                               std::unique_ptr<RecordParser> recordParser)
    : robot(std::move(robot)),
      solManager(std::move(solManager)),
      dataStorage(std::move(dataStorage)),
      recordParser(std::move(recordParser)) {
  this->solManager->addObserver(std::shared_ptr<SOLObserver>(this));
}

void MissionControl::handleRecord(const std::string& record) {
  RecordPtr parsedRecord = recordParser->parseRecord(record);
  robot->processRecord(parsedRecord);
}

void MissionControl::finalizeCurrentSOL() {
  int currentSolNumber = solManager->getCurrentSOL();
  SOLData currentSOLData = robot->getCurrentSOLData(currentSolNumber);
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
