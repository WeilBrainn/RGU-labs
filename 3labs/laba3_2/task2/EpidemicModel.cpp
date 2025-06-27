#include "EpidemicModel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

EpidemicModel::EpidemicModel() {
    std::random_device rd;
    _rng.seed(rd());
}

void EpidemicModel::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("не удалось открыть файл: " + filename);
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    for (size_t i = 0; i + 1 < lines.size(); ++i) {
        std::istringstream iss(lines[i]);
        std::string token;
        std::getline(iss, token, ',');
        int id = std::stoi(token);
        std::getline(iss, token, ',');
        std::string name = token;
        std::getline(iss, token, ',');
        std::string surname = token;

        Person person(id, name, surname);
        while (std::getline(iss, token, ',')) {
            int contactId = std::stoi(token);
            person.addContact(contactId);
        }
        _people.insert({ id, person });
    }

    for (auto it = _people.begin(); it != _people.end(); ++it) {
        Person& person = it->second;
        for (int contactId : person.getContacts()) {
            if (_people.count(contactId)) {
                _people[contactId].addContact(it->first);
            }
        }
    }

    std::istringstream params(lines.back());
    params >> _p1 >> _p2 >> _days;
    std::string rflag;
    params >> rflag;
    _reinfectionAllowed = (rflag == "true");
    params >> _T >> _I;
}

void EpidemicModel::triggerOutbreak() {
    if (_people.empty()) return;
    int id = _outbreakId;
    if (id == -1) {
        std::uniform_int_distribution<int> dist(0, static_cast<int>(_people.size()) - 1);
        auto it = _people.begin();
        std::advance(it, dist(_rng));
        id = it->first;
    }
    _people[id].startInfection(_I);
}

void EpidemicModel::run() {
    triggerOutbreak();
    for (int day = 0; day < _days; ++day) {
        for (auto it = _people.begin(); it != _people.end(); ++it) {
            it->second.updateState(_p2, _T, _rng);
        }

        for (auto it = _people.begin(); it != _people.end(); ++it) {
            const Person& person = it->second;
            if (!person.canInfect()) continue;
            for (int contactId : person.getContacts()) {
                if (_people.count(contactId) == 0) continue;
                Person& contact = _people[contactId];
                if (contact.isSusceptible(_reinfectionAllowed)) {
                    std::bernoulli_distribution infect(_p1);
                    if (infect(_rng)) {
                        contact.startInfection(_I);
                    }
                }
            }
        }
    }
}

void EpidemicModel::writeResults(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("не удалось открыть файл вывода: " + filename);
    }

    out << "не заразившиеся:\n";
    for (auto it = _people.begin(); it != _people.end(); ++it) {
        const Person& person = it->second;
        if (person.getInfectionCount() == 0) {
            out << person.getFullName() << "\n";
        }
    }
    out << "\nисцелившиеся:\n";
    for (auto it = _people.begin(); it != _people.end(); ++it) {
        const Person& person = it->second;
        if (person.getStatus() == Person::HealthStatus::Immune) {
            out << person.getFullName() << "\n";
        }
    }
    out << "\nхронические случаи:\n";
    for (auto it = _people.begin(); it != _people.end(); ++it) {
        const Person& person = it->second;
        if (person.isChronic()) {
            out << person.getFullName() << "\n";
        }
    }
    if (_reinfectionAllowed) {
        out << "\nпереболевшие более одного раза:\n";
        for (auto it = _people.begin(); it != _people.end(); ++it) {
            const Person& person = it->second;
            if (person.getInfectionCount() > 1) {
                out << person.getFullName() << "\n";
            }
        }
    }
}

const std::unordered_map<int, Person>& EpidemicModel::getPeople() const {
    return _people;
}