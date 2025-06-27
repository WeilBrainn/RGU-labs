#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <set>

enum ElevatorState {
    STOPPED_CLOSED,
    STOPPED_OPEN,
    MOVING_UP,
    MOVING_DOWN
};

struct Elevator {
    int id;
    int current_floor;
    ElevatorState state;
    double max_capacity;
    double current_load;
    std::vector<int> passengers; // ID пассажиров в лифте
    std::set<int> target_floors; // Этажи, на которые нужно поехать

    // Статистика для отчета
    int idle_time = 0;
    int travel_time = 0;
    int floors_traveled = 0;
    double total_cargo = 0.0;
    double max_load_used = 0.0;
    int overload_count = 0;

    // Временные переменные для движения
    int move_start_time = 0;
    int move_duration = 0;
    int next_floor = 0;
};

#endif // ELEVATOR_H