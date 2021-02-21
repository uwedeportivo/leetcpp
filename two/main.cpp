#include <bitset>
#include <array>
#include <vector>

// https://leetcode.com/problems/permutations-ii/

const int notSetValue {11};

class Consumer {
public:
    explicit Consumer(const std::array<int, 21>& ys, std::vector<std::vector<int>>& rt) : ms{ys}, result{rt}, permSize {} {
        for (int i = 0; i < 21; i++) {
            permSize += ms[i];
        }
    }

    void consume(const std::vector<std::bitset<8>>& accum) {
        std::array<int, 8> perm {};
        
        for (int i = 0; i < 8; i++) {
            perm[i] = notSetValue;
        }
        
        for (int i = 0; i < 21; i++) {
            apply(perm, accum[i], permSize, i - 10);
        }

        std::vector<int> p {};
        p.reserve(8);
        for (int i = 0; i < 8 && perm[i] != notSetValue; i++) {
            p.push_back(perm[i]);
        }

        result.push_back(p);
    }

    const std::vector<std::vector<int>>& getResult() {
        return result;
    }
private:
    const std::array<int, 21>& ms;
    std::vector<std::vector<int>>& result;
    int permSize;

    static void apply(std::array<int, 8>& perm, const std::bitset<8>& xs, int size, int value) {
        int cursor = 0;

        for (int i = 0; i < size && cursor < 8; i++) {
            while (cursor < 8 && perm[cursor] != notSetValue) {
                cursor++;
            }
            if (xs[i]) {
                perm[cursor] = value;
            }
            cursor++;
        }
    }
};

class SubsetGenerator {
public:
    SubsetGenerator() : sz{0}, ssz{0}, next{nullptr}, consumer{nullptr} {}

    void setState(int s, int k, Consumer* c) {
        sz = s;
        ssz = k;
        consumer = c;
    }

    void setNext(SubsetGenerator* n) {
        next = n;
    }

    void generate(std::vector<std::bitset<8>>& accum) {
        std::bitset<8> xs {};
        if (ssz == 0) {
            consume(xs, accum);
            return;
        }

        subsets(xs, 0, ssz, accum);
    }
private:
    int sz;
    int ssz;
    SubsetGenerator* next;
    Consumer* consumer;

    void consume(const std::bitset<8>& xs, std::vector<std::bitset<8>>& accum) {
        accum.push_back(xs);
        if (next != nullptr) {
            next->generate(accum);
        } else {
            consumer->consume(accum);
        }
        accum.pop_back();
    }

    void subsets(std::bitset<8>& xs, int index, int remaining, std::vector<std::bitset<8>>& accum) {
        if (remaining == 0) {
            consume(xs, accum);
            return;
        }

        if (index + remaining == sz) {
            for (int i = index; i < sz; i++) {
                xs[i] = true;
            }
            consume(xs, accum);
            for (int i = index; i < sz; i++) {
                xs[i] = false;
            }
            return;
        }

        xs[index] = false;
        subsets(xs, index + 1, remaining, accum);
        xs[index] = true;
        subsets(xs, index + 1, remaining - 1, accum);
        xs[index] = false;
    }
};

std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    std::vector<std::vector<int>> result {};
    std::array<int, 21> ms{};
    for (auto x : nums) {
        ms[x + 10]++;
    }
    Consumer c {ms, result};

    int sf = 0;
    std::array<SubsetGenerator, 21> sgs{};

    int n = int(nums.size());
    for (int i = 0; i < 21; i++) {
        if (i < 20) {
            sgs[i].setNext(&sgs[i+1]);
        }
        sgs[i].setState(n - sf, ms[i], &c);
        sf += ms[i];
    }

    std::vector<std::bitset<8>> accum {};
    sgs[0].generate(accum);

    return result;
}

int main() {
    std::vector<int> nums{1, 1, 2};

    auto r = permuteUnique(nums);

    return 0;
}
