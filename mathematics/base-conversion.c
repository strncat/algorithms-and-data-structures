//
//  Simple Base Conversion
//

#include <iostream>
#include <stdio.h>
#include <algorithm>

std::string changeBase(int x, int b) {
    std::string ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string s = "";
    while (x/b) {
        s = ascii[x%b] + s;
        x = x/b;
    }
    if (x > 0) { // last remainder
        s = ascii[x%b] + s;
        x = x/b;
    }
    return s;
}

int main() {
    int b = 13;
    for (int i = 3000; i <= 5000; i+=100) {
        printf("%s\n", changeBase(i, b).c_str());
    }
    return 0;
}
