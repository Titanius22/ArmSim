// Library effective with Windows
#include "ProjectUtilities.h"

#include "SimManager.h"
#include "Sensor.h"
#include "SensorFactory.h"
#include "ActuatorFactory.h"


SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    this->cycleTimeStep_ms = 1000;
            
    this->platform = new Platform();

    SensorFactory* pSensorFactory = new SensorFactory(this->platform);
    pSensorFactory->CreateSensor_AndAddToPlatform(0010, Platform::System_Property::ERIK_POS);
    pSensorFactory->CreateSensor_AndAddToPlatform(0011, Platform::System_Property::ERIK_VEL);
    
    ActuatorFactory* pActuatorFactory = new ActuatorFactory(this->platform);
    pActuatorFactory->CreateActuator_AndAddToPlatform(
        0010, 
        0.0f, 1.0f, 2.0f,
        1.0f, 0.0f, 0.0f);
    this->platform->GetPtrToActuator(0010)->setCommandedActuationValue(2.0f);
}
        
void SimManager::StartRun(){
    
    Sensor* sensor1 = this->platform->GetPtrToSensor(0010);
    Sensor* sensor2 = this->platform->GetPtrToSensor(0011);
    Actuator* actuator1 = this->platform->GetPtrToActuator(0010);
    
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

        printf("Sensor1: %.0f m, Sensor2: %.0f m/s, Actuator1: %.0f m/s^2 \n", 
            sensor1->getSensorMeasurement(), sensor2->getSensorMeasurement(), actuator1->getCommandedActuationValue());


        // Reset timer: -----------------------------------------
        cycleTimer.Reset();
    }
}