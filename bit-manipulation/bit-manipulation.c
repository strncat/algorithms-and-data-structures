#include <stdio.h>
#include <stdbool.h>

// bit manipulation hacks, different sources

/* Example
 15 = 00000000000000000000000000001111
 
 - clear the two least significant bits 00001100
 - clear bits i = 3 through most significant bit 00000111
 - clear bits 0 through i = 1 00001100
 - number of set bits = 4
 - value of least set bit = 1
 - value of highest set bit = 8
 - clear the least significant bit = 00001110
 - next power of two = 16
 - log2(15) = 3
 - reversing the bits of 15 = 4026531840 (11110000000000000000000000000000)
 - swap each pair of bits (0 and 1), (2 and 3) and so on: swapping 17 010001 => 100010
 */

void print_binary(unsigned int n) {
    for (unsigned i = 1 << 31; i > 0; i = i >> 1) {
        if (i & n) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

bool get_bit(unsigned x, int i) {
    // 1 << i is shifting 1 to the left by i positions (to create a 1 at position i, 00000100000)
    return ((x & (1 << i)) != 0);
}

unsigned set_bit(unsigned x, int i) {
    return x | (1 << i);
}

unsigned clear_bit(unsigned x, int i) {
    // first shift 1 to the left by i positions, negate it to create 111111011111
    unsigned mask = ~ (1 << i);
    return x & mask; // and then & with x to clear the bit at position i
}

unsigned update_bit(unsigned x, int i, int v) {
    x = clear_bit(x, i); // clear bit i
    return x | (v << i); // shift v to align it
}

unsigned int clear_n_least_significant_bits(unsigned x, int n) { // 11011 with n = 2 will be 110000
    return (~0 << n) & x;
}

unsigned clear_bits_i_through_ms(unsigned x, int i) { // clear all bits between i through ms bit inclusive
    unsigned mask = (1 << i) - 1; // if i = 5 we will have 00010000 and then 00001111
    return mask & x;
}

unsigned clear_bits_0_through_i(unsigned x, int i) { // clear all bits between 0 and i inclusive
    unsigned mask = ~ ((1 << (i+1)) - 1); // if i = 5 we will have 00010000 and then 00001111
    return mask & x;
}

unsigned isolate_least_significant_set_bit(unsigned x) {
    return x & ~ (x - 1); // ~x+1 = -x
}

unsigned clear_least_significant_set_bit(unsigned x) {
    return x & (x - 1);
}

unsigned count_set_bits(unsigned x) {
    int count = 0;
    while (x) {
        x = clear_least_significant_set_bit(x);
        count++;
    }
    return count;
}

unsigned int fold_over(unsigned x) { /* 32-bit */
    /* every bit sets the bit immediately to its right */
    x |= (x >> 1);
    /* next it's the bit two over to its right */
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x;
}

unsigned isolate_highest_set_bit(unsigned x) {
    x = fold_over(x); // when folding over we make sure everything is set before the most significant bit
    return (x & ~(x >> 1)); // when we shift and negate, everything will be unset except for the highest bit
}

unsigned next_power_of_two(unsigned x) {
    x = fold_over(x);
    return x + 1;
}

unsigned different_bits(unsigned a, unsigned b) { /* between two ints */
    unsigned int c = a ^ b;
    return count_set_bits(c);
}

unsigned log_2(unsigned x) {
    unsigned l = 0;
    while (x >>= 1) {
        l++;
    }
    return l;
}

/* https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious */
unsigned reverse(unsigned x) {
    unsigned int r = x; // r will be reversed bits of x;
    int s = sizeof(x) * 8 - 1; // extra shift needed at end 31 for 32-bit
    for (x >>= 1; x; x >>= 1) {
        r = r << 1;
        r = r | (x & 1);
        s--;
    }
    r = r << s;
    return r;
}

unsigned swap_bits(unsigned x) {
    unsigned odd = (x & 0xaaaaaaaa) >> 1; // get those odd bits and shift to the right
    unsigned even = (x & 0x55555555) << 1; // same for even, the mask is 01010101
    return (odd | even);
}

int main() {
    unsigned x = 15;
    print_binary(x); // 00000000-00000000-00000000-00001111
    
    printf("clear the 2 right most bits = ");
    print_binary(clear_n_least_significant_bits(x, 2));
    
    printf("clear bits i = 3 through ms = ");
    print_binary(clear_bits_i_through_ms(x, 3));
    
    printf("clear bits 0 through (i = 2) = ");
    print_binary(clear_bits_0_through_i(x, 1));
    
    printf("number of set bits = %u\n", count_set_bits(x));
    
    printf("value of least set bit = %u\n", isolate_least_significant_set_bit(x));
    
    printf("value of highest set bit = %u\n", isolate_highest_set_bit(x));
    
    printf("clear the least significant bit = ");
    print_binary(clear_least_significant_set_bit(x));
    
    printf("next power of two = %u\n", next_power_of_two(x));
    
    printf("log2 = %u\n", log_2(x));
    
    printf("reverse of x = ");
    print_binary(reverse(x));
    
    printf("\nswap each two bits 0 and 1, 2 and 3 and so on: \n");
    print_binary(17);
    print_binary(swap_bits(17));
    return 0;
}
