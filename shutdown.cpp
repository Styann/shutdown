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

    input->setDays(input->typeDaysToAdd());
    int i = input->typeFromList("specify a time or a timeout (1, 2) ? ", {1, 2});
    time_t toAdd = NULL;

    if (i == 1) {
        input->timeStringToInt(input->typeSpecifiedTime());
        toAdd = input->createSpecifiedTime();
        cout << "The shutdown is scheduled at " << input->targetTimeToString() << endl;
    }
    else if (i == 2) {
        input->timeStringToInt(input->typeTimeOut());
        toAdd = input->createTimeOut();
        cout << "The shutdown is scheduled in " << input->targetTimeToString() << endl;
    }

    if (toAdd != NULL) {
        killer->startTimeOut(toAdd);
    }
    

    return 0;
}