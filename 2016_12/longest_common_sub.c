#include <stdio.h>
#include <stdlib.h>

int lcs(char* str1, char* str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        i++;
    }

    printf("The longest common substring is [%*.*s]\n", i, i, str1);

    return i;
}

int main(int argc, char* argv[])
{
    lcs(argv[1], argv[2]);
}
