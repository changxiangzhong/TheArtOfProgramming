#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void brutal_force_rotate_string(char* s, int m) {
    int i, j, sz = strlen(s);
    char tmp;
    for (i = 0; i < m; i++) {
        tmp = s[0];

        for (j = 1; j < sz; j++) 
            s[j - 1] = s[j];

        s[sz - 1] = tmp;
    }
}

int main(int argc, char* argv[])
{
    printf("The input string is %s\n", argv[1]);
    brutal_force_rotate_string(argv[1], 5);
    printf("The rotated string is %s\n", argv[1]);
}
