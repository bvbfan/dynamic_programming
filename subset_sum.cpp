
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <vector>

/**
 * Function to find subset with largest sum less than or equal to T
 * @param[in]  T         integer less or equal to
 * @param[in]  I         integer set to look in
 * @param[out] M         integer subset containg elements of largest sum
 * @param[out] S         integer the largest subset sum
 */
void find_largest_sum(uint32_t T, const std::vector<uint32_t> &I,
                      std::vector<uint32_t> &M, uint32_t &S)
{
    if (I.empty())
        return;

    auto start = I.begin();
    std::vector<uint32_t> work;
    auto sum = *start > T ? 0 : *start;
    if (sum)
        work.push_back(sum);
    S = 0;

    // To find sum less or equal to T
    for (auto it = start + 1; it != I.end(); ++it) {

        if (*it > T)
            continue;

        // If sum becomes greater than T
        // remove starting from start till new one fits
        // prefer continuous subset over non-continuous
        while (((sum > UINT_MAX - *it) || (sum + *it > T)) && start != it) {
            if (S < sum) {
                S = sum;
                M = work;
            }
            sum -= *start;
            work.erase(std::find(work.begin(), work.end(), *start));
            ++start;
        }

        // Add element to sum
        sum += *it;
        work.push_back(*it);
    }

    if (S < sum) {
        S = sum;
        M = work;
    }
}

// Driver program to test above function
int main()
{
    uint32_t sum;
    std::vector<uint32_t> arr, b;

    arr = {1, 2, 3, 4, 5, 6, 7};
    sum = 11;

    find_largest_sum(sum, arr, b, sum);

    assert(sum == 11 && "Sum does not match");
    assert(b.size() == 2 && "Result size does not match");
    assert(std::equal(b.begin(), b.end(), std::vector<uint32_t>{5, 6}.begin()) && "Result array does not match");

    arr = {6, 5, 9, 3, 10, 8, 7};
    sum = 18;

    find_largest_sum(sum, arr, b, sum);

    assert(sum == 18 && "Sum does not match");
    assert(b.size() == 2 && "Result size does not match");
    assert(std::equal(b.begin(), b.end(), std::vector<uint32_t>{10, 8}.begin()) && "Result array does not match");

    arr = {6, 2, 4, 10, 8, 9};
    sum = 15;

    find_largest_sum(sum, arr, b, sum);

    assert(sum == 14 && "Sum does not match");
    assert(b.size() == 2 && "Result size does not match");
    assert(std::equal(b.begin(), b.end(), std::vector<uint32_t>{4, 10}.begin()) && "Result array does not match");

    arr.resize(100);
    for (int i = 0; i < 100; i++)
        arr[i] = i + 1;

    sum = 5051;

    find_largest_sum(sum, arr, b, sum);

    assert(sum == 5050 && "Sum does not match");
    assert(b.size() == 100 && "Result size does not match");
    assert(std::equal(b.begin(), b.end(), arr.begin()) && "Result array does not match");

    std::cout << "Tests finishes successfully!\n";
    return 0;
}
