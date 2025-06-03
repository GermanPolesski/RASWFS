#ifndef HASH_H
#define HASH_H

#define HASHDEL (void*) -1

struct Object
{ 
    void** data;
    Object(int, int(*)(void*));
    int size;  int N;
    int(*getKey)(void*); 	 
    bool insert(void*);
    int searchInd(int key); 	
    void* search(int key);
    void* deleteByKey(int key);    
    bool deleteByValue(void*);
    void scan(void(*f)(void*));
};

extern void* DEL;  // Declaration

Object create(int size, int(*getkey)(void*));

#endif // HASH_H