cmake_minimum_required(VERSION 3.5)
project(Enigma VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

# Add include directory
include_directories(
    "include"
    "include/Core"
    "include/Core/MissonControl.h"
    "include/Core/Robot.h"
    "include/Core/RobotInterface.h"
    "include/Data"
    "include/Data/SOLData.h"
    "include/Data/DataStorage.h"
    "include/Data/SOLManager.h"
    "include/Navigation"
    "include/Navigation/Navigation.h"
    "include/Records"
    "include/Records/Records.h"
    "include/Records/RecordFactory.h"
    "include/Records/RecordParser.h"
    "include/Records/RecordProcessingStrategy.h"
    "include/Subsystems"
    "include/Subsystems/Navigation.h"
    "include/Subsystems/SampleAnalysis.h"
    "include/Subsystems/Temperature.h"
    "include/Subsystems/SampleClassification.h"
    "include/Temperature"
    "include/Utility"
    "include/Utility/Measurement.h"
    "include/Utility/Units.h"
)

# Gather all source files
file(GLOB_RECURSE TARGET_SRC 
    "src/*.cpp"
    "src/Core/*.cpp"
    "src/Data/*.cpp"
    "src/Navigation/*.cpp"
    "src/Records/*.cpp"
    "src/SampleAnalysis/*.cpp"
    "src/Temperature/*.cpp"
    "src/Utility/*.cpp"
)

# Create the executable
add_executable(main ${TARGET_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
