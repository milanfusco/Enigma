#include "Robot.h"
#include "RobotInterface.h"

class Robot : public RobotInterface {
private:
    std::unique_ptr<Navigation> navigation;
    std::unique_ptr<Temperature> temperature;
    std::unique_ptr<SampleAnalysis> sampleAnalysis;

public:
    Robot(std::unique_ptr<Navigation> nav, 
          std::unique_ptr<Temperature> temp, 
          std::unique_ptr<SampleAnalysis> sample)
        : navigation(std::move(nav)),
          temperature(std::move(temp)),
          sampleAnalysis(std::move(sample)) {}

    void processRecord(const RecordPtr& record) override {
        record->process(*navigation, *temperature, *sampleAnalysis);
    }

    SOLData getCurrentSOLData(int solNumber) const override {
        TemperatureData tempData = temperature->getTemperatureData();
        std::optional<NavigationData> navData = navigation->getNavigationData();
        std::optional<SampleClassification> sampleData = 
            sampleAnalysis->getSampleClassification();

        SOLData solData(solNumber);
        solData.storeTemperatureData(tempData);
        if (navData) solData.storeNavigationData(*navData);
        if (sampleData) solData.storeSampleData(*sampleData);

        return solData;
    }

    void reset() override {
        navigation->reset();
        temperature->reset();
        sampleAnalysis->reset();
    }
};