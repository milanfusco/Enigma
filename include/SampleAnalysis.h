#ifndef SAMPLEANALYSIS_H
#define SAMPLEANALYSIS_H

#include "Records.h"

/**
 * @class SampleClassification
 * @brief Classifies material samples based on spectral analysis.
 */
class SampleClassification {
 private:
  std::string materialType;

 public:
  /**
   * @brief Classifies a material based on its spectral properties.
   * @param wavelength The wavelength of the spectral reading.
   * @param intensity The intensity of the spectral reading.
   * @return A string describing the classified material type.
   */
  std::string classify(const double wavelength, const double intensity);
};

/**
 * @class SampleAnalysis
 * @brief Manages sample analysis records and classifications.
 */
class SampleAnalysis {
 private:
  std::vector<SampleAnalysisRecord> records;
  std::vector<SampleClassification> classification;

 public:
  /**
   * @brief Adds a new sample analysis record.
   * @param record The SampleAnalysisRecord to add.
   */
  void addRecord(const SampleAnalysisRecord& record);

  /**
   * @brief Classifies all collected samples.
   */
  void classifySamples();

  /**
   * @brief Retrieves the sample classification results.
   * @return The SampleClassification object containing classification results.
   */
  SampleClassification getSampleClassification() const;

  /**
   * @brief Resets the sample analysis data.
   */
  void reset();
};

#endif  // SAMPLEANALYSIS_H