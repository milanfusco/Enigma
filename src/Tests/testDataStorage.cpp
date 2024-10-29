// test_data_storage.cpp
#include <cassert>
#include "Data/DataStorage.h"

void test_store_and_retrieve_sol_data() {
    DataStorage storage;
    SOLData solData(1);
    solData.storeTemperatureData(25.5);
    storage.storeSOLData(solData);

    auto retrievedData = storage.getSOLData(1);
    assert(retrievedData.getTemperatureData() == 25.5);
}
