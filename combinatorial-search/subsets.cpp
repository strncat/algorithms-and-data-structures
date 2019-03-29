#include <iostream>
#include <vector>
#include <set>

// method 1
std::set<std::set<int>> getSubsets(std::vector<int> set, int index) {
    std::set<std::set<int>> allSubsets;
    
    if (set.size() == index) {
        allSubsets.insert(std::set<int>());
    } else {
        allSubsets = getSubsets(set, index + 1);
        int item = set[index];
        std::set<std::set<int>> moreSubsets;
        
        for(auto i = allSubsets.begin(); i != allSubsets.end(); ++i) {
            std::set<int> newSubset = (*i);
            newSubset.insert(item);
            moreSubsets.insert(newSubset);
        }
        allSubsets.insert(moreSubsets.begin(), moreSubsets.end());
    }
    return allSubsets;
}

// method 2
std::set<int> convertIntToSet(int k, std::vector<int> set) {
    std::set<int> subset;
    int index = 0;
    for (int i = k; i > 0; i >>= 1) {
        if (i & 1) {
            subset.insert(set[index]);
        }
        index++;
    }
    return subset;
}

std::set<std::set<int>> getSubsets2(std::vector<int> set) {
    std::set<std::set<int>> allSubsets;
    allSubsets.insert(std::set<int>());
    
    int max = 1 << set.size(); /* number of subsets 2^n */
    for (int k = 0; k < max; k++) {
        std::set<int> subset = convertIntToSet(k, set);
        allSubsets.insert(subset);
    }
    return allSubsets;
}

int main() {
    std::vector<int> set;
    set.push_back(1);
    set.push_back(2);
    set.push_back(3);
    
    // method 1
    std::set<std::set<int>> output = getSubsets(set, 0);
    for(auto i = output.begin(); i != output.end(); ++i) {
        for(auto j = (*i).begin(); j != (*i).end(); ++j) {
            std::cout << *j << " ";
        }
        std::cout << std::endl;
    }
    
    // method 2
    std::set<std::set<int>> output2 = getSubsets2(set);
    for(auto i = output2.begin(); i != output2.end(); ++i) {
        for(auto j = (*i).begin(); j != (*i).end(); ++j) {
            std::cout << *j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
