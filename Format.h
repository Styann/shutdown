#pragma once
#include <iostream>
#include <string>

using namespace std;

class Format
{
public:
    void timeStringToInt(string input, int* hours, int* minutes, int* seconds) {
        *hours = stoi(input.substr(0, 2));
        *minutes = stoi(input.substr(3, 2));
        *seconds = stoi(input.substr(6, 2));
        return;
    }

    string datetimeToString(struct tm* datetime, string format) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), format.c_str(), datetime);
        return buffer;
    }
};

