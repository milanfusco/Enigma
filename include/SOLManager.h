#ifndef SOLMANAGER_H
#define SOLMANAGER_H

#include <memory>
#include <vector>
#include "SOLData.h"

/**
 * @class SOLObserver
 * @brief Abstract base class for objects that observe SOL finalization.
 */
class SOLObserver {
 public:
  /**
   * @brief Called when a SOL is finalized.
   * @param solData The finalized SOL data.
   */
  virtual void onSOLFinalized(const SOLData& solData) = 0;
  virtual ~SOLObserver() = default;
};

using SOLObserverPtr = std::shared_ptr<SOLObserver>;

/**
 * @class SOLManager
 * @brief Manages SOL progression and notifies observers of SOL finalization.
 */
class SOLManager {
 private:
  int currentSOL;
  int totalSOLs;
  std::vector<SOLObserverPtr> observers;

 public:
  /**
   * @brief Advances to the next SOL.
   */
  void advanceSOL();

  /**
   * @brief Gets the current SOL number.
   * @return The current SOL number.
   */
  int getCurrentSOL() const;

  /**
   * @brief Gets the total number of SOLs elapsed.
   * @return The total number of SOLs.
   */
  int getTotalSOLs() const;

  /**
   * @brief Adds an observer to be notified of SOL finalization.
   * @param observer Shared pointer to the observer to add.
   */
  void addObserver(SOLObserverPtr observer);

  /**
   * @brief Removes an observer from the notification list.
   * @param observer Shared pointer to the observer to remove.
   */
  void removeObserver(const SOLObserverPtr& observer);

  /**
   * @brief Notifies all observers of SOL finalization.
   * @param solData The finalized SOL data.
   */
  void notifyObservers(const SOLData& solData);
};

#endif  // SOLMANAGER_H