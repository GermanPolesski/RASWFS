#include <iostream>
using namespace std;

struct Tree {
    int key;
    int num;
    Tree *Left, *Right;
};

Tree* list(int i, int number) {
    Tree *t = new Tree;
    t->key = i;
    t->num = number;
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree *&t, int key, int number) {
    if (!t) {
        t = list(key, number);
        return t;
    }
    Tree *Prev = t;
    while (true) {
        if (key == Prev->key) break;
        if (key < Prev->key) {
            if (!Prev->Left) {
                Prev->Left = list(key, number);
                break;
            }
            Prev = Prev->Left;
        } else {
            if (!Prev->Right) {
                Prev->Right = list(key, number);
                break;
            }
            Prev = Prev->Right;
        }
    }
    return t;
}

Tree* search(Tree* n, int key) {
    if (!n) return NULL;
    if (key < n->key) return search(n->Left, key);
    else if (key > n->key) return search(n->Right, key);
    else return n;
}

Tree* findMin(Tree* t) {
    while (t && t->Left) t = t->Left;
    return t;
}

Tree* delet(Tree* Root, int key) {
    if (!Root) return NULL;
    if (key < Root->key) Root->Left = delet(Root->Left, key);
    else if (key > Root->key) Root->Right = delet(Root->Right, key);
    else {
        if (!Root->Left) {
            Tree* temp = Root->Right;
            delete Root;
            return temp;
        } else if (!Root->Right) {
            Tree* temp = Root->Left;
            delete Root;
            return temp;
        }
        Tree* temp = findMin(Root->Right);
        Root->key = temp->key;
        Root->num = temp->num;
        Root->Right = delet(Root->Right, temp->key);
    }
    return Root;
}

void view(Tree *t, int level) {
    if (t) {
        view(t->Right, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << t->key << " (" << t->num << ")\n";
        view(t->Left, level + 1);
    }
}

int count(Tree *t, int number) {
    if (!t) return 0;
    return (t->num == number) + count(t->Left, number) + count(t->Right, number);
}

void delAll(Tree* t) {
    if (t) {
        delAll(t->Left);
        delAll(t->Right);
        delete t;
    }
}

Tree* makeTree() {
    Tree* Root = NULL;
    int key, number;
    cout << "Конец ввода - отрицательное число\n\n";
    cout << "Введите ключ корня: ";
    cin >> key;
    if (key < 0) return NULL;
    cout << "Введите число корня: ";
    cin >> number;
    Root = insertElem(Root, key, number);
    while (true) {
        cout << "\nВведите ключ: ";
        cin >> key;
        if (key < 0) break;
        cout << "Введите число: ";
        cin >> number;
        insertElem(Root, key, number);
    }
    return Root;
}

int main() {
    setlocale(0, "Russian");
    Tree *Root = NULL;
    int choice, key, number;
    while (true) {
        cout << "1 - Создание дерева\n";
        cout << "2 - Добавление элемента\n";
        cout << "3 - Поиск по ключу\n";
        cout << "4 - Удаление элемента\n";
        cout << "5 - Вывод дерева\n";
        cout << "6 - Подсчет количества чисел\n";
        cout << "7 - Очистка дерева\n";
        cout << "8 - Выход\n";
        cout << "Ваш выбор? ";
        cin >> choice;
        switch (choice) {
            case 1:
                Root = makeTree();
                break;
            case 2:
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите число: ";
                cin >> number;
                insertElem(Root, key, number);
                break;
            case 3: {
                cout << "Введите ключ: ";
                cin >> key;
                Tree* rc = search(Root, key);
                if (rc) cout << "Найденное число: " << rc->num << endl;
                else cout << "Элемент не найден\n";
                break;
            }
            case 4:
                cout << "Введите удаляемый ключ: ";
                cin >> key;
                Root = delet(Root, key);
                break;
            case 5:
                if (Root) {
                    cout << "Дерево повернуто на 90 град. влево:\n";
                    view(Root, 0);
                } else cout << "Дерево пустое\n";
                break;
            case 6:
                cout << "Введите число: ";
                cin >> number;
                cout << "Количество узлов: " << count(Root, number) << endl;
                break;
            case 7:
                delAll(Root);
                Root = NULL;
                break;
            case 8:
                exit(0);
            default:
                cout << "Неверный выбор\n";
        }
    }
}