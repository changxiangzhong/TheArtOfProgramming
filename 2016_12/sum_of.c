#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1024
#define ARR_START_POS 3

int rs[MAX];
int rs_len = 0;

/**
 * Make a decision about the cans[0]
 **/
void sum_of_num(int sum, int rnd, int* cans, int can_len)
{
    int i, j, curr;

    if (sum == 0 && rnd == 0) {
        for(i = 0; i < rs_len; i++) 
            printf("\t%d", rs[i]);

        printf("\n");
        return;
    }

    if (sum <= 0 || rnd <= 0 || can_len <= 0) return;

    curr = cans[0];
    cans[0] = cans[can_len - 1];
    // skip the current one;
    sum_of_num(sum, rnd, cans, can_len - 1);

    // use the curren tone;
    rs[rs_len++] = curr;
    sum_of_num(sum - curr, rnd - 1, cans, can_len - 1);
    rs_len--;

}

int main(int argc, char* argv[])
{
    int sum, i, arr_len, round;
    int array[MAX];

    sum = atoi(argv[1]);
    round = atoi(argv[2]);
    for (i = ARR_START_POS; i < argc; i++) {
        array[i - ARR_START_POS] = atoi(argv[i]);
    }

    arr_len = argc - ARR_START_POS;

    printf("sum = %d, round = %d, arr_len = %d\n", sum, round, arr_len);

    sum_of_num(sum, round, array, arr_len);
}
