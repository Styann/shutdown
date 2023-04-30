#include <iostream>
#include <string>
#include <regex>
#include <time.h>
#include <chrono>
#include <thread>
#include <Windows.h>


using namespace std;
using namespace std::this_thread;

enum class OS{
    windows,
    linux,
    macOs,
    freeBSD,
    unix,
    other
};

string OSToString(OS os) {
    switch (os){
        case OS::windows: return "Windows";
        case OS::linux: return "Linux";
        case OS::macOs: return "Mac OS";
        case OS::freeBSD: return "FreeBSD";
        case OS::unix: return "Unix";
        case OS::other: return "Other";
        default: return "Other";
    }
}

string getOsName() {
    #ifdef _WIN64
        return "Windows 32-bit";
    #elif _WIN32
        return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #elif __unix || __unix__
        return "Unix";
    #else
        return "Other";
    #endif
}


string datetimeToString(struct tm* datetime, string format) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), format.c_str(), datetime);
    return buffer;
}

int inputDaysToAdd() {
    int daysToAdd;

    time_t timenow = NULL;
    struct tm* datetime = nullptr;

    int i = 0;
    do {
        timenow = time(NULL);
        datetime = localtime(&timenow);

        cout << "Type a number between 0 and N (0 is today (" << datetimeToString(datetime, "%Y-%m-%d") << ")) : ";
        if (i != 0) {
            cin.clear();
            cin.ignore(123, '\n');
        }
        i++;
    } while (!(cin >> daysToAdd));
    
    return daysToAdd;
}

string inputSpecifyTime(regex rgx) {
    string timeStr = "";

    do {
        cout << "Type a time (format hh:mm:ss) : ";
        cin >> timeStr;
    } while (!regex_match(timeStr, rgx));

    return timeStr;
}

void timeStringToInt(string input, int* hours, int* minutes, int* seconds) {
    *hours = stoi(input.substr(0, 2));
    *minutes = stoi(input.substr(3, 2));
    *seconds = stoi(input.substr(6, 2));
    return;
}

void shutdown() {
    system("C:/Windows/System32/shutdown.exe /s");
    return;
}


int main()
{
    const regex regexTime("^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$");


    int days, hours, minutes, seconds;
    string timeStr = "";
    
    days = inputDaysToAdd();

    timeStr = inputSpecifyTime(regexTime);
    timeStringToInt(timeStr, &hours, &minutes, &seconds);


    time_t timenow = time(NULL);
    struct tm *datetime = localtime(&timenow);

    datetime->tm_mday += days;
    datetime->tm_hour = hours;
    datetime->tm_min = minutes;
    datetime->tm_sec = seconds;
 
    string targetTimeStr = datetimeToString(datetime, "%Y-%m-%d %Hh:%Mm:%Ss");
    time_t targetTime = mktime(datetime);
    cout << "The shutdown is scheduled at " << targetTimeStr << endl;

    int s = 1;
    while (time(NULL) <= targetTime) {
        sleep_for(1s);
    }

    if (time(NULL) >= targetTime) {
        cout << "end";
        shutdown();
    }

    return 0;
}