#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <stdexcept>

class SubsetGenerator {
public:
    SubsetGenerator(int n, int k) : set_size{n}, subset_size{k}, indices {std::vector<int>(k)}  {}

    void Fill(std::vector<int>& buffer) {
        for (int i = 0; i < subset_size; ++i) {
            buffer[i] = indices[i] - 1;
        }
    }

    bool Next() {
        if (subset_size == 0) {
            return false;
        }
        if (indices[0] == 0) {
            for (int i = 0; i < subset_size; ++i) {
                indices[i] = i + 1;
            }
            return true;
        }

        if (isLast()) {
            return false;
        }

        int j = subset_size - 1;

        while (j >=0 && indices[j] == set_size - subset_size + j + 1) {
            --j;
        }

        int a = indices[j];
        for (int i = j; i < subset_size; ++i) {
            indices[i] = a + i - j + 1;
        }

        return true;
    }

private:
    int set_size;
    int subset_size;
    std::vector<int> indices;

    bool isLast() {
        for (int i = 0; i < subset_size; ++i) {
            if (indices[i] != set_size - subset_size + i + 1) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    std::vector<std::string> xs;

    int n = 64;
    int k = 6;

    for (int i = 0; i < n; ++i) {
        xs.push_back(std::to_string(i+1));
    }
    SubsetGenerator ssg(n, k);

    std::vector<int> buffer(k);

    int iterations = 0;
    while (iterations < 10000 && ssg.Next()) {
        ssg.Fill(buffer);
        std::cout << "{";
        for (int i = 0; i < k - 1; ++i) {
            std::cout << xs[buffer[i]];
            std::cout << ", ";
        }
        std::cout << xs[buffer[k - 1]];
        std::cout << "}";
        std::cout << std::endl;
        std::cout.flush();
        ++iterations;
    }

    return 0;
}
