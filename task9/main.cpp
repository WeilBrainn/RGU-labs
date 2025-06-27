#include <iostream>
#include "./include/leftist_priority_queue.h"

void demo_basic_operations()
{
    std::cout << "=== Демонстрация базовых операций левосторонней кучи ===\n";

    leftist_priority_queue pq;

    // Вставка элементов
    std::cout << "Вставляем элементы:\n";
    pq.insert(10, "задача A");
    std::cout << "После вставки (10, 'задача A'):\n";
    pq.print_tree();

    pq.insert(5, "задача B");
    std::cout << "\nПосле вставки (5, 'задача B'):\n";
    pq.print_tree();

    pq.insert(15, "задача C");
    std::cout << "\nПосле вставки (15, 'задача C'):\n";
    pq.print_tree();

    pq.insert(3, "задача D");
    std::cout << "\nПосле вставки (3, 'задача D'):\n";
    pq.print_tree();

    pq.insert(12, "задача E");
    std::cout << "\nПосле вставки (12, 'задача E'):\n";
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
            std::cout << "Структура после удаления:\n";
            pq.print_tree();
            std::cout << std::endl;
            delete[] removed; // Освобождаем память
        }
    }
}

void demo_leftist_property()
{
    std::cout << "\n=== Демонстрация свойства левосторонности ===\n";
    std::cout << "В левосторонней куче ранг левого поддерева >= ранга правого\n";
    std::cout << "Ранг показывается как 'r=' в выводе\n\n";

    leftist_priority_queue pq;

    // Создаем последовательность, которая хорошо демонстрирует свойство
    int priorities[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35};
    const char* tasks[] = {"T50", "T30", "T70", "T20", "T40", "T60", "T80", "T10", "T25", "T35"};

    for (int i = 0; i < 10; i++) {
        pq.insert(priorities[i], tasks[i]);
        std::cout << "После вставки (" << priorities[i] << ", " << tasks[i] << "):\n";
        pq.print_tree();
        std::cout << std::endl;
    }
}

void demo_merge_operations()
{
    std::cout << "\n=== Демонстрация операций слияния ===\n";

    // Создаем две очереди
    leftist_priority_queue* pq1 = new leftist_priority_queue();
    leftist_priority_queue* pq2 = new leftist_priority_queue();

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
    leftist_priority_queue* melded_leftist = dynamic_cast<leftist_priority_queue*>(melded);
    if (melded_leftist) {
        melded_leftist->print_tree();
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

void demo_rank_invariant()
{
    std::cout << "\n=== Демонстрация поддержания инварианта рангов ===\n";
    std::cout << "Проверим, что ранг левого дочернего >= ранга правого дочернего\n\n";

    leftist_priority_queue pq;

    // Вставляем элементы в порядке, который может нарушить левостороннесть
    pq.insert(100, "корень");
    pq.insert(90, "левый");
    pq.insert(80, "правый");
    pq.insert(70, "левый-левый");
    pq.insert(60, "левый-правый");
    pq.insert(50, "правый-левый");
    pq.insert(40, "правый-правый");

    std::cout << "Финальная структура (обратите внимание на ранги):\n";
    pq.print_tree();

    std::cout << "\nОбратите внимание: в каждом узле ранг левого поддерева >= ранга правого\n";
    std::cout << "Это обеспечивает эффективность операций слияния\n";
}

int main()
{
    try {
        demo_basic_operations();
        demo_leftist_property();
        demo_merge_operations();
        demo_rank_invariant();

        std::cout << "\n=== Все демонстрации левосторонней кучи завершены успешно! ===\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}