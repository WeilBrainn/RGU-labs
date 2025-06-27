#pragma once
#include "Patient.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class WaitingRoom 
{
private:
	int _capacity = N;
	vector<Patient*> _seatedPatients;
	queue<Patient*> _waitingQueue;
	bool _currentRoomInfectionState = false;

public:
	bool tryEnter(Patient* p); // пробует войти
	void tick(int now); // обновляет статус заражает всю очередь если надо
	Patient* pickNextPatient(); // выбирает пациента пришедшего первым
	void markAllInfection(); // заразить всю очередь
};