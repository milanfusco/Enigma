#include "Data/SOLManager.h"
#include <algorithm>

SOLManager::SOLManager(int totalSOLs) : currentSOL(INITIAL_SOL), totalSOLs(INITIAL_SOL) {}

void SOLManager::advanceSOL() {
  currentSOL++;
  totalSOLs++;
}

int SOLManager::getCurrentSOL() const {
  return currentSOL;
}

int SOLManager::getTotalSOLs() const {
  return totalSOLs;
}

void SOLManager::addObserver(SOLObserverPtr observer) {
  observers.push_back(observer);
}

void SOLManager::removeObserver(const SOLObserverPtr& observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

void SOLManager::notifyObservers(const SOLData& solData) {
  for (const auto& observer : observers) {
    observer->onSOLFinalized(solData);
  }
}