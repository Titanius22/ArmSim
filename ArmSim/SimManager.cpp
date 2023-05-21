// Library effective with Windows
#include "ProjectUtilities.h"

#include "SimManager.h"
#include "Sensor.h"
#include "SensorFactory.h"


SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    this->cycleTimeStep_ms = 1000;
            
    this->platform = new Platform();

    SensorFactory* pSensorFactory = new SensorFactory(this->platform);
    pSensorFactory->CreateSensorAndAddToPlatform(0010, Platform::System_Property::ERIK_POS);
    pSensorFactory->CreateSensorAndAddToPlatform(0011, Platform::System_Property::ERIK_VEL);
}
        
void SimManager::StartRun(){
    
    Sensor* sensor1 = this->platform->GetPtrToSensor(0010);
    Sensor* sensor2 = this->platform->GetPtrToSensor(0011);
    
    PerformanceTimer cycleTimer;
    
    // this is the main loop that handles each cycle
    while(true){
                
        // start update timer ---------------------------------------
        cycleTimer.Tic();
                
        // TODO: call this->platform->updateDisturbance()
                
        this->platform->PropagateModelDeltaTime(this->cycleTimeStep_ms);

        // TODO: call SendSensorData()

        // TODO: Run FSW/GNC step

        // TODO: run visualizer

        // TODO: handle_commands()



        // stop update timer: -----------------------------------------
        cycleTimer.Toc();
        uint32_t cycleTimer_time_ms = uint32_t(cycleTimer.TimeInSeconds() * 1000.0f);
        uint32_t remainingTimeToSleep_ms = this->cycleTimeStep_ms - cycleTimer_time_ms;
        
        // sleep for remainder of time; this make its real time
        sleepcp_ms(remainingTimeToSleep_ms);

        // Print loop time
        printf("ProccessTime: %d ms, WaitTime: %d ms \n", cycleTimer_time_ms, remainingTimeToSleep_ms);

        printf("Sensor1: %f m, Sensor2: %f m/s\n", sensor1->getSensorMeasurement(), sensor2->getSensorMeasurement());


        // Reset timer: -----------------------------------------
        cycleTimer.Reset();
    }
}