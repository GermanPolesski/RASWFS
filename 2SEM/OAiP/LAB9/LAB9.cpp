#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
using namespace std;

const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address {
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address *next;
    Address *prev;
};

void insert(Address *e, Address **phead, Address **plast) {
    if (*plast == NULL) {
        e->next = NULL;
        e->prev = NULL;
        *plast = e;
        *phead = e;
        return;
    }
    Address *p = *plast;
    p->next = e;
    e->next = NULL;
    e->prev = p;
    *plast = e;
}

Address* setElement() {
    Address* temp = new Address();
    if (!temp) {
        cerr << "Ошибка выделения памяти";
        return NULL;
    }
    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE, '\n');
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE, '\n');
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void outputList(Address **phead, Address **plast) {
    Address *t = *phead;
    while (t) {
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << endl;
}

void find(char name[NAME_SIZE], Address **phead) {
    Address *t = *phead;
    while (t) {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
        cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address **phead, Address **plast) {
    Address *t = *phead;
    while (t) {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t) {
        cerr << "Имя не найдено" << endl;
        return;
    }
    if (*phead == t) {
        *phead = t->next;
        if (*phead)
            (*phead)->prev = NULL;
        else
            *plast = NULL;
    } else {
        t->prev->next = t->next;
        if (t != *plast)
            t->next->prev = t->prev;
        else
            *plast = t->prev;
    }
    delete t;
    cout << "Элемент удален" << endl;
}

void writeToFile(Address **phead) {
    Address *t = *phead;
    FILE *fp = fopen("mlist", "wb");
    if (!fp) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    cout << "Сохранение в файл" << endl;
    while (t) {
        fwrite(t, sizeof(Address), 1, fp);
        t = t->next;
    }
    fclose(fp);
}

void readFromFile(Address **phead, Address **plast) {
    FILE *fp = fopen("mlist", "rb");
    if (!fp) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    while (*phead) {
        *plast = (*phead)->next;
        delete *phead;
        *phead = *plast;
    }
    *phead = *plast = NULL;
    cout << "Загрузка из файла" << endl;
    while (true) {
        Address *t = new Address();
        if (fread(t, sizeof(Address), 1, fp) != 1) {
            delete t;
            break;
        }
        insert(t, phead, plast);
    }
    fclose(fp);
}

Address* AddEx(int x) {
    Address* temp = new Address();
    if (!temp) {
        cerr << "Ошибка выделения памяти!\n";
        return nullptr;
    }
    
    snprintf(temp->name, NAME_SIZE, "%d", x);
    strcpy(temp->city, "");
    
    temp->next = NULL;
    temp->prev = NULL;
    
    return temp;
}

int menu() {
    int c;
    cout << "\n1. Ввод имени\n2. Удаление имени\n3. Вывод на экран\n4. Поиск\n5. Сохранить\n6. Загрузить\n7. Выход\n8. AddEx()\n";
    do {
        cout << "Ваш выбор: ";
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (c < 1 || c > 8);
    return c;
}

int main() {
    Address *head = NULL;
    Address *last = NULL;
    setlocale(LC_CTYPE, "Rus");
    
    while (true) {
        switch (menu()) {
            case 1:
                insert(setElement(), &head, &last);
                break;
                
            case 2: {
                char dname[NAME_SIZE];
                cout << "Введите имя: ";
                cin.getline(dname, NAME_SIZE, '\n');
                delet(dname, &head, &last);
                break;
            }
                
            case 3:
                outputList(&head, &last);
                break;
                
            case 4: {
                char fname[NAME_SIZE];
                cout << "Введите имя: ";
                cin.getline(fname, NAME_SIZE, '\n');
                find(fname, &head);
                break;
            }
                
            case 5:
                writeToFile(&head);
                break;
                
            case 6:
                readFromFile(&head, &last);
                break;
                
            case 7:
                exit(0);
            case 8: {
                int x;
                cout << "Введите x: ";
                cin >> x;
                Address* newElement = AddEx(x);
                if (newElement) {
                    insert(newElement, &head, &last); 
                }
                break;
            }
        }
    }
    return 0;
}