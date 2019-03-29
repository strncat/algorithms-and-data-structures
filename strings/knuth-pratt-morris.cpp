//
//  Knuth-Morris-Pratt algorithm
//  Source http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/kmpen.htm
/*
 Instead of naively re-matching at every single index in the text, 
 KMP shifts the string by using previously stored information about the pattern.
 
 Text:    abxxabzzzzzavzzabxxabyy
 Pattern: abxxaby
 
 We match successfully abxxab and then we get stuck at index = 6 (y != z)
 Instead of naively re-trying to match starting at index 2 in the text, we use 
 some previously computed information:

 For the matched part of length 6 characters, the longest border is of length 2
 (a border is a proper suffix and a proper prefix) so now we shift the pattern by 
 (6 - 2 = 4) steps. "The shift distance is determined by the widest border 
 of the matching prefix of p"

 Text:    abxxabzz
 Pattern:     abxxabyy
 
 and we resume the comparison at index 5!
 
 Now, the question is how to pre-calculate the widest borders array?
*/


#include <iostream>
#include <assert.h>

int naive_string_matching(std::string text, std::string pattern) {
    int n = (int) text.length();
    int m = (int) pattern.length();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m && i + j < n; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) { // match found
            return i; // first match
        }
    }
    return -1;
}

void compute_border_array(std::string p, int *b, int m) {
    // ababaa the widest border array is [-1 0 0 1 2 3 1]
    // j is the widest border of p[0] ... p[i]
    // "a": widest border = 0 (remember proper suffix/prefix)
    // "ab": widest border = 0
    // 'aba": widest border = 1 and so on

    // A border of width j can be extended by p[i], if p[j] = p[i]. If not,
    // the next-widest border is examined by setting j = b[j]

    // starting from the begining
    // b[0] = -1
    // i = 0, j = -1, b[1] = 0
    // i = 1, j = 0, 'ab' => p[i] != p[j] so j=b[j]=-1; i++ j++ b[2]=0
    // i = 2, j = 0, 'aba' => can we extend the border by adding 'a'? yes p[i] = p[j] so i++ j++ b[3]=1
    // i = 3, j = 1, 'abab' => can we extend the border by adding 'b'? yes p[i] = p[j] so i++ j++ b[4]=2
    // i = 4, j = 2, 'ababa' => can we extend the border by adding 'a'? yes p[i] = p[j] so i++ j++ b[5] = 3
    // i = 5, j = 3, 'ababaa' => can we extend the border by adding 'b'? no p[i] != p[j]
    // in this case j=b[j]=1 why??
    // and we compare p[i]==p[j]? no we again set j=b[j]=0 so that b[6]=1

    int i = 0, j = -1;
    b[i] = j;
    while (i < m) {
        while (j >= 0 && p[i] != p[j]) {
            j = b[j];
        }
        i++;
        j++; // After increasing j in each case j is the width of the widest border of p[0] ... p[i]
        b[i] = j; // This value is written to b[i]
        //printf("new b[i] = j b[%d] = %d\n", i, j);
    }
}

int knuth_morris_pratt(std::string t, std::string p) {
    int m = (int) p.length();
    int n = (int) t.length();
    // b will hold the widest border at each index in the pattern
    int *b = new int[m + 1];
    compute_border_array(p, b, m);

    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && t[i] != p[j]) {
            j = b[j];
        }
        i++;
        j++;
        if (j == m) { // a match
            return i-j;
            //j=b[j]; //continue searcing
        }
    }
    return -1;
}

void tests() {
    //knuth_morris_pratt("abxxabzzzzzavzzabxxabyy", "ababaa");
    std::string text = "hello world !!!";
    std::string s[4] = {"ll", "bbc", "world", "!"};
    int correct[4] = {2, -1, 6, 12};
    int n = 4;
    for (int i = 0; i < n; i++) {
        int index = knuth_morris_pratt(text, s[i]);
        assert(index == correct[i]);
    }
}

int main() {
    tests();
    return 0;
}
