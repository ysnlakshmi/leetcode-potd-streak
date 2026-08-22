class Solution {
public:
    bool checkDivisibility(int n) {
        int z = n;
        int r = 0;
        int x = 1;

        while (z > 0) {
            int dig = z % 10;
            r += dig;
            x *= dig;
            z /= 10;
        }

        int tot = r + x;
        return (n % tot == 0);
    }
};