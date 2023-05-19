//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

// -----------------------------------------------------------
// ASSUME: MMX - SSE4.1 are allowed on the test machine
//         Do NOT use any setting above this level, grade->0
// -----------------------------------------------------------
//#include "OpenGLDevice.h"
#include "Settings.h"
#include "SimManager.h"

PerformanceTimer T1;

int main()
{
	Trace::out("Num Particle: %.1e time:%.1f\n",(float)NUM_PARTICLES,MAX_LIFE);

	srand(1);

	SimManager simMan = SimManager();

	simMan.StartRun();
	
	
	
	// initialize timers:------------------------------

	//// Create a timer objects
	//PerformanceTimer cycleTimer;
	//
	//// counter for printing
	//int i = 0;
	//	
	//// main update loop... do this forever or until some breaks 
	//while(true)
	//{
	//	// start update timer ---------------------------------------
	//	cycleTimer.Tic();

	//		











	//	// stop update timer: -----------------------------------------
	//	cycleTimer.Toc();

	//	//// LEAVE the loop below alone
	//	//if( i++ > PRINT_COUNT ) 
	//	//{
	//	//	i = 0;
	//	//	float updateTime = updateTimer.TimeInSeconds();
	//	//	float drawTime = drawTimer.TimeInSeconds();
	//	//	//updateTimer.Reset();
	//	//	//drawTimer.Reset();

	//	//	//float T1_time = T1.TimeInSeconds();
	//	//	//float T2_time = T2.TimeInSeconds();
	//	//	//T1.Reset();
	//	//	//T2.Reset();

	//	//	//printf("LoopTime: T1:%f ms  T2:%f ms  drawTotal:%f\n", T1_time * 1000.0f, T2_time * 1000.0f, drawTime * 1000.0f);
	//	//	printf("LoopTime: update:%f ms  draw:%f ms  tot:%f\n",updateTime * 1000.0f, drawTime * 1000.0f, (updateTime + drawTime) *1000.0f);
	//	//}
	//}
	
    return 0;
}

// WinMain required for all win32 applications (Windows entry point)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//OpenGLDevice::Initialize(hInstance);
	assert(hInstance);
	main();
}

// --- End of File ---
