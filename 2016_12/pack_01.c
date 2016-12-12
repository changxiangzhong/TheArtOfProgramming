#include <stdio.h>
#include <stdlib.h>

#define MAX 128

typedef struct {
    int size;
    int value;
} Item;

int maximize_price(Item* items, int item_cnt, int capacity, int round)
{
    Item swap;
    int i, tmp, max = 0;
    if (round == 1) {
        for(i = 0; i < item_cnt; i++) {
            if(items[i].size <= capacity && items[i].value >= max) {
                max = items[i].value;
            }
        }
        return max;
    }

    max = maximize_price(items, item_cnt, capacity, round - 1);

    for (i = 0; i < item_cnt; i++) {
        if (items[i].size > capacity) {// We can't fit this item
            continue;
        }

        tmp = items[i].value;
        
        // swap the current item to tail of the queue
        swap = items[i];
        items[i] = items[item_cnt - 1];
        items[item_cnt - 1] = swap;

        tmp += maximize_price(items, item_cnt - 1, capacity - swap.size, round - 1);
        // swap back
        swap = items[i];
        items[i] = items[item_cnt - 1];
        items[item_cnt - 1] = swap;

        if (tmp > max) {
            max = tmp;
        }
    }

    return max;
}

int main(int argc, char* argv[])
{
    int capacity, rnd, j;
    Item items[MAX];
    int item_cnt = 0;

    capacity = atoi(argv[1]);
    rnd = atoi(argv[2]);
    
    item_cnt = (argc - 3) / 2;

    for (j = 3; j < argc; j += 2) {
        items[(j - 3) / 2].size = atoi(argv[j]);
        items[(j - 3) / 2].value = atoi(argv[j + 1]);
    }

    printf("package_capacity = %d\nround = %d\n", capacity, rnd);

    for(j = 0; j < item_cnt; j++) {
        printf("item[%d].size = %d, item[%d].value = %d\n", j, items[j].size, j, items[j].value);
    }

    int max = maximize_price(items, item_cnt, capacity, rnd);
    printf("The max capacity is %d\n", max);
}
