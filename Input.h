#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "Format.h"

using namespace std;

class Input
{
private:
    const regex regexTime = regex("^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$");
    const regex regexFullTime = regex("^([0-9]+):([0-9]+):([0-9]+)$");
    int days, hours, minutes, seconds;

    time_t timenow;
    struct tm* datetime;

    string datetimeToString(struct tm* datetime, string format) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), format.c_str(), datetime);
        return buffer;
    }

    string typeString(regex rgx) {
        string timeStr = "";

        do {
            cout << "Type a time (format hh:mm:ss) : ";
            cin >> timeStr;
        } while (!regex_match(timeStr, rgx));

        return timeStr;
    }

public:
    Input() {

    }

    void timeStringToInt(string input) {
        this->hours = stoi(input.substr(0, 2));
        this->minutes = stoi(input.substr(3, 2));
        this->seconds = stoi(input.substr(6, 2));
        return;
    }

    void setDays(int days) {
        this->days = days;
    }
 
    int typeDaysToAdd() {
        Format* format = new Format();
        time_t timenow = NULL;
        struct tm* datetime = nullptr;
        
        int daysToAdd;
        
        int i = 0;
        do {
            timenow = time(NULL);
            datetime = localtime(&timenow);
            cout << "Type a number between 0 and N (0 is today (" << format->datetimeToString(datetime, "%Y-%m-%d") << ")) : ";

            if (i++ != 0) {
                cin.clear();
                cin.ignore(123, '\n');
            }
        } while (!(cin >> daysToAdd));

        return daysToAdd;
    }

    int typeFromList(string text, vector<int> expectations) {
        int input;
        int i = 0;


        for (int i = 0;; i++) {

            cout << text;
            cin >> input;

            for (int expectation : expectations) {
                if (input == expectation) return input;
            }

            cin.clear();
            cin.ignore(123, '\n');
        }

        return 0;
    }





    string typeSpecifiedTime() {
        return this->typeString(this->regexTime);
    }

    string typeTimeOut() {
        return this->typeString(this->regexFullTime);
    }

    time_t createSpecifiedTime() {
        this->timenow = time(NULL);
        this->datetime = localtime(&this->timenow);

        this->datetime->tm_mday += this->days;
        this->datetime->tm_hour = this->hours;
        this->datetime->tm_min = this->minutes;
        this->datetime->tm_sec = this->seconds;

        return mktime(this->datetime);
    }

    time_t createTimeOut() {
        this->timenow = time(NULL);
        this->datetime = localtime(&this->timenow);

        this->datetime->tm_mday += this->days;
        this->datetime->tm_hour += this->hours;
        this->datetime->tm_min += this->minutes;
        this->datetime->tm_sec += this->seconds;

        return mktime(this->datetime);
    }

    string targetTimeToString() {
        return this->datetimeToString(this->datetime, "%Y-%m-%d %Hh:%Mm:%Ss");
    }

};

