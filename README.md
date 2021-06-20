# c-hash-table
> Created by Nicholas Ramsay

This is my first attempt at reproducing a hash table data structure without having access to external information. This ought to be a first draft to a process wherein I learn the best practices in reconstructing the hash table data structure.

So far, this implementation has awful memory management. At times, it can take up to 0.5 GB of space just for the Hash table at maximum capacity. This will be impproved with better hash functions.

## Todo
* reallocate space for larger hash indices