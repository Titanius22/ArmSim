#ifndef PROJECTUTILITIES_H
#define PROJECTUTILITIES_H

#include <ctime>
#include <iostream>
#include <string>

// include
#ifdef _WIN32
    
	/*
		The Winsock2.h header file internally includes core elements from the Windows.h
		header file, so there is not usually an #include line for the Windows.h header
		file in Winsock applications.If an #include line is needed for the Windows.h header
		file, this should be preceded with the #define WIN32_LEAN_AND_MEAN macro. For historical
		reasons, the Windows.h header defaults to including the Winsock.h header file for
		Windows Sockets 1.1.The declarations in the Winsock.h header file will conflict with
		the declarations in the Winsock2.h header file required by Windows Sockets 2.0.The
		WIN32_LEAN_AND_MEAN macro prevents the Winsock.h from being included by the Windows.h header.
	*/
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

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

std::string gen_random_alphaNum(const size_t len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (size_t i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}


#endif 

// --- End of File ---