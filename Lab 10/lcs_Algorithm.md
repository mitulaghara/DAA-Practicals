# Longest Common Subsequence (LCS) Algorithm & Documentation

This document contains the complete Longest Common Subsequence (LCS) algorithm using Dynamic Programming, pseudocode, step-by-step procedure, dry run trace with DP value and direction tables, complexity analysis, and sample output based on your lab programs [`lcm-with-backtracking.c`](./lcm-with-backtracking.c) and [`LCS.c`](./LCS.c).

---

## 1. Notebook / Whiteboard Algorithm (Exact Professor's Notation)

```text
Practical - 10
Aim :- Develop a Program to implement the Longest Common Subsequence (LCS) Problem using Dynamic Programming and print the subsequence using Backtracking.

LCS_Length(X, Y, m, n)
{
    // Initialize first row and first column
    for i ← 0 to m do
        c[i][0] ← 0

    for j ← 0 to n do
        c[0][j] ← 0

    // Dynamic Programming: Fill tables c (values) and b (directions)
    for i ← 1 to m do
    {
        for j ← 1 to n do
        {
            if (X[i-1] == Y[j-1])
            {
                c[i][j] ← c[i-1][j-1] + 1
                b[i][j] ← 'd'    // diagonal (↖)
            }
            else if (c[i-1][j] > c[i][j-1])
            {
                c[i][j] ← c[i-1][j]
                b[i][j] ← 'u'    // up (↑)
            }
            else
            {
                c[i][j] ← c[i][j-1]
                b[i][j] ← 'l'    // left (←)
            }
        }
    }

    return c[m][n]
}

Print_LCS(b, X, i, j)
{
    if (i == 0 OR j == 0)
        return 0

    if (b[i][j] == 'd')
    {
        Print_LCS(b, X, i-1, j-1)
        Print X[i-1]
    }
    else if (b[i][j] == 'u')
    {
        Print_LCS(b, X, i-1, j)
    }
    else
    {
        Print_LCS(b, X, i, j-1)
    }

    return 0
}

⊙ Time Complexity

T(m, n) = O(m × n)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

### Part A: DP Table Construction

**Algorithm:** `LCS_LENGTH(X, Y, m, n)`

* **Input:** String $X$ of length $m$, String $Y$ of length $n$.
* **Output:** Length of LCS in `c[m][n]`, Value Table `c`, and Direction Table `b`.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Strings and Determine Lengths]**
   Read input strings $X$ and $Y$.
   Compute $m \leftarrow \text{length}(X)$ and $n \leftarrow \text{length}(Y)$.

3. **Step 3: [Initialize Base Cases]**
   * For $i \leftarrow 0$ to $m$, set $c[i][0] \leftarrow 0$.
   * For $j \leftarrow 0$ to $n$, set $c[0][j] \leftarrow 0$.

4. **Step 4: [Fill DP Value & Direction Tables]**
   For $i \leftarrow 1$ to $m$, for $j \leftarrow 1$ to $n$, do:
   * **Case 1 (Character Match):**
     If $X[i-1] == Y[j-1]$:
     * $c[i][j] \leftarrow c[i-1][j-1] + 1$
     * $b[i][j] \leftarrow \text{'d'}$ (diagonal: $\nwarrow$)
   * **Case 2 (Top Cell is Greater):**
     Else if $c[i-1][j] > c[i][j-1]$:
     * $c[i][j] \leftarrow c[i-1][j]$
     * $b[i][j] \leftarrow \text{'u'}$ (up: $\uparrow$)
   * **Case 3 (Left Cell is Greater or Equal):**
     Else:
     * $c[i][j] \leftarrow c[i][j-1]$
     * $b[i][j] \leftarrow \text{'l'}$ (left: $\leftarrow$)

5. **Step 5: [Display Tables]**
   * Display Value Table $c[0..m][0..n]$.
   * Display Direction Table $b[1..m][1..n]$.

6. **Step 6: [Print LCS by Backtracking]**
   Call `PRINT_LCS(m, n)` to reconstruct and print the subsequence characters.

7. **Step 7: [Stop]**
   End of algorithm.

---

### Part B: Backtracking to Print LCS

**Algorithm:** `PRINT_LCS(i, j)`

* **Input:** Indices $i, j$ and direction table $b$.
* **Output:** Common subsequence characters printed in correct sequence.

1. **Step 1:** If $i == 0$ or $j == 0$, return.
2. **Step 2:** If $b[i][j] == \text{'d'}$:
   * Recursively call `PRINT_LCS(i-1, j-1)`.
   * Print character $X[i-1]$.
3. **Step 3:** Else if $b[i][j] == \text{'u'}$:
   * Recursively call `PRINT_LCS(i-1, j)`.
4. **Step 4:** Else ($b[i][j] == \text{'l'}$):
   * Recursively call `PRINT_LCS(i, j-1)`.

---

## 3. Pseudocode

```text
Algorithm LCS_Length(X, Y)
    Input : Strings X[0..m-1] and Y[0..n-1]
    Output: Table c of lengths, table b of directions

    m ← length(X)
    n ← length(Y)

    // Base cases
    for i ← 0 to m do
        c[i][0] ← 0
    end for
    for j ← 0 to n do
        c[0][j] ← 0
    end for

    // Fill table bottom-up
    for i ← 1 to m do
        for j ← 1 to n do
            if X[i-1] == Y[j-1] then
                c[i][j] ← c[i-1][j-1] + 1
                b[i][j] ← 'd'    // Diagonal
            else if c[i-1][j] > c[i][j-1] then
                c[i][j] ← c[i-1][j]
                b[i][j] ← 'u'    // Up
            else
                c[i][j] ← c[i][j-1]
                b[i][j] ← 'l'    // Left
            end if
        end for
    end for

    return c and b
end Algorithm

Algorithm Print_LCS(b, X, i, j)
    if i == 0 or j == 0 then
        return
    end if

    if b[i][j] == 'd' then
        Print_LCS(b, X, i-1, j-1)
        print(X[i-1])
    else if b[i][j] == 'u' then
        Print_LCS(b, X, i-1, j)
    else
        Print_LCS(b, X, i, j-1)
    end if
end Algorithm
```

---

## 4. Dry Run Example

**Input Strings:**
* String 1: $X = \text{"BDCABA"}$ ($m = 6$)
* String 2: $Y = \text{"ABCBDAB"}$ ($n = 7$)

### (a) Value Table `c[i][j]`

| `i \ j` | `0` ($\emptyset$) | `1` (A) | `2` (B) | `3` (C) | `4` (B) | `5` (D) | `6` (A) | `7` (B) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **`0` ($\emptyset$)** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **`1` (B)** | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
| **`2` (D)** | 0 | 0 | 1 | 1 | 1 | 2 | 2 | 2 |
| **`3` (C)** | 0 | 0 | 1 | 2 | 2 | 2 | 2 | 2 |
| **`4` (A)** | 0 | 1 | 1 | 2 | 2 | 2 | 3 | 3 |
| **`5` (B)** | 0 | 1 | 2 | 2 | 3 | 3 | 3 | 4 |
| **`6` (A)** | 0 | 1 | 2 | 2 | 3 | 3 | 4 | **4** |

---

### (b) Direction Table `b[i][j]`

| `i \ j` | `1` (A) | `2` (B) | `3` (C) | `4` (B) | `5` (D) | `6` (A) | `7` (B) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **`1` (B)** | l | **d** ($\nwarrow$) | l | d ($\nwarrow$) | l | l | d ($\nwarrow$) |
| **`2` (D)** | l | u | l | l | **d** ($\nwarrow$) | l | l |
| **`3` (C)** | l | u | **d** ($\nwarrow$) | l | l | l | l |
| **`4` (A)** | d ($\nwarrow$) | l | u | l | l | d ($\nwarrow$) | l |
| **`5` (B)** | u | d ($\nwarrow$) | l | d ($\nwarrow$) | l | l | **d** ($\nwarrow$) |
| **`6` (A)** | d ($\nwarrow$) | u | l | u | l | d ($\nwarrow$) | l |

*(Note: `d` = diagonal $\nwarrow$, `u` = up $\uparrow$, `l` = left $\leftarrow$)*

---

### (c) Backtracking Trace

Starting at `(i = 6, j = 7)`:

1. `b[6][7] == 'l'` $\rightarrow$ Move to `(6, 6)`.
2. `b[6][6] == 'd'` $\rightarrow$ Match found! Save/recurse on $X[5] = \text{'A'}$. Move to `(5, 5)`.
3. `b[5][5] == 'l'` $\rightarrow$ Move to `(5, 4)`.
4. `b[5][4] == 'd'` $\rightarrow$ Match found! Save/recurse on $X[4] = \text{'B'}$. Move to `(4, 3)`.
5. `b[4][3] == 'u'` $\rightarrow$ Move to `(3, 3)`.
6. `b[3][3] == 'd'` $\rightarrow$ Match found! Save/recurse on $X[2] = \text{'C'}$. Move to `(2, 2)`.
7. `b[2][2] == 'u'` $\rightarrow$ Move to `(1, 2)`.
8. `b[1][2] == 'd'` $\rightarrow$ Match found! Save/recurse on $X[0] = \text{'B'}$. Move to `(0, 1)`.
9. `i == 0` $\rightarrow$ Base condition met, recursion unwinds.

Printing characters in ascending sequence of discovery:
$$\text{B} \rightarrow \text{C} \rightarrow \text{B} \rightarrow \text{A} \implies \mathbf{"BCBA"}$$

* **Length of LCS:** $4$
* **Longest Common Subsequence:** **`BCBA`** *(or `BDAB`)*

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(m \times n)$ | Every cell in the $(m+1) \times (n+1)$ table must be computed. |
| **Average Case ($\Theta$)** | $\Theta(m \times n)$ | Requires standard nested loop iterations over lengths $m$ and $n$. |
| **Worst Case ($O$)** | $O(m \times n)$ | Table filling dominates at $O(m \times n)$; backtracking takes $O(m + n)$. |
| **Space Complexity** | $O(m \times n)$ | 2D table `c[m+1][n+1]` and direction table `b[m+1][n+1]` require $O(m \times n)$ space. |

> **Key Takeaways:**
> * **Table Filling Time:** $O(m \times n)$
> * **Backtracking / Printing Time:** $O(m + n)$ (since each step moves either up, left, or diagonally up-left).
> * **Overall Time Complexity:** $O(m \times n)$
> * **Space Complexity:** $O(m \times n)$

---

## 6. C Code Reference

* **Full Implementation with Backtracking:** [`lcm-with-backtracking.c`](./lcm-with-backtracking.c)
* **Basic DP Table Implementation:** [`LCS.c`](./LCS.c)

---

## 7. Sample Program Output

```text
 Enter the string 1: BDCABA

 Enter the string 2: ABCBDAB

 String length for x=6 and y=7

Value Table:
   0   0   0   0   0   0   0   0
   0   0   1   1   1   1   1   1
   0   0   1   1   1   2   2   2
   0   0   1   2   2   2   2   2
   0   1   1   2   2   2   3   3
   0   1   2   2   3   3   3   4
   0   1   2   2   3   3   4   4

Direction Table:
                                
       l   d   l   d   l   l   d
       l   u   l   l   d   l   l
       l   u   d   l   l   l   l
       d   l   u   l   l   d   l
       u   d   l   d   l   l   d
       d   u   l   u   l   d   l

Longest Common Subsequence: BCBA
```
