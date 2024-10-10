#include "MissionControl.h"

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
