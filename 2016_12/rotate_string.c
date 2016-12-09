#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * [from] is includsive
 * [to] is exclusive
 **/
void reverse_string(char* s, int from, int to)
{
    int st; // step
    char tmp;
    for(st = 0; st < (to - from)/2; st++) {
        tmp = s[from + st];
        s[from + st] = s[to - 1 - st];
        s[to - 1 - st] = tmp;
    }
}

void left_rotate_string(char* s, int m) {
    int sz = strlen(s);
    m %= sz;
    reverse_string(s, 0, m);
    reverse_string(s, m, sz);
    reverse_string(s, 0, sz);
}

int main(int argc, char* argv[])
{
    printf("The input string is %s\n", argv[1]);
    left_rotate_string(argv[1], 5);
    printf("The rotated string is %s\n", argv[1]);
}
