#include <iostream>
#include "./include/skew_priority_queue.h"

void demo_basic_operations()
{
    std::cout << "=== Демонстрация базовых операций ===\n";

    skew_priority_queue pq;

    // Вставка элементов
    std::cout << "Вставляем элементы:\n";
    pq.insert(10, "задача A");
    pq.insert(5, "задача B");
    pq.insert(15, "задача C");
    pq.insert(3, "задача D");
    pq.insert(12, "задача E");

    pq.print_tree();

    // Получение максимального элемента
    std::cout << "\nМаксимальный элемент: ";
    const char* max = pq.obtain_max();
    if (max) std::cout << max << std::endl;

    // Удаление элементов
    std::cout << "\nУдаляем элементы в порядке приоритета:\n";
    while (!pq.is_empty()) {
        const char* removed = pq.remove_max();
        if (removed) {
            std::cout << "Удален: " << removed << std::endl;
            delete[] removed; // Освобождаем память
        }
    }
}

void demo_merge_operations()
{
    std::cout << "\n=== Демонстрация операций слияния ===\n";

    // Создаем две очереди
    skew_priority_queue* pq1 = new skew_priority_queue();
    skew_priority_queue* pq2 = new skew_priority_queue();

    // Заполняем первую очередь
    std::cout << "Первая очередь:\n";
    pq1->insert(20, "важная задача");
    pq1->insert(8, "обычная задача");
    pq1->insert(25, "критическая задача");
    pq1->print_tree();

    // Заполняем вторую очередь
    std::cout << "\nВторая очередь:\n";
    pq2->insert(15, "срочная задача");
    pq2->insert(30, "приоритетная задача");
    pq2->insert(5, "простая задача");
    pq2->print_tree();

    // Демонстрация meld (неразрушающее слияние)
    std::cout << "\nРезультат meld (неразрушающее слияние):\n";
    priority_queue* melded = pq1->meld(pq2);
    skew_priority_queue* melded_skew = dynamic_cast<skew_priority_queue*>(melded);
    if (melded_skew) {
        melded_skew->print_tree();
    }

    std::cout << "\nПроверяем, что исходные очереди не изменились:\n";
    std::cout << "Первая очередь все еще содержит:\n";
    pq1->print_tree();
    std::cout << "Вторая очередь все еще содержит:\n";
    pq2->print_tree();

    // Демонстрация merge (деструктивное слияние)
    std::cout << "\nРезультат merge (деструктивное слияние pq1 с pq2):\n";
    pq1->merge(pq2);
    pq1->print_tree();

    std::cout << "\nВторая очередь после merge (должна быть пуста):\n";
    pq2->print_tree();

    // Очистка памяти
    delete pq1;
    delete pq2;
    delete melded;
}

void demo_priority_order()
{
    std::cout << "\n=== Демонстрация правильности приоритетов ===\n";

    skew_priority_queue pq;

    // Вставляем элементы в случайном порядке
    std::cout << "Вставляем элементы с приоритетами: 1, 100, 50, 75, 25, 90\n";
    pq.insert(1, "приоритет 1");
    pq.insert(100, "приоритет 100");
    pq.insert(50, "приоритет 50");
    pq.insert(75, "приоритет 75");
    pq.insert(25, "приоритет 25");
    pq.insert(90, "приоритет 90");

    std::cout << "\nИзвлекаем в порядке убывания приоритета:\n";
    while (!pq.is_empty()) {
        const char* item = pq.remove_max();
        if (item) {
            std::cout << item << std::endl;
            delete[] item;
        }
    }
}

int main()
{
    try {
        demo_basic_operations();
        demo_merge_operations();
        demo_priority_order();

        std::cout << "\n=== Все демонстрации завершены успешно! ===\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}