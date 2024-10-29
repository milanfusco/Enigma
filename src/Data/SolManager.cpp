/**
 * @file SolManager.cpp
 * @brief Implementation of the SOLManager class.
 */

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
  observers.erase(std::remove_if(observers.begin(), observers.end(),
                  [&observer](const std::weak_ptr<SOLObserver>& observer_weak) {
                      if (const auto obs_shared = observer_weak.lock()) {
                          return obs_shared == observer;  // Compare the shared_ptr
                      }
                      return false;  // Skip if the weak_ptr is expired
                  }),
                  observers.end());
}

void SOLManager::notifyObservers(const SOLData& solData) const {
  for ( auto& observer_weak : observers) {
    if (auto observer = observer_weak.lock()) {
      observer->onSOLFinalized(solData);
    }
  }
}
