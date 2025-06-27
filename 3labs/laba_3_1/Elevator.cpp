#include "ElevatorSystem.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <climits>
#include <map>

using namespace std;

ElevatorSystem::ElevatorSystem(int floors, int num_elevators, const vector<double>& capacities)
    : n_floors(floors), k_elevators(num_elevators), max_capacities(capacities),
    floor_call_buttons(floors + 1, false), floor_queues(floors + 1),
    current_time(0) {

    // Инициализация лифтов
    for (int i = 0; i < k_elevators; i++) {
        Elevator elev;
        elev.id = i;
        elev.current_floor = 1; // Все лифты начинают с первого этажа
        elev.state = STOPPED_CLOSED;
        elev.max_capacity = capacities[i];
        elev.current_load = 0.0;
        elevators.push_back(elev);
    }
}

void ElevatorSystem::addPassenger(const Passenger& p) {
    passengers.push_back(p);
}

int ElevatorSystem::calculateMoveTime(int elevator_id) {
    double load_ratio = elevators[elevator_id].current_load / elevators[elevator_id].max_capacity;
    // Возвращаем время в минутах, округляя вверх
    return max(1, static_cast<int>(ceil((3.0 + 5.0 * load_ratio) / 60.0)));
}

int ElevatorSystem::findBestElevator(int floor) {
    int best_elevator = -1;
    int min_distance = INT_MAX;

    for (int i = 0; i < k_elevators; i++) {
        Elevator& elev = elevators[i];

        // Рассчитываем расстояние
        int distance = abs(elev.current_floor - floor);

        // Предпочитаем свободные лифты или лифты, движущиеся в правильном направлении
        bool is_good_choice = false;

        if (elev.state == STOPPED_CLOSED || elev.state == STOPPED_OPEN) {
            is_good_choice = true;
        }
        else if (elev.state == MOVING_UP && floor >= elev.current_floor) {
            is_good_choice = true;
        }
        else if (elev.state == MOVING_DOWN && floor <= elev.current_floor) {
            is_good_choice = true;
        }

        // Выбираем лучший лифт (приоритет хорошим вариантам)
        if (is_good_choice && distance < min_distance) {
            min_distance = distance;
            best_elevator = i;
        }
    }

    // Если не найден подходящий, берем просто ближайший
    if (best_elevator == -1) {
        min_distance = INT_MAX;
        for (int i = 0; i < k_elevators; i++) {
            int distance = abs(elevators[i].current_floor - floor);
            if (distance < min_distance) {
                min_distance = distance;
                best_elevator = i;
            }
        }
    }

    return best_elevator;
}

void ElevatorSystem::processArrivingPassengers() {
    for (size_t i = 0; i < passengers.size(); i++) {
        Passenger& passenger = passengers[i];
        if (passenger.arrival_time == current_time && !passenger.completed) {
            // Пассажир прибывает на этаж
            floor_queues[passenger.source_floor].push(i); // Используем индекс в массиве
            floor_call_buttons[passenger.source_floor] = true;

            cout << "Время " << current_time << ": Пассажир " << passenger.id
                << " прибыл на этаж " << passenger.source_floor << endl;
        }
    }
}

void ElevatorSystem::processBoardingPassengers() {
    for (int i = 0; i < k_elevators; i++) {
        Elevator& elev = elevators[i];

        if (elev.state == STOPPED_OPEN && !floor_queues[elev.current_floor].empty()) {
            queue<int>& queue_ref = floor_queues[elev.current_floor];
            vector<int> remaining_passengers;

            cout << "Время " << current_time << ": Лифт " << i
                << " открыт на этаже " << elev.current_floor << endl;

            while (!queue_ref.empty()) {
                int passenger_index = queue_ref.front();
                queue_ref.pop();

                Passenger& passenger = passengers[passenger_index];

                // Проверяем, поместится ли пассажир
                if (elev.current_load + passenger.weight <= elev.max_capacity) {
                    // Пассажир садится
                    elev.passengers.push_back(passenger_index);
                    elev.current_load += passenger.weight;
                    elev.target_floors.insert(passenger.target_floor);
                    passenger.boarding_time = current_time;

                    // Обновляем статистику
                    elev.total_cargo += passenger.weight;
                    elev.max_load_used = max(elev.max_load_used, elev.current_load);

                    cout << "  Пассажир " << passenger.id << " сел в лифт "
                        << i << " (цель: этаж " << passenger.target_floor << ")" << endl;
                }
                else {
                    // Перегрузка - пассажир остается ждать
                    remaining_passengers.push_back(passenger_index);
                    passenger.ejected_for_overload = true;
                    elev.overload_count++;

                    cout << "  Пассажир " << passenger.id << " не поместился (перегрузка)" << endl;
                }
            }

            // Возвращаем не поместившихся пассажиров в очередь
            for (int pid : remaining_passengers) {
                queue_ref.push(pid);
            }

            if (queue_ref.empty()) {
                floor_call_buttons[elev.current_floor] = false;
            }
        }
    }
}

void ElevatorSystem::processExitingPassengers() {
    for (int i = 0; i < k_elevators; i++) {
        Elevator& elev = elevators[i];

        if (elev.state == STOPPED_OPEN) {
            vector<int> remaining_passengers;

            for (int passenger_index : elev.passengers) {
                Passenger& passenger = passengers[passenger_index];

                if (passenger.target_floor == elev.current_floor) {
                    // Пассажир выходит
                    elev.current_load -= passenger.weight;
                    passenger.travel_time = current_time - passenger.boarding_time;
                    passenger.completed = true;

                    // Записываем спутников
                    for (int other_index : elev.passengers) {
                        if (other_index != passenger_index) {
                            passenger.companions.push_back(passengers[other_index].id);
                        }
                    }

                    cout << "Время " << current_time << ": Пассажир " << passenger.id
                        << " вышел на этаже " << elev.current_floor << endl;
                }
                else {
                    remaining_passengers.push_back(passenger_index);
                }
            }

            elev.passengers = remaining_passengers;
            elev.target_floors.erase(elev.current_floor);
        }
    }
}

void ElevatorSystem::updateElevatorStates() {
    for (int i = 0; i < k_elevators; i++) {
        Elevator& elev = elevators[i];

        switch (elev.state) {
        case STOPPED_CLOSED:
            // Проверяем, есть ли вызовы на текущем этаже
            if (floor_call_buttons[elev.current_floor] ||
                elev.target_floors.count(elev.current_floor) > 0) {
                elev.state = STOPPED_OPEN;
                cout << "Время " << current_time << ": Лифт " << i
                    << " открывается на этаже " << elev.current_floor << endl;
            }
            else if (!elev.target_floors.empty()) {
                // Есть целевые этажи - начинаем движение
                int target = *elev.target_floors.begin();
                if (target > elev.current_floor) {
                    elev.state = MOVING_UP;
                    elev.next_floor = elev.current_floor + 1;
                    elev.move_duration = calculateMoveTime(i);
                    elev.move_start_time = current_time;
                    cout << "Время " << current_time << ": Лифт " << i
                        << " начинает движение вверх с этажа " << elev.current_floor << endl;
                }
                else if (target < elev.current_floor) {
                    elev.state = MOVING_DOWN;
                    elev.next_floor = elev.current_floor - 1;
                    elev.move_duration = calculateMoveTime(i);
                    elev.move_start_time = current_time;
                    cout << "Время " << current_time << ": Лифт " << i
                        << " начинает движение вниз с этажа " << elev.current_floor << endl;
                }
            }
            else {
                // Ищем ближайший вызов
                int closest_call = -1;
                int min_dist = INT_MAX;

                for (int floor = 1; floor <= n_floors; floor++) {
                    if (floor_call_buttons[floor]) {
                        int dist = abs(floor - elev.current_floor);
                        if (dist < min_dist) {
                            min_dist = dist;
                            closest_call = floor;
                        }
                    }
                }

                if (closest_call != -1) {
                    elev.target_floors.insert(closest_call);
                    // Рекурсивно обработаем состояние снова
                    i--; // Обработаем этот лифт заново
                    continue;
                }
                else {
                    elev.idle_time++;
                }
            }
            break;

        case STOPPED_OPEN:
            // Ждем один такт, затем определяем направление движения
            if (elev.target_floors.empty() && !floor_call_buttons[elev.current_floor]) {
                elev.state = STOPPED_CLOSED;
                cout << "Время " << current_time << ": Лифт " << i
                    << " закрывается на этаже " << elev.current_floor << endl;
            }
            else if (!elev.target_floors.empty()) {
                // Определяем направление движения к ближайшей цели
                int next_target = -1;
                int min_dist = INT_MAX;

                for (int target : elev.target_floors) {
                    int dist = abs(target - elev.current_floor);
                    if (dist < min_dist) {
                        min_dist = dist;
                        next_target = target;
                    }
                }

                if (next_target > elev.current_floor) {
                    elev.state = MOVING_UP;
                    elev.next_floor = elev.current_floor + 1;
                    elev.move_duration = calculateMoveTime(i);
                    elev.move_start_time = current_time;
                }
                else if (next_target < elev.current_floor) {
                    elev.state = MOVING_DOWN;
                    elev.next_floor = elev.current_floor - 1;
                    elev.move_duration = calculateMoveTime(i);
                    elev.move_start_time = current_time;
                }
                else {
                    elev.state = STOPPED_CLOSED;
                }
            }
            else {
                elev.state = STOPPED_CLOSED;
            }
            break;

        case MOVING_UP:
        case MOVING_DOWN:
            // Проверяем, завершилось ли движение
            if (current_time - elev.move_start_time >= elev.move_duration) {
                elev.current_floor = elev.next_floor;
                elev.floors_traveled++;
                elev.travel_time += elev.move_duration;

                cout << "Время " << current_time << ": Лифт " << i
                    << " прибыл на этаж " << elev.current_floor << endl;

                // Проверяем, нужно ли остановиться
                bool should_stop = false;
                if (elev.target_floors.count(elev.current_floor) > 0) {
                    should_stop = true;
                }
                if (floor_call_buttons[elev.current_floor]) {
                    should_stop = true;
                }

                if (should_stop) {
                    elev.state = STOPPED_OPEN;
                }
                else {
                    // Продолжаем движение
                    if (elev.state == MOVING_UP && elev.current_floor < n_floors) {
                        elev.next_floor = elev.current_floor + 1;
                        elev.move_duration = calculateMoveTime(i);
                        elev.move_start_time = current_time;
                    }
                    else if (elev.state == MOVING_DOWN && elev.current_floor > 1) {
                        elev.next_floor = elev.current_floor - 1;
                        elev.move_duration = calculateMoveTime(i);
                        elev.move_start_time = current_time;
                    }
                    else {
                        elev.state = STOPPED_CLOSED;
                    }
                }
            }
            break;
        }
    }
}

void ElevatorSystem::simulate() {
    cout << "Начало симуляции..." << endl;

    while (true) {
        // Проверяем, все ли пассажиры доставлены
        bool all_completed = true;
        bool has_waiting_passengers = false;

        for (const auto& p : passengers) {
            if (!p.completed) {
                all_completed = false;
                if (p.arrival_time <= current_time) {
                    has_waiting_passengers = true;
                }
            }
        }

        // Проверяем, есть ли активность в лифтах
        bool elevators_active = false;
        for (const auto& elev : elevators) {
            if (!elev.passengers.empty() || !elev.target_floors.empty() ||
                elev.state == MOVING_UP || elev.state == MOVING_DOWN) {
                elevators_active = true;
                break;
            }
        }

        if (all_completed && current_time > 0) {
            cout << "Все пассажиры доставлены на время " << current_time << endl;
            break;
        }

        if (!has_waiting_passengers && !elevators_active && current_time > 0) {
            // Нет активности - либо все готово, либо что-то сломалось
            bool any_unprocessed = false;
            for (const auto& p : passengers) {
                if (!p.completed && p.arrival_time > current_time) {
                    any_unprocessed = true;
                    break;
                }
            }
            if (!any_unprocessed) break;
        }

        processArrivingPassengers();
        processExitingPassengers();
        processBoardingPassengers();
        updateElevatorStates();

        current_time++;

        // Защита от бесконечного цикла
        if (current_time > 1000) {
            cout << "Превышено максимальное время симуляции!" << endl;
            break;
        }
    }

    cout << "Симуляция завершена на времени " << current_time << endl;
}

void ElevatorSystem::generatePassengerReport(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл " + filename);
    }

    for (const auto& p : passengers) {
        file << "Пассажир ID: " << p.id << "\n";
        file << "Время появления: " << (p.arrival_time / 60) << ":"
            << setfill('0') << setw(2) << (p.arrival_time % 60) << "\n";
        file << "Исходный этаж: " << p.source_floor << "\n";
        file << "Целевой этаж: " << p.target_floor << "\n";

        if (p.boarding_time >= 0) {
            file << "Время погрузки: " << (p.boarding_time / 60) << ":"
                << setfill('0') << setw(2) << (p.boarding_time % 60) << "\n";
            file << "Время в пути: " << p.travel_time << " мин\n";
        }
        else {
            file << "Время погрузки: не был обслужен\n";
            file << "Время в пути: 0 мин\n";
        }

        file << "Спутники: ";
        for (size_t i = 0; i < p.companions.size(); i++) {
            if (i > 0) file << ", ";
            file << p.companions[i];
        }
        file << "\n";

        file << "Покидал из-за перегрузки: " << (p.ejected_for_overload ? "Да" : "Нет") << "\n";
        file << "Завершено: " << (p.completed ? "Да" : "Нет") << "\n";
        file << "---\n";
    }
}

void ElevatorSystem::generateElevatorReport(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл " + filename);
    }

    for (int i = 0; i < k_elevators; i++) {
        const auto& elev = elevators[i];
        file << "Лифт ID: " << i << "\n";
        file << "Текущий этаж: " << elev.current_floor << "\n";
        file << "Время простоя: " << elev.idle_time << " мин\n";
        file << "Время в пути: " << elev.travel_time << " мин\n";
        file << "Пройдено этажей: " << elev.floors_traveled << "\n";
        file << "Суммарный груз: " << fixed << setprecision(2) << elev.total_cargo << " кг\n";
        file << "Максимальная нагрузка: " << fixed << setprecision(2) << elev.max_load_used << " кг\n";
        file << "Максимальная грузоподъемность: " << fixed << setprecision(2) << elev.max_capacity << " кг\n";
        file << "Количество перегрузок: " << elev.overload_count << "\n";
        file << "---\n";
    }
}