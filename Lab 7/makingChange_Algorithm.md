# Making Change Algorithm & Documentation

This document contains the exact Making Change algorithm, pseudocode, dry run trace, complexity analysis, and sample output based on your professor's notes and [`makingChange.c`](./makingChange.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
MakingChange(n, d[], a)
{
    // Initialize table c[0..n][0..a] = 0
    for i ← 0 to n do
        for j ← 0 to a do
            c[i][j] ← 0

    // Fill the DP table
    for i ← 1 to n do
    {
        for j ← 1 to a do
        {
            if (i == 1 AND j < d[i])
                c[i][j] ← 0
            else if (i == 1)
                c[i][j] ← 1 + c[i][j - d[i]]
            else if (j < d[i])
                c[i][j] ← c[i-1][j]
            else
                c[i][j] ← min(c[i-1][j], 1 + c[i][j - d[i]])
        }
    }

    return c[n][a]   // Minimum number of coins
}

⊙ Time Complexity

T(n) = O(n × a)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `MAKING_CHANGE(n, d[], a)`

* **Input:** Number of coin denominations `n`, denomination array `d[]`, amount to be paid `a`.
* **Output:** Minimum number of coins `c[n][a]` and the actual coins used.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input]**
   Read `n` (number of coin types), `d[i]` (each denomination), and `a` (amount to pay).

3. **Step 3: [Initialize Table]**
   Set `c[i][j] ← 0` for all `i` from `0` to `n` and `j` from `0` to `a`.

4. **Step 4: [Fill DP Table]**
   For `i ← 1` to `n`, for `j ← 1` to `a`, do Steps 5 to 8:

5. **Step 5: [Case 1 — First Denomination, Amount Less Than Coin]**
   If `i == 1` AND `j < d[i]`:
   * Set `c[i][j] ← 0` (cannot make change).

6. **Step 6: [Case 2 — First Denomination]**
   Else if `i == 1`:
   * Set `c[i][j] ← 1 + c[i][j - d[i]]`.

7. **Step 7: [Case 3 — Amount Less Than Current Coin]**
   Else if `j < d[i]`:
   * Set `c[i][j] ← c[i-1][j]` (skip current coin).

8. **Step 8: [Case 4 — Take Minimum]**
   Else:
   * Set `c[i][j] ← min(c[i-1][j], 1 + c[i][j - d[i]])`.

9. **Step 9: [Backtrack to Find Coins Used]**
   Trace back through the table from `c[n][a]` to find which coins were used.

10. **Step 10: [Output & Stop]**
    Print `c[n][a]` (minimum coins) and the actual coins used. Stop.

---

## 3. Pseudocode

```text
Algorithm MakingChange(n, d[], a)
    Input : n coin denominations d[], amount a
    Output: Minimum number of coins and coins used

    // Step 1: Initialize DP table
    for i ← 0 to n do
        for j ← 0 to a do
            c[i][j] ← 0
    end for

    // Step 2: Fill DP table
    for i ← 1 to n do
        for j ← 1 to a do
            if i == 1 AND j < d[i] then
                c[i][j] ← 0
            else if i == 1 then
                c[i][j] ← 1 + c[i][j - d[i]]
            else if j < d[i] then
                c[i][j] ← c[i-1][j]
            else
                c[i][j] ← min(c[i-1][j], 1 + c[i][j - d[i]])
            end if
        end for
    end for

    // Step 3: Backtrack to find coins used
    i ← n,  j ← a
    while j > 0 do
        if c[i][j] == c[i-1][j] then
            i ← i - 1
        else
            record d[i] as used coin
            j ← j - d[i]
        end if
    end while

    return c[n][a]
end Algorithm
```

---

## 4. Dry Run Example (3 Denominations)

**Given Input:**

* Denominations: `d[] = {1, 3, 4}` (n = 3)
* Amount: `a = 6`

**DP Table `c[i][j]` (rows = denominations, columns = amount 0 to 6):**

|   | j=0 | j=1 | j=2 | j=3 | j=4 | j=5 | j=6 |
|:-:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| i=0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| i=1 (d=1) | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| i=2 (d=3) | 0 | 1 | 2 | 1 | 2 | 3 | 2 |
| i=3 (d=4) | 0 | 1 | 2 | 1 | 1 | 2 | 2 |

**Filling Logic for i=2, d[2]=3:**

| j | Condition       | Formula                              | Value |
|:-:|:---------------:|:------------------------------------:|:-----:|
| 1 | j < d[i] (1<3)  | c[1][1] = 1                          | 1     |
| 2 | j < d[i] (2<3)  | c[1][2] = 2                          | 2     |
| 3 | min(c[1][3], 1+c[2][0]) = min(3,1) | —                   | 1     |
| 4 | min(c[1][4], 1+c[2][1]) = min(4,2) | —                   | 2     |
| 5 | min(c[1][5], 1+c[2][2]) = min(5,3) | —                   | 3     |
| 6 | min(c[1][6], 1+c[2][3]) = min(6,2) | —                   | 2     |

**Optimal no. of coins = `c[3][6]` = 2**

**Coins used = {3, 3}** (two coins of denomination 3)

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case (Ω)** | Ω(n × a) | Every cell of the DP table must be filled, even in the best case. |
| **Average Case (Θ)** | Θ(n × a) | Standard DP table filling: n denominations × a amount. |
| **Worst Case (O)** | O(n × a) | All n × a cells are computed; backtracking adds O(n + a). |
| **Space Complexity** | O(n × a) | DP table `c[n][a]` requires n × a space. |

> **Note:**
> `T(n) = O(n × a)` where `n` = number of denominations and `a` = the target amount.
> This is a **pseudo-polynomial** time algorithm since complexity depends on the value of `a`, not just `n`.

---

## 6. C Code Reference

Your C code implementation is in [`makingChange.c`](./makingChange.c).

---

## 7. Sample Program Output (3 Denominations, Amount = 6)

```text
How many different denomination coins are required: 3

Enter the Denomination Coin[1] : 1
Enter the Denomination Coin[2] : 3
Enter the Denomination Coin[3] : 4

How much amount to be paid: 6

   0   1   2   3   4   5   6
-----------------------------------
   0   0   0   0   0   0   0
   0   1   2   3   4   5   6
   0   1   2   1   2   3   2
   0   1   2   1   1   2   2

Optimal no. of coins : 2

Coins used:    3   3
```
