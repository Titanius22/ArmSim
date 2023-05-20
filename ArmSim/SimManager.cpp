#include "SimManager.h"
#include "Sensor.h"
#include "SensorFactory.h"


SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    timeStep = 0.100f;
            
    this->platform = new Platform();

    SensorFactory* pSensorFactory = new SensorFactory(this->platform);
    Sensor* pSensor = pSensorFactory->CreateSensor(0010, Platform::System_Property::ERIK_POS);

    EriktestSensor = pSensor;
}
        
void SimManager::StartRun(){
    
    PerformanceTimer cycleTimer;
    
    // this is the main loop that handles each cycle
    while(true){
                
        // start update timer ---------------------------------------
        cycleTimer.Tic();
                
        // TODO: call this->platform->updateDisturbance()
                
        this->platform->PropagateModelDeltaTime(this->timeStep);

        // TODO: call SendSensorData()

        // TODO: Run FSW/GNC step

        // TODO: run visualizer

        // TODO: handle_commands()



        // stop update timer: -----------------------------------------
        cycleTimer.Toc();
        
        // TODO: sleep(this->timeStep - loopTime)

        // Print loop time
        float cycleTimer_time = cycleTimer.TimeInSeconds();
        printf("LoopTime: %f ms \n", cycleTimer_time * 1000.0f);


        printf("SensorData: %f m/s \n", EriktestSensor->getSensorMeasurement());


        // Reset timer: -----------------------------------------
        cycleTimer.Reset();
    }
}