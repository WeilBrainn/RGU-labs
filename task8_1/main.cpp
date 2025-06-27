#include <iostream>
#include <cstring>
#include "./include/fibonacci_heap.h"

void demonstrate_basic_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ БАЗОВЫХ ОПЕРАЦИЙ ===\n\n";

    fibonacci_heap heap;

    // Вставка элементов
    std::cout << "Вставляем элементы:\n";
    heap.insert(10, "Элемент A");
    std::cout << "Вставлен: приоритет 10, значение 'Элемент A'\n";

    heap.insert(5, "Элемент B");
    std::cout << "Вставлен: приоритет 5, значение 'Элемент B'\n";

    heap.insert(15, "Элемент C");
    std::cout << "Вставлен: приоритет 15, значение 'Элемент C'\n";

    heap.insert(8, "Элемент D");
    std::cout << "Вставлен: приоритет 8, значение 'Элемент D'\n";

    heap.insert(20, "Элемент E");
    std::cout << "Вставлен: приоритет 20, значение 'Элемент E'\n";

    std::cout << "\nРазмер кучи: " << heap.get_size() << "\n\n";

    // Получение максимального элемента
    std::cout << "Максимальный элемент: \"" << heap.obtain_max() << "\"\n\n";

    // Печать структуры кучи
    std::cout << "Структура кучи:\n";
    heap.print_heap();
    std::cout << "\n";

    // Удаление элементов
    std::cout << "Удаляем элементы в порядке убывания приоритета:\n";
    while (!heap.is_empty()) {
        char const *max_val = heap.remove_max();
        std::cout << "Удален: \"" << max_val << "\"\n";
        delete[] max_val; // Освобождаем память
        std::cout << "Размер кучи: " << heap.get_size() << "\n";
    }
    std::cout << "\n";
}

void demonstrate_merge_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СЛИЯНИЯ ===\n\n";

    // Создаем первую кучу
    fibonacci_heap *heap1 = new fibonacci_heap();
    heap1->insert(25, "Куча1: Элемент 1");
    heap1->insert(10, "Куча1: Элемент 2");
    heap1->insert(30, "Куча1: Элемент 3");

    std::cout << "Первая куча:\n";
    heap1->print_heap();
    std::cout << "\n";

    // Создаем вторую кучу
    fibonacci_heap *heap2 = new fibonacci_heap();
    heap2->insert(35, "Куча2: Элемент 1");
    heap2->insert(15, "Куча2: Элемент 2");
    heap2->insert(5, "Куча2: Элемент 3");

    std::cout << "Вторая куча:\n";
    heap2->print_heap();
    std::cout << "\n";

    // Демонстрация неразрушающего слияния (meld)
    std::cout << "Неразрушающее слияние (meld):\n";
    priority_queue *melded = heap1->meld(heap2);
    fibonacci_heap *melded_heap = dynamic_cast<fibonacci_heap*>(melded);

    std::cout << "Результат слияния:\n";
    melded_heap->print_heap();
    std::cout << "\n";

    std::cout << "Первая куча после meld (должна остаться неизменной):\n";
    heap1->print_heap();
    std::cout << "\n";

    std::cout << "Вторая куча после meld (должна остаться неизменной):\n";
    heap2->print_heap();
    std::cout << "\n";

    delete melded_heap;

    // Демонстрация разрушающего слияния (merge)
    std::cout << "Разрушающее слияние (merge):\n";
    priority_queue *merged = heap1->merge(heap2);
    fibonacci_heap *merged_heap = dynamic_cast<fibonacci_heap*>(merged);

    std::cout << "Результат слияния:\n";
    merged_heap->print_heap();
    std::cout << "\n";

    // heap2 уже удалена в процессе merge
    // heap1 теперь содержит объединенную кучу

    std::cout << "Извлекаем все элементы из объединенной кучи:\n";
    while (!merged_heap->is_empty()) {
        char const *max_val = merged_heap->remove_max();
        std::cout << "Извлечен: \"" << max_val << "\"\n";
        delete[] max_val;
    }

    delete merged_heap;
    std::cout << "\n";
}

void demonstrate_copy_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ КОПИРОВАНИЯ ===\n\n";

    // Создаем оригинальную кучу
    fibonacci_heap original;
    original.insert(40, "Оригинал: A");
    original.insert(25, "Оригинал: B");
    original.insert(50, "Оригинал: C");
    original.insert(10, "Оригинал: D");

    std::cout << "Оригинальная куча:\n";
    original.print_heap();
    std::cout << "\n";

    // Тестируем конструктор копирования
    fibonacci_heap copy1(original);
    std::cout << "Копия через конструктор копирования:\n";
    copy1.print_heap();
    std::cout << "\n";

    // Тестируем оператор присваивания
    fibonacci_heap copy2;
    copy2.insert(100, "Временный элемент");
    copy2 = original;
    std::cout << "Копия через оператор присваивания:\n";
    copy2.print_heap();
    std::cout << "\n";

    // Проверяем независимость копий
    std::cout << "Удаляем максимум из оригинала:\n";
    char const *removed = original.remove_max();
    std::cout << "Удален: \"" << removed << "\"\n";
    delete[] removed;

    std::cout << "\nОригинал после удаления:\n";
    original.print_heap();
    std::cout << "\n";

    std::cout << "Первая копия (должна остаться неизменной):\n";
    copy1.print_heap();
    std::cout << "\n";

    std::cout << "Вторая копия (должна остаться неизменной):\n";
    copy2.print_heap();
    std::cout << "\n";
}

void demonstrate_edge_cases() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ГРАНИЧНЫХ СЛУЧАЕВ ===\n\n";

    fibonacci_heap empty_heap;

    std::cout << "Операции с пустой кучей:\n";
    std::cout << "Пуста ли куча? " << (empty_heap.is_empty() ? "Да" : "Нет") << "\n";
    std::cout << "Размер: " << empty_heap.get_size() << "\n";
    std::cout << "Максимальный элемент: " << (empty_heap.obtain_max() ? empty_heap.obtain_max() : "null") << "\n";
    std::cout << "Удаление из пустой кучи: " << (empty_heap.remove_max() ? "Успех" : "null") << "\n\n";

    // Вставка элементов с одинаковыми приоритетами
    std::cout << "Вставка элементов с одинаковыми приоритетами:\n";
    fibonacci_heap same_priority;
    same_priority.insert(10, "Первый");
    same_priority.insert(10, "Второй");
    same_priority.insert(10, "Третий");

    same_priority.print_heap();
    std::cout << "\n";

    std::cout << "Извлечение элементов с одинаковыми приоритетами:\n";
    while (!same_priority.is_empty()) {
        char const *val = same_priority.remove_max();
        std::cout << "Извлечен: \"" << val << "\"\n";
        delete[] val;
    }
    std::cout << "\n";

    // Слияние с пустой кучей
    std::cout << "Слияние с пустой кучей:\n";
    fibonacci_heap *heap_with_data = new fibonacci_heap();
    heap_with_data->insert(15, "Элемент");

    fibonacci_heap *empty_heap_ptr = new fibonacci_heap();

    std::cout << "Куча с данными:\n";
    heap_with_data->print_heap();
    std::cout << "\n";

    priority_queue *result = heap_with_data->merge(empty_heap_ptr);
    fibonacci_heap *result_heap = dynamic_cast<fibonacci_heap*>(result);

    std::cout << "Результат слияния с пустой кучей:\n";
    result_heap->print_heap();
    std::cout << "\n";

    delete result_heap;
}

int main() {
    std::cout << "ДЕМОНСТРАЦИЯ РАБОТЫ ФИБОНАЧЧИЕВОЙ ПРИОРИТЕТНОЙ ОЧЕРЕДИ\n";
    std::cout << "======================================================\n\n";

    try {
        demonstrate_basic_operations();
        demonstrate_merge_operations();
        demonstrate_copy_operations();
        demonstrate_edge_cases();

        std::cout << "Все демонстрации завершены успешно!\n";
    } catch (std::exception const &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка\n";
        return 1;
    }

    return 0;
}