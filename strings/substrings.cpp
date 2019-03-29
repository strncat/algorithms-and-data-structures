//
//  generate all substrings
//

#include <iostream>
#include <vector>

int main() {

    std::string s = "abc";
    std::vector<std::string> substrings;

    for (int i = 0; i < s.size(); i++) {
        for (int j = 1; j <= s.size() - i; j++) {
            substrings.push_back(s.substr(i, j));
        }
    }

    for (auto i = substrings.begin(); i != substrings.end(); i++) {
        std::cout << *i << std::endl;
    }

    return 0;
}
