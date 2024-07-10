#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
#include <functional>

class DateTime {
private:
    std::tm m_timeInfo;

    void updateTimeInfo();

public:
    enum class Period {
        Second,
        Minute,
        Hour,
        Day,
        Week,
        Month,
        Year
    };

    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int min = 0, int sec = 0);

    DateTime& addDays(int days);
    DateTime& addMonths(int months);
    DateTime& addYears(int years);

    int getDayOfWeek() const;
    int getDayOfMonth() const;
    int getMonth() const;
    int getYear() const;

    std::string toString(const std::string& format = "%Y-%m-%d %H:%M:%S") const;

    // Periodic actions (non-blocking)
    void doEvery(Period period, int interval, std::function<void()> action);

    // One-time actions after a delay (non-blocking)
    void doAfter(Period period, int interval, std::function<void()> action);

    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
};
