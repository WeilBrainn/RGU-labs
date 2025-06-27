#pragma once

#include "Patient.h"

class Doctor 
{
private:
	int _id = 0;
	bool _isBusy = false;
	int _availableTime = 0; // когда освободился
	Patient* _currentPatient = nullptr;
	int _helpStart = -1, _helpEnd = -1;

public:
	bool isAvailable(int now);
	void startTreatment(Patient* p, int now, int duration);
	void askHelp(Doctor& other, int now, int duratuion);

};