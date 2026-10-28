//
// Created by Junio Moreira on 27/10/26.
// Problem 5: Mitigating the Worst Case - Median of Three Pivot Selection
// Adapted from LeetCode #912 (Sort an Array) and Classical Algorithm Analysis
//
// Strategy:
//  QuickSort with Median-of-Three heuristic:
//   1. Inspect nums[left], nums[mid], and nums[right], where mid = left + (right - left) / 2.
//   2. Locally sort the three elements so that: nums[left] <= nums[mid] <= nums[right].
//   3. Swap the median (currently at mid) with the rightmost element (right),
//      serving as the pivot for Lomuto partitioning.
//   4. Capture the pivot chosen in the root recursive call (range [0..N-1]).
//
// Complexity: O(N log N) expected time | O(log N) auxiliary space.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// Type alias for 64-bit integers
using ll = long long;

struct MedianSortResult {
    ll initialPivot;
    vector<ll> sortedArray;

    bool operator==(const MedianSortResult& other) const {
        return initialPivot == other.initialPivot &&
               sortedArray == other.sortedArray;
    }
};

class Solution {
private:
    // TODO: Implement the private helper method 'selectMedianOfThree':
    //  - Signature: ll selectMedianOfThree(vector<ll>& nums, ll left, ll right)
    //  - Step 1: Calculate midpoint: mid = left + (right - left) / 2.
    //  - Step 2: Compare and swap so nums[left] <= nums[mid] <= nums[right]:
    //      * If nums[mid] < nums[left]: swap(nums[left], nums[mid]).
    //      * If nums[right] < nums[left]: swap(nums[left], nums[right]).
    //      * If nums[right] < nums[mid]: swap(nums[mid], nums[right]).
    //  - Step 3: Place the median element at index 'right' as pivot: swap(nums[mid], nums[right]).
    //  - Step 4: Return nums[right].

    // TODO: Implement the private helper method 'partition':
    //  - Signature: ll partition(vector<ll>& nums, ll left, ll right)
    //  - Step 1: Set pivot = nums[right] and boundary i = left - 1.
    //  - Step 2: Loop j from left to right - 1:
    //      * If nums[j] <= pivot: increment i and swap(nums[i], nums[j]).
    //  - Step 3: Move pivot to correct position: swap(nums[i + 1], nums[right]).
    //  - Step 4: Return i + 1.

    // TODO: Implement the private recursive method 'quickSort':
    //  - Signature: void quickSort(vector<ll>& nums, ll left, ll right, ll& initialPivot, bool isRoot)
    //  - If left < right:
    //      * Select pivot: ll pivotValue = selectMedianOfThree(nums, left, right).
    //      * If isRoot is true: assign initialPivot = pivotValue.
    //      * Partition array: ll pivotIndex = partition(nums, left, right).
    //      * Recurse on left subarray: quickSort(nums, left, pivotIndex - 1, initialPivot, false).
    //      * Recurse on right subarray: quickSort(nums, pivotIndex + 1, right, initialPivot, false).

public:
    MedianSortResult sortWithMedianOfThree(vector<ll> nums) {
        ll initialPivot = 0;

        // TODO: If nums is not empty:
        //  - Invoke quickSort(nums, 0, (ll)nums.size() - 1, initialPivot, true)

        return {initialPivot, nums};
    }
};

// Helper function to print numeric vectors
void printVector(const vector<ll>& nums) {
    ll n = (ll)nums.size();
    cout << "[";
    for (ll i = 0; i < n; i++) {
        cout << nums[i] << (i + 1 < n ? ", " : "");
    }
    cout << "]";
}

// Test runner function matching the standard line-by-line format
void runTest(Solution& solver, int testNum, const string& testName,
             const vector<ll>& input, const MedianSortResult& expected) {
    MedianSortResult output = solver.sortWithMedianOfThree(input);
    bool passed = (output == expected);

    cout << "\nTest " << testNum << " Results (" << testName << "):\n";
    cout << "Input:          "; printVector(input); cout << "\n";
    cout << "Expected:       Pivo inicial: " << expected.initialPivot << "\n";
    cout << "                Array: "; printVector(expected.sortedArray); cout << "\n";
    cout << "Output:         Pivo inicial: " << output.initialPivot << "\n";
    cout << "                Array: "; printVector(output.sortedArray); cout << "\n";
    cout << "Status:         " << (passed ? "Passed" : "Failed") << "\n";
}

int main() {
    FAST_IO;
    Solution solution;

    // --- Test 1 (Assignment Example 1: 10 20 80 40 70 60 50) ---
    // Triple inspects: nums[0]=10, nums[3]=40, nums[6]=50. Median = 40.
    vector<ll> in1 = {10, 20, 80, 40, 70, 60, 50};
    MedianSortResult exp1 = {40, {10, 20, 40, 50, 60, 70, 80}};
    runTest(solution, 1, "Assignment Example 1", in1, exp1);

    // --- Test 2 (Assignment Example 2: 1 2 3 4 5) ---
    // Triple inspects: nums[0]=1, nums[2]=3, nums[4]=5. Median = 3.
    vector<ll> in2 = {1, 2, 3, 4, 5};
    MedianSortResult exp2 = {3, {1, 2, 3, 4, 5}};
    runTest(solution, 2, "Assignment Example 2 (Already Sorted)", in2, exp2);

    // --- Test 3 (Reverse sorted: 9 8 7 6 5 4 3 2 1) ---
    // Triple inspects: nums[0]=9, nums[4]=5, nums[8]=1. Median = 5.
    vector<ll> in3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    MedianSortResult exp3 = {5, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    runTest(solution, 3, "Reverse Sorted (Odd Size)", in3, exp3);

    // --- Test 4 (Array with duplicates and negative values) ---
    // Triple inspects: nums[0]=-5, nums[2]=0, nums[4]=10. Median = 0.
    vector<ll> in4 = {-5, 20, 0, -10, 10};
    MedianSortResult exp4 = {0, {-10, -5, 0, 10, 20}};
    runTest(solution, 4, "Duplicates and Negatives", in4, exp4);

    return 0;
}