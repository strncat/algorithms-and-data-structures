//
//  generate all distinct combinations of a string
//  given "aabb" print "a", "b", "aa", "bb", "ba", "baa" and "bba", "bbaa"
//

#include <iostream>
#include <string.h>
#include <stack>

void print_stack(std::stack<char> s) {
    std::stack<char> t;
    while (!s.empty()) {
        std::cout << s.top();
        t.push(s.top());
        s.pop();
    }
    while (!t.empty()) {
        s.push(t.top());
        t.pop();
    }
    printf("\n");
}

void combination_core(char *s, int index, int size,
                      std::stack<char> result) {

    // reached a valid combination
    if (size == 0) {
        print_stack(result);
        return;
    }

    // no more characters are left to choose from
    if (index == strlen(s)) {
        return;
    }

    // for each character either select that character or don't
    // (1) select the character str[index]
    result.push(s[index]);
    combination_core(s, index+1, size-1, result); // choose the next character


    // (2) don't select the character str[index]
    result.pop(); // don't forget to pop it as a result of (1)

    // only select the next different character
    while (index < strlen(s) - 1 && s[index] == s[index + 1]) {
        index++;
    }

    combination_core(s, index+1, size, result);
}

int compare( const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

void combination(char *s) {
    std::stack<char> result;

    // sort the string
    qsort(s, strlen(s), sizeof(char), compare);

    for (int i = 1; i <= strlen(s); i++) {
        // combination of size i
        combination_core(s, 0, i, result);
    }
}

int main() {
    char s[5] = "abab";
    combination(s);
    return 0;
}
