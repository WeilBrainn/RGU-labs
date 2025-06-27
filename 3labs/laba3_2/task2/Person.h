#pragma once

#include <string>
#include <vector>
#include <random>

class Person {
public:
    // создаёт человека с id, именем и фамилией
    Person(int id, const std::string& name, const std::string& surname);

    // добавляет нового знакомого, если его ещё нет
    void addContact(int otherId);

    // запускает заражение (инкубационный период)
    void startInfection(int incubationDays);

    // обновляет состояние на один день с учётом вероятности выздоровления
    void updateState(double p2, int T, std::mt19937& rng);

    // возвращает true, если человек может заражать
    bool canInfect() const;

    // проверяет можно ли заразить человека повторно
    bool isSusceptible(bool reinfectionAllowed) const;

    // возвращает id
    int getId() const;

    // возвращает полное имя
    std::string getFullName() const;

    // возвращает список контактов
    const std::vector<int>& getContacts() const;

    // возвращает текущее состояние
    enum class HealthStatus { Healthy, Incubating, Infectious, Recovering, Chronic, Immune };
    HealthStatus getStatus() const;

    // проверяет стал ли случай хроническим
    bool isChronic() const;

    // возвращает сколько раз человек болел
    int getInfectionCount() const;

    // был ли хотя бы один раз вылечен
    bool hasRecoveredBefore() const;

private:
    int _id = 0;
    std::string _name;
    std::string _surname;
    std::vector<int> _contacts;

    HealthStatus _currentStatus = HealthStatus::Healthy;
    int _daysSinceInfection = -1;
    int _incubationPeriodRemaining = 0;
    int _recoveryDaysRemaining = 0;
    int _totalInfections = 0;

    bool _recoveredBefore = false;
    bool _isCurrentlyIsolated = false;
    bool _chronic = false;
};
