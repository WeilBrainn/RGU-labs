#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class priority_queue {
public:
	// ����������
	// virtual - ��� ���������� ����� ��� ����, ����� ���� �������� ���������� ����� priority_queue
	// �� � ����� ������ ��������� ����������� �� ��������� � ����� ������ ������ (������� virtual, ����� ����� �� ���������)
	virtual ~priority_queue() = default;

	virtual void insert(int key, char const* value) = 0;
	
	virtual const char* search(int key) = 0;

	virtual const char* top() const = 0;

	virtual void pop() = 0;

	virtual priority_queue* merge(const priority_queue& other) = 0;

	// Fluet API - ��� �����/����������� � ������� ������ ���������� ������, � �������� ��� �����������
	// �������� �������� ������ �������� (+���������� ����, +��������� ���-�� ������������� ����������)
};

#endif