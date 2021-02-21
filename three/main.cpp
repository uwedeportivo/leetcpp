#include <iostream>
#include <string>
#include <vector>

// https://leetcode.com/problems/edit-distance/

int minDistance(std::string word1, std::string word2) {
    auto m = word1.size();
    auto n = word2.size();

    auto mx = std::vector<std::vector<int>>(m + 1);

    for (int i = 0; i < m + 1; i++) {
        mx[i] = std::vector<int>(n + 1);
    }

    for (int j = 0; j < n + 1; j++) {
        mx[0][j] = j;
    }

    for (int i = 1; i < m + 1; i++) {
        mx[i][0] = i;

        for (int j = 1; j < n + 1; j++) {
            auto inserts = mx[i][j - 1] + 1;
            auto deletes = mx[i -1][j] + 1;

            int replaces;
            if (word1[i-1] == word2[j-1]) {
                replaces = mx[i-1][j - 1];
            } else {
                replaces = mx[i-1][j - 1] + 1;
            }

            int min = inserts;
            if (deletes < min) {
                min = deletes;
            }
            if (replaces < min) {
                min = replaces;
            }
            mx[i][j] = min;
        }
    }

    return mx[m][n];
}

int main() {
    std::string word1 = "horse";
    std::string word2 = "ros";

    auto minEditDistance = minDistance(word1, word2);

    std::cout << minEditDistance << std::endl;
    return 0;
}
