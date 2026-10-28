//
// Created by Junio Moreira on 27/10/26.
// Problem 2: Merge Sort Trace (Adapted from beecrowd #1179 and LeetCode #912 - Sort an Array)
//
// Strategy:
//  Divide and Conquer (Merge Sort):
//   1. Divide: Recursively split the array [left..right] at the midpoint:
//      middle = left + (right - left) / 2.
//   2. Conquer: Recursively sort both halves [left..middle] and [middle + 1..right].
//   3. Combine (Merge & Trace): Merge the two sorted subarrays using a pre-allocated
//      helper buffer. At each completed merge, append the trace line in the exact
//      format: "[Merge left..right]: elem1 elem2 ...".
//
// Complexity: O(N log N) time | O(N) auxiliary space.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// Type alias for 64-bit integers
using ll = long long;

class Solution {
private:
    // TODO: Implement the private helper method 'merge':
    //  - Signature: void merge(vector<ll>& nums, vector<ll>& helper, ll left, ll middle, ll right, vector<string>& traces)
    //  - Step 1: Copy range [left..right] from 'nums' to 'helper'.
    //  - Step 2: Initialize pointers i = left, j = middle + 1, k = left.
    //  - Step 3: While i <= middle and j <= right:
    //      * If helper[i] <= helper[j], assign nums[k++] = helper[i++].
    //      * Otherwise, assign nums[k++] = helper[j++].
    //  - Step 4: Copy any remaining elements from the left subarray (while i <= middle).
    //  - Step 5: Construct trace string using ostringstream: "[Merge left..right]: elem1 elem2 ..."
    //      and append it to 'traces'.

    // TODO: Implement the private recursive method 'mergeSort':
    //  - Signature: void mergeSort(vector<ll>& nums, vector<ll>& helper, ll left, ll right, vector<string>& traces)
    //  - Base case: if left >= right, return.
    //  - Step 1: Calculate midpoint: middle = left + (right - left) / 2.
    //  - Step 2: Recursively sort left half: mergeSort(nums, helper, left, middle, traces).
    //  - Step 3: Recursively sort right half: mergeSort(nums, helper, middle + 1, right, traces).
    //  - Step 4: Merge both halves: merge(nums, helper, left, middle, right, traces).

public:
    // Sorts the vector and captures the trace step by step
    pair<vector<ll>, vector<string>> sortAndTrace(vector<ll> nums) {
        vector<string> traces;

        // TODO: If nums is not empty:
        //  - Allocate helper vector: vector<ll> helper(nums.size())
        //  - Call mergeSort(nums, helper, 0, (ll)nums.size() - 1, traces)

        // TODO: Construct final state trace using ostringstream: "[Final]: elem1 elem2 ..."
        //  and append it to 'traces'

        return {nums, traces};
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

// Helper function to print trace lists
void printTraces(const vector<string>& traces) {
    for (size_t i = 0; i < traces.size(); ++i) {
        cout << "\n    " << traces[i];
    }
}

// Test runner function matching the standard testing format
void runTest(Solution& solver, int testNum, const string& testName,
             const vector<ll>& input, const vector<string>& expectedTrace) {
    auto [sortedNums, traces] = solver.sortAndTrace(input);
    bool passed = (traces == expectedTrace);

    cout << "\nTest " << testNum << " Results (" << testName << "):\n";
    cout << "Input:    "; printVector(input); cout << "\n";
    cout << "Expected: "; printTraces(expectedTrace); cout << "\n";
    cout << "Output:   "; printTraces(traces); cout << "\n";
    cout << "Status:   " << (passed ? "Passed" : "Failed") << "\n";
}

int main() {
    FAST_IO;
    Solution solution;

    // --- Test 1: Assignment Example 1 (N = 4) ---
    vector<ll> in1 = {8, 3, 2, 9};
    vector<string> exp1 = {
        "[Merge 0..1]: 3 8",
        "[Merge 2..3]: 2 9",
        "[Merge 0..3]: 2 3 8 9",
        "[Final]: 2 3 8 9"
    };
    runTest(solution, 1, "Assignment Example 1 (N = 4)", in1, exp1);

    // --- Test 2: Assignment Example 2 (N = 5, Odd Size) ---
    vector<ll> in2 = {5, 4, 3, 2, 1};
    vector<string> exp2 = {
        "[Merge 0..1]: 4 5",
        "[Merge 0..2]: 3 4 5",
        "[Merge 3..4]: 1 2",
        "[Merge 0..4]: 1 2 3 4 5",
        "[Final]: 1 2 3 4 5"
    };
    runTest(solution, 2, "Assignment Example 2 (N = 5, Odd Size)", in2, exp2);

    // --- Test 3: Already sorted array (N = 3) ---
    vector<ll> in3 = {10, 20, 30};
    vector<string> exp3 = {
        "[Merge 0..1]: 10 20",
        "[Merge 0..2]: 10 20 30",
        "[Final]: 10 20 30"
    };
    runTest(solution, 3, "Already Sorted (N = 3)", in3, exp3);

    // --- Test 4: Array with duplicates and negative values ---
    vector<ll> in4 = {-2, 5, -2, 0};
    vector<string> exp4 = {
        "[Merge 0..1]: -2 5",
        "[Merge 2..3]: -2 0",
        "[Merge 0..3]: -2 -2 0 5",
        "[Final]: -2 -2 0 5"
    };
    runTest(solution, 4, "Duplicates and Negatives", in4, exp4);

    return 0;
}