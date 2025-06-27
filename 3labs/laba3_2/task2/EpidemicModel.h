#pragma once

#include <string>
#include <vector>
#include <random>
#include <unordered_map> // контейнер, который хранит пары «ключ-значение»
#include <fstream>
#include <iostream>
#include "Person.h"


class EpidemicModel
{

private:
	
	// хранит всех людей по айди для фаст доступа
	std::unordered_map<int, Person> _people;

	// вероятность заражения при контакте
	double _p1 = 0.0; 

	// вероятность выздоровить после инкубации
	double _p2 = 0.0;

	// сколько дней длится симуляция
	int _days = 0;

	// возможно ли заболеть повторно
	bool _reinfectionAllowed = false;

	// минимальная длительность лечения 
	int _T = 0;

	// инкубац. период
	int _I = 0;

	// айди первого зараженного, может быть случайно выбран 
	int _outbreakId = -1;

	// генератор случайных чисел
	std::mt19937 _rng; 
	// генератор псевдослучайных чисел из семейства Mersenne Twister
	// Основан на простом числе Мерсена (2^19937 - 1)

public:

	// конструктор инициализирует генератор случайных чисел
	EpidemicModel();

	// загружает людей, их связи и параметры симуляции из файла
	void loadFromFile(const std::string& filename);

	// запускает начальную вспышку заражения
	void triggerOutbreak();

	// выполняет симуляцию по дням
	void run();

	// записывает результат в файл
	void writeResults(const std::string& filename);

	// доступ к данным
	const std::unordered_map<int, Person>& getPeople() const;


};