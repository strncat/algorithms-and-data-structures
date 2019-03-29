//
//  generate all combinations of a string
//  given "abc" print "a", "b", "c", "ab", "ac", "bc" and "abc"
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
    combination_core(s, index+1, size, result);
}

void combination(char *s) {
    std::stack<char> result;

    for (int i = 1; i <= strlen(s); i++) {
        // combination of size i
        combination_core(s, 0, i, result);
    }
}

int main() {
    char s[4] = "abc";
    combination(s);
    return 0;
}
