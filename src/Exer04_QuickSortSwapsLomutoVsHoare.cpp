//
// Created by Junio Moreira on 27/10/26.
// Problem 4: Swap Count - Lomuto vs Hoare (Adapted from beecrowd #1088 and LeetCode #912)
//
// Strategy:
//  The same input vector is sorted twice, by two copies of Quick Sort that differ only in
//  the partition scheme, and every swap is counted by swapAndCount():
//   - Lomuto: one pointer scans the range from left to right (one direction).
//   - Hoare: two pointers start at the ends and walk towards the center, swapping the
//     pairs that are out of place (pivot = middle element).
//  Effective swap rule: a swap is counted only if the two indices are different (i != j).
//  Then the program reports the swaps of each scheme, the winner (or a tie) and the sorted
//  vector produced by the scheme with fewer swaps.
//
//  Notes about the two schemes:
//   - Lomuto: the pivot is the FIRST element, moved to the end of the range before the scan
//     (that move is a counted swap). The scan is the one seen in class (nums[j] <= pivot).
//     This is what reproduces the numbers of the statement (7 and 6 swaps). With the plain
//     rightmost pivot of the class, the examples give 3 x 3 and 2 x 2 (tie).
//   - Hoare: the partition is the one seen in class, but it returns i (and the recursion is
//     [left..i-1] and [i..right]). Returning j and recursing on [left..j] and [j+1..right]
//     never ends on inputs like {1, 2}, because j can be left - 1.
//
//  Example: 9 4 1 6 7 3  =>  Lomuto: 7 swaps, Hoare: 3 swaps  =>  Hoare wins
//
// Complexity: O(N log N) time on average for both (O(N^2) in the worst case for Lomuto,
//             e.g. sorted input) | O(log N) auxiliary space (recursion) on average.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// Type alias for 64-bit integers (swap counters can exceed 32 bits in the worst case)
using ll = long long;

// Result of the comparison between the two partition schemes
struct ComparisonResult {
    ll lomutoSwaps;
    ll hoareSwaps;
    string winner;              // "Lomuto", "Hoare" or "Empate"
    vector<int> sortedArray;    // vector sorted by the scheme with fewer swaps

    bool operator==(const ComparisonResult& other) const {
        return lomutoSwaps == other.lomutoSwaps &&
               hoareSwaps == other.hoareSwaps &&
               winner == other.winner &&
               sortedArray == other.sortedArray;
    }
};

class Solution {
private:
    ll lomutoSwaps;
    ll hoareSwaps;

    // TODO: Implement the private helper method 'swapAndCount':
    //  - Signature: void swapAndCount(vector<int>& nums, int a, int b, ll& swaps)
    //  - Effective swap rule: only call swap(nums[a], nums[b]) and increment 'swaps' if a != b.

    // TODO: Implement the private helper method 'partition' (Lomuto):
    //  - Signature: int partition(vector<int>& nums, int left, int right)
    //  - Step 1: Move first element to end as pivot: swapAndCount(nums, left, right, lomutoSwaps).
    //  - Step 2: Set pivot = nums[right] and boundary i = left - 1.
    //  - Step 3: Loop j from left to right - 1:
    //      * If nums[j] <= pivot: increment i and call swapAndCount(nums, i, j, lomutoSwaps).
    //  - Step 4: Place pivot in final position: swapAndCount(nums, i + 1, right, lomutoSwaps).
    //  - Step 5: Return i + 1.

    // TODO: Implement the private recursive method 'quickSort' (Lomuto):
    //  - Signature: void quickSort(vector<int>& nums, int left, int right)
    //  - If left < right:
    //      * pivotIndex = partition(nums, left, right)
    //      * quickSort(nums, left, pivotIndex - 1)
    //      * quickSort(nums, pivotIndex + 1, right)

    // TODO: Implement the private helper method 'hoarePartition':
    //  - Signature: int hoarePartition(vector<int>& nums, int left, int right)
    //  - Step 1: Pick middle element as pivot: pivot = nums[left + (right - left) / 2].
    //  - Step 2: Initialize pointers: i = left, j = right.
    //  - Step 3: Loop while i <= j:
    //      * Advance i while i <= j and nums[i] < pivot.
    //      * Retreat j while i <= j and nums[j] > pivot.
    //      * If i <= j: swapAndCount(nums, i, j, hoareSwaps), increment i, and decrement j.
    //  - Step 4: Return i (first index of the right subarray).

    // TODO: Implement the private recursive method 'quickSortHoare':
    //  - Signature: void quickSortHoare(vector<int>& nums, int left, int right)
    //  - If left < right:
    //      * i = hoarePartition(nums, left, right)
    //      * quickSortHoare(nums, left, i - 1)
    //      * quickSortHoare(nums, i, right)

public:
    // Sorts two copies of the input, one per scheme, and returns the comparison
    ComparisonResult compareSwaps(const vector<int>& input) {
        vector<int> byLomuto = input;
        vector<int> byHoare = input;
        lomutoSwaps = 0;
        hoareSwaps = 0;

        // TODO: If input is not empty:
        //  - Run quickSort(byLomuto, 0, (int)byLomuto.size() - 1)
        //  - Run quickSortHoare(byHoare, 0, (int)byHoare.size() - 1)

        // TODO: Compare lomutoSwaps and hoareSwaps:
        //  - If lomutoSwaps < hoareSwaps: return {lomutoSwaps, hoareSwaps, "Lomuto", byLomuto}
        //  - If hoareSwaps < lomutoSwaps: return {lomutoSwaps, hoareSwaps, "Hoare", byHoare}
        //  - Otherwise: return {lomutoSwaps, hoareSwaps, "Empate", byLomuto}

        return {lomutoSwaps, hoareSwaps, "Empate", byLomuto};
    }
};

// Helper function to print numeric vectors
void printVector(const vector<int>& nums) {
    int n = nums.size();
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << nums[i] << (i + 1 < n ? ", " : "");
    }
    cout << "]";
}

// Test runner: shows the input, the expected result, the real output and the status
void runTest(Solution& solver, int testNum, const string& testName,
             const vector<int>& input, const ComparisonResult& expected) {
    ComparisonResult output = solver.compareSwaps(input);
    bool passed = (output == expected);

    cout << "\nTest " << testNum << " Results (" << testName << "):\n";
    cout << "Input:          "; printVector(input); cout << "\n";
    cout << "Expected:       Lomuto: " << expected.lomutoSwaps << " trocas | Hoare: " << expected.hoareSwaps
         << " trocas | Menos trocas: " << expected.winner << "\n";
    cout << "                Array: "; printVector(expected.sortedArray); cout << "\n";
    cout << "Output:         Lomuto: " << output.lomutoSwaps << " trocas | Hoare: " << output.hoareSwaps
         << " trocas | Menos trocas: " << output.winner << "\n";
    cout << "                Array: "; printVector(output.sortedArray); cout << "\n";
    cout << "Status:         " << (passed ? "Passed" : "Failed") << "\n";
}

int main() {
    FAST_IO;
    Solution solution;

    // --- Test 1 (Assignment Example 1) ---
    vector<int> in1 = {9, 4, 1, 6, 7, 3};
    ComparisonResult exp1 = {7, 3, "Hoare", {1, 3, 4, 6, 7, 9}};
    runTest(solution, 1, "Assignment Example 1", in1, exp1);

    // --- Test 2 (Assignment Example 2: Reverse Sorted) ---
    vector<int> in2 = {5, 4, 3, 2, 1};
    ComparisonResult exp2 = {6, 2, "Hoare", {1, 2, 3, 4, 5}};
    runTest(solution, 2, "Assignment Example 2 (Reverse Sorted)", in2, exp2);

    // --- Test 3 (Single Element) ---
    vector<int> in3 = {42};
    ComparisonResult exp3 = {0, 0, "Empate", {42}};
    runTest(solution, 3, "Single Element", in3, exp3);

    // --- Test 4 (Tie) ---
    vector<int> in4 = {2, 3, 4, 1};
    ComparisonResult exp4 = {3, 3, "Empate", {1, 2, 3, 4}};
    runTest(solution, 4, "Tie", in4, exp4);

    // --- Test 5 (Already Sorted: Hoare does not swap anything) ---
    vector<int> in5 = {1, 2, 3, 4, 5, 6, 7, 8};
    ComparisonResult exp5 = {14, 0, "Hoare", {1, 2, 3, 4, 5, 6, 7, 8}};
    runTest(solution, 5, "Already Sorted", in5, exp5);

    // --- Test 6 (Constraint Limits: -10^9 to 10^9) ---
    vector<int> in6 = {1000000000, -1000000000, 0};
    ComparisonResult exp6 = {2, 2, "Empate", {-1000000000, 0, 1000000000}};
    runTest(solution, 6, "Limits", in6, exp6);

    return 0;
}