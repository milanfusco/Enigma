// test_mission_control.cpp
#include <cassert>
#include "Core/MissionControl.h"
#include "Core/Robot.h"
#include "Data/SOLManager.h"
#include "Data/DataStorage.h"
#include "Records/RecordParser.h"
#include "Utility/MakeUnique.h"

void test_handle_record() {
    auto robot = Robot::createRobot();
    auto solManager = make_unique_ptr<SOLManager>();
    auto dataStorage = make_unique_ptr<DataStorage>();
    auto recordParser = make_unique_ptr<RecordParser>();

    auto missionControl = std::make_shared<MissionControl>(std::move(robot), std::move(solManager),
                                                         std::move(dataStorage), std::move(recordParser));
    missionControl->initialize();

    std::string record = "t,20.5,celsius";
    missionControl->handleRecord(record);
    
    missionControl->finalizeCurrentSOL();
    auto observations = missionControl->getObservations();
    
    // Check if the temperature is stored as Kelvin
    double expectedTemperature = 20.5 + 273.15; // Celsius to Kelvin conversion
    assert(observations.size() == 1);
    assert(observations[0].getTemperatureData() == expectedTemperature);
}

void test_distance_record() {
    auto robot = Robot::createRobot();
    auto solManager = make_unique_ptr<SOLManager>();
    auto dataStorage = make_unique_ptr<DataStorage>();
    auto recordParser = make_unique_ptr<RecordParser>();

    auto missionControl = std::make_shared<MissionControl>(std::move(robot), std::move(solManager),
                                                         std::move(dataStorage), std::move(recordParser));
    missionControl->initialize();

    std::string record = 
        "d,10.5,meters,forward,10,minutes,"
        "43.5,centimeters,right,30,seconds,"
        "1.2,kilometers,left,1,hour,"
        "63.8,centimeters,right,2,minutes";
    
    missionControl->handleRecord(record);
    missionControl->finalizeCurrentSOL();

    auto observations = missionControl->getObservations();
    assert(observations.size() == 1);
     // assert(observations[0].getNavigationData().getDistance() == 10.5);
}

void test_finalize_sol() {
    auto robot = Robot::createRobot();
    auto solManager = make_unique_ptr<SOLManager>();
    auto dataStorage = make_unique_ptr<DataStorage>();
    auto recordParser = make_unique_ptr<RecordParser>();

    auto missionControl = std::make_shared<MissionControl>(std::move(robot), std::move(solManager),
                                                         std::move(dataStorage), std::move(recordParser));
    missionControl->initialize();

    missionControl->handleRecord("t,15,kelvin");
    missionControl->finalizeCurrentSOL();
    
    auto observations = missionControl->getObservations();
    assert(observations.size() == 1);
    assert(observations[0].getTemperatureData() == 15);
}