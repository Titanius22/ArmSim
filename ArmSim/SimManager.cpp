#include "SimManager.h"


SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    timeStep = 0.100f;
            
    this->platform = new Platform();
}
        
void SimManager::StartRun(){
            
    // this is the main loop that handles each cycle
    while(true){
                
        // TODO: tic()
                
        // TODO: call this->platform->updateDisturbance()
                
        this->platform->PropagateModelDeltaTime(this->timeStep);

        // TODO: call SendSensorData()

        // TODO: Run FSW/GNC step

        // TODO: run visualizer

        // TODO: handle_commands()



        // TODO: loopTime = toc()
        // TODO: sleep(this->timeStep - loopTime)

    }
}