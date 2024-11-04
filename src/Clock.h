//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

class Clock {
public:
    Clock() = default;
    float restart() {
        float elapsedTime = getElapsedTime();
        startTime = clock();
        return elapsedTime;
    }

    // Returns the time elapsed since the last restart in microseconds
    float getElapsedTime() const {
        return static_cast<float>(clock() - startTime);
    }

    float getElapsedTimeS() const {
        return getElapsedTime() / 100000;
    }
private:
    clock_t startTime;
};

#endif //CLOCK_H
