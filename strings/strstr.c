//
// strstr returns a pointer to the first ocurrence of sub in the string
//

#include <stdio.h>
#include <string.h>

const char* strstr_m(const char *s, const char *sub) { // const, mutable pointer to an immutable string
    if (*sub == 0) { return s; }

    for (; *s != 0; s++) { // *s != 0 or *s != '\0'

        if (*s != *sub) {
            continue;
        }
        // start at this position start searching for sub
        const char *a = s;
        const char *b = sub;
        while (*a == *b && *a != 0 && *b != 0) {
            a++;
            b++;
        }
        if (*b == 0) { // string was found
            return s;
        }
        // not found, continue looking at s+1
    }
    return (char *) 0;
}

void tests() {
    char s[18] = "Hello World Nemo!";
    char subs[][7] = {"Hey", "Hello", "!", "W", "H", "Nemo!", ""};
    for (int i = 0; i < 7; i++) {
        const char *p = strstr(s, subs[i]);
        const char *m = strstr_m(s, subs[i]);
        if (p == m) {
            printf("correct %s %s\n", p, m);
        } else {
            printf("incorrect %s %s\n", p, m);
        }
    }
}

int main() {
    tests();
    return 0;
}
