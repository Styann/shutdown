#include <iostream>
#include <string>
#include <regex>
#include <time.h>
#include <chrono>
#include <thread>
#include <Windows.h>

#include "Input.h"
#include "Killer.h"

using namespace std;
using namespace std::this_thread;


int main()
{
    Input* input = new Input();
    Killer* killer = new Killer();


    input->typeDaysToAdd();
    int i = input->typeFromList("specify a time or a timeout (1, 2) ? ", {1, 2});

    if (i == 1) {
        input->timeStringToInt(input->typeTime());
        cout << "The shutdown is scheduled at " << input->targetTimeToString() << endl;
        killer->startTimeOut(input->toTime_t());
    }
    else if (i == 2) {
        input->timeStringToInt(input->typeFullTime());
    }


    

    return 0;
}