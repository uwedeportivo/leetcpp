#include <iostream>
#include <vector>

// https://leetcode.com/problems/candy/

int Candy(const std::vector<int> &ratings) {
    int n = ratings.size();

    if (n == 0) {
        return 0;
    }

    std::vector<int> candies(n);

    candies[0] = 1;
    int i = 1;
    while (i < n) {
        if (ratings[i - 1] < ratings[i]) {
            // climbing
            candies[i] = candies[i-1]+1;
            i++;
        } else if (ratings[i-1] > ratings[i]) {
            // descending
            int descend_start = i-1;
            while (i < n && ratings[i-1] > ratings[i]) {
                i++;
            }
            candies[i-1] = 1;
            for (int j = i-2; j > descend_start; j--) {
                candies[j] = candies[j+1]+1;
            }
            if (candies[descend_start] < candies[descend_start+1]+1) {
                candies[descend_start] = candies[descend_start+1]+1;
            }
        } else {
            candies[i] = 1;
            i++;
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += candies[i];
    }
    return sum;
}

int main() {
    // expected 5
    std::vector<int> ratings{1, 0, 1};
    std::cout << Candy(ratings) << std::endl;

    // expected 4
    ratings = {1, 2, 2};
    std::cout << Candy(ratings) << std::endl;

    // expected 7
    ratings = {1,3,2,2,1};
    std::cout << Candy(ratings) << std::endl;

    // expected 11
    ratings = {1,3,4,5,2};
    std::cout << Candy(ratings) << std::endl;
    return 0;
}
