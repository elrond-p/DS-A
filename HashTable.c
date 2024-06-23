#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 100000

typedef struct entry_t
{
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct
{
   entry_t **entries;
} ht_t;

unsigned int hash(const char *key) 
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i <key_len; ++i) {
        value = value * 37 + key[i];
    }

    value = value % TABLE_SIZE;
    return value;
}

ht_t *ht_create(void)
{
    // allocate for the table
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);
    int i = 0;

    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);
    for (; i < TABLE_SIZE; i++) {
        hashtable->entries[i] = NULL;
    }
    return hashtable;
}

entry_t *ht_pair(const char *key, const char *value)
{
    entry_t *entry = malloc(sizeof(entry) +1 );
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copy the key-value pair to the entry
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next = NULL;
    return entry;
}

void ht_set(ht_t *hashtable, const char *key, const char *value)
{
    unsigned int slot = hash(key);
    entry_t *entry = hashtable->entries[slot];

    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    // iterate over each entry until the end is reached or the key is found
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }
    }

}

void print_ht(ht_t *hashtable)
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]:", i);

        for (;;) {
            printf("%s = %s ", entry->key, entry->value);

            if (entry->next == NULL) {
                break;
            }
            entry = entry->next;
        }
        

        printf("\n");
    }
}
int main(int argc, char **argv)
{
    ht_t *hashtable = ht_create();

    ht_set(hashtable, "key0", "Toyota");
    ht_set(hashtable, "key1", "Honda");
    ht_set(hashtable, "key2", "Ford");
    ht_set(hashtable, "key3", "Chevy");
    ht_set(hashtable, "key4", "Tesla");

    print_ht(hashtable);

    return 0;
}