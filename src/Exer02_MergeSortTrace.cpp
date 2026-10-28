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
    // Merges two sorted subarrays [left..middle] and [middle+1..right]
    void merge(vector<ll>& nums, vector<ll>& helper, ll left, ll middle, ll right, vector<string>& traces) {
        // Copy range to the auxiliary buffer
        for (ll m = left; m <= right; m++) {
            helper[m] = nums[m];
        }

        ll i = left;          // Pointer for the left subarray
        ll j = middle + 1;    // Pointer for the right subarray
        ll k = left;          // Pointer for destination in nums

        // Merge back into nums in ascending order
        while (i <= middle && j <= right) {
            if (helper[i] <= helper[j]) {
                nums[k++] = helper[i++];
            } else {
                nums[k++] = helper[j++];
            }
        }

        // Copy remaining elements from the left subarray (if any)
        while (i <= middle) {
            nums[k++] = helper[i++];
        }

        // Format trace output: "[Merge left..right]: elem1 elem2 ..."
        ostringstream oss;
        oss << "[Merge " << left << ".." << right << "]:";
        for (ll m = left; m <= right; m++) {
            oss << " " << nums[m];
        }
        traces.resize(traces.size() + 1);
        traces.back() = oss.str();
    }

    // Recursive helper function for Divide and Conquer
    void mergeSort(vector<ll>& nums, vector<ll>& helper, ll left, ll right, vector<string>& traces) {
        if (left < right) {
            ll middle = left + (right - left) / 2;

            mergeSort(nums, helper, left, middle, traces);
            mergeSort(nums, helper, middle + 1, right, traces);
            merge(nums, helper, left, middle, right, traces);
        }
    }

public:
    // Sorts the vector and captures the trace step by step
    pair<vector<ll>, vector<string>> sortAndTrace(vector<ll> nums) {
        vector<string> traces;
        if (!nums.empty()) {
            vector<ll> helper(nums.size());
            mergeSort(nums, helper, 0, (ll)nums.size() - 1, traces);
        }

        // Format final state: "[Final]: elem1 elem2 ..."
        ostringstream oss;
        oss << "[Final]:";
        for (ll x : nums) {
            oss << " " << x;
        }
        traces.resize(traces.size() + 1);
        traces.back() = oss.str();

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