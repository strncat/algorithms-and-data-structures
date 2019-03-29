//
//  Permutations with STL
//
//  Created by FB on 3/12/16.
//  Copyright © 2016 Fatima B. All rights reserved.
//

#include <iostream>

int main() {
    std::string s = "abc";
    do {
        std::cout << s << std::endl;
    } while (next_permutation(s.begin(), s.end()));
    return 0;
}
