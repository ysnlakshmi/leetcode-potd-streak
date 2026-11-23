#include <vector>
using namespace std;

class ProductOfNumbers {
private:
    vector<int> prefix;

public:
    ProductOfNumbers() {
        prefix.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            prefix.clear();
            prefix.push_back(1);
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }

    int getProduct(int k) {
        int m = static_cast<int>(prefix.size());
        if (k >= m) {
            return 0;
        }
        return prefix.back() / prefix[m - 1 - k];
    }
};