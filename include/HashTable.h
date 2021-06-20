#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 10
#define MAX_HASHTABLE_LEN 100000000
#define DEFAULT_HASHTABLE_LEN 10000

typedef struct hash {
    unsigned long long index;
    char* name;
    int value;
} Hash;

typedef struct hashtable {
    Hash* hashes;
    int capacity;
} HashTable;

HashTable* newHashTable();

unsigned long long _hash(char* str);

void setHashTableValue(HashTable* ht, char* name, int value);

int getValueFromHashTable(HashTable* ht, char* name);

int itemExistsInHashTable(HashTable* ht, char* name);

void freeHashTable(HashTable* ht);

#endif