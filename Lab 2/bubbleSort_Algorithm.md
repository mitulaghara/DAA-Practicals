# Bubble Sort Algorithm & Documentation

This document contains the exact Bubble Sort algorithm, pseudocode, dry run trace, and complexity analysis based on your professor's whiteboard notes and [`bubbleSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab%202/bubbleSort.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
BubbleSort(A, n)
{
    for i ← 1 to n - 1 do
    {
        for j ← 1 to n - i do
        {
            if A[j] > A[j+1]
            {
                // Swap
                temp ← A[j]
                A[j] ← A[j+1]
                A[j+1] ← temp
            }
        }
    }
}
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `BubbleSort(A, n)`

* **Input:** Array `A` of `n` elements (1-indexed, i.e., `A[1..n]`).
* **Output:** Sorted array `A` in ascending order.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Size and Array]**
   Read size `n` and array elements `A[1..n]`.

3. **Step 3: [Outer Loop for Passes]**
   For `i ← 1` to `n - 1`, do Steps 4 to 6:

4. **Step 4: [Inner Loop for Comparisons & Swaps]**
   For `j ← 1` to `n - i`, do:
   * If `A[j] > A[j + 1]`, then swap `A[j]` and `A[j + 1]`:
     * `temp ← A[j]`
     * `A[j] ← A[j + 1]`
     * `A[j + 1] ← temp`

5. **Step 5: [End of Inner Loop]**

6. **Step 6: [End of Outer Loop]**

7. **Step 7: [Output & Stop]**
   Print sorted array `A` and Stop.

---

## 3. Dry Run Example (From Whiteboard)

**Given Array `A` (`n = 5`):**
Initial Values: `A = [27, 16, 18, 4, 23]`

Total passes required: $i = 1 \text{ to } n - 1 = 4$

* **Iteration 1 ($i = 1, j = 1 \text{ to } 4$):**
  * $j = 1$: $A[1] > A[2]$ ($27 > 16$) &rarr; **Swap** &rarr; `[16, 27, 18, 4, 23]`
  * $j = 2$: $A[2] > A[3]$ ($27 > 18$) &rarr; **Swap** &rarr; `[16, 18, 27, 4, 23]`
  * $j = 3$: $A[3] > A[4]$ ($27 > 4$) &rarr; **Swap** &rarr; `[16, 18, 4, 27, 23]`
  * $j = 4$: $A[4] > A[5]$ ($27 > 23$) &rarr; **Swap** &rarr; `[16, 18, 4, 23, 27]`
  * *(Largest element `27` bubbles to position 5)*

* **Iteration 2 ($i = 2, j = 1 \text{ to } 3$):**
  * $j = 1$: $A[1] > A[2]$ ($16 > 18$) &rarr; No swap &rarr; `[16, 18, 4, 23, 27]`
  * $j = 2$: $A[2] > A[3]$ ($18 > 4$) &rarr; **Swap** &rarr; `[16, 4, 18, 23, 27]`
  * $j = 3$: $A[3] > A[4]$ ($18 > 23$) &rarr; No swap &rarr; `[16, 4, 18, 23, 27]`
  * *(Second largest element `23` fixed at position 4)*

* **Iteration 3 ($i = 3, j = 1 \text{ to } 2$):**
  * $j = 1$: $A[1] > A[2]$ ($16 > 4$) &rarr; **Swap** &rarr; `[4, 16, 18, 23, 27]`
  * $j = 2$: $A[2] > A[3]$ ($16 > 18$) &rarr; No swap &rarr; `[4, 16, 18, 23, 27]`
  * *(Third largest element `18` fixed at position 3)*

* **Iteration 4 ($i = 4, j = 1$):**
  * $j = 1$: $A[1] > A[2]$ ($4 > 16$) &rarr; No swap &rarr; `[4, 16, 18, 23, 27]`

**Final Sorted Array:** `[4, 16, 18, 23, 27]`

---

## 4. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(n^2)$ | Array is already sorted. Without flag optimization, it still performs all $\frac{n(n-1)}{2}$ comparisons.<br>*(Note: With a swapped flag optimization, Best Case becomes $\Omega(n)$)*. |
| **Average Case ($\Theta$)** | $\Theta(n^2)$ | Array elements are in random order. Requires approximately $\frac{n(n-1)}{2}$ comparisons and $\frac{n(n-1)}{4}$ swaps on average. |
| **Worst Case ($\mathcal{O}$)** | $\mathcal{O}(n^2)$ | Array is sorted in reverse order. Requires maximum number of comparisons $\frac{n(n-1)}{2}$ and maximum number of swaps. |
| **Space Complexity** | $\mathcal{O}(1)$ | Sorting is done in-place, using only constant extra space for the temporary variable (`temp`). |

---

## 5. C Code Reference

Your C code implementation is in [`bubbleSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab%202/bubbleSort.c).
