# 0/1 Knapsack Problem (Dynamic Programming) & Documentation

This document contains the exact 0/1 Knapsack algorithm using Dynamic Programming, pseudocode, dry run trace, complexity analysis, and sample output based on your professor's handwritten notes and [`dynamicKnapsack.c`](./dynamicKnapsack.c).

---

## 1. Notebook Algorithm (Exact Professor's Notation)

```text
Practical - 8
Aim :- Develop a Program to implement the Knapsack Problem using dynamic Programming.

Knapsack(n, wt[], value[], W)
{
    // Initialize first row and first column
    for i ← 0 to n do
        m[i][0] ← 0

    for j ← 0 to W do
        m[0][j] ← 0

    // Dynamic Programming
    for i ← 1 to n do
    {
        for j ← 1 to W do
        {
            if (wt[i] <= j)
            {
                if (m[i-1][j] > value[i] + m[i-1][j - wt[i]])
                    m[i][j] ← m[i-1][j]
                else
                    m[i][j] ← value[i] + m[i-1][j - wt[i]]
            }
            else
            {
                m[i][j] ← m[i-1][j]
            }
        }
    }

    // Print DP Table
    for i ← 0 to n do
    {
        for j ← 0 to W do
            Print m[i][j]
    }

    // Display Maximum value
    Print m[n][W]

    // Backtracking
    i ← n
    j ← W

    while (i > 0 AND j > 0)
    {
        if (m[i][j] != m[i-1][j])
        {
            Print "Item ", i,
                  "Weight = ", wt[i],
                  "Value = ", value[i]
            j ← j - wt[i]
        }
        i ← i - 1
    }

    return m[n][W]
}

⊙ Time Complexity

T(n) = O(n × W)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `0/1_KNAPSACK_DP(n, wt[], value[], W)`

* **Input:** Number of items `n`, weight array `wt[]`, value array `value[]`, knapsack capacity `W`.
* **Output:** Maximum profit/value `m[n][W]` and list of selected items.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input]**
   Read `n` (number of items), `wt[i]` and `value[i]` for each item `1` to `n`, and knapsack capacity `W`.

3. **Step 3: [Initialize First Row & Column]**
   * For `i ← 0` to `n`, set `m[i][0] ← 0`.
   * For `j ← 0` to `W`, set `m[0][j] ← 0`.

4. **Step 4: [Fill DP Table]**
   For `i ← 1` to `n`, for `j ← 1` to `W`, do:
   * If `wt[i] <= j`:
     * If `m[i-1][j] > value[i] + m[i-1][j - wt[i]]`:
       * Set `m[i][j] ← m[i-1][j]`
     * Else:
       * Set `m[i][j] ← value[i] + m[i-1][j - wt[i]]`
   * Else:
     * Set `m[i][j] ← m[i-1][j]`

5. **Step 5: [Print DP Table & Maximum Value]**
   * Display the DP table `m[0..n][0..W]`.
   * Print Maximum Value = `m[n][W]`.

6. **Step 6: [Backtrack for Selected Items]**
   * Initialize `i ← n` and `j ← W`.
   * While `i > 0` AND `j > 0`, do:
     * If `m[i][j] != m[i-1][j]`:
       * Item `i` is included in knapsack.
       * Print Item `i`, its weight `wt[i]`, and value `value[i]`.
       * Decrement capacity: `j ← j - wt[i]`.
     * Decrement item counter: `i ← i - 1`.

7. **Step 7: [Stop]**
   Return `m[n][W]` and stop.

---

## 3. Pseudocode

```text
Algorithm DynamicKnapsack(n, wt[], value[], W)
    Input : Number of items n, weights wt[1..n], values value[1..n], capacity W
    Output: Maximum profit and selected items

    // Step 1: Base Cases (0 items or 0 capacity)
    for i ← 0 to n do
        m[i][0] ← 0
    end for
    for j ← 0 to W do
        m[0][j] ← 0
    end for

    // Step 2: Build DP Table bottom-up
    for i ← 1 to n do
        for j ← 1 to W do
            if wt[i] ≤ j then
                m[i][j] ← max(m[i-1][j], value[i] + m[i-1][j - wt[i]])
            else
                m[i][j] ← m[i-1][j]
            end if
        end for
    end for

    // Step 3: Backtrack to find selected items
    i ← n
    j ← W
    while i > 0 and j > 0 do
        if m[i][j] ≠ m[i-1][j] then
            include item i (weight = wt[i], value = value[i])
            j ← j - wt[i]
        end if
        i ← i - 1
    end while

    return m[n][W]
end Algorithm
```

---

## 4. Dry Run Example (4 Items, Capacity = 8)

**Given Input:**
* Items: `n = 4`
* Capacity: `W = 8`

| Item (i) | Weight (`wt[i]`) | Value (`value[i]`) |
|:--------:|:----------------:|:------------------:|
| 1        | 3                | 2                  |
| 2        | 4                | 3                  |
| 3        | 6                | 1                  |
| 4        | 5                | 4                  |

**DP Table `m[i][j]` (rows = items 0 to 4, columns = capacity 0 to 8):**

| `i \ j` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|:-------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| **i = 0** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **i = 1 (w=3, v=2)** | 0 | 0 | 0 | 2 | 2 | 2 | 2 | 2 | 2 |
| **i = 2 (w=4, v=3)** | 0 | 0 | 0 | 2 | 3 | 3 | 3 | 5 | 5 |
| **i = 3 (w=6, v=1)** | 0 | 0 | 0 | 2 | 3 | 3 | 3 | 5 | 5 |
| **i = 4 (w=5, v=4)** | 0 | 0 | 0 | 2 | 3 | 4 | 4 | 5 | **6** |

**Filling Logic Highlights:**
* For `i = 1`, `wt[1] = 3`, `v[1] = 2`: Can only fit from `j >= 3`, gets value `2`.
* For `i = 2`, `wt[2] = 4`, `v[2] = 3`: At `j = 7`, `max(m[1][7]=2, 3 + m[1][3]=5) = 5`.
* For `i = 3`, `wt[3] = 6`, `v[3] = 1`: No improvement over `i = 2`.
* For `i = 4`, `wt[4] = 5`, `v[4] = 4`: At `j = 8`, `max(m[3][8]=5, 4 + m[3][3]=6) = 6`.

**Backtracking Trace:**
1. Start at `(i=4, j=8)`: `m[4][8] = 6 ≠ m[3][8] = 5` $\rightarrow$ **Select Item 4** (wt=5, val=4). New `j = 8 - 5 = 3`, `i = 3`.
2. At `(i=3, j=3)`: `m[3][3] = 2 == m[2][3] = 2` $\rightarrow$ Skip Item 3. `i = 2`.
3. At `(i=2, j=3)`: `m[2][3] = 2 == m[1][3] = 2` $\rightarrow$ Skip Item 2. `i = 1`.
4. At `(i=1, j=3)`: `m[1][3] = 2 ≠ m[0][3] = 0` $\rightarrow$ **Select Item 1** (wt=3, val=2). New `j = 3 - 3 = 0`, `i = 0`.
5. `j = 0`, loop terminates.

**Selected Items:**
* **Item 4** $\rightarrow$ Weight = 5, Value = 4
* **Item 1** $\rightarrow$ Weight = 3, Value = 2
* **Total Weight** = 5 + 3 = 8 (within capacity 8)
* **Maximum Profit / Value** = 4 + 2 = **6**

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case (Ω)** | Ω(n × W) | Every cell of the `(n+1) × (W+1)` table must be filled. |
| **Average Case (Θ)** | Θ(n × W) | Table construction takes `(n × W)` iterations; backtracking takes `O(n)`. |
| **Worst Case (O)** | O(n × W) | All entries are evaluated; total time is dominated by nested loops `O(n × W)`. |
| **Space Complexity** | O(n × W) | 2D table `m[n+1][W+1]` requires `O(n × W)` space. |

> **Note:**
> `T(n) = O(n × W)` where `n` = number of items and `W` = knapsack capacity.
> This is a **pseudo-polynomial** time algorithm since its runtime depends on the numeric value of `W`.

---

## 6. C Code Reference

Your C code implementation is in [`dynamicKnapsack.c`](./dynamicKnapsack.c).

---

## 7. Sample Program Output

```text
How many items: 4

Enter weight and value of each item:

Enter weight of item 1: 3
Enter value of item 1: 2

Enter weight of item 2: 4
Enter value of item 2: 3

Enter weight of item 3: 6
Enter value of item 3: 1

Enter weight of item 4: 5
Enter value of item 4: 4

Enter Knapsack Capacity: 8


Knapsack DP Table:

    0    0    0    0    0    0    0    0    0
    0    0    0    2    2    2    2    2    2
    0    0    0    2    3    3    3    5    5
    0    0    0    2    3    3    3    5    5
    0    0    0    2    3    4    4    5    6

Maximum Value = 6

Selected Items:
Item 4 -> Weight = 5, Value = 4
Item 1 -> Weight = 3, Value = 2
```
