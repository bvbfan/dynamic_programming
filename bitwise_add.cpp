#include <assert.h>
#include <iostream>
#include <limits.h>

/**
 * Function to add to integers with bitwise operatrions
 * in case of overflow function returns 0
 * @param[in]  a         integer
 * @param[in]  b         integer
 */
int add(int a, int b)
{
    // found out overflow in two negative ints
    if (a < 0 && b < 0 && !((a & b) & INT_MAX))
        return 0; // overflow

    bool overflow = a >= 0 && b >= 0;
    while (b != 0) {
        int carry = a & b;
        // find out overflow in two positive ints
        if (overflow && ((carry >> (sizeof(a) * 8 -2) & 1)))
            return 0; // overflow
        a ^= b;
        b = carry << 1;
    }
    return a;
}

int main()
{
    assert(add(5, 6) == 11 && "5 + 6 is 11");
    assert(add(-1, 6) == 5 && "-1 + 6 is 5");
    assert(add(-1, -6) == -7 && "-1 + -6 is -7");
    assert(add(INT_MAX, 1) == 0 && "INT_MAX +1 is overflow");
    assert(add(INT_MIN, -1) == 0 && "INT_MIN -1 is overflow");
    assert(add(INT_MAX-1, 1) == INT_MAX && "INT_MAX-1+1 is INT_MAX");
    assert(add(INT_MIN+2, -2) == INT_MIN && "INT_MIN+2 -2 is INT_MIN");
    std::cout << "Tests finishes successfully!\n";
    return 0;
}
