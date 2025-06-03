#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string DELETED = "<deleted>";

struct HashTable {
    vector<string> table;
    int capacity;
    int size;
};

// Хеш-функция
int hashFunction(const string& key, int capacity) {
    unsigned int h = 0;
    for (char c : key)
        h = 31 * h + c;
    return h % capacity;
}

// Загрузка
float loadFactor(const HashTable& ht) {
    return static_cast<float>(ht.size) / ht.capacity;
}

// Рехеширование
void rehash(HashTable& ht);

// Вставка
void insert(HashTable& ht, const string& key) {
    if (loadFactor(ht) >= 0.7f)
        rehash(ht);

    int index = hashFunction(key, ht.capacity);
    while (!ht.table[index].empty() && ht.table[index] != DELETED && ht.table[index] != key)
        index = (index + 1) % ht.capacity;

    if (ht.table[index].empty() || ht.table[index] == DELETED)
        ++ht.size;

    ht.table[index] = key;
}

// Удаление
void remove(HashTable& ht, const string& key) {
    int index = hashFunction(key, ht.capacity);
    int start = index;

    while (!ht.table[index].empty()) {
        if (ht.table[index] == key) {
            ht.table[index] = DELETED;
            --ht.size;
            return;
        }
        index = (index + 1) % ht.capacity;
        if (index == start) break;
    }
}

// Поиск
bool contains(const HashTable& ht, const string& key) {
    int index = hashFunction(key, ht.capacity);
    int start = index;

    while (!ht.table[index].empty()) {
        if (ht.table[index] != DELETED && ht.table[index] == key)
            return true;
        index = (index + 1) % ht.capacity;
        if (index == start) break;
    }
    return false;
}

// Вывод таблицы
void print(const HashTable& ht) {
    cout << "\nТекущее содержимое хеш-таблицы:\n";
    for (int i = 0; i < ht.capacity; ++i)
        cout << i << ": " << ht.table[i] << endl;
}

// Реализация рехеширования
void rehash(HashTable& ht) {
    int old_capacity = ht.capacity;
    vector<string> old_table = ht.table;

    ht.capacity *= 3;
    ht.table.clear();
    ht.table.resize(ht.capacity, "");
    ht.size = 0;

    for (const auto& key : old_table) {
        if (!key.empty() && key != DELETED)
            insert(ht, key);
    }
}

int main() {
    HashTable ht;
    ht.capacity = 8;
    ht.size = 0;
    ht.table.resize(ht.capacity, "");

    int choice;
    string key;

    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Добавить строку\n";
        cout << "2. Удалить строку\n";
        cout << "3. Поиск строки\n";
        cout << "4. Печать таблицы\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Введите строку для добавления: ";
                getline(cin, key);
                insert(ht, key);
                break;
            case 2:
                cout << "Введите строку для удаления: ";
                getline(cin, key);
                remove(ht, key);
                break;
            case 3:
                cout << "Введите строку для поиска: ";
                getline(cin, key);
                cout << (contains(ht, key) ? "Строка найдена." : "Строка не найдена.") << endl;
                break;
            case 4:
                print(ht);
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Повторите ввод.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}