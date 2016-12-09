#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/**
 * Suppose set1 and set2 are ordered sets.
 * */
bool set_contains(int* set1, int sz1, int* set2, int sz2)
{
    int i, j;
    i = j = 0;
    bool last_match;
    while (i < sz1 && j < sz2) {
        if(set2[j] == set1[i]) {
            i++;
            j++;
            last_match = true;
        } else if (set2[j] > set1[i]) {
            i++;
            last_match = false;
        } else {
            return false;
        }
    }

    return last_match;
}

int main(int argc, char* argv[])
{
    int set1[128];
    int sz1;
    int set2[128];
    int sz2;

    int i = 1;
    int offset;

    while (i < argc) {
        int tmp = atoi(argv[i]);
        if (tmp) {
            set1[i - 1] = tmp;
            i++;
        } else {
            offset = ++i;
            break;
        }
    }
    sz1 = i - 2;

    sz2 = argc - sz1 - 2;

    while (i < argc) {
        set2[i - offset] = atoi(argv[i]);
        i++;
    }
    
    printf("set1[] = ");
    for(i = 0; i < sz1; i++) {
        printf("\t%d", set1[i]);
    }

    printf("\nset2[] = ");
    for(i = 0; i < sz2; i++) {
        printf("\t%d", set2[i]);
    }
    if (set_contains(set1, sz1, set2, sz2)) {
        printf("\nMatches!\n");
    } else {
        printf("\nNot matches!\n");
    }
}
