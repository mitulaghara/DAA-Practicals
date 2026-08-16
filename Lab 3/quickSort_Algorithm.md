# Quick Sort Algorithm & Documentation

This document contains the exact Quick Sort algorithm, pseudocode, dry run trace, and complexity analysis based on the professor's handwritten notes (DAA Practical - 3) and [`quickSort.c`](./quickSort.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
QuickSort(A, lb, ub)
{
    if (lb < ub)
    {
        loc = Partition(A, lb, ub);
        QuickSort(A, lb, loc - 1);
        QuickSort(A, loc + 1, ub);
    }
}
```

```text
Partition(A, lb, ub)
{
    start = lb;
    end   = ub;
    pivot = A[lb];

    while (start < end)
    {
        while (A[start] <= pivot)
            start++;
        while (A[end] > pivot)
            end--;
        if (start < end)
        {
            swap(A[start], A[end]);
        }
    }

    swap(A[lb], A[end]);
    return end;
}
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

### Algorithm 1: `QuickSort(A, lb, ub)`
* **Input:** Array `A`, lower bound `lb`, upper bound `ub`.
* **Output:** Array `A` sorted in ascending order from index `lb` to `ub`.

1. **Step 1: [Check Condition]**
   If `lb < ub`, execute Steps 2 to 5; otherwise exit.

2. **Step 2: [Partition the Array]**
   Call `loc = Partition(A, lb, ub)`.
   This places the pivot element at its correct sorted position `loc`.

3. **Step 3: [Recursive Call – Left Sub-array]**
   Call `QuickSort(A, lb, loc - 1)` to sort all elements to the left of the pivot.

4. **Step 4: [Recursive Call – Right Sub-array]**
   Call `QuickSort(A, loc + 1, ub)` to sort all elements to the right of the pivot.

5. **Step 5: [Exit]**
   Return sorted array.

---

### Algorithm 2: `Partition(A, lb, ub)`
* **Input:** Array `A`, lower bound `lb`, upper bound `ub`.
* **Output:** Final position `end` (loc) of the pivot element.

1. **Step 1: [Initialize Pointers and Pivot]**
   * `start <- lb`
   * `end   <- ub`
   * `pivot <- A[lb]`  (first element taken as pivot)

2. **Step 2: [Scan from Left]**
   While `A[start] <= pivot`, do:
   * `start <- start + 1`
   (Move `start` right until an element greater than `pivot` is found.)

3. **Step 3: [Scan from Right]**
   While `A[end] > pivot`, do:
   * `end <- end - 1`
   (Move `end` left until an element less than or equal to `pivot` is found.)

4. **Step 4: [Swap if Pointers Haven't Crossed]**
   If `start < end`, then:
   * Swap `A[start]` and `A[end]`.
   * Go back to Step 2.

5. **Step 5: [Place Pivot at Correct Position]**
   Swap `A[lb]` and `A[end]`.

6. **Step 6: [Return Pivot Position]**
   Return `end`.

---

## 3. Dry Run Example

**Given Array `A` (n = 5, lb = 0, ub = 4):**

```
Initial:  A = [12, 43, 56, 12, 43]
               lb=0              ub=4
```

---

### Pass 1: `Partition(A, 0, 4)`

* `start = 0`, `end = 4`, `pivot = A[0] = 12`

| Step        | start | end | A[start] | A[end] | Action                                      |
|:-----------:|:-----:|:---:|:--------:|:------:|:--------------------------------------------|
| Scan Left   | 0→1   | 4   | A[1]=43>12 | —    | stop `start` at 1                           |
| Scan Right  | 1     | 4→3 | —        | A[3]=12≤12 | stop `end` at 3                        |
| start<end   | 1     | 3   | 43       | 12     | **Swap** → A = [12, **12**, 56, **43**, 43] |
| Scan Left   | 1→2   | 3   | A[2]=56>12 | —    | stop `start` at 2                           |
| Scan Right  | 2     | 3→1 | —        | A[1]=12≤12 | stop `end` at 1                        |
| start≥end   | 2     | 1   | —        | —      | Exit while loop                             |

* Swap `A[lb]=A[0]` with `A[end]=A[1]`:
  `A = [12, 12, 56, 43, 43]`
* **loc = 1** → pivot `12` is placed at index 1 ✅

---

### Pass 2: `Partition(A, 2, 4)` → `QuickSort(A, 2, 4)`

* `start = 2`, `end = 4`, `pivot = A[2] = 56`

| Step       | start | end | A[start] | A[end] | Action                              |
|:----------:|:-----:|:---:|:--------:|:------:|:------------------------------------|
| Scan Left  | 2→3→4→5 | 4 | 56≤56,43≤56,43≤56 | — | start=5 (exits) |
| Scan Right | 5     | 4   | —        | A[4]=43≤56 | stop `end` at 4              |
| start≥end  | 5     | 4   | —        | —      | Exit while loop                     |

* Swap `A[lb]=A[2]=56` with `A[end]=A[4]=43`:
  `A = [12, 12, **43**, 43, **56**]`
* **loc = 4** → pivot `56` placed at index 4 ✅

---

### Pass 3: `Partition(A, 2, 3)` → `QuickSort(A, 2, 3)`

* `start = 2`, `end = 3`, `pivot = A[2] = 43`

| Step       | start  | end | A[start] | A[end] | Action                   |
|:----------:|:------:|:---:|:--------:|:------:|:-------------------------|
| Scan Left  | 2→3→4  | 3   | 43≤43,43≤43 | —   | start=4 (exits)          |
| Scan Right | 4      | 3→2 | —        | A[2]=43≤43 | end=2 (exits)        |
| start≥end  | 4      | 2   | —        | —      | Exit while loop          |

* Swap `A[lb]=A[2]` with `A[end]=A[2]` → no change
* **loc = 2** → pivot `43` placed at index 2 ✅

**QuickSort(A, 2, 1)** → lb > ub → no action  
**QuickSort(A, 3, 3)** → lb == ub → no action

---

### Final Sorted Array:

```
A = [12, 12, 43, 43, 56]
```

---

## 4. Complexity Analysis

| Case                   | Time Complexity | Description |
|:-----------------------|:---------------:|:------------|
| **Best Case (Omega)**  | O(n log n)      | Pivot always divides the array into two equal halves. Recurrence: T(n) = 2T(n/2) + O(n). |
| **Average Case (Theta)** | O(n log n)    | On average, partitioning produces reasonably balanced sub-arrays. |
| **Worst Case (O)**     | O(n^2)          | Pivot is always the smallest or largest element (e.g., already sorted array). Recurrence: T(n) = T(n-1) + O(n). |
| **Space Complexity**   | O(log n)        | In-place algorithm — no auxiliary array. Stack space for recursion is O(log n) average, O(n) worst case. |

> **Note:** Quick Sort is an **in-place** sorting algorithm. It does **not** require extra memory like Merge Sort.

---

## 5. C Code Reference

Your C code implementation is in [`quickSort.c`](./quickSort.c).

---

## 6. Sample Program Output

```
Enter the number of elements:5

 Enter the element[1] : 12

 Enter the element[2] : 43

 Enter the element[3] : 56

 Enter the element[4] : 12

 Enter the element[5] : 43

 Quick sort:  12  12  43  43  56
```
