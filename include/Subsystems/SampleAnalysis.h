#ifndef SAMPLEANALYSIS_H
#define SAMPLEANALYSIS_H

#include "Records.h"
#include "SampleClassification.h"

/**
 * @class SampleAnalysis
 * @brief Manages sample analysis records and classifications.
 */
class SampleAnalysis {
 private:
  std::pair<Measurement, double> sample; /**< The samples collected. */
  SampleClassification
      classification; /**< The classifications of the samples. */

 public:
  /**
   * @brief Adds a new sample analysis record.
   * @param wavelength The wavelength of the sample.
   * @param intensity The intensity of the sample.
   */
  void addRecord(const Measurement& wavelength, const double intensity);

  /**
   * @brief Classifies the sample based on the intensity and wavelength.
   */
  void classifySample();

  /**
   * @brief Retrieves the classification of the sample.
   * @return A string representing the classification of the sample.
   */
  std::string getElementClassification() const;

  /**
   * @brief Retrieves the sample classification.
   * @return The sample classification object.
   */
  SampleClassification getSampleClassification() const;

  /**
   * @brief Resets the sample analysis data.
   */
  void reset();
};

#endif  // SAMPLEANALYSIS_H