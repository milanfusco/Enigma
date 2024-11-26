# Enigma

**Enigma** is a modular framework designed for a companion rover to NASA's Curiosity and the Mars Science Laboratory (MSL) mission. It supports advanced robotic operations, data analysis, and subsystem management, extending the capabilities of robotic exploration in challenging environments like Mars.

## Features

- **Mission Control**: Provides centralized coordination and execution of rover operations.
- **Robotic Subsystems**: Includes support for navigation, temperature monitoring, sample analysis, and classification.
- **Data Management**: Robust mechanisms for data storage, processing, and retrieval of scientific and operational data.
- **Record Handling**: Flexible strategies for creating, parsing, and processing mission records.
- **Utility Support**: Includes tools for unit conversions, unique pointer utilities, and measurement processing.

## Project Structure

### Core Components
- **Mission Control**:
  - `MissionControl.h/cpp`: Coordinates overall rover operations and subsystem interactions.
  - `Robot.h/cpp`: Abstracts the rover and its interfaces.
  - **Data Management**:
   - `DataStorage.h/cpp`, `SOLData.h/cpp`, `SolManager.h/cpp`: Handles data related to SOLs (Martian days), ensuring accurate recording and management of mission data.


### Subsystems
- **Navigation**:
  - `Navigation.h/cpp`, `DirectionManager.cpp`, `Position.cpp`: Enables precise maneuvering and direction handling for the rover.
- **Sample Analysis**: - `SampleAnalysis.h/cpp`, `SampleClassification.h/cpp`: Processes and classifies samples collected during missions.
- - **Temperature Monitoring**:\n - `Temperature.h/cpp`, `Statistics.cpp`: Analyzes and records temperature variations.


### Utility
- `Units.h/cpp`, `Measurement.h/cpp`, `MakeUnique.h`: Provides measurement handling and utility functions for the system.


### Tests
- `src/Tests/`: Contains test scripts for validating components like `MissionControl`, `SOLManager`, and `DataStorage`.


### Build and Configuration
- `CMakeLists.txt`: Build system configuration for easy project compilation.
- `TestFiles/`: Contains test data for system validation (e.g., `lab2_test_data.txt`).


## Getting Started

### Prerequisites
- **C++ Compiler**: Requires a modern C++ compiler (C++11 or later).
- **CMake**: For building the project.


### Building the Project
1. Clone the repository:
  ```git clone https://github.com/milanfusco/Enigma.git```
- 2. Navigate to the project directory:
  ```cd Enigma```
- 3. Build using CMake:
     - ```mkdir build```
     - ```cd build```
     - ```cmake ..```
     - ```make```


### Running the Application
Run the main program:```./Enigma```

### Testing
Run the test cases:
```./src/Tests/testMain```

## License
[MIT License](LICENSE)

## Acknowledgments
**Inspired by**: NASA’s Mars Science Laboratory mission and its groundbreaking rover, Curiosity.

**Tools Used**: CMake, modern C++ practices.
