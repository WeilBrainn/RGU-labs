#include <iostream>
#include <cstring>
#include "./include/treap.h"

void demonstrate_basic_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ БАЗОВЫХ ОПЕРАЦИЙ ДЕКАРТОВА ДЕРЕВА ===\n\n";

    treap tree;

    // Вставка элементов
    std::cout << "Вставляем элементы:\n";
    tree.insert(50, "Элемент A (приоритет 50)");
    std::cout << "Вставлен: приоритет 50, значение 'Элемент A'\n";

    tree.insert(30, "Элемент B (приоритет 30)");
    std::cout << "Вставлен: приоритет 30, значение 'Элемент B'\n";

    tree.insert(70, "Элемент C (приоритет 70)");
    std::cout << "Вставлен: приоритет 70, значение 'Элемент C'\n";

    tree.insert(20, "Элемент D (приоритет 20)");
    std::cout << "Вставлен: приоритет 20, значение 'Элемент D'\n";

    tree.insert(80, "Элемент E (приоритет 80)");
    std::cout << "Вставлен: приоритет 80, значение 'Элемент E'\n";

    tree.insert(40, "Элемент F (приоритет 40)");
    std::cout << "Вставлен: приоритет 40, значение 'Элемент F'\n";

    tree.insert(60, "Элемент G (приоритет 60)");
    std::cout << "Вставлен: приоритет 60, значение 'Элемент G'\n";

    std::cout << "\nРазмер дерева: " << tree.get_total_size() << "\n\n";

    // Структура дерева
    std::cout << "Структура декартова дерева:\n";
    tree.print_tree();
    std::cout << "\n";

    // Получение максимального элемента
    std::cout << "Максимальный элемент: \"" << tree.obtain_max() << "\"\n\n";

    // Печать в отсортированном порядке
    tree.print_sorted();
    std::cout << "\n";
}

void demonstrate_search_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ ПОИСКА ===\n\n";

    treap tree;

    // Создаем дерево с известными приоритетами
    tree.insert(45, "Сорок пять");
    tree.insert(23, "Двадцать три");
    tree.insert(67, "Шестьдесят семь");
    tree.insert(12, "Двенадцать");
    tree.insert(89, "Восемьдесят девять");
    tree.insert(34, "Тридцать четыре");
    tree.insert(56, "Пятьдесят шесть");

    std::cout << "Созданное дерево:\n";
    tree.print_tree();
    std::cout << "\n";

    // Поиск существующих элементов
    std::cout << "Поиск существующих элементов:\n";
    int priorities_to_find[] = {45, 23, 89, 12};
    for (int i = 0; i < 4; i++) {
        int p = priorities_to_find[i];
        std::cout << "Поиск приоритета " << p << ": ";
        if (tree.contains(p)) {
            std::cout << "найден, значение: \"" << tree.find(p) << "\"\n";
        } else {
            std::cout << "не найден\n";
        }
    }
    std::cout << "\n";

    // Поиск несуществующих элементов
    std::cout << "Поиск несуществующих элементов:\n";
    int missing_priorities[] = {100, 5, 50, 75};
    for (int i = 0; i < 4; i++) {
        int p = missing_priorities[i];
        std::cout << "Поиск приоритета " << p << ": ";
        if (tree.contains(p)) {
            std::cout << "найден, значение: \"" << tree.find(p) << "\"\n";
        } else {
            std::cout << "не найден\n";
        }
    }
    std::cout << "\n";
}

void demonstrate_removal_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ УДАЛЕНИЯ ===\n\n";

    treap tree;

    // Заполняем дерево
    tree.insert(50, "Пятьдесят");
    tree.insert(25, "Двадцать пять");
    tree.insert(75, "Семьдесят пять");
    tree.insert(10, "Десять");
    tree.insert(35, "Тридцать пять");
    tree.insert(65, "Шестьдесят пять");
    tree.insert(85, "Восемьдесят пять");

    std::cout << "Исходное дерево:\n";
    tree.print_tree();
    std::cout << "\n";

    // Удаление максимальных элементов
    std::cout << "Удаляем максимальные элементы:\n";
    while (!tree.is_empty()) {
        char const *max_val = tree.remove_max();
        std::cout << "Удален максимальный: \"" << max_val << "\"\n";
        std::cout << "Размер дерева: " << tree.get_total_size() << "\n";
        if (!tree.is_empty()) {
            std::cout << "Новый максимум: \"" << tree.obtain_max() << "\"\n";
        }
        std::cout << "\n";
        delete[] max_val;
    }

    // Восстанавливаем дерево для демонстрации удаления по приоритету
    std::cout << "Восстанавливаем дерево для демонстрации удаления по приоритету:\n";
    tree.insert(40, "Сорок");
    tree.insert(20, "Двадцать");
    tree.insert(60, "Шестьдесят");
    tree.insert(10, "Десять");
    tree.insert(30, "Тридцать");
    tree.insert(50, "Пятьдесят");
    tree.insert(70, "Семьдесят");

    tree.print_tree();
    std::cout << "\n";

    // Удаление конкретных элементов
    std::cout << "Удаляем элемент с приоритетом 20:\n";
    tree.remove(20);
    tree.print_tree();
    std::cout << "\n";

    std::cout << "Удаляем элемент с приоритетом 60:\n";
    tree.remove(60);
    tree.print_tree();
    std::cout << "\n";

    std::cout << "Удаляем элемент с приоритетом 40 (корень):\n";
    tree.remove(40);
    tree.print_tree();
    std::cout << "\n";
}

void demonstrate_merge_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СЛИЯНИЯ ===\n\n";

    // Создаем первое дерево
    treap *tree1 = new treap();
    tree1->insert(30, "Дерево1: Тридцать");
    tree1->insert(10, "Дерево1: Десять");
    tree1->insert(50, "Дерево1: Пятьдесят");
    tree1->insert(20, "Дерево1: Двадцать");

    std::cout << "Первое дерево:\n";
    tree1->print_tree();
    std::cout << "\n";

    // Создаем второе дерево
    treap *tree2 = new treap();
    tree2->insert(70, "Дерево2: Семьдесят");
    tree2->insert(40, "Дерево2: Сорок");
    tree2->insert(90, "Дерево2: Девяносто");
    tree2->insert(60, "Дерево2: Шестьдесят");

    std::cout << "Второе дерево:\n";
    tree2->print_tree();
    std::cout << "\n";

    // Неразрушающее слияние (meld)
    std::cout << "Неразрушающее слияние (meld):\n";
    priority_queue *melded = tree1->meld(tree2);
    treap *melded_tree = dynamic_cast<treap*>(melded);

    std::cout << "Результат слияния:\n";
    melded_tree->print_tree();
    std::cout << "\n";

    std::cout << "Первое дерево после meld (должно остаться неизменным):\n";
    tree1->print_tree();
    std::cout << "\n";

    std::cout << "Второе дерево после meld (должно остаться неизменным):\n";
    tree2->print_tree();
    std::cout << "\n";

    delete melded_tree;

    // Разрушающее слияние (merge)
    std::cout << "Разрушающее слияние (merge):\n";
    priority_queue *merged = tree1->merge(tree2);
    treap *merged_tree = dynamic_cast<treap*>(merged);

    std::cout << "Результат слияния:\n";
    merged_tree->print_tree();
    std::cout << "\n";

    // tree2 уже удалено в процессе merge

    std::cout << "Элементы объединенного дерева в порядке убывания:\n";
    merged_tree->print_sorted();
    std::cout << "\n";

    delete merged_tree;
}

void demonstrate_copy_operations() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ КОПИРОВАНИЯ ===\n\n";

    // Создаем оригинальное дерево
    treap original;
    original.insert(45, "Оригинал: Сорок пять");
    original.insert(25, "Оригинал: Двадцать пять");
    original.insert(65, "Оригинал: Шестьдесят пять");
    original.insert(15, "Оригинал: Пятнадцать");
    original.insert(35, "Оригинал: Тридцать пять");
    original.insert(55, "Оригинал: Пятьдесят пять");
    original.insert(75, "Оригинал: Семьдесят пять");

    std::cout << "Оригинальное дерево:\n";
    original.print_tree();
    std::cout << "\n";

    // Тестируем конструктор копирования
    treap copy1(original);
    std::cout << "Копия через конструктор копирования:\n";
    copy1.print_tree();
    std::cout << "\n";

    // Тестируем оператор присваивания
    treap copy2;
    copy2.insert(100, "Временный элемент");
    copy2 = original;
    std::cout << "Копия через оператор присваивания:\n";
    copy2.print_tree();
    std::cout << "\n";

    // Проверяем независимость копий
    std::cout << "Удаляем элемент с приоритетом 45 из оригинала:\n";
    original.remove(45);

    std::cout << "Оригинал после удаления:\n";
    original.print_tree();
    std::cout << "\n";

    std::cout << "Первая копия (должна остаться неизменной):\n";
    copy1.print_tree();
    std::cout << "\n";

    std::cout << "Вторая копия (должна остаться неизменной):\n";
    copy2.print_tree();
    std::cout << "\n";

    // Изменяем копии
    std::cout << "Добавляем элемент в первую копию:\n";
    copy1.insert(99, "Копия1: Девяносто девять");
    copy1.print_tree();
    std::cout << "\n";

    std::cout << "Добавляем элемент во вторую копию:\n";
    copy2.insert(11, "Копия2: Одиннадцать");
    copy2.print_tree();
    std::cout << "\n";

    std::cout << "Оригинал остается неизменным:\n";
    original.print_tree();
    std::cout << "\n";
}

void demonstrate_edge_cases() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ГРАНИЧНЫХ СЛУЧАЕВ ===\n\n";

    // Работа с пустым деревом
    std::cout << "Работа с пустым деревом:\n";
    treap empty_tree;

    std::cout << "Размер пустого дерева: " << empty_tree.get_total_size() << "\n";
    std::cout << "Пустое ли дерево: " << (empty_tree.is_empty() ? "да" : "нет") << "\n";

    std::cout << "Попытка найти элемент в пустом дереве (приоритет 10): ";
    std::cout << (empty_tree.contains(10) ? "найден" : "не найден") << "\n";

    std::cout << "Попытка удалить элемент из пустого дерева (приоритет 10): ";
    empty_tree.remove(10);
    std::cout << "выполнено без ошибок\n\n";

    // Вставка дублирующих приоритетов
    std::cout << "Вставка элементов с одинаковыми приоритетами:\n";
    treap dup_tree;
    dup_tree.insert(50, "Первый элемент с приоритетом 50");
    dup_tree.insert(50, "Второй элемент с приоритетом 50");
    dup_tree.insert(50, "Третий элемент с приоритетом 50");

    std::cout << "Размер дерева после вставки дубликатов: " << dup_tree.get_total_size() << "\n";
    std::cout << "Найденное значение для приоритета 50: \"" << dup_tree.find(50) << "\"\n";
    dup_tree.print_tree();
    std::cout << "\n";

    // Удаление из дерева с одним элементом
    std::cout << "Удаление из дерева с одним элементом:\n";
    treap single_tree;
    single_tree.insert(42, "Единственный элемент");

    std::cout << "Дерево с одним элементом:\n";
    single_tree.print_tree();
    std::cout << "\n";

    char const *removed_val = single_tree.remove_max();
    std::cout << "Удаленный элемент: \"" << removed_val << "\"\n";
    std::cout << "Размер после удаления: " << single_tree.get_total_size() << "\n";
    std::cout << "Пустое ли дерево: " << (single_tree.is_empty() ? "да" : "нет") << "\n";

    delete[] removed_val;
    std::cout << "\n";

    // Слияние с пустыми деревьями
    std::cout << "Слияние с пустыми деревьями:\n";
    treap *tree_with_data = new treap();
    tree_with_data->insert(30, "Тридцать");
    tree_with_data->insert(20, "Двадцать");

    treap *empty_tree_ptr = new treap();

    std::cout << "Дерево с данными:\n";
    tree_with_data->print_tree();
    std::cout << "\n";

    priority_queue *merged_with_empty = tree_with_data->merge(empty_tree_ptr);
    treap *result_tree = dynamic_cast<treap*>(merged_with_empty);

    std::cout << "Результат слияния с пустым деревом:\n";
    result_tree->print_tree();
    std::cout << "\n";

    delete result_tree;
}

void demonstrate_performance_characteristics() {
    std::cout << "=== ДЕМОНСТРАЦИЯ ХАРАКТЕРИСТИК ПРОИЗВОДИТЕЛЬНОСТИ ===\n\n";

    treap performance_tree;

    std::cout << "Вставка большого количества элементов (1000 элементов):\n";

    // Вставляем элементы в случайном порядке
    for (int i = 0; i < 1000; i++) {
        char *value = new char[50];
        sprintf(value, "Элемент номер %d", i);
        performance_tree.insert(i * 17 % 1000, value); // Псевдослучайные приоритеты
        delete[] value;
    }

    std::cout << "Размер дерева после вставки 1000 элементов: "
              << performance_tree.get_total_size() << "\n";

    // Поиск нескольких элементов
    std::cout << "Тестирование операций поиска:\n";
    int test_priorities[] = {100, 500, 750, 999, 1001}; // Последний не существует
    for (int i = 0; i < 5; i++) {
        int priority = test_priorities[i];
        bool found = performance_tree.contains(priority);
        std::cout << "Поиск приоритета " << priority << ": "
                  << (found ? "найден" : "не найден") << "\n";
    }

    std::cout << "\nУдаление половины элементов:\n";
    int removed_count = 0;
    for (int i = 0; i < 500; i++) {
        if (performance_tree.contains(i * 2)) {
            performance_tree.remove(i * 2);
            removed_count++;
        }
    }

    std::cout << "Удалено элементов: " << removed_count << "\n";
    std::cout << "Размер дерева после удаления: "
              << performance_tree.get_total_size() << "\n\n";
}

int main() {
    std::cout << "ДЕМОНСТРАЦИЯ ФУНКЦИОНАЛЬНОСТИ ДЕКАРТОВА ДЕРЕВА (TREAP)\n";
    std::cout << "====================================================\n\n";

    try {
        demonstrate_basic_operations();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_search_operations();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_removal_operations();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_merge_operations();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_copy_operations();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_edge_cases();
        std::cout << "\n" << std::string(60, '=') << "\n\n";

        demonstrate_performance_characteristics();

        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА УСПЕШНО!\n";
        std::cout << std::string(60, '=') << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Ошибка во время выполнения демонстрации: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка во время выполнения демонстрации" << std::endl;
        return 1;
    }

    return 0;
}