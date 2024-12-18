/**
 * @file SampleClassification.h
 * @brief Declaration of the SampleClassification class.
 *
 * The SampleClassification class manages the classification of samples
 * collected during the mission. It provides methods to classify samples based
 * on intensity and wavelength, and to retrieve the classified element.
 */
#ifndef SAMPLECLASSIFICATION_H
#define SAMPLECLASSIFICATION_H

#include <string>
#include <vector>
/**
 * @class SampleClassification
 * @brief Classifies the sample based on the intensity and wavelength.
 */
class SampleClassification {
 public:
  /**
   * @struct Element
   * @brief Represents the element and its intensity ranges.
   */
  struct Element {
    std::string name;
    std::pair<int, int> highIntensityRange;
    std::pair<int, int> mediumIntensityRange;
    std::pair<int, int> lowIntensityRange;
  };
  /**
   * @struct IntensityRanges
   * @brief Represents the intensity ranges for an element.
   */
  struct IntensityRanges {
    std::string elementName;
    double highIntensityRange;
    double mediumIntensityRange;
    double lowIntensityRange;
  };

 private:
  std::string classification;
  std::vector<Element> elementLibrary;
  std::vector<IntensityRanges> intensityRanges;

 public:
  SampleClassification();
  /**
   * @brief Initializes the intensity ranges for elements.
   * @return A vector of IntensityRanges.
   */
  static std::vector<IntensityRanges> initializeIntensityRanges();
  /**
   * @brief Initializes the element library.
   * @return A vector of Element.
   */
  static std::vector<Element> initializeElementLibrary();
  /**
   * @brief Classifies the sample based on the intensity and wavelength.
   * @param wavelength The wavelength of the sample.
   * @param intensity The intensity of the sample.
   */
  void classify(double wavelength, double intensity);
  /**
   * @brief Retrieves the classified element.
   * @return A string representing the classified element.
   */
  const std::string& getClassifiedElement() const;

  SampleClassification getSampleClassification() const;
};

#endif  // SAMPLECLASSIFICATION_H
