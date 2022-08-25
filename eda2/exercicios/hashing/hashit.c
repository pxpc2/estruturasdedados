#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(x) (x.key)
#define null(x) (key(table[x]) == key(NULL_ITEM))

typedef struct
{
    char *key;
    int index;
} Item;

static Item *table;
static Item NULL_ITEM = {0, -1};
static int M = 20 * 101;

int hash(char *string);
void init_table();

void init_table()
{
    table = malloc(sizeof(Item) * M);
    table->key = malloc(sizeof(char)*16);
    for (int i = 0; i < M; i++)
        table[i] = NULL_ITEM;
}

int hash(char *string)
{
    int r = 0, len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        short k = string[i];
        r += (k * (i+1));
    }
    return (19 * r) % 101;
}

int find_index(char *string)
{
    int i = hash(string), j = 1;
    while (!null(i))
    {
        if (strcmp(string, table[i].key) == 0)
            return table[i].index;
        else
        {
            if (++j > 20) break;
            i = (i + j*j + 23*j) % 101;
        }
    }
    return -1;
}