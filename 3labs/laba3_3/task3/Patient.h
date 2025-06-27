#pragma once

class Patient 
{
private:
	int _id = 0; // ну тут и говорить нечего
	bool _isInfected = false; // болен или нет
	int _arrivalTime = 0; // время приходи в больницу 
	int _enterTime = -1; // когда попал в смотровую 
	int _serviceStartTime = -1; // когда начали "обслуживать"
	int _serviceEndTime = -1; // когда закончили "обслуживать"
	bool _wasTreated = false;
};