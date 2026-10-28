//
// Created by Junio Moreira on 27/10/26.
// Problem 1: Two Pointers Merge (LeetCode #88 - Merge Sorted Array)
//
// Strategy:
//  In-place direct merge scanning from back to front using two pointers.
//  nums1 has a total size of m + n (the last n positions are free room).
//  We compare the largest unprocessed elements from nums1 and nums2
//  and write the greater one at index k (the end of nums1).
//  Walking backwards guarantees that unread elements in nums1 are never overwritten.
//
// Complexity: O(N + M) time | O(1) auxiliary space (in-place).
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// Type alias for 64-bit integers
using ll = long long;

class Solution {
public:
    // LeetCode #88: merges nums2 directly into nums1 in non-decreasing order
    void merge(vector<ll>& nums1, ll m, const vector<ll>& nums2, ll n) {
        ll i = m - 1;         // Last valid element in nums1
        ll j = n - 1;         // Last element in nums2
        ll k = m + n - 1;     // Insertion index at the end of nums1

        // While there are remaining elements to place from nums2
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
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

// Test runner function matching the standard testing format
void runTest(Solution& solver, int testNum, const string& testName,
             vector<ll> nums1, const vector<ll>& nums2, const vector<ll>& expected) {
    ll m = (ll)nums1.size();
    ll n = (ll)nums2.size();

    // Preserve original inputs for logging
    vector<ll> originalA = nums1;
    vector<ll> originalB = nums2;

    // Allocate room at the end of nums1 to receive nums2
    nums1.resize(m + n);

    solver.merge(nums1, m, nums2, n);
    bool passed = (nums1 == expected);

    cout << "\nTest " << testNum << " Results (" << testName << "):\n";
    cout << "Input A:   "; printVector(originalA); cout << "\n";
    cout << "Input B:   "; printVector(originalB); cout << "\n";
    cout << "Expected:  "; printVector(expected); cout << "\n";
    cout << "Output:    "; printVector(nums1); cout << "\n";
    cout << "Status:    " << (passed ? "Passed" : "Failed") << "\n";
}

int main() {
    FAST_IO;
    Solution solution;

    // --- Test 1 (Assignment Example 1) ---
    runTest(solution, 1, "Assignment Example 1", {1, 3, 5}, {2, 4, 6}, {1, 2, 3, 4, 5, 6});

    // --- Test 2 (Assignment Example 2: B ends first) ---
    runTest(solution, 2, "Assignment Example 2 (B ends first)", {2, 5, 7, 9}, {1, 3}, {1, 2, 3, 5, 7, 9});

    // --- Test 3 (A ends first) ---
    runTest(solution, 3, "A ends first", {1, 2}, {3, 4, 5, 6}, {1, 2, 3, 4, 5, 6});

    // --- Test 4 (All of B before A) ---
    runTest(solution, 4, "All of B before A", {5, 6, 7}, {1, 2, 3}, {1, 2, 3, 5, 6, 7});

    // --- Test 5 (Duplicates and negative numbers) ---
    runTest(solution, 5, "Duplicates and Negatives", {-5, -1, 0, 0, 3}, {-3, 0, 4}, {-5, -3, -1, 0, 0, 0, 3, 4});

    // --- Test 6 (Constraint limits -10^9 to 10^9) ---
    runTest(solution, 6, "Limits of Statement (-10^9 to 10^9)",
            {-1000000000, 0, 1000000000}, {-1000000000, 1000000000},
            {-1000000000, -1000000000, 0, 1000000000, 1000000000});

    return 0;
}