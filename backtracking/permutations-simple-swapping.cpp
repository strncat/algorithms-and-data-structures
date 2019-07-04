//
// a string example
//

/*
          abc
    /      |       \ outer loop index=0, swap (0, 0), (0, 1), (0, 2) (3 branches)
   /       |        \
  abc      bac      cba
 /  \      /  \     /  \ recursive call index=1, swap (1,1), swap(1,2) for the first branch (abc)
abc acb  bac  bca  cba cab
 
*/

#include <iostream>

void swap(char *a, char *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *s, int index) {
    if (s[index] == '\0') {
        printf("%s\n", s);
        return;
    }
    for (int i = index; s[i] != '\0'; i++) {
        swap(&s[i], &s[index]);
        permute(s, index + 1);
        swap(&s[i], &s[index]);
    }
}

int main() {
    char s[4] = "abc";
    permute(s, 0);
    return 0;
}

