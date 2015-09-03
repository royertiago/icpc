#include <iostream>

int main() {
    /* There are at most 50 values to be summed,
     * and each value has absolute value at most 5000.
     * Thus, the sum of all these values have absolute value at most
     *  50 * 5000 = 250000 = 2.5e5,
     * which fits in a 32-bit signed integer.
     */
    int N, X, sum = 0;
    std::cin >> N;

    /* Any non-zero value is treated as true by C and C++,
     * and any zero value is treated as false.
     * Thus, the following loop will execute exactly N times,
     * because in the N+1th, N will be zero and will evaluate to false.
     * (It will also be decremented to -1 AFTER the boolean evaluation,
     * but this is harmless since we do not use N afterwards.
     */
    while( N-- ) {
        std::cin >> X;
        sum += X;
    }
    std::cout << sum << '\n';
    return 0;
}
