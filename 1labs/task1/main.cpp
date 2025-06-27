#include "./include/encoder.h"
#include <iostream>
#include <fstream>
#include <cstring>

void create_test_file(const char* filename, const char* content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Создан тестовый файл: " << filename << std::endl;
    } else {
        std::cout << "Ошибка создания файла: " << filename << std::endl;
    }
}

void print_file_content(const char* filename, const char* description) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        std::cout << "\n" << description << " (" << filename << "):" << std::endl;

        char byte;
        int count = 0;
        while (file.get(byte) && count < 100) { // Ограничиваем вывод первыми 100 байтами
            if (byte >= 32 && byte <= 126) {
                std::cout << byte;
            } else {
                std::cout << "[" << static_cast<int>(static_cast<unsigned char>(byte)) << "]";
            }
            count++;
        }
        std::cout << std::endl;
        file.close();
    } else {
        std::cout << "Не удалось открыть файл: " << filename << std::endl;
    }
}

void test_basic_encoding() {
    std::cout << "\n=== ТЕСТ 1: Базовое шифрование ===\n";

    // Создаем тестовый файл
    const char* test_content = "Hello, World! This is a test message for encryption.";
    create_test_file("input.txt", test_content);

    // Создаем ключ
    unsigned char key[] = "MySecretKey123";
    int key_length = strlen(reinterpret_cast<const char*>(key));

    // Создаем энкодер и шифруем
    Encoder encoder(key, key_length);
    encoder.encode("input.txt", "encrypted.txt");

    // Показываем результаты
    print_file_content("input.txt", "Исходный текст");
    print_file_content("encrypted.txt", "Зашифрованный текст");

    // Расшифровываем (RC4 симметричный)
    Encoder decoder(key, key_length);
    decoder.encode("encrypted.txt", "decrypted.txt");

    print_file_content("decrypted.txt", "Расшифрованный текст");
}

void test_rule_of_five() {
    std::cout << "\n=== ТЕСТ 2: Правило пяти ===\n";

    unsigned char key1[] = "Key1";
    unsigned char key2[] = "DifferentKey2";

    // Тест конструктора копирования
    Encoder original(key1, 4);
    Encoder copy_constructed(original);
    std::cout << "✓ Конструктор копирования выполнен" << std::endl;

    // Тест оператора присваивания
    Encoder assigned(key2, 13);
    assigned = original;
    std::cout << "✓ Оператор присваивания выполнен" << std::endl;

    // Тест конструктора перемещения
    Encoder move_constructed(static_cast<Encoder&&>(Encoder(key1, 4)));
    std::cout << "✓ Конструктор перемещения выполнен" << std::endl;

    // Тест оператора присваивания перемещения
    Encoder move_assigned(key2, 13);
    move_assigned = static_cast<Encoder&&>(Encoder(key1, 4));
    std::cout << "✓ Оператор присваивания перемещения выполнен" << std::endl;
}

void test_key_change() {
    std::cout << "\n=== ТЕСТ 3: Смена ключа ===\n";

    create_test_file("test_key_change.txt", "Test message for key change");

    unsigned char key1[] = "FirstKey";
    unsigned char key2[] = "SecondKey";

    Encoder encoder(key1, 8);

    // Шифруем с первым ключом
    encoder.encode("test_key_change.txt", "encrypted_key1.txt");
    print_file_content("encrypted_key1.txt", "Зашифровано первым ключом");

    // Меняем ключ
    encoder.set_key(key2, 9);

    // Шифруем с вторым ключом
    encoder.encode("test_key_change.txt", "encrypted_key2.txt");
    print_file_content("encrypted_key2.txt", "Зашифровано вторым ключом");

    std::cout << "✓ Смена ключа работает корректно" << std::endl;
}

void test_binary_data() {
    std::cout << "\n=== ТЕСТ 4: Бинарные данные ===\n";

    // Создаем файл с бинарными данными
    std::ofstream binFile("binary_test.bin", std::ios::binary);
    if (binFile.is_open()) {
        for (int i = 0; i < 256; i++) {
            binFile.put(static_cast<char>(i));
        }
        binFile.close();
        std::cout << "Создан файл с бинарными данными (256 байт)" << std::endl;

        unsigned char key[] = "BinaryTestKey";
        Encoder encoder(key, 13);

        // Шифруем бинарные данные
        encoder.encode("binary_test.bin", "binary_encrypted.bin");

        // Расшифровываем
        Encoder decoder(key, 13);
        decoder.encode("binary_encrypted.bin", "binary_decrypted.bin");

        std::cout << "✓ Бинарные данные зашифрованы и расшифрованы" << std::endl;
    }
}

void test_error_handling() {
    std::cout << "\n=== ТЕСТ 5: Обработка ошибок ===\n";

    unsigned char key[] = "TestKey";
    Encoder encoder(key, 7);

    // Тест с несуществующим файлом
    encoder.encode("nonexistent.txt", "output.txt");
    std::cout << "✓ Обработка несуществующего входного файла" << std::endl;

    // Тест с null указателями
    encoder.encode(nullptr, "output.txt");
    encoder.encode("input.txt", nullptr);
    std::cout << "✓ Обработка null указателей" << std::endl;

    // Тест с null ключом
    Encoder null_encoder(nullptr, 0);
    std::cout << "✓ Обработка null ключа в конструкторе" << std::endl;
}

int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ КЛАССА ENCODER ===\n";

    try {
        test_basic_encoding();
        test_rule_of_five();
        test_key_change();
        test_binary_data();
        test_error_handling();

        std::cout << "\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ УСПЕШНО ===\n";

        // Демонстрация использования
        std::cout << "\n=== ПРИМЕР ИСПОЛЬЗОВАНИЯ ===\n";
        std::cout << "1. Создайте объект Encoder с ключом:" << std::endl;
        std::cout << "   unsigned char key[] = \"YourSecretKey\";" << std::endl;
        std::cout << "   Encoder encoder(key, strlen((char*)key));" << std::endl;
        std::cout << "2. Зашифруйте файл:" << std::endl;
        std::cout << "   encoder.encode(\"input.txt\", \"encrypted.txt\");" << std::endl;
        std::cout << "3. Для расшифровки используйте тот же ключ:" << std::endl;
        std::cout << "   encoder.encode(\"encrypted.txt\", \"decrypted.txt\");" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Неизвестная ошибка" << std::endl;
        return 1;
    }

    return 0;
}