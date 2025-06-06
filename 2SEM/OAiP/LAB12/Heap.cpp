#include "Heap.h"  // Подключение заголовочного файла с объявлениями
#include <iostream>
#include <iomanip>  // Для форматированного вывода (setw, setfill)

void AAA::print()
{ std::cout << x; }  // Вывод значения переменной x

namespace heap {  // Пространство имен для работы с кучей

    // Создание новой кучи
    Heap create(int maxsize, CMP(*f)(void*, void*))
    { return *(new Heap(maxsize, f)); }  // Возвращает объект кучи (возможна утечка памяти!)

    // Методы класса Heap
    int Heap::left(int ix)  // Левый потомок
    { return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1); }  // -1 если потомка нет

    int Heap::right(int ix)  // Правый потомок
    { return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2); }  // -1 если потомка нет

    int Heap::parent(int ix)  // Родительский узел
    { return (ix + 1) / 2 - 1; }  // Формула для индексации с 0

    void Heap::swap(int i, int j)  // Обмен элементов
    { 
        void* buf = storage[i];    
        storage[i] = storage[j];  
        storage[j] = buf;
    }

    // Восстановление свойств кучи (просеивание вниз)
    void Heap::heapify(int ix)
    { 
        int l = left(ix), r = right(ix), irl = ix;  // irl - индекс наибольшего элемента
        
        // Поиск наибольшего среди узла и его потомков
        if (l > 0)  // Если левый потомок существует
        { 
            if (isGreat(storage[l], storage[ix])) irl = l;  // Левый > текущего
            if (r > 0 && isGreat(storage[r], storage[irl])) irl = r;  // Правый > наибольшего
            if (irl != ix)  // Если найден больший потомок
            { 
                swap(ix, irl);  // Меняем местами
                heapify(irl);   // Рекурсивно обрабатыем поддерево
            }
        }
    }

    // Вставка элемента в кучу
    void Heap::insert(void* x)
    { 
        int i;  // Индекс нового элемента
        if (!isFull())  // Проверка переполнения (isFull должна быть определена)
        { 
            storage[i = ++size - 1] = x;  // Добавление в конец
            // Просеивание вверх
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            { 
                swap(parent(i), i);  // Обмен с родителем
                i = parent(i);       // Переход к родителю
            }
        }
    }

    // Извлечение максимального элемента (корня)
    void* Heap::extractMax()
    { 
        void* rc = nullptr;
        if (!isEmpty())  // Проверка пустоты (isEmpty должна быть определена)
        { 
            rc = storage[0];         // Сохраняем корень
            storage[0] = storage[size - 1];  // Последний элемент -> в корень
            size--;                   // Уменьшаем размер
            heapify(0);               // Восстанавливаем свойства кучи
        } 
        return rc;
    }

    // Извлечение минимального элемента (неэффективно, поиск по листьям)
    void* Heap::extractMin()
    { 
        void* rc = nullptr;
        if (!isEmpty())
        {
            int minIndex = size / 2;  // Минимум ищется во второй половине (листья)
            // Поиск минимального элемента среди листьев
            for (int i = minIndex + 1; i < size; ++i)
                if (isLess(storage[i], storage[minIndex]))
                    minIndex = i;
            rc = extractI(minIndex);  // Извлечение по найденному индексу
        }
        return rc;
    }

    // Извлечение элемента по произвольному индексу
    void* Heap::extractI(int index)
    { 
        if (index < 0 || index >= size) return nullptr;  // Проверка корректности индекса
        
        void* rc = storage[index];  // Сохраняем элемент
        
        // Если элемент последний - просто уменьшаем размер
        if (index == size - 1) {
            size--;
            return rc;
        }
        
        // Замена удаляемого элемента последним
        storage[index] = storage[size - 1];
        size--;
        
        int current = index;
        // Просеивание вверх (если элемент больше родителя)
        while (current > 0) {
            int p = parent(current);
            if (isGreat(storage[current], storage[p])) {
                swap(p, current);
                current = p;
            } else break;  // Условие кучи восстановлено
        }
        
        // Если не было просеивания вверх - просеиваем вниз
        if (current == index)
            heapify(index);
            
        return rc;
    }

    // Слияние двух куч (текущей и переданной)
    void Heap::merge(Heap& other) {
        // Проверка необходимости расширения памяти
        if (size + other.size > maxSize) {
            int newMaxSize = size + other.size + 10;  // Новый размер с запасом
            void** newStorage = new void*[newMaxSize];  // Выделение новой памяти
            
            // Копирование текущих элементов
            std::copy(storage, storage + size, newStorage);
            
            // Замена старого хранилища
            delete[] storage;
            storage = newStorage;
            maxSize = newMaxSize;
        }
        
        // Копирование элементов из другой кучи
        for (int i = 0; i < other.size; ++i) {
            storage[size + i] = other.storage[i];
        }
        size += other.size;  // Обновление размера
        
        // Построение кучи за O(n)
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
        
        other.size = 0;  // Очистка другой кучи (память не освобождается!)
    }

    // Визуализация кучи в виде дерева
    void Heap::scan(int i) const  // Параметр 'i' не используется
    { 
        int probel = 20;  // Начальный отступ
        std::cout << '\n';
        if (size == 0)  // Проверка пустоты
            std::cout << "Куча пуста";
        
        // Построчный вывод элементов
        for (int u = 0, y = 0; u < size; u++) {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();  // Преобразование и вывод (опасно!)
            
            // Перевод строки при завершении уровня
            if (u == y) { 
                std::cout << '\n'; 
                // Расчет следующего уровня
                if (y == 0) y = 2;  
                else y += y * 2;  // Уровни: 0, 2, 6, 14...
            }
            probel /= 2;  // Уменьшение отступа
        }
        std::cout << '\n';
    }
}
