# Fractional Knapsack Algorithm & Documentation

This document contains the exact Knapsack algorithm, pseudocode, dry run trace, complexity analysis, and sample output based on your professor's handwritten notes and [`index.c`](./index.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
Knapsack(n, w, v, cap)
{
    for i ← 1 to n do
    {
        x[i] ← 0
        ratio[i] ← v[i] / w[i]
    }

    → Sort the elements (items) ratio[i] into descending order.

    profit ← 0
    for i ← 1 to n do
    {
        if w[i] ≤ cap
        {
            x[i] ← 1
            profit ← profit + (x[i] × v[i])
            cap ← cap - w[i]
        }
        else
        {
            x[i] ← cap / w[i]
            profit ← profit + (x[i] × v[i])
            break
        }
    }
}

⊙ Time Complexity

T(n) = O(n) = O(n log n)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `KNAPSACK(n, w, v, cap)`

* **Input:** Number of items `n`, weight array `w[]`, value array `v[]`, knapsack capacity `cap`.
* **Output:** Maximum profit `profit` and fraction array `x[]` indicating how much of each item is selected.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Items]**
   Read `n` (number of items), `w[i]` (weight of each item), and `v[i]` (value of each item), and `cap` (knapsack capacity).

3. **Step 3: [Initialize & Calculate Ratios]**
   For `i ← 1` to `n`, do:
   * Set `x[i] ← 0`
   * Set `ratio[i] ← v[i] / w[i]`

4. **Step 4: [Sort by Ratio]**
   Sort the items in **descending order** of `ratio[i]` (i.e., value-to-weight ratio).

5. **Step 5: [Initialize Profit]**
   Set `profit ← 0`.

6. **Step 6: [Greedy Selection Loop]**
   For `i ← 1` to `n`, do Steps 7 to 9:

7. **Step 7: [Take Full Item if Possible]**
   If `w[i] ≤ cap`, then:
   * `x[i] ← 1`
   * `profit ← profit + (x[i] × v[i])`
   * `cap ← cap - w[i]`

8. **Step 8: [Take Fraction of Item]**
   Else:
   * `x[i] ← cap / w[i]`
   * `profit ← profit + (x[i] × v[i])`
   * **Break** out of the loop.

9. **Step 9: [End of Loop]**

10. **Step 10: [Output & Stop]**
    Print `x[]` array and `profit`. Stop.

---

## 3. Pseudocode

```text
Algorithm FractionalKnapsack(n, w[], v[], cap)
    Input : n items with weights w[i], values v[i], capacity cap
    Output: Maximum profit and selection fractions x[i]

    // Step 1: Compute ratio and initialize x[]
    for i ← 1 to n do
        x[i] ← 0
        ratio[i] ← v[i] / w[i]
    end for

    // Step 2: Sort items by ratio in descending order
    Sort items by ratio[i] in non-increasing order

    // Step 3: Greedy selection
    profit ← 0
    for i ← 1 to n do
        if w[i] ≤ cap then
            x[i] ← 1
            profit ← profit + (x[i] × v[i])
            cap ← cap - w[i]
        else
            x[i] ← cap / w[i]
            profit ← profit + (x[i] × v[i])
            break
        end if
    end for

    return profit, x[]
end Algorithm
```

---

## 4. Dry Run Example (5 Items)

**Given Items (`n = 5`):**

| Item | Weight `w[i]` | Value `v[i]` | Ratio `v[i]/w[i]` |
|:----:|:-------------:|:------------:|:-----------------:|
| 1    | 20            | 100          | 5.0               |
| 2    | 10            | 60           | 6.0               |
| 3    | 30            | 120          | 4.0               |
| 4    | 50            | 100          | 2.0               |
| 5    | 40            | 120          | 3.0               |

**Knapsack Capacity:** `cap = 50`

**After sorting items by ratio (descending order):**

| Item | `w[i]` | `v[i]` | `ratio` |
|:----:|:------:|:------:|:-------:|
| 1    | 10     | 60     | 6.0     |
| 2    | 20     | 100    | 5.0     |
| 3    | 30     | 120    | 4.0     |
| 4    | 40     | 120    | 3.0     |
| 5    | 50     | 100    | 2.0     |

**Greedy Selection Process:**

| i | `w[i]` | `cap` before | Condition   | `x[i]`      | Profit Added       | `cap` after |
|:--:|:------:|:------------:|:-----------:|:------------:|:------------------:|:-----------:|
| 1  | 10     | 50           | 10 ≤ 50 ✅   | 1.0          | 1.0 × 60 = 60      | 40          |
| 2  | 20     | 40           | 20 ≤ 40 ✅   | 1.0          | 1.0 × 100 = 100    | 20          |
| 3  | 30     | 20           | 30 > 20 ❌   | 20/30 ≈ 0.67 | 0.67 × 120 = 80    | 0 (break)   |
| 4  | 40     | 0            | Not checked | 0.0          | 0                  | 0           |
| 5  | 50     | 0            | Not checked | 0.0          | 0                  | 0           |

**Optimal Profit = 60 + 100 + 80 = `240.00`**

**X array = `[ 1.0, 1.0, 0.7, 0.0, 0.0 ]`**

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case (Ω)** | Ω(n log n) | Dominated by the sorting step (sorting items by ratio). Even in the best case, sorting takes n log n comparisons. |
| **Average Case (Θ)** | Θ(n log n) | On average, sorting takes n log n and the greedy loop runs in O(n). Overall: Θ(n log n). |
| **Worst Case (O)** | O(n log n) | All n items must be considered. Sorting dominates at O(n log n); greedy loop is O(n). |
| **Space Complexity** | O(n) | Extra space is used for arrays x[], ratio[], w[], and v[] of size n. |

> **Note (from Professor's notes):**
> `T(n) = O(n) = O(n log n)`
> The O(n) refers to the greedy selection loop alone; the overall complexity is **O(n log n)** due to sorting.

---

## 6. C Code Reference

Your C code implementation is in [`index.c`](./index.c) / [`knapSack.c`](./knapSack.c).

---

## 7. Sample Program Output (5 Items)

```text
Enter the number of items: 5

-----Item[1]------
Enter the weight of the item: 20
Enter the value of the item: 100

-----Item[2]------
Enter the weight of the item: 10
Enter the value of the item: 60

-----Item[3]------
Enter the weight of the item: 30
Enter the value of the item: 120

-----Item[4]------
Enter the weight of the item: 50
Enter the value of the item: 100

-----Item[5]------
Enter the weight of the item: 40
Enter the value of the item: 120

Enter the capacity of the knapsack: 50

Scenario Before Sorting

Weight:      20     10     30     50     40
Values:     100     60    120    100    120
Ratios:     5.0    6.0    4.0    2.0    3.0


Scenario After Sorting

Weight:      10     20     30     40     50
Values:      60    100    120    120    100
Ratios:     6.0    5.0    4.0    3.0    2.0

Xarray:     1.0    1.0    0.7    0.0    0.0

Optimal Profit: 240.00
```
