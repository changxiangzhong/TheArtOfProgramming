#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>

bool string_contains(char* s1, char* s2)
{
    int i, j;
    int sz1 = strlen(s1);
    int sz2 = strlen(s2);

    assert(sz1 > sz2);

    for (i = 0; i <= sz1 - sz2; i++) {
        for (j = 0; j < sz2; j++) {
            if (s1[i + j] != s2[j])
                break;
        }

        if (j == sz2)
            return true;
    }

    return false;
}

int main(int argc, char* argv[])
{
    if(string_contains(argv[1], argv[2])) {
        printf("Contains\n");
    } else {
        printf("Not contains\n");
    }
    return 0;
}
