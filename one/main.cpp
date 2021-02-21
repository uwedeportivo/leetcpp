#include <iostream>
#include <vector>

// https://leetcode.com/problems/container-with-most-water/

class Solution {
public:
    static int maxArea(const std::vector<int>& height) {
        size_t i = 0;
        size_t j = height.size() - 1;
        int max_area = 0;

        while (i < j) {
            if (height[i] < height[j]) {
                auto area = (j - i) * height[i];
                if (area > max_area) {
                    max_area = area;
                }
                i++;
            } else {
                auto area = (j - i) * height[j];
                if (area > max_area) {
                    max_area = area;
                }
                j--;
            }
        }
        return max_area;
    }
};

int main() {
    Solution s;
    std::vector<int> height1{1,8,6,2,5,4,8,3,7};

    std::cout << s.maxArea(height1);

    std::vector<int> height2{1,1};

    std::cout << s.maxArea(height2);

    std::vector<int> height3{4,3,2,1,4};

    std::cout << s.maxArea(height3);

    std::vector<int> height4{1,2,1};

    std::cout << s.maxArea(height4);

    return 0;
}
