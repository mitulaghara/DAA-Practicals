# Selection Sort Algorithm & Documentation

This document contains the exact Selection Sort algorithm, pseudocode, and dry run as written on your professor's whiteboard, along with complete complexity analysis.

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
SelectionSort(A, n)
{
    for i ← 1 to n - 1 do
    {
        minv ← A[i]
        minI ← i

        for j ← i + 1 to n do
        {
            if minv > A[j]
            {
                minv ← A[j]
                minI ← j
            }
        }

        temp ← A[minI]
        A[minI] ← A[i]
        A[i] ← temp
    }
}
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `SelectionSort(A, n)`

* **Input:** Array `A` of `n` elements (1-indexed, i.e., `A[1..n]`).
* **Output:** Sorted array `A` in ascending order.

1. **Step 1: [Outer Loop]**
   For `i ← 1` to `n - 1`, execute Steps 2 to 5:

2. **Step 2: [Initialize Minimum Value & Index]**
   * Set `minv ← A[i]`
   * Set `minI ← i`

3. **Step 3: [Inner Loop to Find Minimum Element]**
   For `j ← i + 1` to `n`, do:
   * If `minv > A[j]`, then:
     * `minv ← A[j]`
     * `minI ← j`

4. **Step 4: [Swap Element at `minI` with `A[i]`]**
   * `temp ← A[minI]`
   * `A[minI] ← A[i]`
   * `A[i] ← temp`

5. **Step 5: [End of Outer Loop]**

6. **Step 6: [Exit]**
   Return sorted array `A`.

---

## 3. Dry Run Example (From Whiteboard)

**Given Array `A` (`n = 6`):**
Indices: `1, 2, 3, 4, 5, 6`
Initial values: `[27, 7, 19, 3, 18, 23]`

| Index | Initial `A` | Iteration 1 (`i=1`) | Iteration 2 (`i=2`) | Iteration 3 (`i=3`) | Iteration 4 (`i=4`) | Iteration 5 (`i=5`) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **1** | **27** | **3** | 3 | 3 | 3 | 3 |
| **2** | 7 | **7** | **7** | 7 | 7 | 7 |
| **3** | 19 | 19 | 19 | **18** | 18 | 18 |
| **4** | 3 | **27** | 27 | 27 | **19** | 19 |
| **5** | 18 | 18 | 18 | **19** | **27** | **23** |
| **6** | 23 | 23 | 23 | 23 | 23 | **27** |
| **Details** | - | `minv = 3`, `minI = 4`<br>Swap `A[1]` & `A[4]` | `minv = 7`, `minI = 2`<br>No swap (`A[2]` same) | `minv = 18`, `minI = 5`<br>Swap `A[3]` & `A[5]` | `minv = 19`, `minI = 5`<br>Swap `A[4]` & `A[5]` | `minv = 23`, `minI = 6`<br>Swap `A[5]` & `A[6]` |

---

## 4. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(n^2)$ | Array is already sorted. The algorithm still performs all $\frac{n(n-1)}{2}$ comparisons to find the minimum element in each pass. |
| **Average Case ($\Theta$)** | $\Theta(n^2)$ | Array elements are in random order. Requires $\frac{n(n-1)}{2}$ comparisons across all passes. |
| **Worst Case ($\mathcal{O}$)** | $\mathcal{O}(n^2)$ | Array is sorted in reverse order. Performs maximum comparisons and $O(n)$ swaps. |
| **Space Complexity** | $\mathcal{O}(1)$ | Sorting is performed in-place using only constant extra space for variables (`minv`, `minI`, `temp`). |

---

## 5. C Code Reference

Your C implementation in [`selectionSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab%202/selectionSort.c) uses 0-based indexing (`0` to `n-1`), which is functionally identical to the 1-based indexing taught on the whiteboard.
