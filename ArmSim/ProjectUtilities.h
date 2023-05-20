#ifndef PROJECTUTILITIES_H
#define PROJECTUTILITIES_H

// include
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif // _WIN32

using namespace std;

// TODO: maybe split into header/src
void sleepcp_ms(uint32_t milliseconds);

void sleepcp_ms(uint32_t milliseconds) // Cross-platform sleep function
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        assert(false)
        usleep(milliseconds * 1000);
    #endif // _WIN32
}


#endif 

// --- End of File ---