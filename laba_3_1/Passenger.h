#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>

struct Passenger {
    int id;
    double weight;
    int source_floor;
    int arrival_time; // в минутах
    int target_floor;

    // Данные для отчета
    int boarding_time = -1;
    int travel_time = 0;
    std::vector<int> companions;
    bool ejected_for_overload = false;
    bool completed = false;
};

#endif // PASSENGER_H