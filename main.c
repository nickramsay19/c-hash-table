#include <stdio.h>

#include "include/HashTable.h"

int main(int argc, char **argv) {
    HashTable* ht = newHashTable();

    setHashTableValue(ht, "cat", 6);
    setHashTableValue(ht, "dog", 64);
    setHashTableValue(ht, "mynam", 16);

    int cat, dog, bat, jeff;

    if (itemExistsInHashTable(ht, "cat")) 
        cat = getValueFromHashTable(ht, "cat");
    if (itemExistsInHashTable(ht, "dog")) 
        dog = getValueFromHashTable(ht, "dog");
    if (itemExistsInHashTable(ht, "bat")) 
        bat = getValueFromHashTable(ht, "bat");
    if (itemExistsInHashTable(ht, "mynam")) 
        jeff = getValueFromHashTable(ht, "mynam");

    printf("cat: %d\ndog: %d\nbat: %d\njeff: %d\n", cat, dog, bat, jeff);

    // free the hash table
    freeHashTable(ht);

    // return success
    return 0;
}