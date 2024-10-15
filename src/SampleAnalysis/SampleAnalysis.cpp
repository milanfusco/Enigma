#include "Subsystems/SampleAnalysis.h"
#include "Subsystems/SampleClassification.h"

void SampleAnalysis::addRecord(const Measurement& wavelength,
                               double intensity) {
  sample = std::make_pair(wavelength, intensity);
}

void SampleAnalysis::classifySample() {
  classification.classify(sample.first.toBaseUnit(), sample.second);
}

std::string SampleAnalysis::getElementClassification() const {
  return classification.getClassifiedElement();
}

SampleClassification SampleAnalysis::getSampleClassification() const {
  return SampleAnalysis::classification.getSampleClassification();
}

void SampleAnalysis::reset() {
  sample.first = Measurement();
  sample.second = 0.0;
  classification = SampleClassification();
}
