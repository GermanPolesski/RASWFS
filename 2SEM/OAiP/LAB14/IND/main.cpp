#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Passport {
    string number; // ключ – номер паспорта
    string name;   // имя клиента
};

struct HashTable {
    vector<vector<Passport>> table;
    int capacity;
};

// Хеш-функция
int hashFunction(const string& key, int capacity) {
    unsigned int hash = 0;
    for (char c : key)
        hash = 31 * hash + c;
    return hash % capacity;
}

// Инициализация таблицы
void init(HashTable& ht, int cap = 8) {
    ht.capacity = cap;
    ht.table.resize(cap);
}

// Добавление (обновление по ключу)
void insert(HashTable& ht, const Passport& p) {
    int index = hashFunction(p.number, ht.capacity);
    for (auto& entry : ht.table[index]) {
        if (entry.number == p.number) {
            entry.name = p.name; // обновить имя
            return;
        }
    }
    ht.table[index].push_back(p); // добавить новый элемент
}

// Поиск
bool find(const HashTable& ht, const string& number, Passport& result) {
    int index = hashFunction(number, ht.capacity);
    for (const auto& entry : ht.table[index]) {
        if (entry.number == number) {
            result = entry;
            return true;
        }
    }
    return false;
}

// Удаление
void remove(HashTable& ht, const string& number) {
    int index = hashFunction(number, ht.capacity);
    auto& bucket = ht.table[index];
    for (size_t i = 0; i < bucket.size(); ++i) {
        if (bucket[i].number == number) {
            bucket.erase(bucket.begin() + i);
            return;
        }
    }
}

// Печать всей таблицы
void print(const HashTable& ht) {
    cout << "\n--- Содержимое хеш-таблицы ---\n";
    for (int i = 0; i < ht.capacity; ++i) {
        cout << i << ": ";
        for (const auto& p : ht.table[i]) {
            cout << "[" << p.number << " - " << p.name << "] ";
        }
        cout << endl;
    }
}

int main() {
    HashTable ht;
    init(ht);

    int choice;
    string number, name;
    Passport p;

    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Добавить паспорт\n";
        cout << "2. Удалить паспорт\n";
        cout << "3. Поиск паспорта\n";
        cout << "4. Печать таблицы\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Введите номер паспорта: ";
                getline(cin, number);
                cout << "Введите имя клиента: ";
                getline(cin, name);
                insert(ht, {number, name});
                break;
            case 2:
                cout << "Введите номер паспорта для удаления: ";
                getline(cin, number);
                remove(ht, number);
                break;
            case 3:
                cout << "Введите номер паспорта для поиска: ";
                getline(cin, number);
                if (find(ht, number, p))
                    cout << "Найден: " << p.name << endl;
                else
                    cout << "Не найден.\n";
                break;
            case 4:
                print(ht);
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный ввод. Повторите.\n";
        }
    } while (choice != 0);

    return 0;
}