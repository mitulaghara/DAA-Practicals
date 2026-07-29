# Merge Sort Algorithm & Documentation

This document contains the exact Merge Sort algorithm, pseudocode, dry run trace, and complexity analysis based on your professor's whiteboard notes and [`mergeSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab3/mergeSort.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
MergeSort(A, lb, ub)
{
    if lb < ub
    {
        mid = (lb + ub) / 2
        MergeSort(A, lb, mid)
        MergeSort(A, mid + 1, ub)
        Merge(A, lb, mid, ub)
    }
}
```

```text
Merge(A, lb, mid, ub)
{
    i ← lb, j ← mid + 1, k ← lb

    while i ≤ mid and j ≤ ub
    {
        if A[i] < A[j]
        {
            b[k] ← A[i]
            i++, k++
        }
        else
        {
            b[k] ← A[j]
            k++, j++
        }
    }

    if (j > ub)
    {
        while (i ≤ mid)
        {
            b[k] ← A[i]
            k++, i++
        }
    }
    else if (i > mid)
    {
        while (j ≤ ub)
        {
            b[k] ← A[j]
            k++, j++
        }
    }
}
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

### Algorithm 1: `MergeSort(A, lb, ub)`
* **Input:** Array `A`, lower bound `lb`, upper bound `ub`.
* **Output:** Array `A` sorted in ascending order from index `lb` to `ub`.

1. **Step 1: [Check Condition]**
   If `lb < ub`, execute Steps 2 to 5.

2. **Step 2: [Find Mid Index]**
   Calculate `mid = (lb + ub) / 2`.

3. **Step 3: [Recursive Call - Left Half]**
   Call `MergeSort(A, lb, mid)`.

4. **Step 4: [Recursive Call - Right Half]**
   Call `MergeSort(A, mid + 1, ub)`.

5. **Step 5: [Merge Sorted Subarrays]**
   Call `Merge(A, lb, mid, ub)`.

6. **Step 6: [Exit]**
   Return sorted array.

---

### Algorithm 2: `Merge(A, lb, mid, ub)`
* **Input:** Subarrays `A[lb..mid]` and `A[mid+1..ub]` sorted individually.
* **Output:** Merged single sorted array `A[lb..ub]`.

1. **Step 1: [Initialize Index Pointers]**
   * `i ← lb` (left subarray pointer)
   * `j ← mid + 1` (right subarray pointer)
   * `k ← lb` (auxiliary array pointer)

2. **Step 2: [Compare and Merge Elements]**
   While `i <= mid` and `j <= ub`, do:
   * If `A[i] < A[j]`, then:
     * `b[k] ← A[i]`
     * `i ← i + 1`, `k ← k + 1`
   * Else:
     * `b[k] ← A[j]`
     * `j ← j + 1`, `k ← k + 1`

3. **Step 3: [Copy Remaining Elements of Left Subarray]**
   If `j > ub`, then:
   * While `i <= mid`, do:
     * `b[k] ← A[i]`
     * `k ← k + 1`, `i ← i + 1`

4. **Step 4: [Copy Remaining Elements of Right Subarray]**
   Else if `i > mid`, then:
   * While `j <= ub`, do:
     * `b[k] ← A[j]`
     * `k ← k + 1`, `j ← j + 1`

5. **Step 5: [Copy Back to Original Array]**
   For `i = lb` to `ub`, do:
   * `A[i] ← b[i]`

6. **Step 6: [Exit]**

---

## 3. Dry Run Example (From Whiteboard)

**Given Array `A` (`n = 8`, `lb = 0`, `ub = 7`):**
Initial Values: `A = [15, 5, 24, 8, 3, 16, 10, 20]`

### **Division Tree (Divide Step):**

```text
                          [15, 5, 24, 8, 3, 16, 10, 20] (lb=0, ub=7, mid=3)
                                       |
            +--------------------------+--------------------------+
            |                                                     |
 [15, 5, 24, 8] (lb=0, ub=3, mid=1)                   [3, 16, 10, 20] (lb=4, ub=7, mid=5)
            |                                                     |
      +-----+-----+                                         +-----+-----+
      |           |                                         |           |
  [15, 5]      [24, 8]                                   [3, 16]     [10, 20]
  (0..1)       (2..3)                                    (4..5)       (6..7)
    |            |                                         |            |
  +--+--+      +--+--+                                   +--+--+      +--+--+
  |     |      |     |                                   |     |      |     |
 [15]  [5]    [24]  [8]                                 [3]   [16]   [10]  [20]
```

### **Merge Steps (Conquer Step):**

1. **Merge `[15]` & `[5]`** (indices 0 to 1) $\rightarrow$ `[5, 15]`
2. **Merge `[24]` & `[8]`** (indices 2 to 3) $\rightarrow$ `[8, 24]`
3. **Merge `[5, 15]` & `[8, 24]`** (indices 0 to 3) $\rightarrow$ `[5, 8, 15, 24]`
4. **Merge `[3]` & `[16]`** (indices 4 to 5) $\rightarrow$ `[3, 16]`
5. **Merge `[10]` & `[20]`** (indices 6 to 7) $\rightarrow$ `[10, 20]`
6. **Merge `[3, 16]` & `[10, 20]`** (indices 4 to 7) $\rightarrow$ `[3, 10, 16, 20]`

### **Final Merge of Left `[5, 8, 15, 24]` and Right `[3, 10, 16, 20]`:**

* $i = 0, j = 4, k = 0$: Compare $A[0](15)$ and $A[4](3) \rightarrow A[4] < A[0] \rightarrow b[0] = 3$, $j=5, k=1$
* $i = 0, j = 5, k = 1$: Compare $A[0](5\text{ sorted: }5)$ and $A[5](16) \rightarrow 5 < 16 \rightarrow b[1] = 5$, $i=1, k=2$
* $i = 1, j = 5, k = 2$: Compare $A[1](8)$ and $A[5](16) \rightarrow 8 < 16 \rightarrow b[2] = 8$, $i=2, k=3$
* $i = 2, j = 5, k = 3$: Compare $A[2](15)$ and $A[6](10) \rightarrow 10 < 15 \rightarrow b[3] = 10$, $j=6, k=4$
* $i = 2, j = 6, k = 4$: Compare $A[2](15)$ and $A[6](16) \rightarrow 15 < 16 \rightarrow b[4] = 15$, $i=3, k=5$
* $i = 3, j = 6, k = 5$: Compare $A[3](24)$ and $A[6](16) \rightarrow 16 < 24 \rightarrow b[5] = 16$, $j=7, k=6$
* $i = 3, j = 7, k = 6$: Compare $A[3](24)$ and $A[7](20) \rightarrow 20 < 24 \rightarrow b[6] = 20$, $j=8, k=7$
* $j = 8 > ub(7)$: Right array completed $\rightarrow$ Copy remaining element $A[3](24) \rightarrow b[7] = 24$.

**Auxiliary Array `b`:** `[3, 5, 8, 10, 15, 16, 20, 24]`  
**Final Sorted Array `A`:** `[3, 5, 8, 10, 15, 16, 20, 24]`

---

## 4. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(n \log n)$ | Even if the array is already sorted, the algorithm recursively divides the array $\log n$ times and merges in $\mathcal{O}(n)$ time per level. |
| **Average Case ($\Theta$)** | $\Theta(n \log n)$ | Recurrence relation $T(n) = 2T(n/2) + \Theta(n)$ resolves to $\Theta(n \log n)$ using Master Theorem. |
| **Worst Case ($\mathcal{O}$)** | $\mathcal{O}(n \log n)$ | In any input distribution, division takes $\mathcal{O}(\log n)$ levels and merging takes $\mathcal{O}(n)$ work per level. |
| **Space Complexity** | $\mathcal{O}(n)$ | Requires an auxiliary array `b` of size `n` for temporary merging, plus $\mathcal{O}(\log n)$ stack space for recursive function calls. |

---

## 5. C Code Reference

Your C code implementation is in [`mergeSort.c`](file:///Users/mitulaghara/Desktop/Marwadi%20University/Sem%205/DAA%20Lab/Lab3/mergeSort.c).

---

## 6. Sample Program Output

```text
Enter number of elements: 8
Enter elements:
15 5 24 8 3 16 10 20
Sorted array:
3 5 8 10 15 16 20 24 
```

