# Insertion Sort Algorithm & Documentation

This document contains the step-by-step algorithm, pseudocode, flowchart representation, and complexity analysis for the Insertion Sort implementation in [`insertionSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab%202/insertionSort.c).

---

## 1. Algorithm (Step-by-Step for DAA Lab / Exam)

**Algorithm:** `INSERTION_SORT(A, N)`
* **Input:** An array `A` of `N` elements.
* **Output:** Array `A` sorted in ascending order.

1. **Step 1: [Start]**
   Start the process.

2. **Step 2: [Input Array Size]**
   Read the number of elements `N`.

3. **Step 3: [Input Array Elements]**
   Read array elements `A[0], A[1], ..., A[N-1]`.

4. **Step 4: [Outer Loop for Passes]**
   For `i = 1` to `N - 1`, repeat Steps 5 to 9:

5. **Step 5: [Store Current Element]**
   Set `temp = A[i]`
   Set `j = i - 1`

6. **Step 6: [Inner Loop for Shifting Elements]**
   While `j >= 0` and `A[j] > temp`, do:
   * `A[j + 1] = A[j]` (Shift element to the right)
   * `j = j - 1`

7. **Step 7: [Insert Element]**
   Set `A[j + 1] = temp`

8. **Step 8: [End of Outer Loop]**

9. **Step 9: [Output Sorted Array]**
   Print the sorted array `A[0..N-1]`.

10. **Step 10: [Stop]**
    End the algorithm.

---

## 2. Pseudocode

```text
Algorithm InsertionSort(A, n)
    Input: Array A of n elements
    Output: Array A sorted in ascending order

    for i ← 1 to n - 1 do
        key ← A[i]
        j ← i - 1

        // Shift elements of A[0..i-1] that are greater than key
        while j >= 0 and A[j] > key do
            A[j + 1] ← A[j]
            j ← j - 1
        end while

        A[j + 1] ← key
    end for
end Algorithm
```

---

## 3. Example Dry Run

Consider Array `A = [12, 11, 13, 5, 6]` (`N = 5`)

| Pass (`i`) | `temp = A[i]` | Comparisons & Shifts | Array State after Pass |
|:---:|:---:|:---|:---|
| **Initial** | - | - | `[12, 11, 13, 5, 6]` |
| **i = 1** | `11` | `12 > 11` &rarr; shift 12 | `[11, 12, 13, 5, 6]` |
| **i = 2** | `13` | `12 < 13` &rarr; no shift | `[11, 12, 13, 5, 6]` |
| **i = 3** | `5` | Shift 13, 12, 11 &rarr; insert 5 | `[5, 11, 12, 13, 6]` |
| **i = 4** | `6` | Shift 13, 12, 11 &rarr; insert 6 | `[5, 6, 11, 12, 13]` |

---

## 4. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(n)$ | Array is already sorted. The inner loop condition `A[j] > temp` fails on the first check every time ($n-1$ comparisons, 0 shifts). |
| **Average Case ($\Theta$)** | $\Theta(n^2)$ | Array elements are in random order. On average, each element is compared with half of the sorted subarray. |
| **Worst Case ($\mathcal{O}$)** | $\mathcal{O}(n^2)$ | Array is sorted in reverse order. Every element must be compared and shifted across the entire sorted subarray. |
| **Space Complexity** | $\mathcal{O}(1)$ | Sorting is done in-place, using only constant extra space for the temporary variable (`temp`). |

---

## 5. C Code Reference

The full C code implementation is available in [`insertionSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab%202/insertionSort.c).
