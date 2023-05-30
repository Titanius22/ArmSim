// Library effective with Windows
#include "ProjectUtilities.h"

#include "SimManager.h"
#include "Sensor.h"
#include "SensorFactory.h"
#include "ActuatorFactory.h"
#include "PlatformController.h"


SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    this->cycleTimeStep_ms = 1000;
            
    this->platform = new Platform();
    
    ActuatorFactory* pActuatorFactory = new ActuatorFactory(this->platform);
    pActuatorFactory->CreateActuator_AndAddToPlatform(
        0000, 
        0.0f, 1.0f, 2.0f,
        1.0f, 0.0f, 0.0f);
    this->platform->GetPtrToActuator(0000)->setCommandedActuationValue(2.0f);

    SensorFactory* pSensorFactory = new SensorFactory(this->platform);
    pSensorFactory->CreateSensor_AndAddToPlatform(0000, Platform::System_Property::ERIK_POS);
    pSensorFactory->CreateSensor_AndAddToPlatform(0001, Platform::System_Property::ERIK_VEL);
    pSensorFactory->CreateSensor_AndAddToPlatform(0002, this->platform->GetPtrToActuator(0000));


}
        
void SimManager::StartRun(){
    
    Sensor* sensor1 = this->platform->GetPtrToSensor(0000);
    Sensor* sensor2 = this->platform->GetPtrToSensor(0001);
    Sensor* sensor3 = this->platform->GetPtrToSensor(0002);
    Actuator* actuator1 = this->platform->GetPtrToActuator(0000);

    PlatformController platController = PlatformController(this->platform);
    
    PerformanceTimer cycleTimer;
    
    
    int cycleCount = 0;
    float actuatorValue;
    Command_Platform command(Command_Platform::CommanndType::DO_NOTHING); // will not get used, just so that "command" can get defined outside the loop

    // this is the main loop that handles each cycle
    while(true){
        if ((cycleCount > 0) && (cycleCount % 5 == 0))
        {
            actuatorValue = actuator1->getCommandedActuationValue();
            command = Command_Platform(Command_Platform::CommanndType::CHANGE_ACTUATOR_VALUE, 0000, actuatorValue+1.0f);

            platController.ReceiveCommand(&command);

            command.GetActuatorValue();
        }

        // start update timer ---------------------------------------
        cycleTimer.Tic();
                
        // TODO: call this->platform->updateDisturbance()
                
        this->platform->PropagateModelDeltaTime(this->cycleTimeStep_ms);

        // TODO: call SendSensorData()

        // TODO: Run FSW/GNC step

        // TODO: run visualizer

        // TODO: handle_commands()
        platController.HandleCommands();


        // stop update timer: -----------------------------------------
        cycleTimer.Toc();
        uint32_t cycleTimer_time_ms = uint32_t(cycleTimer.TimeInSeconds() * 1000.0f);
        uint32_t remainingTimeToSleep_ms = this->cycleTimeStep_ms - cycleTimer_time_ms;
        
        // sleep for remainder of time; this make its real time
        sleepcp_ms(remainingTimeToSleep_ms);

        // Print loop time
        printf("ProccessTime: %d ms, WaitTime: %d ms \n", cycleTimer_time_ms, remainingTimeToSleep_ms);

        printf("Sensor1: %.0f m, Sensor2: %.0f m/s, Sensor3: %.0f m/s^2, Actuator1: %.0f m/s^2 \n", 
            sensor1->getSensorMeasurement(), sensor2->getSensorMeasurement(), sensor3->getSensorMeasurement(), actuator1->getCommandedActuationValue());


        // Reset timer: -----------------------------------------
        cycleTimer.Reset();

        cycleCount++;
    }
}