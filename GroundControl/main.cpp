// include
#include <iostream>
#include "GroundControl.h"

int main()
{

    //char port[] = "27015";
    char dummy[500];

    // cause system to wait
    std::cout << "Type anything, then press ENTER when ready..."; // Type a number and press enter
    std::cin >> dummy; // Get user input from the keyboard

    GroundControl* groundControl = new GroundControl();

    groundControl->Start();

    return 0;
}