//
// Created by Junio Moreira on 27/10/26.
// Problem 3: Quick Sort with Records and Tie-Break (Adapted from beecrowd #2312 and #1258)
//
// Strategy:
//  Lomuto Partitioning with a custom comparator:
//   1. Candidate precedence rule:
//      - Primary key: Score in descending order (higher score comes first).
//      - Secondary key (tie-breaker): Name in lexicographical ascending order.
//   2. QuickSort partitions the array around the pivot chosen at index 'right'.
//      Elements that should precede the pivot are swapped to the left partition.
//
// Complexity: O(N log N) average time, O(N^2) worst case | O(log N) auxiliary space.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

// Type alias for 64-bit integers
using ll = long long;

struct Candidate {
    string name;
    ll score;

    // Operator == to allow direct comparison in test assertions
    bool operator==(const Candidate& other) const {
        return name == other.name && score == other.score;
    }
};

class Solution {
private:
    // Returns true if candidate 'a' must appear before candidate 'b'
    bool comesBefore(const Candidate& a, const Candidate& b) {
        if (a.score != b.score) {
            return a.score > b.score; // Higher score comes first
        }
        return a.name < b.name;       // Tie: alphabetical order
    }

    // Lomuto partitioning: places elements that precede pivot on the left
    ll partition(vector<Candidate>& arr, ll left, ll right) {
        Candidate pivot = arr[right];
        ll i = left; // Boundary for elements that come before pivot

        for (ll j = left; j < right; j++) {
            if (comesBefore(arr[j], pivot)) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[right]);
        return i;
    }

    // Recursive QuickSort
    void quickSort(vector<Candidate>& arr, ll left, ll right) {
        if (left < right) {
            ll pivotIndex = partition(arr, left, right);
            quickSort(arr, left, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, right);
        }
    }

public:
    // Sorts the candidates and returns the sorted vector
    vector<Candidate> sortCandidates(vector<Candidate> arr) {
        if (!arr.empty()) {
            quickSort(arr, 0, (ll)arr.size() - 1);
        }
        return arr;
    }
};

// Helper function to print candidates in a compact list format
void printCandidates(const vector<Candidate>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "{" << arr[i].name << ", " << arr[i].score << "}" << (i + 1 < arr.size() ? ", " : "");
    }
    cout << "]";
}

// Test runner function matching the standard testing format
void runTest(Solution& solver, int testNum, const string& testName,
             const vector<Candidate>& input, const vector<Candidate>& expected) {
    vector<Candidate> output = solver.sortCandidates(input);
    bool passed = (output == expected);

    cout << "\nTest " << testNum << " Results (" << testName << "):\n";
    cout << "Input:    "; printCandidates(input); cout << "\n";
    cout << "Expected: "; printCandidates(expected); cout << "\n";
    cout << "Output:   "; printCandidates(output); cout << "\n";
    cout << "Status:   " << (passed ? "Passed" : "Failed") << "\n";
}

int main() {
    FAST_IO;
    Solution solution;

    // --- Test 1 (Assignment Example 1: Tie between Bruno and Carlos) ---
    vector<Candidate> in1 = {{"Bruno", 85}, {"Alice", 90}, {"Carlos", 85}, {"Daniel", 70}};
    vector<Candidate> exp1 = {{"Alice", 90}, {"Bruno", 85}, {"Carlos", 85}, {"Daniel", 70}};
    runTest(solution, 1, "Assignment Example 1", in1, exp1);

    // --- Test 2 (Assignment Example 2: All scores equal) ---
    vector<Candidate> in2 = {{"Pedro", 50}, {"Lucas", 50}, {"Ana", 50}};
    vector<Candidate> exp2 = {{"Ana", 50}, {"Lucas", 50}, {"Pedro", 50}};
    runTest(solution, 2, "Assignment Example 2 (Ties Only)", in2, exp2);

    // --- Test 3 (Single candidate) ---
    vector<Candidate> in3 = {{"Zoe", 0}};
    vector<Candidate> exp3 = {{"Zoe", 0}};
    runTest(solution, 3, "Single Candidate", in3, exp3);

    // --- Test 4 (Several ties across different scores) ---
    vector<Candidate> in4 = {{"Marta", 70}, {"Zeca", 90}, {"Ana", 70}, {"Bia", 90}, {"Caio", 70}};
    vector<Candidate> exp4 = {{"Bia", 90}, {"Zeca", 90}, {"Ana", 70}, {"Caio", 70}, {"Marta", 70}};
    runTest(solution, 4, "Multiple Tie Groups", in4, exp4);

    // --- Test 5 (Already sorted with duplicate records) ---
    vector<Candidate> in5 = {{"Ana", 100}, {"Ana", 100}, {"Bia", 90}, {"Caio", 80}, {"Caio", 80}};
    vector<Candidate> exp5 = {{"Ana", 100}, {"Ana", 100}, {"Bia", 90}, {"Caio", 80}, {"Caio", 80}};
    runTest(solution, 5, "Already Sorted and Duplicates", in5, exp5);

    return 0;
}