/**
 * @file SOLManager.h
 * @brief Declaration of the SOLManager class.
 *
 * This class manages the progression of SOLs and notifies observers of SOL
 * finalization.
 */
#ifndef SOLMANAGER_H
#define SOLMANAGER_H

#include <memory>
#include <vector>
#include "Data/SOLData.h"

/**
 * @brief The initial SOL number.
 */
const int INITIAL_SOL = 1;

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

  /**
   * @brief Destructor for SOLObserver.
   */
  virtual ~SOLObserver() = default;
};

using SOLObserverPtr = std::shared_ptr<SOLObserver>;

/**
 * @class SOLManager
 * @brief Manages SOL progression and notifies observers of SOL finalization.
 */
class SOLManager {
 private:
  int currentSOL; /**< The current SOL number. */
  int totalSOLs;  /**< The total number of SOLs. */
  std::vector<std::weak_ptr<SOLObserver>>
      observers; /**< The observers of the SOL. */

 public:
  /**
   * @brief Constructor for SOLManager.
   * @param totalSOLs The total number of SOLs.
   */
  SOLManager(int totalSOLs = 0);

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
  void notifyObservers(const SOLData& solData) const;
};

#endif  // SOLMANAGER_H