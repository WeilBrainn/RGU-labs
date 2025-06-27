#include "ElevatorSystem.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <exception>

using namespace std;

void printUsage(const char* program_name) {
    cout << "Использование: " << program_name << " <файл_параметров> <файл_пассажиров1> [файл_пассажиров2] ..." << endl;
    cout << "\nФормат файла параметров:" << endl;
    cout << "n k" << endl;
    cout << "M1 M2 ... Mk" << endl;
    cout << "\nГде:" << endl;
    cout << "  n  - количество этажей" << endl;
    cout << "  k  - количество лифтов" << endl;
    cout << "  Mi - грузоподъемность i-го лифта (кг)" << endl;
    cout << "\nФормат файлов пассажиров:" << endl;
    cout << "id вес исходный_этаж время целевой_этаж" << endl;
    cout << "\nПример:" << endl;
    cout << "1 80 3 00:01 8" << endl;
    cout << "11 65 2 00:15 6" << endl;
}

bool validateParameters(int n, int k, const vector<double>& capacities) {
    if (n <= 0 || k <= 0) {
        cerr << "Ошибка: количество этажей и лифтов должно быть больше 0" << endl;
        return false;
    }

    if (n > 100) {
        cerr << "Предупреждение: большое количество этажей (" << n << "), симуляция может быть медленной" << endl;
    }

    for (size_t i = 0; i < capacities.size(); i++) {
        if (capacities[i] <= 0) {
            cerr << "Ошибка: грузоподъемность лифта " << i << " должна быть больше 0" << endl;
            return false;
        }
    }

    return true;
}

bool loadParameters(const string& filename, int& n, int& k, vector<double>& capacities) {
    ifstream param_file(filename);
    if (!param_file.is_open()) {
        cerr << "Ошибка открытия файла параметров: " << filename << endl;
        return false;
    }

    if (!(param_file >> n >> k)) {
        cerr << "Ошибка чтения параметров n и k из файла" << endl;
        return false;
    }

    capacities.resize(k);
    for (int i = 0; i < k; i++) {
        if (!(param_file >> capacities[i])) {
            cerr << "Ошибка чтения грузоподъемности лифта " << i << endl;
            return false;
        }
    }

    param_file.close();
    return validateParameters(n, k, capacities);
}

bool loadPassengers(const string& filename, ElevatorSystem& system, int& passenger_count) {
    ifstream passenger_file(filename);
    if (!passenger_file.is_open()) {
        cerr << "Ошибка открытия файла пассажиров: " << filename << endl;
        return false;
    }

    string line;
    int line_number = 0;
    int file_passenger_count = 0;

    while (getline(passenger_file, line)) {
        line_number++;

        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        Passenger p;
        string time_str;

        if (!(iss >> p.id >> p.weight >> p.source_floor >> time_str >> p.target_floor)) {
            cerr << "Ошибка парсинга строки " << line_number << " в файле " << filename << endl;
            cerr << "Строка: " << line << endl;
            continue;
        }

        // Валидация данных пассажира
        if (p.weight <= 0) {
            cerr << "Предупреждение: некорректный вес пассажира " << p.id << " (" << p.weight << " кг)" << endl;
            continue;
        }

        if (p.source_floor == p.target_floor) {
            cerr << "Предупреждение: пассажир " << p.id << " не нуждается в поездке (исходный = целевой этаж)" << endl;
            continue;
        }

        try {
            p.arrival_time = parseTime(time_str);
        }
        catch (const exception& e) {
            cerr << "Ошибка парсинга времени '" << time_str << "' для пассажира " << p.id << endl;
            continue;
        }

        system.addPassenger(p);
        file_passenger_count++;
    }

    passenger_file.close();
    passenger_count += file_passenger_count;

    cout << "Загружено пассажиров из файла " << filename << ": " << file_passenger_count << endl;
    return true;
}

int main(int argc, char* argv[]) {


    setlocale(LC_ALL, "Russian");
    cout << "=== Система моделирования лифтов ===" << endl;

    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    // Чтение параметров системы
    int n, k;
    vector<double> capacities;

    if (!loadParameters(argv[1], n, k, capacities)) {
        return 1;
    }

    cout << "Параметры системы:" << endl;
    cout << "  Этажей: " << n << endl;
    cout << "  Лифтов: " << k << endl;
    cout << "  Грузоподъемности: ";
    for (size_t i = 0; i < capacities.size(); i++) {
        if (i > 0) cout << ", ";
        cout << capacities[i] << " кг";
    }
    cout << endl << endl;

    // Создание системы лифтов
    ElevatorSystem system(n, k, capacities);

    // Чтение файлов пассажиров
    int total_passengers = 0;
    for (int file_idx = 2; file_idx < argc; file_idx++) {
        loadPassengers(argv[file_idx], system, total_passengers);
    }

    if (total_passengers == 0) {
        cerr << "Ошибка: не загружено ни одного пассажира" << endl;
        return 1;
    }

    cout << "\nВсего загружено пассажиров: " << total_passengers << endl;

    // Запуск симуляции
    cout << "\nЗапуск симуляции..." << endl;
    auto start_time = chrono::high_resolution_clock::now();

    system.simulate();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Симуляция завершена за " << duration.count() << " мс" << endl;

    // Генерация отчетов
    cout << "\nГенерация отчетов..." << endl;

    try {
        system.generatePassengerReport("passenger_report.txt");
        system.generateElevatorReport("elevator_report.txt");

        cout << "Отчеты успешно сохранены:" << endl;
        cout << "  - passenger_report.txt (отчет по пассажирам)" << endl;
        cout << "  - elevator_report.txt (отчет по лифтам)" << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка при генерации отчетов: " << e.what() << endl;
        return 1;
    }

    cout << "\nПрограмма завершена успешно." << endl;
    return 0;
}