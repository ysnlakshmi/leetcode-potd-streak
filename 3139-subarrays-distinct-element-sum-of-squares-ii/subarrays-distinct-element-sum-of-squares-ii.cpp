class LazySegmentTree {
public:
    LazySegmentTree(int n, int kMod)
        : n(n), kMod(kMod), lazy(4 * n, 0), sums(4 * n, 0), squaredSums(4 * n, 0) {}

    void updateRange(int l, int r) {
        updateRange(0, 0, n - 1, l, r, 1);
    }

    int getTreeSquaredSums() const {
        return squaredSums[0];
    }

private:
    const int n;
    const int kMod;
    vector<int> lazy;
    vector<long long> sums;
    vector<long long> squaredSums;

    void updateRange(int treeIndex, int lo, int hi, int l, int r, int val) {
        if (r < lo || hi < l)
            return;
        if (l <= lo && hi <= r) {
            apply(treeIndex, lo, hi, val);
            return;
        }
        push(treeIndex, lo, hi);
        const int mid = lo + (hi - lo) / 2;
        updateRange(2 * treeIndex + 1, lo, mid, l, r, val);
        updateRange(2 * treeIndex + 2, mid + 1, hi, l, r, val);
        pull(treeIndex);
    }

    void apply(int treeIndex, int lo, int hi, int val) {
        lazy[treeIndex] = (lazy[treeIndex] + val) % kMod;
        const long long length = hi - lo + 1;
        squaredSums[treeIndex] = (squaredSums[treeIndex] + 2 * sums[treeIndex] * val + length * val * val) % kMod;
        sums[treeIndex] = (sums[treeIndex] + length * val) % kMod;
    }

    void push(int treeIndex, int lo, int hi) {
        if (lazy[treeIndex] == 0)
            return;
        const int mid = lo + (hi - lo) / 2;
        apply(2 * treeIndex + 1, lo, mid, lazy[treeIndex]);
        apply(2 * treeIndex + 2, mid + 1, hi, lazy[treeIndex]);
        lazy[treeIndex] = 0;
    }

    void pull(int treeIndex) {
        sums[treeIndex] = (sums[2 * treeIndex + 1] + sums[2 * treeIndex + 2]) % kMod;
        squaredSums[treeIndex] = (squaredSums[2 * treeIndex + 1] + squaredSums[2 * treeIndex + 2]) % kMod;
    }
};

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int kMod = 1e9 + 7;
        const int n = nums.size();
        int ans = 0;
        unordered_map<int, int> lastSeen;
        LazySegmentTree tree(n, kMod);

        for (int r = 0; r < n; ++r) {
            const int l = lastSeen.count(nums[r]) ? lastSeen[nums[r]] + 1 : 0;
            tree.updateRange(l, r);
            lastSeen[nums[r]] = r;
            ans = (ans + tree.getTreeSquaredSums()) % kMod;
        }

        return ans;
    }
};