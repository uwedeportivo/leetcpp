#include <iostream>

// https://leetcode.com/problems/number-of-digit-one/

int num_digits(int n) {
    int x = n;
    int count = 0;

    while (x != 0) {
        ++count;
        x /= 10;
    }
    return count;
}

unsigned long count_digit_one(int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long count = 0;
    int nd = num_digits(n);

    unsigned long block_size = 1;
    unsigned long block_size_div_ten;
    for (int i = 1; i <= nd; ++i) {
        block_size_div_ten = block_size;
        block_size *= 10;
        unsigned long num_blocks = (n + 1) / block_size;
        unsigned long remainder = (n + 1) % block_size;

        count += block_size_div_ten * num_blocks;
        if (remainder >= 2 * block_size_div_ten) {
            count += block_size_div_ten;
        } else if (remainder > block_size_div_ten) {
            count += remainder - block_size_div_ten;
        }
    }

    return count;
}

int main() {
    std::cout << count_digit_one(1410065408) << std::endl;
    return 0;
}
