//
//  main.cpp
//  BigNumber
//
//  Source: Programming Challenges
//
//

#include <iostream>

#define MAXDIGITS 1000
#define PLUS +1
#define MINUS -1

typedef struct bignum {
    char digits[MAXDIGITS];
    int signbit;
    int lastdigit; // index of last digit
} bignum;

void subtract_bignum(bignum *a, bignum *b, bignum *c);

void print_bignum(bignum *n) {
    if (n->signbit == -1) { printf("- "); }
    for (int i = n->lastdigit; i >= 0; i--) {
        printf("%c", n->digits[i]+'0');
    }
    printf("\n");
}

void int_to_bignum(int s, bignum *n) {
    if (s >= 0) { n->signbit = PLUS; } else { n->signbit = MINUS; }

    for (int i = 0; i < MAXDIGITS; i++) {
        n->digits[i] = (char) 0;
    }
    n->lastdigit = -1;
    int t = abs(s);

    while (t > 0) {
        n->lastdigit++;
        n->digits[n->lastdigit] = t % 10;
        t /= 10;
    }
    if (s == 0) { n->lastdigit = 0; }
}

void initialize_bignum(bignum *n) {
    int_to_bignum(0, n);
}


void zero_justify(bignum *n) {
    while (n->lastdigit > 0 && n->digits[n->lastdigit] == 0) {
        n->lastdigit--;
    }
    if (n->lastdigit == 0 && n->digits[0] == 0) { // just to avoid -0
        n->signbit = PLUS;
    }
}

void digit_shift(bignum *n, int d) { // multiply n by 10^d
    if ((n->lastdigit == 0) && (n->digits[0] == 0)) { return; }
    for (int i = n->lastdigit; i >= 0; i--) {
        n->digits[i+d] = n->digits[i];
    }
    for (int i = 0; i < d; i++) {
        n->digits[i] = 0;
    }
    n->lastdigit += d;
}

int compare_bignum(bignum *a, bignum *b) { // is a larger than b?
    // different signs, easy case
    if ((a->signbit == MINUS) && (b->signbit == PLUS)) { return (PLUS); }
    if ((a->signbit == PLUS) && (b->signbit == MINUS)) { return (MINUS); }

    // compare the number of digits
    if (b->lastdigit > a->lastdigit) { return (PLUS * a->signbit); }
    if (a->lastdigit > b->lastdigit) { return (MINUS * a->signbit); }

    // both have the same sign
    for (int i = a->lastdigit; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) { return (MINUS * a->signbit); }
        if (b->digits[i] > a->digits[i]) { return(PLUS * a->signbit); }
    }
    return 0;
}

void add_bignum(bignum *a, bignum *b, bignum *c) {
    initialize_bignum(c);

    // same sign
    if (a->signbit == b->signbit) {
        c->signbit = a->signbit;
    // different signs
    } else {
        if (a->signbit == MINUS) {
            a->signbit = PLUS; // make them both +, b > a so b-a
            subtract_bignum(b, a, c);
            a->signbit = MINUS;
        } else {
            b->signbit = PLUS;
            subtract_bignum(a, b, c); // a > b so a-b
            b->signbit = MINUS;
        }
        return;
    }
    c->lastdigit = std::max(a->lastdigit, b->lastdigit)+1;
    int carry = 0;
    for (int i = 0; i <= c->lastdigit; i++) {
        c->digits[i] = (char) (carry + a->digits[i] + b->digits[i]) % 10;
        carry = (carry + a->digits[i] + b->digits[i]) / 10;
    }
    zero_justify(c);
}

void subtract_bignum(bignum *a, bignum *b, bignum *c) {
    initialize_bignum(c);
    //
    if (a->signbit == MINUS || b->signbit == MINUS) {
        b->signbit = -1 * b->signbit;
        add_bignum(a, b, c);
        b->signbit = -1 * b->signbit;
        return;
    }
    // if b is larger flip the order
    if (compare_bignum(a, b) == PLUS) {
        subtract_bignum(b, a, c);
        c->signbit = MINUS;
        return;
    }
    c->lastdigit = std::max(a->lastdigit, b->lastdigit);
    int borrow = 0;
    for (int i = 0; i <= c->lastdigit; i++) {
        int v = a->digits[i] - borrow - b->digits[i];
        if (a->digits[i] > 0) {
            borrow = 0;
        }
        if (v < 0) {
            borrow = 1;
            v = v + 10;
        }
        c->digits[i] = (char) v%10;
    }
    zero_justify(c);
}

void multiply_bignum(bignum *a, bignum *b, bignum *c) {
    initialize_bignum(c);
    c->signbit = a->signbit * b->signbit;

    bignum row = *a;
    bignum temp;
    for (int i = 0; i <= b->lastdigit; i++) {
        for (int j = 1; j <= b->digits[i]; j++) {
            add_bignum(c, &row, &temp);
            *c = temp;
        }
        digit_shift(&row, 1);
    }
    zero_justify(c);
}

void divide_bignum(bignum *a, bignum *b, bignum *c) {
    initialize_bignum(c);
    c->signbit = a->signbit * b->signbit;

    int asign = a->signbit;
    int bsign = b->signbit;

    a->signbit = PLUS;
    b->signbit = PLUS;

    bignum row, tmp;
    initialize_bignum(&row);
    initialize_bignum(&tmp);

    c->lastdigit = a->lastdigit;

    for (int i = a->lastdigit; i >= 0; i--) {
        digit_shift(&row,1);
        row.digits[0] = a->digits[i];
        c->digits[i] = 0;
        while (compare_bignum(&row,b) != PLUS) {
            c->digits[i]++;
            subtract_bignum(&row,b,&tmp);
            row = tmp;
        }
    }
    zero_justify(c);
    a->signbit = asign;
    b->signbit = bsign;
}

int main() {
    bignum a;
    a.signbit = PLUS;
    a.digits[0] = 2;
    a.digits[1] = 3;
    a.digits[2] = 1;
    a.lastdigit = 2;
    print_bignum(&a);

    bignum b;
    b.signbit = PLUS;
    b.digits[0] = 5;
    b.digits[1] = 6;
    b.lastdigit = 1;
    print_bignum(&b);

    printf("add:\n");
    bignum c;
    add_bignum(&a, &b, &c);
    print_bignum(&c);

    printf("subtract:\n");
    bignum d;
    subtract_bignum(&a, &b, &d);
    print_bignum(&d);

    printf("multiply:\n");
    bignum e;
    multiply_bignum(&a, &b, &e);
    print_bignum(&e);

    printf("divide:\n");
    bignum f;
    divide_bignum(&a, &b, &f);
    print_bignum(&f);

    return 0;
}
