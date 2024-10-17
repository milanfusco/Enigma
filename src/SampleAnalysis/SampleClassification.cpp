#include "Subsystems/SampleClassification.h"
#include <string>
#include <vector>

std::vector<SampleClassification::Element>
SampleClassification::initializeElementLibrary() {
  return {
      {"Iron", {380, 400}, {400, 420}, {420, 450}},
      {"Magnesium", {285, 300}, {300, 320}, {320, 340}},
      {"Silicon", {250, 270}, {270, 290}, {290, 310}},
      {"Aluminum", {308, 330}, {330, 350}, {350, 370}},
      {"Calcium", {393, 405}, {405, 425}, {425, 445}},
      {"Titanium", {330, 345}, {345, 365}, {365, 385}},
      {"Manganese", {405, 425}, {425, 445}, {445, 465}},
      {"Sodium", {589, 590}, {590, 600}, {600, 610}},
      {"Lithium", {670, 690}, {690, 710}, {710, 730}},
      {"Potassium", {766, 770}, {771, 774}, {774, 780}},
      {"Oxygen", {759, 763}, {763, 770}, {770, 780}},
      {"Hydrogen", {656, 660}, {660, 670}, {670, 680}},
      {"Carbon", {430, 450}, {450, 470}, {470, 490}},
  };
}

std::vector<SampleClassification::IntensityRanges>
SampleClassification::initializeIntensityRanges() {
  return {{"Iron", 0.8, 0.5, 0.2},        {"Magnesium", 0.85, 0.6, 0.3},
          {"Silicon", 0.9, 0.65, 0.35},   {"Aluminum", 0.88, 0.6, 0.3},
          {"Calcium", 0.92, 0.7, 0.4},    {"Titanium", 0.87, 0.63, 0.32},
          {"Manganese", 0.9, 0.65, 0.33}, {"Sodium", 0.95, 0.7, 0.4},
          {"Lithium", 0.9, 0.6, 0.3},     {"Potassium", 0.9, 0.65, 0.35},
          {"Oxygen", 0.85, 0.6, 0.3},     {"Hydrogen", 0.93, 0.68, 0.4},
          {"Carbon", 0.88, 0.6, 0.3}};
}

SampleClassification::SampleClassification()
    : elementLibrary(initializeElementLibrary()),
      intensityRanges(initializeIntensityRanges()) {}

void SampleClassification::classify(double wavelength, double intensity) {
  std::string intensityLevel;
  for (const auto& range : intensityRanges) {
    if (intensity >= range.highIntensityRange) {
      intensityLevel = "high";
    } else if (intensity >= range.mediumIntensityRange) {
      intensityLevel = "medium";
    } else if (intensity >= range.lowIntensityRange) {
      intensityLevel = "low";
    } else {
      continue;
    }
    for (const auto& element : elementLibrary) {
      if (element.name == range.elementName) {
        if ((intensityLevel == "high" &&
             wavelength >= element.highIntensityRange.first &&
             wavelength <= element.highIntensityRange.second) ||
            (intensityLevel == "medium" &&
             wavelength >= element.mediumIntensityRange.first &&
             wavelength <= element.mediumIntensityRange.second) ||
            (intensityLevel == "low" &&
             wavelength >= element.lowIntensityRange.first &&
             wavelength <= element.lowIntensityRange.second)) {
          classification = element.name;
          break;
        } else {
          classification = "Unknown";
        }
      }
    }
  }
}

const std::string& SampleClassification::getClassifiedElement() const {
  return classification;
}

SampleClassification SampleClassification::getSampleClassification() const {
  return *this;
}