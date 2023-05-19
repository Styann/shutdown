#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>

using namespace std;
using namespace std::this_thread;

class Killer
{
public:
    enum class OS {
        windows,
        linux,
        macOs,
        freeBSD,
        unix,
        other
    };

    string OSToString(OS os) {
        switch (os) {
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



    void shutdown() {
        system("C:/Windows/System32/shutdown.exe /s");
        return;
    }


    string datetimeToString(struct tm* datetime, string format) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), format.c_str(), datetime);
        return buffer;
    }

    void startTimeOut(time_t target) {
        int s = 0;
        while (time(NULL) <= target) {
            sleep_for(1s);
            cout << s++;
        }

        if (time(NULL) >= target) {
            cout << "end";

        }
    }

};


