# Heap Sort Algorithm & Documentation

This document contains the exact Heap Sort algorithm, pseudocode, step-by-step dry run trace, and complexity analysis based on your professor's whiteboard notes (DAA Practical - 4) and [`heapSort.c`](./heapSort.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
Heapsort(A, n)
{
    for i ← n/2 to 1 do
    {
        MaxHeapify(A, n, i)
    }

    For i ← n to 1 do
    {
        Swap A[1], A[i]
        MaxHeapify(A, i - 1, 1)
    }
}
```

```text
MaxHeapify(A, n, i)
{
    largest ← i
    L ← 2 * i
    R ← 2 * i + 1

    while L ≤ n and A[L] > A[largest]
    {
        largest ← L
    }

    while R ≤ n and A[R] > A[largest]
    {
        largest ← R
    }

    if (i != largest)
    {
        swap A[i], A[largest]
        MaxHeapify(A, n, largest)
    }
}
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

### Algorithm 1: `Heapsort(A, n)`
* **Input:** Array `A` of size `n` (1-indexed).
* **Output:** Array `A` sorted in ascending order.

1. **Step 1: [Build Max Heap]**
   For `i = n/2` down to `1`, do:
   * Call `MaxHeapify(A, n, i)` to satisfy max-heap property for all parent nodes.

2. **Step 2: [Sort / Extract Elements]**
   For `i = n` down to `1`, do:
   * **Swap** `A[1]` (root / maximum element) with `A[i]` (current last element).
   * Call `MaxHeapify(A, i - 1, 1)` to restore max-heap property for remaining `i - 1` elements.

3. **Step 3: [Exit]**
   Return sorted array `A`.

---

### Algorithm 2: `MaxHeapify(A, n, i)`
* **Input:** Array `A`, heap size `n`, index `i` of node to heapify.
* **Output:** Rearranged array such that subtree rooted at index `i` forms a Max-Heap.

1. **Step 1: [Initialize Index Pointers]**
   * Set `largest ← i`
   * Left Child `L ← 2 * i`
   * Right Child `R ← 2 * i + 1`

2. **Step 2: [Check Left Child]**
   If `L ≤ n` and `A[L] > A[largest]`, set:
   * `largest ← L`

3. **Step 3: [Check Right Child]**
   If `R ≤ n` and `A[R] > A[largest]`, set:
   * `largest ← R`

4. **Step 4: [Swap and Recursively Heapify]**
   If `i ≠ largest`, do:
   * Swap `A[i]` and `A[largest]`
   * Call `MaxHeapify(A, n, largest)` recursively to propagate changes down the tree.

---

## 3. Dry Run Example

**Given Whiteboard Array `A` (n = 7, 1-indexed):**

```
Index: [1]   [2]   [3]   [4]   [5]   [6]   [7]
  A  :  15    17    20     1     5    10    30
```

---

### Phase 1: Build Max Heap (`for i = 7/2 = 3` down to `1`)

* **Non-leaf Parent Nodes:** Indices `3`, `2`, `1`.

#### 1. `i = 3` (Node `A[3] = 20`):
* `L = 6` (`A[6] = 10`), `R = 7` (`A[7] = 30`).
* `A[7] = 30 > A[3] = 20` $\rightarrow$ `largest = 7`.
* Swap `A[3]` (20) and `A[7]` (30).
* Array becomes: `[15, 17, 30, 1, 5, 10, 20]`

#### 2. `i = 2` (Node `A[2] = 17`):
* `L = 4` (`A[4] = 1`), `R = 5` (`A[5] = 5`).
* Neither child is greater than `A[2] = 17` $\rightarrow$ `largest = 2`.
* No swap needed.

#### 3. `i = 1` (Node `A[1] = 15`):
* `L = 2` (`A[2] = 17`), `R = 3` (`A[3] = 30`).
* `A[3] = 30` is the largest child $\rightarrow$ `largest = 3`.
* Swap `A[1]` (15) and `A[3]` (30).
* Array becomes: `[30, 17, 15, 1, 5, 10, 20]`
* Recursive call `MaxHeapify(A, 7, 3)`:
  * For node at index 3 (`A[3] = 15`), right child `A[7] = 20 > 15` $\rightarrow$ `largest = 7`.
  * Swap `A[3]` (15) and `A[7]` (20).
* Array becomes: `[30, 17, 20, 1, 5, 10, 15]`

> **Max Heap Built:** `A = [30, 17, 20, 1, 5, 10, 15]`  
> Root node `A[1] = 30` is maximum.

---

### Phase 2: Extract Root & Re-heapify (`for i = 7` down to `1`)

| Iteration `i` | Swap `A[1]` & `A[i]` | Array State | Call `MaxHeapify(A, i-1, 1)` Result |
|:-------------:|:--------------------:|:------------|:-----------------------------------|
| **i = 7** | Swap `A[1]`(30) & `A[7]`(15) | `[15, 17, 20, 1, 5, 10, \| 30]` | `MaxHeapify(A, 6, 1)` $\rightarrow$ `[20, 17, 15, 1, 5, 10, \| 30]` |
| **i = 6** | Swap `A[1]`(20) & `A[6]`(10) | `[10, 17, 15, 1, 5, \| 20, 30]` | `MaxHeapify(A, 5, 1)` $\rightarrow$ `[17, 10, 15, 1, 5, \| 20, 30]` |
| **i = 5** | Swap `A[1]`(17) & `A[5]`(5) | `[5, 10, 15, 1, \| 17, 20, 30]` | `MaxHeapify(A, 4, 1)` $\rightarrow$ `[15, 10, 5, 1, \| 17, 20, 30]` |
| **i = 4** | Swap `A[1]`(15) & `A[4]`(1) | `[1, 10, 5, \| 15, 17, 20, 30]` | `MaxHeapify(A, 3, 1)` $\rightarrow$ `[10, 1, 5, \| 15, 17, 20, 30]` |
| **i = 3** | Swap `A[1]`(10) & `A[3]`(5) | `[5, 1, \| 10, 15, 17, 20, 30]` | `MaxHeapify(A, 2, 1)` $\rightarrow$ `[5, 1, \| 10, 15, 17, 20, 30]` |
| **i = 2** | Swap `A[1]`(5) & `A[2]`(1) | `[1, \| 5, 10, 15, 17, 20, 30]` | `MaxHeapify(A, 1, 1)` $\rightarrow$ `[1, \| 5, 10, 15, 17, 20, 30]` |
| **i = 1** | Swap `A[1]`(1) & `A[1]`(1) | `[1, 5, 10, 15, 17, 20, 30]` | Done |

---

### Final Sorted Array:

```text
A = [1, 5, 10, 15, 17, 20, 30]
```

---

## 4. Time Complexity Calculation

### i) Best Case:
**No. of Comparisons:**
- At every level of recursion, all $n$ elements are processed.

**No. of Levels:** $\log_2 n$

Therefore,
$$T(n) = n + n + n + n + \dots + n$$
$$\text{(Repeated } \log_2 n \text{ times)}$$
$$= n \times \log_2 n$$
$$= O(n \log n)$$

---

### ii) Worst Case:

| No. of levels | Comparisons |
|:---:|:---:|
| 1 | $n$ |
| 2 | $n$ |
| 3 | $n$ |
| $\vdots$ | $\vdots$ |
| $\log_2 n$ | $n$ |

Therefore,
$$T(n) = n + n + n + n + \dots + n$$
$$\text{(Repeated } \log_2 n \text{ times)}$$
$$= n \times \log_2 n$$
$$= O(n \log n)$$

---

### iii) Average Case:

| No. of levels | Comparisons |
|:---:|:---:|
| 1 | $n$ |
| 2 | $n$ |
| 3 | $n$ |
| $\vdots$ | $\vdots$ |
| $\log_2 n$ | $n$ |

Therefore,
$$T(n) = n + n + n + n + \dots + n$$
$$\text{(Repeated } \log_2 n \text{ times)}$$
$$= n \times \log_2 n$$
$$= O(n \log n)$$

---

### Summary & Space Complexity

| Case | Time Complexity | Auxiliary Space | Description |
|:---|:---:|:---:|:---|
| **Best Case ($\Omega$)** | $O(n \log n)$ | $O(1)$ | Equal division at each heap level. |
| **Worst Case ($O$)** | $O(n \log n)$ | $O(1)$ | Tree height is $\log_2 n$, max heapify takes $O(\log_2 n)$ for $n$ elements. |
| **Average Case ($\Theta$)** | $O(n \log n)$ | $O(1)$ | Average operations across all levels equal $n \times \log_2 n$. |

> **Note:** Heap Sort is an **in-place** sorting algorithm with a guaranteed $O(n \log n)$ time complexity across all cases.

---

## 5. C Code Reference

Your C code implementation is in [`heapSort.c`](./heapSort.c).

---

## 6. Sample Program Output

```text
How many elements you want to sort: 7

Enter Elements: 15
Enter Elements: 17
Enter Elements: 20
Enter Elements: 1
Enter Elements: 5
Enter Elements: 10
Enter Elements: 30

Heapsort Element:    1    5   10   15   17   20   30
```
