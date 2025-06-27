#include "Person.h"
#include <algorithm>
#include <random>

// создаёт нового человека
Person::Person(int id, const std::string& name, const std::string& surname)
    : _id(id), _name(name), _surname(surname) {
}

// добавляет id контакта, если он не дублируется и не равен своему
void Person::addContact(int otherId) {
    if (otherId != _id && std::find(_contacts.begin(), _contacts.end(), otherId) == _contacts.end()) {
        _contacts.push_back(otherId);
    }
}

// начинает инкубационный период, если человек был здоров
void Person::startInfection(int incubationDays) {
    if (_currentStatus != HealthStatus::Healthy) return;
    _currentStatus = HealthStatus::Incubating;
    _incubationPeriodRemaining = incubationDays;
    _daysSinceInfection = 0;
    _isCurrentlyIsolated = false;
    _totalInfections++;
}

// обновляет статус: инкубация -> инфекция -> лечение или хроническое
void Person::updateState(double p2, int T, std::mt19937& rng) {
    if (_currentStatus == HealthStatus::Incubating) {
        _incubationPeriodRemaining--;
        if (_incubationPeriodRemaining == 0) {
            _currentStatus = HealthStatus::Infectious;
        }
    }
    else if (_currentStatus == HealthStatus::Infectious) {
        std::bernoulli_distribution cure(p2);
        if (cure(rng)) {
            _currentStatus = HealthStatus::Recovering;
            _isCurrentlyIsolated = true;
            std::uniform_int_distribution<int> durationDist(T, 3 * T);
            _recoveryDaysRemaining = durationDist(rng);
        }
        else {
            _currentStatus = HealthStatus::Chronic;
            _chronic = true;
        }
    }
    else if (_currentStatus == HealthStatus::Recovering) {
        _recoveryDaysRemaining--;
        if (_recoveryDaysRemaining == 0) {
            _currentStatus = HealthStatus::Immune;
            _recoveredBefore = true;
            _isCurrentlyIsolated = false;
        }
    }
}

// можно ли заразить других (если не в изоляции)
bool Person::canInfect() const {
    return _currentStatus == HealthStatus::Infectious && !_isCurrentlyIsolated;
}

// можно ли заразиться снова
bool Person::isSusceptible(bool reinfectionAllowed) const {
    if (_currentStatus == HealthStatus::Healthy) {
        return true;
    }
    else if (_currentStatus == HealthStatus::Immune && reinfectionAllowed) {
        return true;
    }
    return false;
}

// получить id
int Person::getId() const {
    return _id;
}

// получить фамилию и имя
std::string Person::getFullName() const {
    return _surname + " " + _name;
}

// вернуть ссылки на контакты
const std::vector<int>& Person::getContacts() const {
    return _contacts;
}

// вернуть текущее состояние
Person::HealthStatus Person::getStatus() const {
    return _currentStatus;
}

// стал ли хроническим
bool Person::isChronic() const {
    return _chronic;
}

// сколько раз заражался
int Person::getInfectionCount() const {
    return _totalInfections;
}

// выздоравливал ли хоть раз
bool Person::hasRecoveredBefore() const {
    return _recoveredBefore;
}
