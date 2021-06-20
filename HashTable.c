#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/HashTable.h"

HashTable* newHashTable() {

    // allocate space for the hashtable
    HashTable* ht = (HashTable*) malloc(sizeof(HashTable));

    // check if malloc was successful
    if (ht == NULL) {
        fprintf(stderr, "Error: Couldn't allocate space for the hash table.\n");
        exit(-1);
    }

    // allocate sapce for the hashes
    ht->hashes = (Hash*) malloc(sizeof(Hash) * DEFAULT_HASHTABLE_LEN);

    // check if malloc was successful
    if (ht == NULL) {
        fprintf(stderr, "Error: Couldn't allocate space for the hash table's hashes.\n");
        exit(-1);
    }

    // assing the capacity value
    ht->capacity = DEFAULT_HASHTABLE_LEN;

    return ht;
}

unsigned long long _hash(char* name) {

    // store the index as a total
    unsigned long long total = 0;
    int nameLen = 0;

    for (int i = 0; name[i] != '\0'; i++) {

        // get the base by converting the characters from a to numbers
        int base = (unsigned long long) name[i] - 97;

        // add the base to the powers starting from 1 to total
        total += (unsigned long long) pow((double) base, (double) i + 1);

        // increment nameLen to track the length of the name
        if (++nameLen > MAX_NAME_LEN) {
            fprintf(stderr, "Error: Hash name \"%s\" is must be less than %d characters long.\n", name, MAX_NAME_LEN);
            exit(-1);
        }
    }

    // return the produced index
    return total;
}

void setHashTableValue(HashTable* ht, char* name, int value) {
    
    // calculate the index from the name
    unsigned long long index = _hash(name);

    // check if the index is larger than the maximum index allowed
    // if so show an error and exit
    if (index >= MAX_HASHTABLE_LEN) {
        fprintf(stderr, "Error: Index exceeds the maximum allowed within hash table capacity.\n");
        exit(-1);

    // check if there isn't space within current capacity but more can be added
    } else if (index >= ht->capacity) {
        
        // declare a new capacity sufficient to store the current index
        int newCapacity = index + 1;

        // reallocate the hashes
        ht->hashes = (Hash*) realloc(ht->hashes, sizeof(Hash) * newCapacity);

        // check if reallocation was a success
        if (ht->hashes == NULL) {
            fprintf(stderr, "Error: Couldn't reallocate space for index.\n");
            exit(-1);
        }

        // update capacity value
        ht->capacity = newCapacity;

    // check if there exists a value there already.
    // if so free the space
    // this wont need to be checked if the previous else if was ...
    // called since that will ensure that the space is empty
    } else if (ht->hashes[index].name != NULL || ht->hashes[index].index != 0) {
        free(ht->hashes[index].name);
    }

    // now we can safely assign the values at the index
    ht->hashes[index].index = index;
    ht->hashes[index].name = (char *) malloc(sizeof(char) * MAX_NAME_LEN);
    strcpy(ht->hashes[index].name, name);
    ht->hashes[index].value = value;
}

int getValueFromHashTable(HashTable* ht, char* name) {

    // calculate the index from the name
    unsigned long long index = _hash(name);

    // check if the hashtable has the capacity to store the index
    if (index < ht->capacity) {

        // check if the item at index is valid
        // i.e. it's stored index corresponds to the searched index
        if (ht->hashes[index].index != index) {
            fprintf(stderr, "Error: No item at index \"%llu\" with name \"%s\".\n", index, name);
            exit(-1);
        }

        // return the value at the index
        return ht->hashes[index].value;

    } else {
        fprintf(stderr, "Error: Insufficient capacity to store hash index.\n");
        exit(-1);
    }
}

int itemExistsInHashTable(HashTable* ht, char* name) {

    // calculate the index from the name
    unsigned long long index = _hash(name);

    // check if the hashtable has the capacity to store the index
    if (index < ht->capacity) {

        // check if the item at index is valid
        // i.e. it's stored index corresponds to the searched index
        if (ht->hashes[index].index != index) {
            return 0;
        } else {
            // return true
            return 1;
        }

    
    } else {
        fprintf(stderr, "Error: Insufficient capacity to store hash index.\n");
        exit(-1);
    }
}

void freeHashTable(HashTable* ht) {

    // check if we can free memory
    if (ht == NULL) return;

    // loop through hashes and free each hash name
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->hashes[i].name != NULL) {
            free(ht->hashes[i].name);
        }
    }

    // free hashes
    if (ht->hashes != NULL) free(ht->hashes);

    // finally free the hashtable
    free(ht);
}