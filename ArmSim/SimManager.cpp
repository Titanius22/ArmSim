// Library effective with Windows
#include "ProjectUtilities.h"

#include "SimManager.h"
#include "Sensor.h"
#include "SensorFactory.h"
#include "ActuatorFactory.h"
#include "PlatformController.h"

#include <fstream>
#include <iostream>

SimManager::SimManager()
{
    Configure();
}

void SimManager::Configure(){
    this->cycleTimeStep_ms = 10;
    this->currentSimTime = 0;

    // create output file
    this->exportFile.open("ArmSim_export_" + gen_random_alphaNum(12) + ".csv");
            
    this->platform = new Platform("Arm");
    
    ActuatorFactory* pActuatorFactory = new ActuatorFactory(this->platform);
    pActuatorFactory->CreateActuator_AndAddToPlatform(
        0001, "Actuator1",
        0.0f, 1.0f, 2.0f,
        1.0f, 0.0f, 0.0f);
    this->platform->GetPtrToActuator(0001)->setCommandedActuationValue(2.0f);

    SensorFactory* pSensorFactory = new SensorFactory(this->platform);
	pSensorFactory->CreateSensor_AndAddToPlatform(0001, "theta", Platform::System_Property::ANG_POS);
	pSensorFactory->CreateSensor_AndAddToPlatform(0002, "theta_dot", Platform::System_Property::ANG_VEL);
	pSensorFactory->CreateSensor_AndAddToPlatform(0003, "theta_dot_dot", Platform::System_Property::ANG_ACC);
    //pSensorFactory->CreateSensor_AndAddToPlatform(0004, this->platform->GetPtrToActuator(0001));


}
        
void SimManager::StartRun(){
    
    Sensor* sensor1 = this->platform->GetPtrToSensor(0001);
    Sensor* sensor2 = this->platform->GetPtrToSensor(0002);
    Sensor* sensor3 = this->platform->GetPtrToSensor(0003);
    //Actuator* actuator1 = this->platform->GetPtrToActuator(0001);

    PlatformController platController = PlatformController(this->platform);
    
    PerformanceTimer cycleTimer;
    
    
    int cycleCount = 0;
    //float actuatorValue;
    Command_Platform command(Command_Platform::CommanndType::DO_NOTHING); // will not get used, just so that "command" can get defined outside the loop

    // this is the main loop that handles each cycle
    while(true){
        /*if ((cycleCount > 0) && (cycleCount % 5 == 0))
        {
            actuatorValue = actuator1->getCommandedActuationValue();
            command = Command_Platform(Command_Platform::CommanndType::CHANGE_ACTUATOR_VALUE, 0000, actuatorValue+1.0f);

            platController.ReceiveCommand(&command);

            command.GetActuatorValue();
        }*/

        // start update timer ---------------------------------------
        cycleTimer.Tic();
                
        // TODO: call this->platform->updateDisturbance()
                
        this->platform->PropagateModelDeltaTime(this->cycleTimeStep_ms);

        // TODO: call SendSensorData()

        // TODO: Run FSW/GNC step

        // TODO: export data and run visualizer
        this->ExportToFile(this->platform);

        // TODO: handle_commands()



        // stop update timer: -----------------------------------------
        cycleTimer.Toc();
        uint32_t cycleTimer_time_ms = uint32_t(cycleTimer.TimeInSeconds() * 1000.0f);
        uint32_t remainingTimeToSleep_ms;
        if (this->cycleTimeStep_ms > cycleTimer_time_ms)
        {
            remainingTimeToSleep_ms = this->cycleTimeStep_ms - cycleTimer_time_ms;
        }
        else
        {
            // otherwise overflow will occur
            remainingTimeToSleep_ms = 0;
        }
        
        // sleep for remainder of time; this make its real time
        sleepcp_ms(remainingTimeToSleep_ms);

        // Print loop time
        //printf("ProccessTime: %d ms, WaitTime: %d ms \n", cycleTimer_time_ms, remainingTimeToSleep_ms);

		if ((cycleCount > 0) && (cycleCount % 20 == 0))
		{
			printf("Sensor1: %.4f m, Sensor2: %.4f m/s, Sensor3: %.4f m/s^2\n", // , Actuator1: % .0f m / s ^ 2 \n",
				sensor1->getSensorMeasurement(), sensor2->getSensorMeasurement(), sensor3->getSensorMeasurement()); // , actuator1->getCommandedActuationValue());
		}

        // Reset timer: -----------------------------------------
        cycleTimer.Reset();

        cycleCount++;
        this->currentSimTime += (double(this->cycleTimeStep_ms) / 1000);
    }
}

void SimManager::ExportToFile(Platform* _platform)
{
    // exports 1 row at a time
    
    if(!this->exportFile)
    {
        // TODO: how should this be handled
        assert(false);
    }

    // print simTime column
    this->exportFile << this->currentSimTime << ",";

    // print platform name column
    this->exportFile << _platform->GetName() << ",";

    // print sensor data columns
    for (Sensor* sensor : _platform->sensorList)
    {
        this->exportFile << sensor->GetName() << ",";
        this->exportFile << sensor->getSensorID() << ",";
        this->exportFile << sensor->getRealValue() << ",";
    }

    // print actuator data columns
    for (Actuator* actuator : _platform->actuatorList)
    {
        this->exportFile << actuator->GetName() << ",";
        this->exportFile << int(actuator->getActuatorID()) << ",";
        this->exportFile << actuator->getRealActuationValue() << ",";
    }

    // end of row
    this->exportFile << endl;
}