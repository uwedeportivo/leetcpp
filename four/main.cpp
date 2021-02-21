#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

// https://leetcode.com/problems/max-points-on-a-line/

struct Slope {
    long dx;
    long dy;

    bool operator==(const Slope &other) const
    { return dy * other.dx == other.dy * dx;
    }
};

namespace std {
    template <>
    struct hash<Slope>
    {
        std::size_t operator()(const Slope& k) const
        {
            using std::size_t;
            using std::hash;
            using std::gcd;

            int g = gcd(k.dx, k.dy);
            int dx = k.dx / g;
            int dy = k.dy / g;
            return ((hash<int>()(dx)
                     ^ (hash<int>()(dy) << 1)) >> 1);
        }
    };
}

struct Point {
    int x;
    int y;

    bool operator==(const Point &other) const
    { return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Point>
    {
        std::size_t operator()(const Point& k) const
        {
            using std::size_t;
            using std::hash;

            return ((hash<int>()(k.x)
                     ^ (hash<int>()(k.y) << 1)) >> 1);
        }
    };
}

class Solution {
public:
    static int maxPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();
        if (n == 0) {
            return 0;
        }
        int mp = 0;

        std::unordered_map<Point, int> counts;

        for (int i = 0; i < n; i++) {
            Point p {.x = points[i][0], .y = points[i][1]};
            counts[p]++;
        }

        if (counts.size() == 1) {
            Point p {.x = points[0][0], .y = points[0][1]};

            return counts[p];
        }

        for (int i = 0; i < n ; i++) {
            std::unordered_map<Slope, int> sls;
            Point p {.x = points[i][0], .y = points[i][1]};
            int count = counts[p];

            int vp = count;

            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }

                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    continue;
                }

                // special case of vertical lines
                if (points[i][0] == points[j][0]) {
                    vp++;
                    if (mp < vp) {
                        mp = vp;
                    }
                } else {
                    Slope sl {.dx = points[i][0] - points[j][0], .dy = points[i][1] - points[j][1]};
                    int lp = sls[sl];

                    if (lp == 0) {
                        lp = count;
                    }
                    lp++;
                    sls[sl] = lp;

                    if (mp < lp) {
                        mp = lp;
                    }
                }
            }
        }
        return mp;
    }
};

int main() {
    // expected 4
    std::vector<std::vector<int>> points = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    std::cout << Solution::maxPoints(points) << std::endl;

    // exptected 3
    points = {{1,1},{2,2},{3,3}};
    std::cout << Solution::maxPoints(points) << std::endl;

    // expected 6
    points = {{15,12},{9,10},{-16,3},{-15,15},{11,-10},{-5,20},{-3,-15},{-11,-8},{-8,-3},
              {3,6},{15,-14},{-16,-18},{-6,-8},{14,9},{-1,-7},{-1,-2},{3,11},{6,20},{10,-7},
              {0,14},{19,-18},{-10,-15},{-17,-1},{8,7},{20,-18},{-4,-9},{-9,16},{10,14},
              {-14,-15},{-2,-10},{-18,9},{7,-5},{-12,11},{-17,-6},{5,-17},{-2,-20},{15,-2},
              {-5,-16},{1,-20},{19,-12},{-14,-1},{18,10},{1,-20},{-15,19},{-18,13},{13,-3},
              {-16,-17},{1,0},{20,-18},{7,19},{1,-6},{-7,-11},{7,1},{-15,12},{-1,7},{-3,-13},
              {-11,2},{-17,-5},{-12,-14},{15,-3},{15,-11},{7,3},{19,7},{-15,19},{10,-14},
              {-14,5},{0,-1},{-12,-4},{4,18},{7,-3},{-5,-3},{1,-11},{1,-1},{2,16},{6,-6},
              {-17,9},{14,3},{-13,8},{-9,14},{-5,-1},{-18,-17},{9,-10},{19,19},{16,7},
              {3,7},{-18,-12},{-11,12},{-15,20},{-3,4},{-18,1},{13,17},{-16,-15},{-9,-9},
              {15,8},{19,-9},{9,-17}};
    std::cout << Solution::maxPoints(points) << std::endl;
    return 0;
}
