#ifndef ELEVATOR_SYSTEM_H
#define ELEVATOR_SYSTEM_H

#include "Passenger.h"
#include "Elevator.h"
#include <vector>
#include <queue>
#include <string>

class ElevatorSystem {
private:
    int n_floors;
    int k_elevators;
    std::vector<Elevator> elevators;
    std::vector<double> max_capacities;
    std::vector<Passenger> passengers;

    // Кнопки вызова на этажах
    std::vector<bool> floor_call_buttons;

    // Очереди пассажиров на этажах
    std::vector<std::queue<int>> floor_queues;

    int current_time; // в минутах

    // Приватные методы
    int calculateMoveTime(int elevator_id);
    int findBestElevator(int floor);
    void processArrivingPassengers();
    void processBoardingPassengers();
    void processExitingPassengers();
    void updateElevatorStates();

public:
    ElevatorSystem(int floors, int num_elevators, const std::vector<double>& capacities);

    void addPassenger(const Passenger& p);
    void simulate();
    void generatePassengerReport(const std::string& filename);
    void generateElevatorReport(const std::string& filename);
};

#endif // ELEVATOR_SYSTEM_H