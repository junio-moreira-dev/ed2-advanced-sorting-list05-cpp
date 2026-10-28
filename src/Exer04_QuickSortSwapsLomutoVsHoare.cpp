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

    // Swaps nums[a] and nums[b] and counts it, only if the indices are different
    void swapAndCount(vector<int>& nums, int a, int b, ll& swaps) {
        if (a != b) {
            swap(nums[a], nums[b]);
            swaps++;
        }
    }

    // Lomuto partition (one direction scan)
    int partition(vector<int>& nums, int left, int right) {
        // Move the first element (the pivot) to the end of the range.
        // Remove this line to use the rightmost pivot seen in class.
        swapAndCount(nums, left, right, lomutoSwaps);

        int pivot = nums[right]; // The pivot is now the rightmost element
        int i = left - 1;        // Pointer for elements smaller than or equal to the pivot

        // Traverse through all elements from left to right - 1
        for (int j = left; j < right; j++) {
            // If the current element is smaller than or equal to the pivot
            if (nums[j] <= pivot) {
                i++;                                // Increment index of smaller element
                swapAndCount(nums, i, j, lomutoSwaps);
            }
        }

        // Move the pivot to its correct final position in the middle
        swapAndCount(nums, i + 1, right, lomutoSwaps);

        // Return the partitioning index
        return i + 1;
    }

    // Recursive function for QuickSort using Lomuto partition
    void quickSort(vector<int>& nums, int left, int right) {
        if (left < right) {
            int pivotIndex = partition(nums, left, right);

            quickSort(nums, left, pivotIndex - 1);   // Sort the left subarray
            quickSort(nums, pivotIndex + 1, right);  // Sort the right subarray
        }
    }

    // Hoare partition scheme using a middle pivot and convergent pointers
    int hoarePartition(vector<int>& nums, int left, int right) {
        // Choose the middle element as the pivot
        int pivot = nums[left + (right - left) / 2];
        int i = left;
        int j = right;

        while (i <= j) {
            // Move left pointer forward while elements are smaller than the pivot
            while (i <= j && nums[i] < pivot) {
                i++;
            }

            // Move right pointer backward while elements are greater than the pivot
            while (i <= j && nums[j] > pivot) {
                j--;
            }

            // If pointers haven't crossed yet, swap and advance both inward
            if (i <= j) {
                swapAndCount(nums, i, j, hoareSwaps);
                i++;
                j--;
            }
        }

        // The pointers crossed: i is the first index of the right subarray
        return i;
    }

    // Recursive function for QuickSort using Hoare partition
    void quickSortHoare(vector<int>& nums, int left, int right) {
        if (left < right) {
            int i = hoarePartition(nums, left, right);

            quickSortHoare(nums, left, i - 1);  // Sort the left subarray
            quickSortHoare(nums, i, right);     // Sort the right subarray
        }
    }

public:
    // Sorts two copies of the input, one per scheme, and returns the comparison
    ComparisonResult compareSwaps(const vector<int>& input) {
        vector<int> byLomuto = input;
        vector<int> byHoare = input;
        lomutoSwaps = 0;
        hoareSwaps = 0;

        quickSort(byLomuto, 0, (int)byLomuto.size() - 1);
        quickSortHoare(byHoare, 0, (int)byHoare.size() - 1);

        if (lomutoSwaps < hoareSwaps) {
            return {lomutoSwaps, hoareSwaps, "Lomuto", byLomuto};
        }
        if (hoareSwaps < lomutoSwaps) {
            return {lomutoSwaps, hoareSwaps, "Hoare", byHoare};
        }
        return {lomutoSwaps, hoareSwaps, "Empate", byLomuto};  // on a tie both vectors are the same
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