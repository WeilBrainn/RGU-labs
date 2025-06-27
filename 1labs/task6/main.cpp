#include "./include/binary_priority_queue.h"
#include <iostream>

void print_separator(const char* title) {
    std::cout << "\n=== " << title << " ===\n";
}

void test_basic_operations() {
    print_separator("ТЕСТ 1: Базовые операции");

    binary_priority_queue pq;

    // Тестируем вставку
    std::cout << "Вставляем элементы:\n";
    pq.insert(5, "Задача средней важности");
    pq.insert(10, "Критическая задача");
    pq.insert(1, "Низкий приоритет");
    pq.insert(8, "Высокий приоритет");
    pq.insert(3, "Обычная задача");

    std::cout << "Размер очереди: " << pq.get_size() << std::endl;

    // Тестируем получение максимума без удаления
    std::cout << "\nМаксимальный элемент (без удаления): ";
    const char* max = pq.obtain_max();
    if (max) {
        std::cout << max << std::endl;
    }
    std::cout << "Размер после obtain_max: " << pq.get_size() << std::endl;

    // Тестируем удаление элементов в порядке приоритета
    std::cout << "\nИзвлекаем элементы по приоритету:\n";
    while (!pq.is_empty()) {
        const char* task = pq.remove_max();
        if (task) {
            std::cout << "Извлечен: " << task << std::endl;
        }
    }

    std::cout << "Очередь пуста: " << (pq.is_empty() ? "Да" : "Нет") << std::endl;
}

void test_rule_of_five() {
    print_separator("ТЕСТ 2: Правило пяти");

    binary_priority_queue original;
    original.insert(10, "Высокий приоритет");
    original.insert(5, "Средний приоритет");
    original.insert(15, "Максимальный приоритет");

    std::cout << "Исходная очередь создана с " << original.get_size() << " элементами\n";

    // Тест конструктора копирования
    binary_priority_queue copy_constructed(original);
    std::cout << "Конструктор копирования: " << copy_constructed.get_size() << " элементов\n";
    std::cout << "Максимум в копии: " << copy_constructed.obtain_max() << std::endl;

    // Тест оператора присваивания
    binary_priority_queue assigned;
    assigned.insert(1, "Временный элемент");
    assigned = original;
    std::cout << "Оператор присваивания: " << assigned.get_size() << " элементов\n";
    std::cout << "Максимум в присвоенной очереди: " << assigned.obtain_max() << std::endl;

    // Тест конструктора перемещения
    binary_priority_queue move_source;
    move_source.insert(20, "Элемент для перемещения");
    move_source.insert(25, "Максимальный для перемещения");

    binary_priority_queue move_constructed(static_cast<binary_priority_queue&&>(move_source));
    std::cout << "Конструктор перемещения: " << move_constructed.get_size() << " элементов\n";
    std::cout << "Исходная очередь после перемещения: " << move_source.get_size() << " элементов\n";

    // Тест оператора присваивания перемещения
    binary_priority_queue move_assigned;
    binary_priority_queue move_source2;
    move_source2.insert(30, "Для перемещения присваиванием");

    move_assigned = static_cast<binary_priority_queue&&>(move_source2);
    std::cout << "Оператор присваивания перемещения: " << move_assigned.get_size() << " элементов\n";

    std::cout << "✓ Все операции правила пяти выполнены успешно\n";
}

void test_merge_operations() {
    print_separator("ТЕСТ 3: Операции слияния");

    binary_priority_queue pq1;
    pq1.insert(10, "Задача A");
    pq1.insert(5, "Задача B");
    pq1.insert(15, "Задача C");

    binary_priority_queue pq2;
    pq2.insert(8, "Задача X");
    pq2.insert(12, "Задача Y");
    pq2.insert(3, "Задача Z");

    std::cout << "Первая очередь: " << pq1.get_size() << " элементов\n";
    std::cout << "Вторая очередь: " << pq2.get_size() << " элементов\n";

    // Тест merge (деструктивное слияние)
    std::cout << "\nТест merge (деструктивное слияние):\n";
    binary_priority_queue pq1_copy(pq1);
    binary_priority_queue pq2_copy(pq2);

    pq1_copy.merge(&pq2_copy);
    std::cout << "После merge - первая очередь: " << pq1_copy.get_size() << " элементов\n";
    std::cout << "После merge - вторая очередь: " << pq2_copy.get_size() << " элементов\n";

    // Тест meld (неизменяющее слияние)
    std::cout << "\nТест meld (неизменяющее слияние):\n";
    const priority_queue* merged = pq1.meld(&pq2);
    const binary_priority_queue* bin_merged = dynamic_cast<const binary_priority_queue*>(merged);

    if (bin_merged) {
        std::cout << "Результат meld: " << bin_merged->get_size() << " элементов\n";
        std::cout << "Исходная первая очередь: " << pq1.get_size() << " элементов\n";
        std::cout << "Исходная вторая очередь: " << pq2.get_size() << " элементов\n";

        // Показываем результат слияния
        binary_priority_queue result_copy(*bin_merged);
        std::cout << "\nЭлементы объединенной очереди:\n";
        while (!result_copy.is_empty()) {
            const char* task = result_copy.remove_max();
            if (task) {
                std::cout << "- " << task << std::endl;
            }
        }

        delete merged;
    }
}

void test_edge_cases() {
    print_separator("ТЕСТ 4: Граничные случаи");

    binary_priority_queue pq;

    // Тест с пустой очередью
    std::cout << "Тест с пустой очередью:\n";
    std::cout << "obtain_max() на пустой очереди: " << (pq.obtain_max() ? pq.obtain_max() : "nullptr") << std::endl;
    std::cout << "remove_max() на пустой очереди: " << (pq.remove_max() ? pq.remove_max() : "nullptr") << std::endl;

    // Тест с одним элементом
    std::cout << "\nТест с одним элементом:\n";
    pq.insert(42, "Единственный элемент");
    std::cout << "Размер: " << pq.get_size() << std::endl;
    std::cout << "Максимум: " << pq.obtain_max() << std::endl;
    std::cout << "Удаляем: " << pq.remove_max() << std::endl;
    std::cout << "Размер после удаления: " << pq.get_size() << std::endl;

    // Тест с одинаковыми приоритетами
    std::cout << "\nТест с одинаковыми приоритетами:\n";
    pq.insert(5, "Первый с приоритетом 5");
    pq.insert(5, "Второй с приоритетом 5");
    pq.insert(5, "Третий с приоритетом 5");

    std::cout << "Извлекаем элементы с одинаковым приоритетом:\n";
    while (!pq.is_empty()) {
        const char* task = pq.remove_max();
        if (task) {
            std::cout << "- " << task << std::endl;
        }
    }

    // Тест с большим количеством элементов
    std::cout << "\nТест производительности (100 элементов):\n";
    for (int i = 0; i < 100; i++) {
        pq.insert(i, "Элемент");
    }
    std::cout << "Вставлено 100 элементов, размер: " << pq.get_size() << std::endl;

    int count = 0;
    while (!pq.is_empty() && count < 5) {
        pq.remove_max();
        count++;
    }
    std::cout << "Удалено 5 элементов, размер: " << pq.get_size() << std::endl;

    pq.clear();
    std::cout << "После clear(), размер: " << pq.get_size() << std::endl;
}

void test_interface_usage() {
    print_separator("ТЕСТ 5: Использование через интерфейс");

    // Создаем объект через интерфейс
    priority_queue* pq = new binary_priority_queue();

    std::cout << "Работа через интерфейс priority_queue:\n";

    pq->insert(10, "Через интерфейс - высокий");
    pq->insert(5, "Через интерфейс - средний");
    pq->insert(15, "Через интерфейс - максимальный");

    std::cout << "Максимальный элемент: " << pq->obtain_max() << std::endl;

    // Создаем вторую очередь для слияния
    priority_queue* pq2 = new binary_priority_queue();
    pq2->insert(7, "Вторая очередь - элемент");

    // Тест meld через интерфейс
    const priority_queue* melded = pq->meld(pq2);
    std::cout << "Слияние через интерфейс выполнено\n";

    delete pq;
    delete pq2;
    delete melded;

    std::cout << "✓ Работа через интерфейс успешна\n";
}

void demonstration() {
    print_separator("ДЕМОНСТРАЦИЯ: Система задач");

    binary_priority_queue task_queue;

    std::cout << "Добавляем задачи в систему:\n";
    task_queue.insert(1, "Ответить на email");
    task_queue.insert(9, "Исправить критическую ошибку");
    task_queue.insert(5, "Обновить документацию");
    task_queue.insert(10, "Презентация для клиента");
    task_queue.insert(3, "Заказать обед");
    task_queue.insert(7, "Code review");
    task_queue.insert(2, "Проверить почту");
    task_queue.insert(8, "Встреча с командой");

    std::cout << "\nВыполняем задачи по приоритету:\n";
    int task_number = 1;
    while (!task_queue.is_empty()) {
        const char* task = task_queue.remove_max();
        if (task) {
            std::cout << task_number++ << ". " << task << std::endl;
        }
    }
}

int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ ДВОИЧНОЙ ПРИОРИТЕТНОЙ ОЧЕРЕДИ ===\n";

    try {
        test_basic_operations();
        test_rule_of_five();
        test_merge_operations();
        test_edge_cases();
        test_interface_usage();
        demonstration();

        std::cout << "\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ УСПЕШНО ===\n";

        std::cout << "\n=== ПРИМЕР ИСПОЛЬЗОВАНИЯ ===\n";
        std::cout << "binary_priority_queue pq;\n";
        std::cout << "pq.insert(10, \"Высокий приоритет\");\n";
        std::cout << "pq.insert(5, \"Средний приоритет\");\n";
        std::cout << "const char* max = pq.obtain_max(); // Получить без удаления\n";
        std::cout << "const char* removed = pq.remove_max(); // Получить и удалить\n";

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Неизвестная ошибка" << std::endl;
        return 1;
    }

    return 0;
}