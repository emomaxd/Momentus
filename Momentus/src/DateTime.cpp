#include "DateTime.h"
#include <sstream>
#include <thread>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

DateTime::DateTime() {
    std::time_t t = std::time(nullptr);
#ifdef _WIN32
    localtime_s(&m_timeInfo, &t);
#else
    localtime_r(&t, &m_timeInfo);
#endif
}

DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) {
    m_timeInfo = {};
    m_timeInfo.tm_year = year - 1900;
    m_timeInfo.tm_mon = month - 1;
    m_timeInfo.tm_mday = day;
    m_timeInfo.tm_hour = hour;
    m_timeInfo.tm_min = min;
    m_timeInfo.tm_sec = sec;
    mktime(&m_timeInfo);
}

void DateTime::updateTimeInfo() {
    std::time_t t = std::mktime(&m_timeInfo);
#ifdef _WIN32
    localtime_s(&m_timeInfo, &t);
#else
    localtime_r(&t, &m_timeInfo);
#endif
}

DateTime& DateTime::addDays(int days) {
    m_timeInfo.tm_mday += days;
    updateTimeInfo();
    return *this;
}

DateTime& DateTime::addMonths(int months) {
    m_timeInfo.tm_mon += months;
    updateTimeInfo();
    return *this;
}

DateTime& DateTime::addYears(int years) {
    m_timeInfo.tm_year += years;
    updateTimeInfo();
    return *this;
}

int DateTime::getDayOfWeek() const {
    return m_timeInfo.tm_wday;
}

int DateTime::getDayOfMonth() const {
    return m_timeInfo.tm_mday;
}

int DateTime::getMonth() const {
    return m_timeInfo.tm_mon + 1;
}

int DateTime::getYear() const {
    return m_timeInfo.tm_year + 1900;
}

std::string DateTime::toString(const std::string& format) const {
    std::ostringstream oss;
    oss << std::put_time(&m_timeInfo, format.c_str());
    return oss.str();
}

void DateTime::doEvery(Period period, int interval, std::function<void()> action) {
    std::thread([period, interval, action]() {
        std::chrono::milliseconds delay;
        switch (period) {
        case Period::Second:
            delay = std::chrono::seconds(interval);
            break;
        case Period::Minute:
            delay = std::chrono::minutes(interval);
            break;
        case Period::Hour:
            delay = std::chrono::hours(interval);
            break;
        case Period::Day:
            delay = std::chrono::hours(24 * interval);
            break;
        case Period::Week:
            delay = std::chrono::hours(24 * 7 * interval);
            break;
        case Period::Month:
            delay = std::chrono::hours(24 * 30 * interval);
            break;
        case Period::Year:
            delay = std::chrono::hours(24 * 365 * interval);
            break;
        }
        while (true) {
            std::this_thread::sleep_for(delay);
            action();
        }
        }).detach();
}

void DateTime::doAfter(Period period, int interval, std::function<void()> action) {
    std::thread([period, interval, action]() {
        std::chrono::milliseconds delay;
        switch (period) {
        case Period::Second:
            delay = std::chrono::seconds(interval);
            break;
        case Period::Minute:
            delay = std::chrono::minutes(interval);
            break;
        case Period::Hour:
            delay = std::chrono::hours(interval);
            break;
        case Period::Day:
            delay = std::chrono::hours(24 * interval);
            break;
        case Period::Week:
            delay = std::chrono::hours(24 * 7 * interval);
            break;
        case Period::Month:
            delay = std::chrono::hours(24 * 30 * interval);
            break;
        case Period::Year:
            delay = std::chrono::hours(24 * 365 * interval);
            break;
        }
        std::this_thread::sleep_for(delay);
        action();
        }).detach();
}

bool DateTime::operator==(const DateTime& other) const {
    return std::difftime(std::mktime(const_cast<std::tm*>(&m_timeInfo)), std::mktime(const_cast<std::tm*>(&other.m_timeInfo))) == 0;
}

bool DateTime::operator!=(const DateTime& other) const {
    return !(*this == other);
}

bool DateTime::operator<(const DateTime& other) const {
    return std::difftime(std::mktime(const_cast<std::tm*>(&m_timeInfo)), std::mktime(const_cast<std::tm*>(&other.m_timeInfo))) < 0;
}

bool DateTime::operator<=(const DateTime& other) const {
    return !(*this > other);
}

bool DateTime::operator>(const DateTime& other) const {
    return std::difftime(std::mktime(const_cast<std::tm*>(&m_timeInfo)), std::mktime(const_cast<std::tm*>(&other.m_timeInfo))) > 0;
}

bool DateTime::operator>=(const DateTime& other) const {
    return !(*this < other);
}
