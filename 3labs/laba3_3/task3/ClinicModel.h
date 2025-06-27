#pragma once

#include "WaitingRoom.h"
#include "Doctor.h"
#include "Patient.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class ClinicModel 
{
private:
	int _time = 0; 
	int _maxTime = ...; 
	int _T = ;
	vector<Doctor> _doctors;
	vector<Patient> _patients;
	WaitingRoom _room;
	ofstream _log;

public:
	void simulate();
	void logEvent();
	void generateRandomPatients();
};
