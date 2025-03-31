#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class priority_queue {
public:
	// Деструктор
	// virtual - тут специально нужен для того, чтобы если удаление произойдет через priority_queue
	// то в таком случае наследник деструктора не вызовется и будет утечка памяти (поэтому virtual, чтобы такое не произошло)
	virtual ~priority_queue() = default;

	virtual void insert(int key, char const* value) = 0;
	
	virtual const char* search(int key) = 0;

	virtual const char* top() const = 0;

	virtual void pop() = 0;

	virtual priority_queue* merge(const priority_queue& other) = 0;

	// Fluet API - Это стиль/методология в котором методы возвращают объект, к которому они принадлежат
	// позволяя вызывать методы цепочкой (+читаемость кода, +уменьшает кол-во промежуточных переменных)
};

#endif